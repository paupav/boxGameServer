#include <iostream>
#include <SFML/Network.hpp>

#include "Cliff.hpp"
#include "Client.hpp"
void Cliff::run()
{

    unsigned short serverPort = 5400;//sf::Socket::AnyPort;
    int i = 0;

    socket.bind(serverPort);


    sf::IpAddress recipient = sf::IpAddress::getLocalAddress();
    std::cout << "Server adress: " << sf::IpAddress::getLocalAddress() << ":" << serverPort << std::endl;//
    std::cout << "You should give that adress to your friend!" << std::endl;
    newClient = false;
    while(i == 0)
    {
        sf::Vector2f pos;
        float rotation;
        if(socket.receive(packet, ip, port) == sf::Socket::Done)
        {
            cPacket = packet;
            if(cPacket >> pos.x >> pos.y >> rotation)
            {
                updatePositions(packet, ip, port);
                sendPositions();
            }
            else
                addPlayer();

        }


    }

}

void Cliff::addPlayer()
{
    Client client;
    client.ip = ip;
    client.port = port;
    int i = clients.size() - 1;


    clients.push_back(client);
    std::cout << "New client joined. Client number: " << clients.size() - 1 << std::endl;
    sendID(clients.size() - 1, clients.back().ip, clients.back().port);

}

//check if works
void Cliff::updatePositions(sf::Packet packet, sf::IpAddress ip, unsigned short port)
{
    sf::Vector2f pos;
    int playerID;
    packet >> playerID;
    sf::Packet cPacket;
    cPacket = packet; //fix delete later
    //std::cout << "Player ID: " << playerID << std::endl;
    packet >> clients.at(playerID).pos.x >> clients.at(playerID).pos.y >> clients.at(playerID).rotation;
    std::cout << "Player : " << playerID << " Pos:" <<clients.at(playerID).pos.x << ", " <<  clients.at(playerID).pos.y << "Rotation: " << clients.at(playerID).rotation << std::endl;
}

void Cliff::sendPositions()
{
    int i = clients.size() - 1;
    while(i >= 0)
    {
        int j = clients.size() - 1;
        while(j >= 0)
        {
            sf::Packet senderPacket, cPacket; //fix delete later cPacket
            //std::cout << "About: " << j << " To: " << i << std::endl;
            int clientsSize = clients.size()-1;
            senderPacket << clientsSize << i << clients.at(i).pos.x << clients.at(i).pos.y << clients.at(i).rotation;
            cPacket = senderPacket;
            socket.send(senderPacket, clients.at(j).ip, clients.at(j).port);
            //cPacket >> clientsSize >> i >> clients.at(i).pos.x >> clients.at(i).pos.y >> clients.at(i).rotation;
            //std::cout << "Client size: " << clientsSize << " Client: " << i << " Pos: " << clients.at(i).pos.x << ", " << clients.at(i).pos.y << std::endl;
            j--;
        }
        i--;
    }
}

void Cliff::sendID(int ID, sf::IpAddress ip, unsigned short port)
{
    sf::Packet packet;
    int clientSize = clients.size()-1;
    packet << ID << clientSize;
    socket.send(packet, ip, port);
}
