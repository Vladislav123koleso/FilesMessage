#pragma once

#include <string>
#include <iostream>

using namespace std;

class Message 
{
public:
    string _text;
    string _sender;
    string _receiver;
    Message(const string& text, const string& sender, const string& receiver)
        : _text(text), _sender(sender), _receiver(receiver) {}

    string getText() const { return _text; }
    string getSender() const { return _sender; }
    string getReceiver() const { return _receiver; }
};