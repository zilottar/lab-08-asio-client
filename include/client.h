// Copyright 2020 <LinkIvan333>

#ifndef INCLUDE_CLIENT_HPP_
#define INCLUDE_CLIENT_HPP_

#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <memory>
#include <boost/aligned_storage.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/thread.hpp>

const int PORT = 8001;
const unsigned int max_msg = 1024;
const int sleep_time = 7000;
class Client
{
public:
   explicit Client(const std::string & username): socket(service),
        started(true), username_(username) {
     run_client();
   }

private:
    boost::asio::io_service service;
    boost::asio::ip::tcp::socket socket;
    char buff[1024];
    bool started;
    std::string username_;
    void read_answer();
    void process_msg();
    void loop();
    void on_login(const std::string & msg);
    void on_ping(const std::string & msg);
    void on_clients(const std::string & msg);
    void do_ask_clients();
    void write(const std::string & msg);
    void run_client();
    std::string username() const;
    size_t read_complete(const boost::system::error_code & err);
};

#endif // INCLUDE_CLIENT_HPP_
