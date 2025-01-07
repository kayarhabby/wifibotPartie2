#include <unistd.h>
#include <iostream>
#include <cmath>
#include "wifibot.h"


using namespace std;

Wifibot::Wifibot():
	m_order(),
	m_stop(false),
	m_p_thread (NULL),
	m_socket()
{
}

Wifibot::~Wifibot(){
	this->disconnect();
}

void Wifibot::stop(){
	m_order.set_order(0,0);
	cout << "Stop()" << endl;
}

void Wifibot::speed_up(){
	if (m_order.get_order_L()==m_order.get_order_R()) {
		m_order.set_order(m_order.get_order_L()+10,m_order.get_order_R()+10);
	}
	else {
		int moy=m_order.get_order_R()+m_order.get_order_L()/2;
		m_order.set_order(moy+10,moy+10);
	}
	cout << "UP" << endl;
	cout << "Gauche : " << m_order.get_order_L() << "    Droite : " << m_order.get_order_R() << endl;
}

void Wifibot::speed_down(){
	if (m_order.get_order_L()==m_order.get_order_R()) {
		m_order.set_order(m_order.get_order_L()-10,m_order.get_order_R()-10);
	}
	else {
		int moy=m_order.get_order_R()+m_order.get_order_L()/2;
		m_order.set_order(moy-10,moy-10);
	}
	cout << "DOWN" << endl;
	cout << "Gauche : " << m_order.get_order_L() << "    Droite : " << m_order.get_order_R() << endl;
	
}

void Wifibot::turn(int direction){
	cout << "TURN" << endl;
	if (direction==+1) {
		m_order.set_order(m_order.get_order_L()*1.2,m_order.get_order_R()*0.8);
		cout << "Tourne à Droite" << endl;
		cout << "Gauche : " << m_order.get_order_L() << "    Droite : " << m_order.get_order_R() << endl;
	}
	else {
		m_order.set_order(m_order.get_order_L()*0.8,m_order.get_order_R()*1.2);
		cout << "Tourne à Gauche" << endl;
		cout << "Gauche : " << m_order.get_order_L() << "    Droite : " << m_order.get_order_R() << endl;
	}
}

void Wifibot::rotate(int direction){
	cout << "ROTATE" << endl;
	this->stop();
	usleep(1000000);
	if (direction==+1) {
		 m_order.set_order(10,-10);
		 cout << "Rotation à Droite" << endl;
		 cout << "Gauche : " << m_order.get_order_L() << "    Droite : " << m_order.get_order_R() << endl;
	}
	else {
		m_order.set_order(-10,10);
		cout << "Rotation à Gauche" << endl;
		cout << "Gauche : " << m_order.get_order_L() << "    Droite : " << m_order.get_order_R() << endl;
	}
}

void Wifibot::run(){
	static int cpt;
	short crc;
	while (m_stop==false) {
		cout << "Thread [send] : " << ++cpt << endl;
		bool speed_ctr=m_order.get_speed_ctr();
		bool sens_right=((m_order.get_order_R() >=0) ? true :false);
		short speed_right=abs(m_order.get_order_R());
		bool sens_left=((m_order.get_order_L() >=0) ? true :false);
		short speed_left=abs(m_order.get_order_L());

		m_output_buf[0]=0xFF;
		m_output_buf[1]=0x07;
		m_output_buf[2]=speed_left & 0xFF;
		m_output_buf[3]=(speed_left >> 8) & 0xFF;
		m_output_buf[4]=speed_right & 0xFF;
		m_output_buf[5]=(speed_right >> 8) & 0xFF;
		m_output_buf[6]=(char)(128*speed_ctr+64*sens_left+32*speed_ctr+16*sens_right+8);

		trame_crc[0]=(unsigned char) m_output_buf[1];
		trame_crc[1]=(unsigned char) m_output_buf[2];
		trame_crc[2]=(unsigned char) m_output_buf[3];
		trame_crc[3]=(unsigned char) m_output_buf[4];
		trame_crc[4]=(unsigned char) m_output_buf[5];
		trame_crc[5]=(unsigned char) m_output_buf[6];

		crc=crc16(trame_crc,6);
		m_output_buf[7] = crc & 0xFF;
		m_output_buf[8] = (crc >> 8) & 0xFF;
	
		m_socket.send(m_output_buf,9);
	
		this_thread::sleep_for(std::chrono::milliseconds(LOOP_TIME));
	}
	cout << "Thread [send] : stop !" << endl << endl;
}	

void Wifibot::connect(string ip){
	m_socket.open(ip,PORT);
	cout << "Wifibot connect()" << endl;
	if (m_socket.is_open()) m_p_thread=new thread([this]() { this->run(); });
}

void Wifibot::disconnect(){
	m_stop=true;
	delete m_p_thread;
	m_p_thread = NULL;
	m_socket.close();

}


 short Wifibot::crc16(unsigned char* trame, int longueur){
	unsigned int Crc = 0xFFFF;
	unsigned int Polynome = 0xA001;
	unsigned int CptOctet = 0;
	unsigned int CptBit = 0;
	unsigned int Parity= 0;

	for ( CptOctet= 0 ; CptOctet < longueur ; CptOctet++)
	{
		Crc ^= *( trame + CptOctet);

		for ( CptBit = 0; CptBit <= 7 ; CptBit++)
		{
			Parity= Crc;
			Crc >>= 1;
			if (Parity%2 == true) Crc ^= Polynome;
		}
	}
	return(Crc);
	
}