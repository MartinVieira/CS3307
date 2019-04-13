/**
  *@file doxygen.config
  *@author Martin Vieira
  *@date 28 Nov 2017
  *@brief Contains methods that are used to alter a groups attributes such as id, name, brightness, color and state
  *
  *Uses http get, post, and put requests to change and view the value of a groups id, name, brightness, color and state
  */

#include <stdio.h>
#include <iostream>
#include <string>
#include <array>
#include "LightBulb.h"
#include "bridge.h"
#define ARRAY_MAX 12
using namespace std;

/**
  *@brief Class that creates a GroupOfBulbs object
  *
  *All the methods that can alter a groups id, name, brightness, color and state using http requests to parse the json given by the hueEmulator
  */
class GroupOfBulbs{
	Bridge bridge;
	stringstream ss; /**< Used to change the bulbs id to a string */
	string groupName;
	int groupId;
	int groupBrightness;
	string groupColor;
	bool groupState;
	string red, green, yellow, blue, purple;
	boost::system::error_code err; /**< Error handling */
	
	public:
		GroupOfBulbs();
		GroupOfBulbs(int newId, string newName, int newBrightness, string newColor, bool newState);
		~GroupOfBulbs();
	
		int getGroupId();
		void setGroupId(int newId);
		void getGroupName();
		void setGroupName(string newName);
		void getGroupBrightness();
		void setGroupBrightness(int newBrightness);
		void getGroupColor();
		void setGroupColor(string newColor);
		void getGroupState();
		void setGroupState(bool newState);
		void listBulbs(int groupId);
		/**< Methods to handle http requests and return appropriate responses */
		void handleHttpGroupName(boost::system::error_code err, const Http::Message& response);
		void handleHttpGroupBrightness(boost::system::error_code err, const Http::Message& response);
		void handleHttpGroupColor(boost::system::error_code err, const Http::Message& response);
		void handleHttpGroupState(boost::system::error_code err, const Http::Message& response);	
		void handleHttpGroupString(boost::system::error_code err, const Http::Message& response);
		/**< Methods to handle add, editing and deleting groups */
		void createGroup(LightBulb group[]);
		void editGroup(LightBulb group[]);
		void deleteGroup(int groupId);	
};
