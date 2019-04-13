/**
  *@file doxygen_c.h
  *@author Weizhi Chen, Hejia Tang and Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This class represents bridge widget which used to show the information of bridge
  *
  *Uses http get to test whether connect to the hue api
  */
#include "bridgeWidget.h"
//#include "bridge.h"
#include "dbo.h"
#include "user.h"
using namespace Wt;
using namespace std;
extern User user_profile;
//DatabaseObject bridge;
Bridge bdges[1000];/**<bridge array to store bridge object*/
int bdgeNum;/**<current number of bridge on the array*/
Bridge bridgeObj;
int maxnumber=0;
int deleteIndex;
Bridge* bridgeArray=new Bridge[100];
WComboBox *cb;
WComboBox *editBox;
bridgeWidget::bridgeWidget(WContainerWidget *parent):WContainerWidget(parent)
{
    
    
}

/**
  @brief Display existing bridge in the list and show the attributes of bridge information
  @param void 
  @return void
  */
void bridgeWidget::display(){
     WApplication::instance()->styleSheet().addRule(".white", "color:white;");
    clear();
    addWidget(new WText("<h2><font color='white'>Bridges</font></h2>"));


  WTable *bridge = new WTable();
  bridge->setWidth(WLength("100%"));
  bridge->addStyleClass("table form-inline white");
  addWidget(bridge);
  bridge->elementAt(0, 0)->addWidget(new WText("<b style='color:white;'>Name</b>"));
  bridge->elementAt(0, 1)->addWidget(new WText("<b style='color:white;'>Location</b>"));
  bridge->elementAt(0, 2)->addWidget(new WText("<b style='color:white;'>IP Address</b>"));
  bridge->elementAt(0, 3)->addWidget(new WText("<b style='color:white;'>Port</b>"));
  bridge->elementAt(0, 4)->addWidget(new WText("<b style='color:white;'>UserName</b>"));
 if(maxnumber >0)
 {
     int i=1;
     
     while(i<=maxnumber)
     {
    int a=bridgeArray[i].getPortNumber();
    stringstream ss;
    ss<<a;
    string portNumber=ss.str();
    
    bridge->elementAt(i+1, 0)->addWidget(new WText(bridgeArray[i].getBridgeName()));
     bridge->elementAt(i+1, 1)->addWidget(new WText(bridgeArray[i].getLocation()));
    bridge->elementAt(i+1, 2)->addWidget(new WText(bridgeArray[i].getHost()));
    bridge->elementAt(i+1, 3)->addWidget(new WText(portNumber));
    bridge->elementAt(i+1, 4)->addWidget(new WText(bridgeArray[i].getUsername()));
         i=i+1;
     }
 }
    
    
  WPushButton *add = new WPushButton("Add");
  add->setLink(WLink(WLink::InternalPath,"/menu/bridge/add"));
  add->setMargin(5, Left);
  addWidget(add);
  add->clicked().connect(this,&bridgeWidget::add);

  WPushButton *edit = new WPushButton("Edit");
  edit->setLink(WLink(WLink::InternalPath,"/menu/bridge/edit"));
  edit->setMargin(5, Left);
  addWidget(edit);
  edit->clicked().connect(this,&bridgeWidget::edit);

    WPushButton *del = new WPushButton("Delete");
    del->setLink(WLink(WLink::InternalPath,"/menu/bridge/delete"));
    del->setMargin(5, Left);
    addWidget(del);
    del->clicked().connect(this,&bridgeWidget::del);
    
    
}

/**
  @brief add button event
  @param void 
  @return void
  */
void bridgeWidget::add(){
  clear();
   Wt::WRegExpValidator *nameValidator = new Wt::WRegExpValidator("[a-zA-Z]");
    Wt::WRegExpValidator *iphostValidator = new Wt::WRegExpValidator("[0-9.a-zA-Z]");
    WIntValidator *intValidator=new WIntValidator(0, 100000000);

  WTable *mod = new WTable();
  mod->setWidth(WLength("100%"));
  mod->addStyleClass("table form-inline");
  addWidget(mod);
  mod->elementAt(0, 0)->addWidget(new WText("<b style='color:white;' >Name</b>"));
  mod->elementAt(0, 1)->addWidget(new WText("<b style='color:white;'>Location</b>"));
  mod->elementAt(0, 2)->addWidget(new WText("<b style='color:white;'>IP Address</b>"));
  mod->elementAt(0, 3)->addWidget(new WText("<b style='color:white;'>Port</b>"));
  mod->elementAt(0, 4)->addWidget(new WText("<b style='color:white;'>User Name(Optional)</b>"));

    
    portNumber=new WLineEdit();
    portNumber->setValidator(intValidator);
    
    
  mod->elementAt(1, 0)->addWidget(bridgeName=new WLineEdit());
  mod->elementAt(1, 1)->addWidget(bridgeLocation=new WLineEdit());
  mod->elementAt(1, 2)->addWidget(hostName=new WLineEdit());
  mod->elementAt(1, 3)->addWidget(portNumber);
  mod->elementAt(1, 4)->addWidget(userNames=new WLineEdit());

  WPushButton *button = new WPushButton("Add");
  button->setLink(WLink(WLink::InternalPath,"/menu/bridge"));
  button->setMargin(5, Left);
  addWidget(button);

  button->clicked().connect(this,&bridgeWidget::saveBridge);

  button->clicked().connect(this,&bridgeWidget::display);
    

}

/**
 @Function that help saved the information enter by user and put data into bridgeobject
 @param void
 @return void
 */


void bridgeWidget::saveBridge()
{
    maxnumber=maxnumber+1;     //increase the total number of brdige by one
    WString bridgeName1=bridgeName->text();         //obtain the values form widgetline edit
    string sbridgeName=bridgeName1.toUTF8();
    
    WString bridgeLocation2=bridgeLocation->text();
    string sbridgeLocation2=bridgeLocation2.toUTF8();
    
    WString bridgeIp3=hostName->text();
    string sbridgeIp3=bridgeIp3.toUTF8();
    
    WString portNumber4=portNumber->text();
    string sportNumber4=portNumber4.toUTF8();
    std::stringstream str(sportNumber4);
    int bridgePort4;
    str >> bridgePort4;
    
    WString bridgeUserName5=userNames->text();
    string sbridgeUserName5=bridgeUserName5.toUTF8();
    
    int d = 0;
    
    
    if( (bridgeUserName5.empty())==true )   //empty username will be newdeveloper
    {
        bridgeArray[maxnumber].setBridgeName(sbridgeName);
        bridgeArray[maxnumber].setLocation(sbridgeLocation2);
        bridgeArray[maxnumber].setHost(sbridgeIp3);
        bridgeArray[maxnumber].setPortNumber(bridgePort4);
        bridgeArray[maxnumber].setUsername("newdeveloper");
        
        
        string url = Bridge::generateURL(bridgeArray[d+1]);   //connect backend url
        Http::Client *client=new Http::Client(this);
        client->setTimeout(15);
        client->setMaximumResponseSize(10*1024);
        client->done().connect(boost::bind(&bridgeWidget::handleHttpResponse,this,_1,_2));
        client->get(url);
        
    }
    
    else
    {   // not empty username
        
        bridgeArray[maxnumber].setBridgeName(sbridgeName);
        bridgeArray[maxnumber].setLocation(sbridgeLocation2);
        bridgeArray[maxnumber].setHost(sbridgeIp3);
        bridgeArray[maxnumber].setPortNumber(bridgePort4);
        bridgeArray[maxnumber].setUsername(sbridgeUserName5);
        
        
        
        string url = Bridge::generateURL(bridgeArray[d+1]);
        Http::Client *client=new Http::Client(this);
        client->setTimeout(15);
        client->setMaximumResponseSize(10*1024);
        client->done().connect(boost::bind(&bridgeWidget::handleHttpResponse,this,_1,_2));
        client->get(url);
    }
    
}

/**
 @Function that let user edit bridge information and connect to function that replace the data to the bridge
 @param void
 @return void
 */

void bridgeWidget::edit(){
  clear();
    WIntValidator *intValidator=new WIntValidator(0, 100000000);  //limit the portnumber only integer and value
    WApplication::instance()->styleSheet().addRule(".selects", "width:50%");
    editBox= new WComboBox();
    editBox->setStyleClass("selects");  //choose existing bridge, maxnumber=0 means no bridge
    if(maxnumber==0)
    {
        editBox->addItem("Nothing");
    }
    
    else
    {
        for(int q=1;q<=maxnumber;q++)
        {
            string namess= bridgeArray[q].getBridgeName();  //name of bridge
            editBox->addItem(WString("{1}").arg(namess));
        }
    }
    editBox->setMargin(10, Right);
    editBox->setCurrentIndex(0);
    WText *out1 = new WText();
    out1->addStyleClass("help-block");
   
    
    addWidget(editBox);
    

    addWidget(out1);
    lineEdit4=new WLineEdit();
    
    lineEdit4->setValidator(intValidator);

  WTable *mod = new WTable();
  mod->setWidth(WLength("100%"));
  mod->addStyleClass("table form-inline");
  addWidget(mod);
  mod->elementAt(0, 0)->addWidget(new WText("<b style='color:white;'>Name</b>"));
  mod->elementAt(0, 1)->addWidget(new WText("<b style='color:white;'>Location</b>"));
  mod->elementAt(0, 2)->addWidget(new WText("<b style='color:white;'>IP Address</b>"));
  mod->elementAt(0, 3)->addWidget(new WText("<b style='color:white;'>Port</b>"));
  mod->elementAt(0, 4)->addWidget(new WText("<b style='color:white;'>User Name(Optional)</b>"));

  mod->elementAt(1, 0)->addWidget(lineEdit1=new WLineEdit());//receive the input
  mod->elementAt(1, 1)->addWidget(lineEdit2=new WLineEdit());
  mod->elementAt(1, 2)->addWidget(lineEdit3=new WLineEdit());
  mod->elementAt(1, 3)->addWidget(lineEdit4);
  mod->elementAt(1, 4)->addWidget(lineEdit5=new WLineEdit());

    
  WPushButton *button = new WPushButton("Save");
  button->setLink(WLink(WLink::InternalPath,"/menu/bridge"));
  button->setMargin(5, Left);
  addWidget(button);

  button->clicked().connect(this,&bridgeWidget::editButton);  //connect to functions
  button->clicked().connect(this,&bridgeWidget::display);
}

/**
 @Function that actually store the information enter by user and put data into bridgeobject
 @param void
 @return void
 */


void bridgeWidget::editButton()
{
    int d= (editBox->currentIndex());
    
    WString newbridgeName1=lineEdit1->text();
    string newsbridgeName=newbridgeName1.toUTF8();
    
    WString newbridgeLocation2=lineEdit2->text();  //receivefrom wlinedit
    string newsbridgeLocation2=newbridgeLocation2.toUTF8();
    
    WString newbridgeIp3=lineEdit3->text();
    string newsbridgeIp3=newbridgeIp3.toUTF8();
    
    WString newportNumber4=lineEdit4->text();
    string newsportNumber4=newportNumber4.toUTF8();
    std::stringstream str(newsportNumber4);
    int newbridgePort4;
    str>>newbridgePort4;
    
    WString newbridgeUserName5=lineEdit5->text();   //check if the userName is empty or not
    
    if((newbridgeUserName5.empty())==true)
    {
        bridgeArray[d+1].setBridgeName(newsbridgeName);
        bridgeArray[d+1].setLocation(newsbridgeLocation2);
        bridgeArray[d+1].setHost(newsbridgeIp3);
        bridgeArray[d+1].setPortNumber(newbridgePort4);
        bridgeArray[d+1].setUsername("newdeveloper");
        
        

    
        
    }
    else
    {
        string newsbridgeUserName5=newbridgeUserName5.toUTF8();
        //    bridgeObj=new Bridge();
        bridgeArray[d+1].setBridgeName(newsbridgeName);
        bridgeArray[d+1].setLocation(newsbridgeLocation2);
        bridgeArray[d+1].setHost(newsbridgeIp3);
        bridgeArray[d+1].setPortNumber(newbridgePort4);
        bridgeArray[d+1].setUsername(newsbridgeUserName5);
    }
}

/**
 @Function that help delete the information enter by user and refresh the bridge array
 @param void
 @return void
 */


void bridgeWidget::del(){
    clear();
   WApplication::instance()->styleSheet().addRule(".select", "width:50%");
    cb= new WComboBox();
    cb->setStyleClass("select");
    
    if(maxnumber==0)   //currenly no existing brdige
    {
    cb->addItem("Nothing");
    }
    
    else
    {
    
        for(int q=1;q<=maxnumber;q++)
    {
      string names= bridgeArray[q].getBridgeName();  //select a bridgee
        cb->addItem(WString("{1}").arg(names));
    }

    }
    cb->setMargin(10, Right);
    cb->setCurrentIndex(0);
    WText *out = new WText();
    out->addStyleClass("help-block");
    //out->setText(WString("You selected {1}.").arg(cb->currentText()));
    
    addWidget(cb);
    
    // cb->activated().connect(this, out->setText(WString("You selected {1}.").arg(cb->currentText())));
    addWidget(out);
    
    
    WPushButton *button = new WPushButton("Delete");
    button->setLink(WLink(WLink::InternalPath,"/menu/bridge"));
    button->setMargin(5, Left);
    addWidget(button);

    
     button->clicked().connect(this,&bridgeWidget::deletee);
    
    button->clicked().connect(this,&bridgeWidget::display);
    
    
    
    
}

/**
 @Function that delete the bridge from the array
 @param void
 @return void
 */

void bridgeWidget::deletee(){
    int d= (cb->currentIndex());
    bridgeArray[d+1].deleteBridge( bridgeArray[d+1].getBridgeName() );
    maxnumber=maxnumber-1;    //total number of bridge dec rease by 1
}


/**
 @Function that view the exisitng bridge(not used)
 @param void
 @return void
 */

void bridgeWidget::view(){
    clear();

    WTable *mod = new WTable();
    mod->setWidth(WLength("100%"));
    mod->addStyleClass("table form-inline");
    addWidget(mod);
    mod->elementAt(0, 0)->addWidget(new WText("<b style='color:white;' >Name</b>"));
    mod->elementAt(0, 1)->addWidget(new WText("<b style='color:white;'>Location</b>"));
    mod->elementAt(0, 2)->addWidget(new WText("<b style='color:white;'>IP Address</b>"));
    mod->elementAt(0, 3)->addWidget(new WText("<b style='color:white;'>Port</b>"));
    mod->elementAt(0, 4)->addWidget(new WText("<b style='color:white;'>User Name(Optional)</b>"));
    
    mod->elementAt(1, 0)->addWidget(new WText("<b style='color:white;' >Sam's bulb</b>"));
    mod->elementAt(1, 1)->addWidget(new WText("<b style='color:white;'>Living Room</b>"));
    mod->elementAt(1, 2)->addWidget(new WText("<b style='color:white;'>305.325</b>"));
    mod->elementAt(1, 3)->addWidget(new WText("<b style='color:white;'>8080</b>"));
    mod->elementAt(1, 4)->addWidget(new WText("<b style='color:white;'>NewDeveloper(Optional)</b>"));
    
 
    mod->elementAt(2, 0)->addWidget(new WText("<b style='color:white;' >Kl's bulb</b>"));
    mod->elementAt(2, 1)->addWidget(new WText("<b style='color:white;'>Faily Room</b>"));
    mod->elementAt(2, 2)->addWidget(new WText("<b style='color:white;'>305.s325</b>"));
    mod->elementAt(2, 3)->addWidget(new WText("<b style='color:white;'>8080</b>"));
    mod->elementAt(2, 4)->addWidget(new WText("<b style='color:white;'>NewD2eqeveloper(Optional)</b>"));
    
    mod->elementAt(3, 0)->addWidget(new WText("<b style='color:white;' >Rt's bulb</b>"));
    mod->elementAt(3, 1)->addWidget(new WText("<b style='color:white;'>BathRoom</b>"));
    mod->elementAt(3, 2)->addWidget(new WText("<b style='color:white;'>302.323125</b>"));
    mod->elementAt(3, 3)->addWidget(new WText("<b style='color:white;'>8080</b>"));
    mod->elementAt(3, 4)->addWidget(new WText("<b style='color:white;'>NewDeeqw(Optional)</b>"));
    
    WPushButton *button = new WPushButton("Back");
    button->setLink(WLink(WLink::InternalPath,"/menu/bridge"));
    button->setMargin(5, Left);
    addWidget(button);
    
    button->clicked().connect(this,&bridgeWidget::display);
}

/**
  @brief the method of adding bridges and use http to test
  *whether connect successfully 
  @param string
  @return none
  */
void bridgeWidget::addBridge(string newBridgeName,string newLocation,string newHost,int newPortNumber,string newUsername){
     string url;
     Bridge bgobj(newBridgeName,newLocation,newHost,newPortNumber,newUsername);  
     bdges[bdgeNum] = bgobj;
     url = Bridge::generateURL(bdges[bdgeNum]);
     Http::Client *client = new Http::Client(this);
     //Http::Message msg;
     //msg.addBodyText("{\"devicetype\":\"my_hue_app\"}");
     client->setTimeout(15);
     client->setMaximumResponseSize(10*1024);
     client->done().connect(boost::bind(&bridgeWidget::handleHttpResponse,this,_1,_2));
        
     if(client->get(url)){
       if(newUsername=="")
       {
         //bridge.addBridge(user_profile.getUserName(),newBridgeName,newLocation,newHost,newPortNumber,"newdeveloper");
       }
       else
       {
         //bridge.addBridge(user_profile.getUserName(),newBridgeName,newLocation,newHost,newPortNumber,newUsername);
       }
     }
     bdgeNum++;     
}


/**
  @brief the method of editing bridges and use http to test
  *whether edit successfully 
  *param oldbridge newbridge
  *return none
  */
void bridgeWidget::editBridge(Bridge oldbridge,Bridge newbridge){
   string url;
   oldbridge.setBridgeName(newbridge.getBridgeName());
   oldbridge.setLocation(newbridge.getLocation());
   oldbridge.setHost(newbridge.getHost());
   oldbridge.setPortNumber(newbridge.getPortNumber());
   oldbridge.setUsername(newbridge.getUsername());
   url = Bridge::generateURL(oldbridge);
   Http::Client *check = new Http::Client(this);
   check->setTimeout(15);
   check->setMaximumResponseSize(10*1024);
   check->done().connect(boost::bind(&bridgeWidget::handleHttpResponse,this,_1,_2));
   
   check->get(url);
}


/**
  @brief handle http request and making test request
  @param err response
  @return none
  */
void bridgeWidget::handleHttpResponse(boost::system::error_code err, const Http::Message& response){
    if(err || response.status()!=200)
    {
      cerr<< "Error:" << err.message() << "," <<response.status()<< endl;
    }
    else
    {
       cout<< response.body()<<endl;
    }
}






