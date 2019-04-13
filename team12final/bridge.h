/**
  *@file doxygen_c.h
  *@author Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This is the header file of the bridge
  */
#ifndef bridge_H
#define bridge_H




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
#include <Wt/WIOService>

using namespace std;
using namespace Wt;

/**
  *@brief this class has some getter and setting method, a help method to generate url of bridge
  */
class Bridge{
    public:
      void setBridgeName(string newBridgeName);
      void setLocation(string newLocation);
      void setHost(string newHost);
      void setPortNumber(int newPortNumber);
      void setUsername(string newUsername);
      string getBridgeName();
      string getLocation();
      string getHost();
      int getPortNumber();
      string getUsername();
      static string generateURL(Bridge brgobj);
      static bool deleteBridge(string bridgenm);
      Bridge();
      Bridge(std::string newBridgeName,std::string newLocation,std::string newHost,int newPort,std::string newUsername);
      ~Bridge();
    private:
      std::string bridgeName;
      std::string location;
      std::string host;
      int portNumber;
      std::string username;//the user name optionally specify by user
};
#endif
