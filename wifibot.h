#pragma once
#include <thread>
#include "order.h"
#include "socket.h"

#define LOOP_TIME 200
#define PORT 15020

class Wifibot {
private:
	Order m_order;
	std::thread* m_p_thread;
	bool m_stop;
	Socket_TCP m_socket;
	char m_output_buf[9];
	unsigned char trame_crc[6];
	

public:
	Wifibot();
	~Wifibot();
	void stop();
	void speed_up();
	void speed_down();
	void turn(int direction);
	void rotate(int direction);
	void connect(std::string ip);
	void disconnect();
	


private:	
	void run();
	short crc16(unsigned char*,int);

};