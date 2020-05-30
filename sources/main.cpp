// Copyright 2020 <>

#include <client.h>

int main() {
    std::string username;
    std::getline(std::cin, username);
    Client client(username);
    return 0;
}
