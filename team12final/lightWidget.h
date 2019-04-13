/**
  *@file doxygen_c.h
  *@author Martin Vieira & Hejia Tang & Ryan Chen
  *@date 28 Nov 2017
  *@brief Contains methods that show the group page and add, edit, delete methods send the data to API
  * 
  *Uses Wt widget to display all the groups and control panel   
  *Uses http get, post, and put requests to change the value of a bulb's id, name, brightness, color and state
  */

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WMenuItem>
#include <Wt/WSlider>
#include <Wt/WBreak>
#include <Wt/WTabWidget>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WPopupMenu>
#include <Wt/WPushButton>
#include <Wt/WCheckBox>
#include <Wt/WStackedWidget>
#include <Wt/WComboBox>
#include <Wt/WApplication>
#include "LightBulb.h"
#include "bridge.h"
using namespace Wt;

/**
  *@brief Class that creates the light page
  *
  *All the methods that show the user what they can do in this page
  */
class lightWidget: public WContainerWidget
{
 public:
 	//all the pages
     lightWidget(WContainerWidget *parent=0); 
     void display();
     void add();
     void edit();
     void delet();
     void save();
     void addition();
     WTable *v;
 
 private:

 	WTable *a;
 	//attributs
 	WSlider *br;
 	WComboBox *colo;	
 	WComboBox *delett;

 	WComboBox *switcH;
 	WComboBox *bridgeList;
 	WComboBox *lightList;
 	LightBulb lightBulb[100];
 	string lights[100];

 	//get user input
 	WLineEdit *lightName;
    WLineEdit *lightBright;
    WLineEdit *lightColor;
    WLineEdit *lightState;

	
};
