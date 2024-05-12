#pragma once

#include <string>
#include <iostream>

using namespace std;

class User 
{
public:
    string _name;
    string _login;
    string _pass;
    User(const string& name, const string& login, const string& pass) 
    : _name(name), _login(login), _pass(pass) {}

    string getName() const { return _name; }
    string getLogin() const { return _login; }
    string getPassword() const { return _pass; }
};