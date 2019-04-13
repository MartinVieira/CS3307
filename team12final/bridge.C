/**
  *@file doxygen_c.h
  *@author Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This class represents bridge class and used for connecting hue API
  */
#include "bridge.h"
#include <cstddef>


Bridge bridges[100];/**<the array that used for storing bridge object*/
int bridgeNum;/**<the current number of bridge object */
ostringstream convert;
string port;

//constructor
Bridge::Bridge()
{
    bridgeName="";
    location="";
    host="";
    int portNumber=0;
    username=""; 
}

/**
  @brief basic constructor of the bridge object
  *
  *This constructor initializes a new bridge object with bridgename,location,host,port,newUsername
  */
Bridge::Bridge(std::string newBridgeName,std::string newLocation,std::string newHost,int newPort,std::string newUsername){
    bridgeName = newBridgeName;
    location = newLocation;
    host = newHost;
    portNumber = newPort;
    if(newUsername=="")
       username = "newdeveloper";
    else
       username = newUsername;
}

/*
Bridge::Bridge(string newBridgeName,string newLocation,string newHost,int newPort,string newUsername){
    bridgeName = newBridgeName;
    location = newLocation;
    host = newHost;
    portNumber = newPort;
    username = newUsername;
}
*/

/**
  @brief destructor  
  */
//destructor
Bridge::~Bridge(){

}

/**
  @brief bridge name setter method 
  */
void Bridge::setBridgeName(string newBridgeName){
   bridgeName = newBridgeName; 
}

/**
  @brief location setter method  
  */
void Bridge::setLocation(string newLocation){
   location = newLocation;
}

/**
  @brief host setter method
  */
void Bridge::setHost(string newHost){
   host = newHost;
}

/**
  @brief port number setter method  
  */
void Bridge::setPortNumber(int newPortNumber){
   portNumber = newPortNumber;
}

/**
  @brief username setter method  
  */
void Bridge::setUsername(string newUsername){
   username = newUsername;
}

/**
  @brief bridge name getter method  
  */
string Bridge::getBridgeName(){
   return bridgeName;
}

/**
  @brief location getter method  
  */
string Bridge::getLocation(){
   return location;
}

/**
  @brief host getter method  
  */
string Bridge::getHost(){
   return host;
}

/**
  @brief port number method  
  */
int Bridge::getPortNumber(){
   return portNumber;
}

/**
  @brief username getter method  
  */
string Bridge::getUsername(){
   return username;
}

/**
  @brief the method to generate the url of bridge
*/
string Bridge::generateURL(Bridge brgobj){
   string url;
   string a = "http://";
   string b ="/api/";
   convert << brgobj.getPortNumber();
   port = convert.str();
   if(brgobj.getUsername()=="newdeveloper")
    {
      url = a+brgobj.getHost()+":"+port+b+"newdeveloper";//"http://localhost:port/api/newdeveloper" 
    }
   else
    {
      url = a+brgobj.getHost()+":"+port+b+brgobj.getUsername();//"http://localhost:port/api/username"
    }
  convert.str("");
  return url;
}

/**
  @brief the method for removing bridge  
  */
bool Bridge::deleteBridge(string bridgenm){
  const int notfound = -1;
  int search = notfound;
  if(bridgeNum == 0){
     return false;
  }
  for(int i=0;i<bridgeNum && search==notfound;i++){
     if(bridges[i].getBridgeName()==bridgenm)
     {
       search = i;
     }
  } 
  if(search==-1)
  {
    return false;
  }
  bridges[search]=bridges[bridgeNum+1];
  bridgeNum--;

  return true; 
}
