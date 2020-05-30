// Copyright 2020 <LinkIvan333>

#include <include/client.h>

void Client::run_client()
{
  boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), PORT);
  try
  {
    socket.connect(ep);
    loop();
  }
  catch(boost::system::system_error & err)
  {
    std::cout << "client terminated " << std::endl;
  }
}

void Client::loop() {
    write("login " + username() + "\n");
    read_answer();
    while (started)
    {
        std::string msg;
        std::getline(std::cin, msg);
        write(msg+"\n");
        read_answer();
        std::srand(std::time(0));
        boost::this_thread::sleep
        (boost::posix_time::millisec(std::rand() % sleep_time));
    }
}

std::string Client::username() const {
  return username_;
}

void Client::read_answer() {
    for (unsigned i = 0; i < max_msg; ++i)
        buff[i] = ' ';
    read(socket, boost::asio::buffer(buff),
         boost::bind(&Client::read_complete, this, _1));
    process_msg();
}

void Client::process_msg()
{
    std::string msg = "";
    for (unsigned i = 0; i < max_msg; ++i) {
        if (buff[i] == '\n') {
            msg += buff[i];
            break;
        }
        msg += buff[i];
    }
    if ( msg.find("login ") == 0) on_login(msg);
    else if ( msg.find("ping") == 0 || msg.find("ping") == 1) on_ping(msg);
    else if ( msg.find("clients ") == 0 ||
             msg.find("clients ") == 1) on_clients(msg);
    else
        std::cerr << msg;
}

void Client::on_ping(const std::string & msg)
{
    std::cout << msg;
    if (msg.find("ping client_list_changed") == 1 ||
        msg.find("ping client_list_changed") == 0)
        do_ask_clients();
}

void Client::on_login(const std::string & msg) {
  std::cout << msg;
}

void Client::on_clients(const std::string & msg)
{
    std::string clients = msg.substr(8);
    std::cout << username() << ", new client list:"
              << clients;
}

void Client::do_ask_clients()
{
    write("list\n");
    read_answer();
}

void Client::write(const std::string & msg) {
    socket.write_some(boost::asio::buffer(msg));
}

size_t Client::read_complete(
    const boost::system::error_code & err) {
    if (err) return 0;
    unsigned enter = 0;
    for (unsigned i = 0; i < max_msg; i++) {
        if (buff[i] == '\n') enter = i;
    }
    bool found = false;
    if (enter != 0) found = true;
    return found ? 0 : 1;
}



