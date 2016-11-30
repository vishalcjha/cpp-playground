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

class printer{
    public:
    printer(boost::asio::io_service& io) : m_timer(io, boost::posix_time::seconds(1)), m_count(0){
        m_timer.async_wait(async_func);
    }
    void print(const boost::system::error_code&){
        if(m_count > 5){
            return;
        }
        cout << ++m_count << endl;
        m_timer.expires_at(m_timer.expires_at() + boost::posix_time::seconds(1));
        m_timer.async_wait(async_func);
    }
    ~printer(){
        cout << "Final Call To Printer \n";
    }
    private:
    boost::asio::deadline_timer m_timer;
    int m_count;
    function<void(const boost::system::error_code& ec)> async_func = [this](const boost::system::error_code& ec){print(ec);};
};

boost::asio::io_service ioService;
boost::asio::ip::tcp::acceptor accp(ioService);
void onAccept(const boost::system::error_code& ec, shared_ptr<boost::asio::ip::tcp::socket> soc){
    using boost::asio::ip::tcp;
    soc->set_option(boost::asio::ip::tcp::no_delay(true));
    auto buf = new boost::asio::streambuf;
    boost::asio::async_read_until(*soc, *buf, "\r\n\r\n",
    [=](const boost::system::error_code& ec, std::size_t) {
        delete buf;
        boost::asio::async_write(*soc, boost::asio::buffer("HTTP/1.1 200 OK\r\n\r\n\r\n"), [=](const boost::system::error_code& ec, std::size_t){
        soc->shutdown(boost::asio::ip::tcp::socket::shutdown_send);
        soc->close();
        });
    });
    soc.reset(new tcp::socket(ioService));
    accp.async_accept(*soc, [=](const boost::system::error_code& ec){
        onAccept(ec, soc);
    });
}
/*int main( int argc, char * argv[] )
{
    using boost::asio::ip::tcp;
    boost::asio::ip::tcp::resolver resolver(ioService );
    try{
    boost::asio::ip::tcp::resolver::query query(
        "127.0.0.1",
        boost::lexical_cast< std::string >( 9999 )
    );
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
    accp.open( endpoint.protocol() );
    accp.set_option( boost::asio::ip::tcp::acceptor::reuse_address( true ) );
    accp.bind( endpoint );
    cout << "Ready to accept @ 9999" << endl;
    auto t1 = boost::thread([&](){
            ioService.run();
        });
    accp.listen( boost::asio::socket_base::max_connections );
    std::shared_ptr<tcp::socket> soc = make_shared<tcp::socket>(ioService);
    accp.async_accept(*soc, [=](const boost::system::error_code& ec){
        onAccept(ec, soc);
    });
   t1.join();
    }catch(std::exception & ex){
        std::cout << "[" << boost::this_thread::get_id()
			<< "] Exception: " << ex.what() << std::endl;
    }
}*/
