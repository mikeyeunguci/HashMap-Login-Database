#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <sstream>
#include "HashMap.hpp"


class Commands
{
public:
    Commands();
    void InputProcessor();
private:
    HashMap h;

    bool debug;

    void Create(HashMap& h, const std::string& user, const std::string& pwd);

    void Login(HashMap& h, const std::string& user, const std::string& pwd);

    void Remove(HashMap& h, const std::string& user);

    void Debug(const std::string on_off);

};
#endif