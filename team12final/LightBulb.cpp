/**
  *@file doxygen_c.h
  *@author Martin Vieira
  *@date 28 Nov 2017
  *@brief Contains methods that are used to alter a bulb's attributes such as id, name, brightness, color and state
  *
  *Uses http get, post, and put requests to change the value of a bulb's id, name, brightness, color and state
  */

#include <Wt/WApplication>
#include <iostream>
#include <string>
#include <sstream>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Value>
#include "LightBulb.h"
using namespace std;
using namespace Wt;


/**
  *@brief Basic constructor for a LightBulb object
  *
  *This contructor initializes a new LightBulb object with no parameters and returns an empty LightBulb object
  *@param none
  *@return empty LightBulb object
  */
LightBulb::LightBulb(){
}

/**
  *@brief Basic constructor for a LightBulb object
  *
  *This contructor initializes a new LightBulb object with id, name, color, brightness and state parameters and returns a LightBulb object
  *@param newId This is an integer given to a bulb to identify it
  *@param newName This is a string name given to a bulb
  *@param newBrightness This is an integer value used to set the brightness of a bulb
  *@param newColor This is a string used to set the color of a bulb
  *@param newState This is a boolean value to set the bulb true=on or false=off
  *@return LightBulb object
  */
LightBulb::LightBulb(int newId, string newName, int newBrightness, string newColor, bool newState){
	id = newId;
	bulbName= newName;
	brightness= newBrightness;
	color= newColor;
	state= newState;
}

/**
  *@brief Basic deconstructor for a LightBulb object
  *
  *The purpose of the deconstructor is to free the resources that the object may have acquired
  *@param none
  *@return empty LightBulb object
  */
LightBulb::~LightBulb() {
}

/**
  *@brief Getter method to get the id of a bulb
  *
  *Returns the integer value of the bulb's id
  *@param none
  *@return id This is an integer given to a bulb to identify it
  */
int LightBulb::getId()
{
	return id;
}

/**
  *@brief setter method to get the id of a bulb
  *
  *Sets the integer value of the bulb's id
  *@param newId This is an integer given to a bulb to identify it
  *@return none
  */
void LightBulb::setId(int newId)
{
	id = newId;
}

/**
  *@brief the method copy the table from front end
  *   and output the WTable when calls the function
  *
  *@param WTable from front end
  *@return none
  */
void LightBulb::setTable(WTable *table){
  t = table;
}


/**
  *@brief Getter method to get the name of a bulb
  *
  *Returns the string name of a bulb using a http get request to parse through the json and return a bulb's name
  *@param none
  *@return none
  */
 void LightBulb::getBulbName()
 {	
 	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

  const Http::Message response; /**< Used for the response given by the http request */
  client->done().connect(boost::bind(&LightBulb::handleHttpName,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpName" */
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  if (client->get(Bridge::generateURL(bridge)+"/lights/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
  {
    WApplication::instance()->deferRendering();
  }
 }

/**
  *@brief Setter method to get the name of a bulb
  *
  *Sets the string name of a bulb using a http put request to replace the existing bulb's name or place a new one
  *@param newName This is a string name given to a bulb
  *@return none
  */
void LightBulb::setBulbName(string newName)
{
	bulbName = newName; /**< Updates bulb name */

  Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

  const Http::Message response; /**< Used for the response given by the http request */
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  string url(Bridge::generateURL(bridge)+"/lights/"+ss.str());/**< Url that leads to a lights attributes */
  Http::Message msg; /**< Initializes a http message */
  ss<<bulbName;
  msg.addBodyText("{\"name\":\""+ss.str()+"\"}"); /**< Body text used to change a bulbs name */
  client->put(url,msg); /**< Sends the message text to the url to update the bulbs name */
}

/**
  *@brief Getter method to get the name of a bulb
  *
  *Returns the string name of a bulb using a http get request to parse through the json and return a bulb's name
  *@param none
  *@return none
  */
void LightBulb::getBrightness()
{
 	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

  const Http::Message response; /**< Used for the response given by the http request */
  client->done().connect(boost::bind(&LightBulb::handleHttpBrightness,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpBrightness" */
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  if (client->get(Bridge::generateURL(bridge)+"/lights/"+ss.str()+"/state")) /**< If the url is valid defers rendering to method for handling http requests */
  {
    WApplication::instance()->deferRendering();
  }
 }

/**
  *@brief Setter method to set the brightness of a bulb
  *
  *Sets the integer value brightness using a http put request to replace the existing bulb's brightness or place a new one
  *@param newBrightness This is an integer value used to set the brightness of a bulb
  *@return none
  */
void LightBulb::setBrightness(int newBrightness)
{
	brightness = newBrightness; /**< Updates bulb brightness */

  Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  string url(Bridge::generateURL(bridge)+"/lights/"+ss.str()+"/state"); /**< Url that leads to a lights attributes */
  Http::Message msg; /**< Initializes a http message */
  ss<<brightness;
  msg.addBodyText("{\"bri\":"+ss.str()+"}"); /**< Body text used to change a bulbs name */
  client->put(url,msg); /**< Sends the message text to the url to update the bulbs brightness */
}

/**
  *@brief Getter method to get the color of a bulb
  *
  *Updates ui with a bulb's color using a http get request to parse through the json and get the color
  *@param none
  *@return none
  */
void LightBulb::getColor()
 {
	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

  const Http::Message response; /**< Used for the response given by the http request */
  client->done().connect(boost::bind(&LightBulb::handleHttpColor,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpColor" */
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  if (client->get(Bridge::generateURL(bridge)+"/lights/"+ss.str()+"/state")) /**< If the url is valid defers rendering to method for handling http requests */
  {
    WApplication::instance()->deferRendering();
  }
 }

/**
  *@brief Setter method to set the color of a bulb
  *
  *Sets the string color using a http put request to replace the existing bulb's color or place a new one
  *@param newColor This is a string used to set the color of a bulb
  *@return none
  */
void LightBulb::setColor(string newColor)
{
	color = newColor; /**< Updates bulb color */

  Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */
 
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  string url(Bridge::generateURL(bridge)+"/lights/"+ss.str()+"/state"); /**< Url that leads to a lights attributes */
  Http::Message msg; /**< Initializes a http message */
  if (color==red)
  {
  msg.addBodyText("{\"hue\":0}"); /**< Body text used to change a bulbs color */
  }
  else if (color==yellow)
  {
  msg.addBodyText("{\"hue\":12750}"); /**< Body text used to change a bulbs color */
  }
  else if (color==green)
  {
  msg.addBodyText("{\"hue\":25500}"); /**< Body text used to change a bulbs color */
  }
  else if (color==blue)
  {
  msg.addBodyText("{\"hue\":46920}"); /**< Body text used to change a bulbs color */
  }
  else if (color==purple)
  {
  msg.addBodyText("{\"hue\":56100}"); /**< Body text used to change a bulbs color */
  }
  client->put(url,msg); /**< Sends the message text to the url to update the bulbs color */
}

/**
  *@brief Getter method to get the state of a bulb
  *
  *Updates ui with a bulb's state using a http get request to parse through the json and get the state
  *@param none
  *@return none
  */
void LightBulb::getState()
 {
 	Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */

  const Http::Message response; /**< Used for the response given by the http request */
  client->done().connect(boost::bind(&LightBulb::handleHttpState,this,_1,_2)); /**< Sends the response data to the http handler "handleHttpState" */
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  if (client->get(Bridge::generateURL(bridge)+"/lights/"+ss.str())) /**< If the url is valid defers rendering to method for handling http requests */
  {
    WApplication::instance()->deferRendering();
  }
 }

/**
  *@brief Setter method to set the state of a bulb
  *
  *Sets the boolean value state using a http put request to replace the existing bulb's state or place a new one
  *@param newState This is a boolean value to set the bulb true=on or false=off
  *@return none
  */
void LightBulb::setState(bool newState)
{
	state = newState; /**< Updates bulb state */

  Http::Client *client = new Http::Client(); /**< Creates and initializes a http client *client */
  
  ss<<getId(); /**< Used to change the int value of a bulbs id to string for the url */
  string url(Bridge::generateURL(bridge)+"/lights/"+ss.str()); /**< Url that leads to a lights attributes */
  Http::Message msg; /**< Initializes a http message */
  ss<<state;
  msg.addBodyText("{\"on\":"+ss.str()+"}"); /**< Body text used to change a bulbs state */
  client->put(url,msg); /**< Sends the message text to the url to update the bulbs state */
}

/**
  *@brief Handles http request to get a bulb's name
  *
  *Updates ui with a bulb's name using a http get request to parse through the json and get the name
  *@param none
  *@return none
  */
void LightBulb::handleHttpName(boost::system::error_code err, const Http::Message& response)
{
   WApplication::instance()->resumeRendering();
   Json::Object result;
   WString n;
	 string bName;
   int i;
   if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the name */
      Json::parse(response.body(),result); 
      n = result.get("name");
	    bName=n.toUTF8(); 
      text = new WText((WString("<font color='white'>{1}</font>").arg(bName)));
      t->elementAt(i+1, 1)->addWidget(text);
      i++;
   }

 }

/**
  *@brief Handles http request to get a bulb's brightness
  *
  *Updates ui with a bulb's brightness using a http get request to parse through the json and get the brightness
  *@param none
  *@return none
  */
 void LightBulb::handleHttpBrightness(boost::system::error_code err, const Http::Message& response){
   WApplication::instance()->resumeRendering();
   Json::Object store;
   Json::Object result;
   int b;
   int i = 0;
   if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the brightness */
      Json::parse(response.body(),result); 
      store = result.get("state");
      b = store.get("bri");
      text = new WText((WString("<font color='white'>{1}</font>").arg(b)));
      t->elementAt(i+1, 2)->addWidget(text);
      i++;
   }
 }

/**
  *@brief Handles http request to get a bulb's color
  *
  *Updates ui with a bulb's color using a http get request to parse through the json and get the color
  *@param none
  *@return none
  */
 void LightBulb::handleHttpColor(boost::system::error_code err, const Http::Message& response){
   WApplication::instance()->resumeRendering();
   Json::Object store;
   Json::Object result;
   int c;
   int i = 0;
   if(!err && response.status() == 200){ /**< If it is the correct response then it parses the data and stores the color */
      Json::parse(response.body(),result); 
      store=result.get("state");
      c=store.get("hue");
 	if (0<=c<12750)
 	{
 	color=red;
 	}
 	else if (12750<=c<25500)
 	{
 	color=yellow;
 	}
 	else if (25500<=c<46920)
 	{
 	color=green;
 	}
 	else if (46920<=c<56100)
 	{
 	color=blue;
 	}
 	else if (56100<=c)
 	{
 	color=purple;
 	}
      
      text = new WText((WString("<font color='white'>{1}</font>").arg(color)));
      t->elementAt(i+1, 3)->addWidget(text);
      i++;
   }
 }

/**
  *@brief Handles http request to get a bulb's state
  *
  *Updates ui with a bulb's state using a http get request to parse through the json and get the state
  *@param none
  *@return none
  */
 void LightBulb::handleHttpState(boost::system::error_code err, const Http::Message& response){
   WApplication::instance()->resumeRendering();
   Json::Object store;
   Json::Object result;
   bool s;
   int i = 0;
   if(!err && response.status() == 200){/**< If it is the correct response then it parses the data and stores the state */
      Json::parse(response.body(),result);
      store=result.get("state");
      s=store.get("on");
      text = new WText((WString("<font color='white'>{1}</font>").arg(s)));
      t->elementAt(i+1, 4)->addWidget(text);
      i++;
   }
 }
