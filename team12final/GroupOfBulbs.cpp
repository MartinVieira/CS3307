/**
  *@file doxygen.config
  *@author Martin Vieira
  *@date 28 Nov 2017
  *@brief Contains methods that are used to alter a group of bulbs attributes such as id, name, brightness, color and state
  *
  *Uses http get, post, and put requests to change and view the value of a group of bulbs id, name, brightness, color and state
  */

#include <Wt/WApplication>
#include <iostream>
#include <string>
#include <sstream>
#include "GroupOfBulbs.h"
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Value>
using namespace std;
using namespace Wt;

/**
  *@brief Basic constructor for a GroupOfBulbs object
  *
  *This contructor initializes a new GroupOfBulbs object with no parameters and returns an empty LightBulb object
  *@param none
  *@return empty GroupOfBulbs object
  */
GroupOfBulbs::GroupOfBulbs(){
	groupId=0;
	groupName="";
	groupBrightness=0;
	groupColor="";
	groupState=0;
}

/**
  *@brief Basic constructor for a GroupOfBulbs object
  *
  *This contructor initializes a new GroupOfBulbs object with id, name, color, brightness and state parameters and returns a GroupOfBulbs object
  *@param newId This is an integer given to a group to identify it
  *@param newName This is a string name given to a group
  *@param newBrightness This is an integer value used to set the brightness of a group
  *@param newColor This is a string used to set the color of a group
  *@param newState This is a boolean value to set the group of bulbs true=on or false=off
  *@return GroupOfBulbs object
  */
GroupOfBulbs::GroupOfBulbs(int newId, string newName, int newBrightness, string newColor, bool newState){
	groupId=newId; /**< Constructor adds an id to a GroupOfBulbs object */
	groupName=newName; /**< Constructor adds a name to a GroupOfBulbs object */
	groupBrightness= newBrightness; /**< Constructor adds a brightness to a GroupOfBulbs object */
	groupColor= newColor; /**< Constructor adds a color to a GroupOfBulbs object */
	groupState= newState; /**< Constructor adds a state to a GroupOfBulbs object */
}

/**
  *@brief Basic deconstructor for a LightBulb object
  *
  *The purpose of the deconstructor is to free the resources that the object may have acquired
  *@param none
  *@return empty LightBulb object
  */
GroupOfBulbs::~GroupOfBulbs(){
}

/**
  *@brief Getter method to get the id of a group
  *
  *Returns the integer value of the groups id
  *@param none
  *@return id This is an integer given to a group to identify it
  */
int GroupOfBulbs::getGroupId()
{
	return groupId; /**< Returns integer value groupId */
}

/**
  *@brief Setter method to set the id of a bulb
  *
  *Sets the integer value of the bulb's id
  *@param newId This is an integer given to a bulb to identify it
  *@return none
  */
void GroupOfBulbs::setGroupId(int newId)
{
	groupId = newId; /**< Replaces the integer value groupId with newId */
}

/**
  *@brief Getter method to get the name of a group
  *
  *Updates ui with a groups name using a http get request to parse through the json and get the name
  *@param none
  *@return none
  */
void GroupOfBulbs::getGroupName()
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	const Http::Message response; /**< Used for the response given by the http request */
	client->done().connect(boost::bind(&GroupOfBulbs::handleHttpGroupName,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpName" */
	ss<<getGroupId(); /**< Used to change the int value of a groups id to string for the url */
	if (client->get(Bridge::generateURL(bridge)+"/groups/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
	{
		WApplication::instance()->deferRendering();
	}
}

/**
  *@brief Setter method to set the name of a bulb
  *
  *Sets the string name of a bulb using a http put request to replace the existing bulb's name or place a new one
  *@param newName This is a string name given to a bulb
  *@return none
  */
void GroupOfBulbs::setGroupName(string newName)
{
	groupName = newName; /**< Updates group name */

	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	const Http::Message response; /**< Used for the response given by the http request */
	ss<<getGroupId(); /**< Used to change the int value of a groups id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str()); /**< Url that leads to a groups attributes */
	Http::Message msg; /**< Initializes a http message */
	msg.addBodyText("{\"name\":\""+groupName+"\"}"); /**< Body text used to change a groups name */
	client->put(url,msg); /**< Sends the message text to the url to update the groups name */
}

/**
  *@brief Getter method to get the brightness of a group
  *
  *Updates ui with a groups brightness using a http get request to parse through the json and get the brightness
  *@param none
  *@return none
  */
void GroupOfBulbs::getGroupBrightness()
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	const Http::Message response; /**< Used for the response given by the http request */
	client->done().connect(boost::bind(&GroupOfBulbs::handleHttpGroupBrightness,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpBrightness" */
	ss<<getGroupId(); /**< Used to change the int value of a bulbs id to string for the url */
	if (client->get(Bridge::generateURL(bridge)+"/groups/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
	{
		WApplication::instance()->deferRendering();
	}
}

/**
  *@brief Setter method to set the brightness of a group
  *
  *Sets the integer value brightness using a http put request to replace the existing groups brightness or place a new one
  *@param newBrightness This is an integer value used to set the brightness of a group
  *@return none
  */
void GroupOfBulbs::setGroupBrightness(int newBrightness)
{
	groupBrightness = newBrightness; /**< Updates group brightness */

	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	ss<<getGroupId(); /**< Used to change the int value of a bulbs id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str()+"/action"); /**< Url that leads to a lights attributes */
	Http::Message msg; /**< Initializes a http message */
	ss<<groupBrightness;
	msg.addBodyText("{\"bri\":"+ss.str()+"}"); /**< Body text used to change a groups brightness */
	client->put(url,msg); /**< Sends the message text to the url to update the groups brightness */
}

/**
  *@brief Getter method to get the color of a group
  *
  *Updates ui with a groups color using a http get request to parse through the json and get the color
  *@param none
  *@return none
  */
void GroupOfBulbs::getGroupColor()
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	const Http::Message response; /**< Used for the response given by the http request */
	client->done().connect(boost::bind(&GroupOfBulbs::handleHttpGroupColor,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpColor" */
	ss<<getGroupId(); /**< Used to change the int value of a bulbs id to string for the url */
	if (client->get(Bridge::generateURL(bridge)+"/groups/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
	{
		WApplication::instance()->deferRendering();
	}
}

/**
  *@brief Setter method to set the color of a group
  *
  *Sets the string color using a http put request to replace the existing groups color or place a new one
  *@param newColor This is a string used to set the color of a group
  *@return none
  */
void GroupOfBulbs::setGroupColor(string newColor)
{
	groupColor = newColor; /**< Updates group color */

	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */
 
	ss<<getGroupId(); /**< Used to change the int value of a bulbs id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str()+"/action"); /**< Url that leads to a lights attributes */
	Http::Message msg; /**< Initializes a http message */
	if (groupColor==red)
	{
	msg.addBodyText("{\"hue\":0}"); /**< Body text used to change a groups color */
	}
	else if (groupColor==yellow)
	{
	msg.addBodyText("{\"hue\":12750}"); /**< Body text used to change a groups color */
	}
	else if (groupColor==green)
	{
	msg.addBodyText("{\"hue\":25500}"); /**< Body text used to change a groups color */
	}
	else if (groupColor==blue)
	{
	msg.addBodyText("{\"hue\":46920}"); /**< Body text used to change a groups color */
	}
	else if (groupColor==purple)
	{
	msg.addBodyText("{\"hue\":56100}"); /**< Body text used to change a groups color */
	}
	client->put(url,msg); /**< Sends the message text to the url to update the groups color */
}

/**
  *@brief Getter method to get the state of a group
  *
  *Updates ui with a groups state using a http get request to parse through the json and get the state
  *@param none
  *@return none
  */
void GroupOfBulbs::getGroupState()
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	const Http::Message response; /**< Used for the response given by the http request */
	client->done().connect(boost::bind(&GroupOfBulbs::handleHttpGroupState,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpState" */
	ss<<getGroupId(); /**< Used to change the int value of a bulbs id to string for the url */
	if (client->get(Bridge::generateURL(bridge)+"/groups/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
	{
		WApplication::instance()->deferRendering();
	}
}

/**
  *@brief Setter method to set the state of a group
  *
  *Sets the boolean value state using a http put request to replace the existing groups state or place a new one
  *@param newState This is a boolean value to set the group true=on or false=off
  *@return none
  */
void GroupOfBulbs::setGroupState(bool newState)
{
	groupState = newState; /**< Updates bulb state */

	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */
	
	ss<<getGroupId(); /**< Used to change the int value of a bulbs id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str()+"/action"); /**< Url that leads to a lights attributes */
	Http::Message msg; /**< Initializes a http message */
	ss<<groupState;
	msg.addBodyText("{\"on\":"+ss.str()+"}"); /**< Body text used to change a groups state */
	client->put(url,msg); /**< Sends the message text to the url to update the groups state */
}

/**
  *@brief Handles http request to get a groups name
  *
  *Updates ui with a groups name using a http get request to parse through the json and get the name
  *@param none
  *@return none
  */
void GroupOfBulbs::handleHttpGroupName(boost::system::error_code err, const Http::Message& response){
  WApplication::instance()->resumeRendering();
  Json::Object result;
  WString n;
  string gName;
  if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the name */
     Json::parse(response.body(),result); 
     n = result.get("name");
     gName = n.toUTF8();
  }
}

/**
  *@brief Handles http request to get a groups brightness
  *
  *Updates ui with a groups brightness using a http get request to parse through the json and get the brightness
  *@param none
  *@return none
  */
void GroupOfBulbs::handleHttpGroupBrightness(boost::system::error_code err, const Http::Message& response){
  WApplication::instance()->resumeRendering();
  Json::Object store;
  Json::Object result;
  int b;
  if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the brightness */
     Json::parse(response.body(),result); 
     store = result.get("action");
     b = store.get("bri");
  }
}

/**
  *@brief Handles http request to get a groups color
  *
  *Updates ui with a bulb's color using a http get request to parse through the json and get the color
  *@param none
  *@return none
  */
void GroupOfBulbs::handleHttpGroupColor(boost::system::error_code err, const Http::Message& response){
  WApplication::instance()->resumeRendering();
  Json::Object store;
  Json::Object result;
  int c;
  if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the color */
     Json::parse(response.body(),result); 
     store=result.get("action");
     c=store.get("hue");
	if (0<=c<12750)
	{
	groupColor=red;
	}
	else if (12750<=c<25500)
	{
	groupColor=yellow;
	}
	else if (25500<=c<46920)
	{
	groupColor=green;
	}
	else if (46920<=c<56100)
	{
	groupColor=blue;
	}
	else if (56100<=c)
	{
	groupColor=purple;
	}
  }
}

/**
  *@brief Handles http request to get a groups state
  *
  *Updates ui with a groups state using a http get request to parse through the json and get the state
  *@param none
  *@return none
  */
void GroupOfBulbs::handleHttpGroupState(boost::system::error_code err, const Http::Message& response){
  WApplication::instance()->resumeRendering();
  Json::Object store;
  Json::Object result;
  bool s;
  if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the state */
     Json::parse(response.body(),result);
     store=result.get("action");
     s=store.get("on");
  }
}

/**
  *@brief Handles http request to get all information regarding a group
  *
  *Updates ui with a groups information using a http get request to parse through the json
  *@param none
  *@return none
  */
void GroupOfBulbs::handleHttpGroupString(boost::system::error_code err, const Http::Message& response){
  WApplication::instance()->resumeRendering();
 
  if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data */
     string out = response.body();
  }
}

/**
  *@brief Method for creating a group of LightBulb objects
  *
  *Takes in a LightBulb array and get the bulbs id to put into a group message body
  *@param group This is an array of LightBulb objects used for input into a group object
  *@return none
  */
void GroupOfBulbs::createGroup(LightBulb group[])
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	ss<<groupId; /**< Used to change the int value of a groups id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str());/**< Url that leads to a groups attributes */
	Http::Message msg; /**< Initializes a http message */

	string lightArray[sizeof(group)/sizeof(group[0])]; /**< Used for storing the light bulbs ids */
	for (int i=0;i<sizeof(group)/sizeof(group[0]);i++) /**< Adds each light bulb id to the json object */
	{
	ss<<group[i].getId();
	lightArray[i]="\""+ss.str()+"\", ";
	}
	ss<<lightArray;
	msg.addBodyText("{\"lights\": ["+ss.str()+"]}");
	client->post(url,msg); /**< Creates the group of bulbs */
}

/**
  *@brief Method for editing a group of LightBulb objects
  *
  *Takes in a LightBulb array and get the bulbs id to put into a group message body
  *@param group This is an array of LightBulb objects used for input into a group object
  *@return none
  */
void GroupOfBulbs::editGroup(LightBulb group[])
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	ss<<groupId; /**< Used to change the int value of a groups id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str());/**< Url that leads to a groups attributes */
	Http::Message msg; /**< Initializes a http message */

	string lightArray[sizeof(group)/sizeof(group[0])]; /**< Used for storing the light bulbs ids */
	for (int i=0;i<sizeof(group)/sizeof(group[0]);i++) /**< Adds each light bulb id to the json object */
	{
	ss<<group[i].getId();
	lightArray[i]="\""+ss.str()+"\", ";
	}
	ss<<lightArray;
	msg.addBodyText("{\"lights\": ["+ss.str()+"]}");
	client->put(url,msg); /**< Replaces the group with the new bulbs */
}

/**
  *@brief Method for deleting a group of LightBulb objects
  *
  *Takes in a groupId and deletes it
  *@param groupId This is an integer used to identify a group
  *@return none
  */
void GroupOfBulbs::deleteGroup(int groupId)
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */
	
	ss<<groupId; /**< Used to change the int value of a groups id to string for the url */
	string url(Bridge::generateURL(bridge)+"/groups/"+ss.str()); /**< Url that leads to a group */
	Http::Message msg; /**< Initializes a http message */
	msg.addBodyText("");
	client->deleteRequest(url,msg); /**< Deletes the group */
}

/**
  *@brief Method for listing all information regarding a group
  *
  *Takes in a groupId and gets all information on a group of bulbs
  *@param groupId This is an integer used to identify a group
  *@return none
  */
void GroupOfBulbs::listBulbs(int groupId)
{
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

	client->done().connect(boost::bind(&GroupOfBulbs::handleHttpGroupString,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpString" */
	ss<<getGroupId(); /**< Used to change the int value of a groups id to string for the url */
	if (client->get(Bridge::generateURL(bridge)+"/groups/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
	{
		WApplication::instance()->deferRendering();
	}
}
