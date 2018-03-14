#pragma once
#include "GLHeaders.h"
#include <iostream>
#include "ThreadQueue.h"
#include <thread>
#include <map>
#include <string>
#include <memory>
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 9999
#define DEFAULT_CHANNEL 1

struct Message
{
	std::string key;
	std::map<std::string, std::string> data;
};

class NetworkingManager
{
private:
	int m_handshakeListenerID;
	bool m_inLobby = false; //closeall will set both of these to false
	bool m_gameStarted = false;
	bool m_isHost = false;
	static NetworkingManager* s_instance;
	ThreadQueue<std::string> *m_messageQueue;
	std::thread m_receiverThread;
	std::thread m_udpReceiverThread;
	std::vector<Message> m_messagesToSend;
	char *IP = DEFAULT_IP;
	int m_port = DEFAULT_PORT;


	UDPpacket *m_udpPacket;
	UDPpacket m_udpReceivedPacket;
	UDPsocket m_udpSocket = NULL;
	UDPsocket m_udpClient = NULL;
	TCPsocket m_socket = NULL;
	bool accept();
	bool host();
	bool join();
	void pollMessages(int id);
	void pollMessagesThread(int id);
	void pollMessagesUDP();
	void pollMessagesThreadUDP();
	std::string serializeMessage(Message message);
	std::map<std::string, void*> deserializeMessage(std::string message);
	void sendEventToReceiver(std::map<std::string, void*> data);
	void sendAcceptPacket (int id);

public:
	int m_assignedID = -1;
	std::map<int, std::pair<Uint32, TCPsocket>> m_clients;
	void listenForStart();
	void stopListeningForStart();
	void sendStartPacket();
	void listenforAcceptPacket ();
	void stopListeningForAcceptPacket ();
	bool closeClientAsHost (int id);
	bool closeClient ();
	bool closeUDP();
	NetworkingManager();
	static NetworkingManager* getInstance();
	IPaddress getIP();
	bool startGame();
	bool startGameClient();
	bool createHost();
	bool createClient();
	void send(int id, std::string *msg);
	bool createUDPPacket(int packetSize);
	void sendUDP(std::string *msg);
	bool getMessage(std::string &msg);
	void prepareMessageForSending(std::string key, std::map<std::string, std::string> data);
	void sendQueuedEvents();
	void handleParsingEvents(std::string packet);
	bool isConnected();
	bool isSelf (int id);
	bool isHost();
	bool inLobby () {
		return m_inLobby;
	}
	bool inGame () {
		return m_gameStarted;
	}
	void setIP(char *ip, int port = DEFAULT_PORT);
	int addPlayer(Uint32 ip, TCPsocket sock);
	int removePlayer(int ip);
};