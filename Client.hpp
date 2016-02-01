#pragma once
#include <SFML/Network.hpp>

class Client
{
public:
    sf::IpAddress ip;
    unsigned short port;
    sf::Packet packet;
    sf::Vector2f pos;
    float rotation;

};
