/**
  *@file doxygen_c.h
  *@author Weizhi Chen, Hejia Tang and Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This is the header file of the bridge widget
  *
  */
#include <Wt/WContainerWidget>
#include <Wt/WTextArea>
#include <Wt/WText>
#include <Wt/WMenuItem>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WComboBox>
#include <Wt/WApplication>
#include <Wt/WRegExpValidator>
#include <Wt/WIntValidator>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include "bridge.h"
#include <sstream>
using namespace Wt;
using namespace std;
class bridgeWidget: public WContainerWidget
{
private:
    WLineEdit *bridgeName;/**<variable of letting user input bridge name*/
    WLineEdit *bridgeLocation;/**<variable of letting user input bridge location*/
    WLineEdit *hostName;/**<variable of letting user input bridge host name*/
    WLineEdit *portNumber;/**<variable of letting user input port number*/
    WLineEdit *userNames;/**<variable of letting user input user name*/
    
    Wt::WLineEdit *lineEdit1;
    Wt::WLineEdit *lineEdit2;
    Wt::WLineEdit *lineEdit3;
    Wt::WLineEdit *lineEdit4;
    Wt::WLineEdit *lineEdit5;

 
 public:
     bridgeWidget(WContainerWidget *parent=0); 
     void display();
     void edit();
     void add();
    void del();
     void view();
    void saveBridge();
    void deletee();
    void editButton();
    void addBridge(string newBridgeName,string newLocation,string newHost,int newPortNumber,string newUsername);
    bool deleteBridge(string bridgenm);
    void editBridge(Bridge oldbridge,Bridge newbridge);
    void handleHttpResponse(boost::system::error_code err, const Http::Message& response);
    // void del();
};
