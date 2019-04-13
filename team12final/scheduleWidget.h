/**
  *@file doxygen_c.h
  *@author Weizhi Chen, Hejia Tang and Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This is the header file of the schedule widget
  *
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
#include <Wt/WTextArea>
#include <Wt/WCalendar>
#include <Wt/WDate>
#include <Wt/WTemplate>
#include <Wt/WTimeEdit>
#include <Wt/WTime>
#include <Wt/WApplication>
#include "schedule.h"
using namespace Wt;
using namespace std;

class scheduleWidget: public WContainerWidget
{
 public:
     scheduleWidget(WContainerWidget *parent=0); 
     void display();
     void showUpdate();
     void showAdd();
     void showDel();
    void showDetail();
    void addition();
    void addSchedule(Bridge bridgeobj,string newScheName,string newScheTime,string newDescription,string choice,string id,string newState,string newColor,int newBrightness,int newTransitionTime);/**<this is the method of adding schedule and send request to api*/
    bool removeSchedule(string scheName);/**<this is the method of removing schedule and send request to api*/
    void updateSchedule(Schedule oldSchedule, Schedule newSchedule);/**<this is the method of editing schedule and send request to api*/
    void handleHttpResponse(boost::system::error_code err, const Http::Message& response);/**the method that handle delete and edit*/
    string handlePostHttpResponse(boost::system::error_code err, const Http::Message& response);/**the method that handle add*/

  private:

   WSlider *br;
   WToolBar *toolBar;	
 	 WComboBox *cb;
 	 WButtonGroup *bg;
 	 WRadioButton *on;
 	 WRadioButton *off;
   WTreeTable *treeTable;
   WContainerWidget *view;
 	 WComboBox *scheList;
 	 WTable *mod;
 	 WStackedWidget *details;
 	 WRadioButton *lig;
 	 WRadioButton *gro;
 	 WCalendar *calendar;
 	 WTimeEdit *te;
    
   Wt::WLineEdit *IDs;
   Wt::WLineEdit *scheName;
   Wt::WTextArea *descript;
   string sbrightvalue;

};
