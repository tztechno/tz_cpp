#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

class session : public std::enable_shared_from_this<session> {
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;

public:
    explicit session(tcp::socket socket)
        : socket_(std::move(socket)) {}

    void run() {
        auto self = shared_from_this();
        http::async_read(socket_, buffer_, req_,
            [self](beast::error_code ec, std::size_t bytes_transferred) {
                self->on_read(ec, bytes_transferred);
            });
    }

    void on_read(beast::error_code ec, std::size_t) {
        if (ec == http::error::end_of_stream)
            return do_close();
        if (ec)
            return fail(ec, "read");

        // Prepare the response
        auto const response = [&]() {
            http::response<http::string_body> res{ http::status::ok, req_.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/plain");
            res.keep_alive(req_.keep_alive());
            res.body() = "Hello, Beast!";
            res.prepare_payload();
            return res;
        }();

        auto self = shared_from_this();
        http::async_write(socket_, response,
            [self, response](beast::error_code ec, std::size_t) {
                self->on_write(ec, response.need_eof());
            });
    }

    void on_write(beast::error_code ec, bool close) {
        if (ec)
            return fail(ec, "write");
        if (close) {
            return do_close();
        }
        buffer_.consume(buffer_.size());
        run();
    }

    void do_close() {
        beast::error_code ec;
        socket_.shutdown(tcp::socket::shutdown_send, ec);
    }
};

void do_listen(net::io_context& ioc, tcp::endpoint endpoint) {
    auto acceptor = std::make_shared<tcp::acceptor>(ioc);
    acceptor->open(endpoint.protocol());
    acceptor->set_option(net::socket_base::reuse_address(true));
    acceptor->bind(endpoint);
    acceptor->listen(net::socket_base::max_listen_connections);

    std::function<void()> do_accept;
    do_accept = [&] {
        acceptor->async_accept(
            [&ioc, &do_accept](beast::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<session>(std::move(socket))->run();
                }
                do_accept();
            });
    };

    do_accept();
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: http-server-async <address> <port>\n";
            std::cerr << "Example:\n";
            std::cerr << "    http-server-async 0.0.0.0 8080\n";
            return EXIT_FAILURE;
        }
        auto const address = net::ip::make_address(argv[1]);
        auto const port = static_cast<unsigned short>(std::atoi(argv[2]));

        net::io_context ioc{1};
        do_listen(ioc, tcp::endpoint{address, port});
        ioc.run();
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
