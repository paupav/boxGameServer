#pragma once
#include "SFML/Network.hpp"

#include "Client.hpp"
class Cliff
{
public:
    void run();

private:
    void addPlayer();
    void updatePositions(sf::Packet packet, sf::IpAddress ip, unsigned short port);
    void sendPositions();
    void sendID(int ID, sf::IpAddress ip, unsigned short port);
    bool newClient;
    sf::UdpSocket socket;
    sf::Packet packet, cPacket;
    sf::IpAddress ip;
    unsigned short port;
    int ID;
    sf::Time time;
    sf::Clock clock;
    std::vector<Client> clients;
};
