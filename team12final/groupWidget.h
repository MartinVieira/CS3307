/**
  *@file doxygen_c.h
  *@author Martin Vieira & Hejia Tang & Weizhi Chen
  *@date 28 Nov 2017
  *@brief Contains methods that show the group page and add, edit, delete methods send the data to API
  * 
  *Uses Wt widget to display all the groups and control panel   
  *Uses http get, post, and put requests to change the value of a group of bulbs's id, name, brightness, color and state
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
#include <Wt/WStackedWidget>
#include <Wt/WString>
#include <Wt/WToolBar>
#include <Wt/WIconPair>
#include <Wt/WTree>
#include <Wt/WTreeTable>
#include <Wt/WTreeTableNode>
#include <Wt/WComboBox>
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>
#include <Wt/WApplication>
#include "GroupOfBulbs.h"

using namespace Wt;

/**
  *@brief Class that creates the group page
  *
  *All the methods that display the page the user will see
  */
class groupWidget: public WContainerWidget
{
 public:
     groupWidget(WContainerWidget *parent=0); 
     void display();
     void select();
     void control();
     void add();
     void deletee();


  private:

  WContainerWidget *controlPanel;
  WSlider *br;
  WToolBar *toolBar;	
 	WComboBox *cb;
  WComboBox *delett;
 	WButtonGroup *bg;
 	WRadioButton *on;
 	WRadioButton *off;
  WTable *a;
  WLineEdit *gNames;
  //store all group names
  string groups[100];
};