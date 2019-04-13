/**
  *@file doxygen_c.h
  *@author Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This class represents schedule header file which include some function of 
  *setting and getting basic information of schedule
  */
#include <iostream>
#include <string>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Value>
#include "bridge.h"

using namespace std;
using namespace Wt;

class Schedule{
    public:
          Bridge bridge;
          string color;
          void setScheduleName(string scheName);
          void setScheduleTime(string scheTime);
          void setDescription(string newDescription);
          void setAddress(string addr);
          void setState(string newState);
          void setScheduleID(int newID);
          void setBrightness(int newBrightness);
          void setTransitionTime(int newTransitionTime);
          string getScheduleName();
          string getScheduleTime();
          string getDescription();
          string getAddress();
          string getState();
          int getScheduleID();
          int getBrightness();
          int getTransitionTime();
          static string generateHttpMessage(Schedule scheduleobj);
          Schedule();
          Schedule(Bridge bridgeobj,string scheName,string scheTime,string newDescription,string choice,string id,string newState,string newColor,int newBrightness,int newTransitionTime);
          ~Schedule();
    private:
          string scheduleName;
	  string scheduleTime;
          string description;
          string address;
          string state;
          int scheduleID;
          int brightness;
          int transitionTime;
};
