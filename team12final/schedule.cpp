/**
  *@file doxygen_c.h
  *@author Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This class represents schedule class which used to set and get information of schedule
  *
  */
#include "schedule.h"

using namespace std;

/**
  @brief the empty constructor
  */
Schedule::Schedule(){

}

/**
  @brief the constructor,get the schedule name,schedule time,schedule description,
  *choices of lights or groups,id of lights or groups,state for "on",color,brightness and 
  *transition time
  */
Schedule::Schedule(Bridge bridgeobj,string scheName, string scheTime,string newDescription,string choice,string id,string newState,string newColor,int newBrightness,int newTransitionTime){
  scheduleName = scheName;
  scheduleTime = scheTime;
  description = newDescription;
  state = newState;
  bridge = bridgeobj;
  color = newColor;
  brightness = newBrightness;
  transitionTime = newTransitionTime;
  //light.setColor(newColor);
  if(choice == "groups")
    {
      address = "/api/"+bridgeobj.getUsername()+"/groups/"+id+"/action";
    }
  else
    {
      address = "/api/"+bridgeobj.getUsername()+"/lights/"+id+"/action";
    } 
}

/**
  @brief destructor
  */
Schedule::~Schedule(){
}

/**
  @brief schedule name setter method
  @param scheName
  @return none
  */
void Schedule::setScheduleName(string scheName){
    scheduleName = scheName; 
}

/**
  @brief schedule time setter method
  @param scheTime
  @return none
  */
void Schedule::setScheduleTime(string scheTime){
    scheduleTime = scheTime;
}

/**
  @brief schedule description setter method
  @param newDescription
  @return none 
  */
void Schedule::setDescription(string newDescription){
    description = newDescription;
}

/**
  @brief "on" state setter method
  @param newState
  @return none
  */
void Schedule::setState(string newState){
    state = newState;
}

/**
  @brief the action address setter method
  @param addr
  @return none
  */
void Schedule::setAddress(string addr){
    address = addr;
}

/**
  @brief the scheduleID(return by api)setter method
  @param newID
  @return none
  */
void Schedule::setScheduleID(int newID)
{
    scheduleID = newID;
}

/**
  @brief the brightness setter method
  @param newBrightness
  @return none
  */
void Schedule::setBrightness(int newBrightness){
    brightness = newBrightness;
}

/**
  @brief the transition time setter method
  @param newTransitionTime
  @return none
  */
void Schedule::setTransitionTime(int newTransitionTime){
    transitionTime = newTransitionTime;
}

/**
  @brief schedule name get method
  @param none
  @return string
  */
string Schedule::getScheduleName(){
    return scheduleName;
}

/**
  @brief schedule time getter method
  @param none
  @return string
  */
string Schedule::getScheduleTime(){
    return scheduleTime;
}

/**
  @brief schedule description getter method
  @param none
  @return string
  */
string Schedule::getDescription(){
    return description; 
}

/**
  @brief action address getter method
  @param none
  @return string
  */
string Schedule::getAddress(){
    return address;
}

/**
  @brief "on" state getter method
  @param none
  @return string
  */
string Schedule::getState(){
    return state;
}

/**
  @brief scheduleID(return by api) getter method
  @param none
  @return int
  */
int Schedule::getScheduleID(){
    return scheduleID; 
} 

/**
  @brief brightness setter method
  @param none
  @return int
  */
int Schedule::getBrightness(){
    return brightness;
}

/**
  @brief schedule transition time getter method
  @param none
  @return int
  */
int Schedule::getTransitionTime(){
    return transitionTime;
}

/**
  @brief this is the helper method for generating http message body
  @param scheduleobj
  @return string
  * 
  */
string Schedule::generateHttpMessage(Schedule scheduleobj){
   stringstream ss,tt;
   ss << scheduleobj.getBrightness();
   string bri = ss.str();
   tt << scheduleobj.getTransitionTime();
   string transition = tt.str();
   Json::Object out;
   string s1 = "\"";
   string s2 = ":";
   string s3 = ",";
   string s4 = "}";
   string a = "{";
   string b = s1+"name"+s1+s2;
   string c = s1+scheduleobj.getScheduleName()+s1+s3;
   string d = s1+"description"+s1+s2;
   string e = s1+scheduleobj.getDescription()+s1+s3;
   string f = s1+"command"+s1+s2+a;
   string g = s1+"address"+s1+s2+s1+scheduleobj.getAddress()+s1+s3;
   string h = s1+"method"+s1+s2+s1+"PUT"+s1+s3;
   string i = s1+"body"+s1+s2+a;
   string j = s1+"on"+s1+s2+scheduleobj.getState()+s3;
   string k= s1+"bri"+s1+s2+bri+s3;
   string l = s1+"xy"+s1+s2+scheduleobj.color+s3;
   string m = s1+"transitiontime"+s1+s2+transition+s4+s4+s3;
   string n = s1+"time"+s1+s2+s1+scheduleobj.getScheduleTime()+s1+s4;
   string sum = a+b+c+d+e+f+g+h+i+j+k+l+m+n;
   Json::parse(sum,out);
   string text = Json::serialize(out);
   ss.str("");
   tt.str("");
   return text;
}
