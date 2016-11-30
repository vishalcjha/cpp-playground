/*
 * connection.h
 *
 *  Created on: Dec 1, 2016
 *      Author: vikumar
 */

#ifndef ASIO_CONNECTION_H_
#define ASIO_CONNECTION_H_
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/asio.hpp>
#include <boost/asio/coroutine.hpp>
#include <iostream>

class Connection : public boost::asio::coroutine ,
					public std::enable_shared_from_this<Connection> {
private:
	boost::asio::io_service& mService;
	boost::asio::ip::tcp::socket mSocket;
	boost::asio::streambuf mStream;
public:
	boost::asio::ip::tcp::socket& socket(){
		return mSocket;
	}
	void start();
	// self is needed to move forward the state after yield.
	void readPacket(const boost::system::error_code& ec,
			std::size_t read,
			std::shared_ptr<Connection> self);
	Connection(boost::asio::io_service& service) : mService(service), mSocket(service){
	}

};

#endif /* ASIO_CONNECTION_H_ */
