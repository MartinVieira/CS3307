/**
  *@file doxygen_c.h
  *@author Martin Vieira
  *@date 28 Nov 2017
  *@brief Contains methods that are used to alter a bulb's attributes such as id, name, brightness, color and state
  *
  *Uses http get, post, and put requests to change the value of a bulb's id, name, brightness, color and state
  */

#ifndef lightbulb_H_
#define lightbulb_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <Wt/WText>
#include <Wt/WTable>
#include "bridge.h"

using namespace std;
using namespace Wt;

/**
  *@brief Class that creates a LightBulb object
  *
  *All the methods that can alter a light bulb id, name, brightness, color and state using http requests to parse the json given by the hueEmulator
  */
class LightBulb{

	 Bridge bridge;
	 stringstream ss;
	 int id;
	 string bulbName;
	 int brightness;
	 string color;
	 bool state;
	 string red, green, yellow, blue, purple;
	 boost::system::error_code err;
	 WTable *t;
	
	public:
		LightBulb();
		~LightBulb();
		LightBulb(int newId,string newName,int newBrightness,string newColor,bool newState);
		
		int getId();
		void setId(int newId);
		void setTable(WTable *table);

		void getBulbName();
		void setBulbName(string newName);
		void getBrightness();
		void setBrightness(int newBrightness);
		void getColor();
		void setColor(string newColor);
		void getState();
		void setState(bool newState);
		void handleHttpName(boost::system::error_code err, const Http::Message& response);
		void handleHttpBrightness(boost::system::error_code err, const Http::Message& response);
		void handleHttpColor(boost::system::error_code err, const Http::Message& response);
		void handleHttpState(boost::system::error_code err, const Http::Message& response);	
		void handleHttpString(boost::system::error_code err, const Http::Message& response);

		WText *text;
		
};
#endif