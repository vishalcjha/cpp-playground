/*
 * server.h
 *
 *  Created on: Dec 1, 2016
 *      Author: vikumar
 */

#ifndef ASIO_SERVER_H_
#define ASIO_SERVER_H_
#include <boost/asio.hpp>
#include <vector>
#include <thread>

template<typename ConnectionHandler>
class Server {
public:
	Server(int threadCount) : mAcceptor(mService), mThreadCount(threadCount){}
	void startServer(uint16_t port);
private :
	void handleNewConnection(std::shared_ptr<ConnectionHandler> handler,
			const boost::system::error_code& ec);
	boost::asio::io_service mService;
	boost::asio::ip::tcp::acceptor mAcceptor;
	int mThreadCount;
	std::vector<std::thread> mThreadPool;
};


template<typename ConnectionHandler>
void Server<ConnectionHandler>::startServer(uint16_t port){
	auto handler = std::make_shared<ConnectionHandler>(mService);
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
	mAcceptor.open(ep.protocol());
	mAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	mAcceptor.bind(ep);
	mAcceptor.listen();
	mAcceptor.async_accept(handler->socket(), [=](const boost::system::error_code& ec){
		handleNewConnection(handler, ec);
	});

	for(auto i = 0; i < mThreadCount; i++){
		mThreadPool.push_back(std::thread([=]{mService.run();}));
	}
}

template<typename ConnectionHandler>
void Server<ConnectionHandler>::handleNewConnection(std::shared_ptr<ConnectionHandler> handler,
		const boost::system::error_code& er){
	handler->start();

	auto newHandler = std::make_shared<ConnectionHandler>(mService);
	mAcceptor.async_accept(newHandler->socket(), [=](const boost::system::error_code& ec){
		handleNewConnection(newHandler, ec);
	});
}

#endif /* ASIO_SERVER_H_ */
