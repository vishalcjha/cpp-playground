/*
 * connection.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: vikumar
 */

#include "connection.h"
#include <boost/asio/unyield.hpp>
#include <boost/asio/yield.hpp>
#include <iostream>
#include <iterator>

void Connection::start(){
	readPacket(boost::system::error_code(), 0, shared_from_this());
}


void Connection::readPacket(const boost::system::error_code& ec,
		size_t read,
		std::shared_ptr<Connection> self){
	reenter(this) {
		yield boost::asio::async_read_until(mSocket, mStream, "\r\n\r\n",
				[&,self](const boost::system::error_code& ec, size_t read){
					self->readPacket(ec, read, self);
			}
		);
		std::cout << std::string(std::istreambuf_iterator<char>(&mStream),
		std::istreambuf_iterator<char>()) << "\n";
		boost::asio::write(mSocket, boost::asio::buffer("HTTP/1.1 200 OK\r\n\r\n\r\n"));
		mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
		mSocket.close();
	}
}
