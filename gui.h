#pragma once
#include "wifibot.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/table.h>
#include <gtkmm/label.h>
#include <iostream>




class Gui : public Gtk::Window 
{
private:
	Wifibot m_robot;
	Gtk::Button m_bouton_1;
	Gtk::Button m_bouton_up;
	Gtk::Button m_bouton_down;
	Gtk::Button m_bouton_stop;
	Gtk::Button m_bouton_left;
	Gtk::Button m_bouton_right;
	Gtk::Button m_bouton_rot_l;
	Gtk::Button m_bouton_rot_r;
	Gtk::Entry m_entree_1;
	Gtk::Label titre;
	Gtk::Label fin;
	

public:
	Gui();
	~Gui();


};