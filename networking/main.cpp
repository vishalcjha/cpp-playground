#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/functional/hash.hpp>
#include <functional>
#include <string>
#include <iomanip>
#include <climits>
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <asio/server.h>
#include <asio/connection.h>

using namespace boost::asio;
using namespace std;
int main(){
	Server<Connection> server(1);
	server.startServer(9999);
	cout << "Started Server @9999 \n";
	while(1);
	cout << "This can not be coming here\n";
}
