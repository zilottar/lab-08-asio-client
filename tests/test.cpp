// Copyright 2020 <>

#include <client.h>
#include <gtest/gtest.h>


int main() {
    std::string username;
    std::getline(std::cin, username);
    Client client(username);
    return 0;
}


TEST(talk_to_srv, Test1) {
  EXPECT_TRUE(true);
}

