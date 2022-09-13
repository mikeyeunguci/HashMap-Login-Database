#include "Commands.hpp"


Commands::Commands()
    :debug{false}
{
}


void Commands::Create(HashMap& h, const std::string& user, const std::string& pwd)
{
    if (h.contains(user))
    {
        std::cout << "EXISTS" << std::endl;
        return;
    }
    else
    {
        h.add(user, pwd);
        std::cout << "CREATED" << std::endl;
        return;
    }
}


void Commands::Login(HashMap& h, const std::string& user, const std::string& pwd)
{
    if (h.contains(user) && h.value(user) == pwd)
    {
        std::cout << "SUCCEEDED" << std::endl;
    }
    else 
    {
        std::cout << "FAILED" << std::endl;
    }
}


void Commands::Remove(HashMap& h, const std::string& user)
{
    if (h.remove(user) == true)
    {
        std::cout << "REMOVED" << std::endl;
    }
    else 
    {
        std::cout << "NONEXISTENT" << std::endl;
    }
}


void Commands::Debug(const std::string on_off)
{
    if (on_off == "ON")
    {
        if (debug == false)
        {
            std::cout << "ON NOW" << std::endl;
            debug = true;
        }
        else
        {
            std::cout << "ON ALREADY" << std::endl;
        }
    }
    if (on_off == "OFF")
    {
        if (debug == true)
        {
            std::cout << "OFF NOW" << std::endl;
            debug = false;
        }
        else
        {
            std::cout << "OFF ALREADY" << std::endl;
        }
    }
}

namespace
{
void ParseInputs(std::string& command, std::string& user, std::string& pwd)
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream parse_input(line);
    parse_input >> command >> user >> pwd;
}
}

void Commands::InputProcessor()
{
    while (true)
    {
        std::string command = "";
        std::string user = "";
        std::string pwd = "";
        ParseInputs(command, user, pwd);
        if (command == "CREATE" && user != "" && pwd != "")
        {
            Create(h, user, pwd);
        }
        else if (command == "LOGIN" && user != "" && pwd != "")
        {
            Login(h, user, pwd);
        }
        else if (command == "REMOVE" && user != "" && pwd == "")
        {
            Remove(h, user);
        }
        else if (command == "CLEAR" && user == "" && pwd == "")
        {
            h.clear();
            std::cout << "CLEARED" << std::endl;
        }
        else if (command == "QUIT")
        {
            std::cout << "GOODBYE" << std::endl;
            break;
        }
        else if (command == "DEBUG" && user == "ON" && pwd == "")
        {
            Debug(user);
        }
        else if (command == "DEBUG" && user == "OFF" && pwd == "")
        {
            Debug(user);
        }
        else if (debug == true)
        {
            if (command == "LOGIN" && user == "COUNT" && pwd == "")
            {
                std::cout << h.size() << std::endl;
            }
            else if (command == "BUCKET" && user == "COUNT" && pwd == "")
            {
                std::cout << h.bucketCount() << std::endl;
            }
            else if (command == "LOAD" && user == "FACTOR" && pwd == "")
            {
                std::cout << h.loadFactor() << std::endl;
            }
            else if (command == "MAX" && user == "BUCKET" && pwd == "SIZE")
            {
                std::cout << h.maxBucketSize() << std::endl;
            }
            else 
            {
                std::cout << "INVALID" << std::endl;
            }
        }
        else
        {
            std::cout << "INVALID" << std::endl;
        }
    }
}

