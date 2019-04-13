/**
  *@file doxygen_c.h
  *@author Weizhi Chen, Hejia Tang and Yuhan Zhang
  *@date 28 Nov 2017
  *@brief This class represents schedule widget which used to show the information of schedule
  */

#include "scheduleWidget.h"
#include "bridgeWidget.h"
#include <Wt/WIntValidator>
#include <Wt/WTime>

using namespace Wt;
using namespace std;


extern Bridge bridgeArray[100];/**<the bridge that used to store bridge object*/
Schedule schedules[1000];/**<the schedule that used to store schedule object*/
Schedule scheduleq;
int schenum=0;
int idnum=1;
extern int maxnumber;
WComboBox *lightGroup;
WComboBox *bridgeList;
WComboBox *switchs;
WComboBox *colors;
Bridge *bridgeobj1;
Bridge *bridgeobj2;
Bridge *bridgeobj3;

string scheduleName;/**<string that used to store schedule name*/
string scheTimess;/**<string that used to store schedule time*/
string descriptions;/**<string that used to store schedule description*/
string choicesss;/**<string that used to store choice*/
int ids;/**<string that used to id*/
string states;/**<string that used to store states*/
string colorss;/**<string that used to store colors*/
int brightness;/**<string that used to store brightness*/
int transitionTime;/**<string that used to store transition time*/

int check=0;





namespace{
  WPushButton *createColorButton(const char *className, const WString& text)
  {
    WPushButton *button = new WPushButton();
    button->setTextFormat(Wt::XHTMLText);
    button->setText(text);
    button->addStyleClass(className);
    return button;
  }

}

scheduleWidget::scheduleWidget(WContainerWidget *parent):WContainerWidget(parent)
{
}

/**
  @brief Display existing schedule in the list and show the attributes of schedule information
  @param void 
  @return void
  */
void scheduleWidget::display(){
    
    int portn=8080;
     bridgeobj1=new Bridge("TomBridge","Tom's house","Local",portn,"TomZask");
    bridgeobj2=new Bridge("KyleBridge","Kyle's house","Local",portn,"KyleZasg");  //ceate obejct of bridge
    bridgeobj3=new Bridge("JonnyBridge","Jonny's house","Local",portn,"Jonnyask");
    
    
    
    WApplication::instance()->styleSheet().addRule(".white", "color:white;");
    clear();
    addWidget(new WText("<h2><font color='white'>Schedules</font></h2>"));

  treeTable = new WTreeTable();

  treeTable->resize(1000, 400);
  treeTable->tree()->setSelectionMode(Wt::SingleSelection);  //add header to the treetable
  treeTable->addColumn("Group/Light", 100);
  treeTable->addColumn("ID", 60);
  treeTable->addColumn("Name", 80);
  treeTable->addColumn("Description", 150);
  treeTable->addColumn("State", 60);  
  treeTable->addColumn("Brightness", 100);
  treeTable->addColumn("Colour", 80);
  treeTable->addColumn("Date", 100);
  treeTable->addColumn("Time", 100);
 treeTable->setStyleClass("white");

    
  WTreeTableNode *root = new WTreeTableNode("All Bridges");
  treeTable->setTreeRoot(root, "Bridge Name");
  WTreeTableNode *node1 = new WTreeTableNode("", 0, root);

    node1->setStyleClass("white");
  root->expand();
  addWidget(treeTable);
  
//define three buttons
  WPushButton *add = new WPushButton("Add");
  add->setLink(WLink(WLink::InternalPath,"/menu/schedule/add"));
  add->setMargin(5, Left);
  addWidget(add);
  add->clicked().connect(this,&scheduleWidget::showAdd);

  WPushButton *update = new WPushButton("Update");
  update->setLink(WLink(WLink::InternalPath,"/menu/schedule/update"));
  update->setMargin(5, Left);
  addWidget(update);
  update->clicked().connect(this,&scheduleWidget::showUpdate);

  WPushButton *del = new WPushButton("Delete");
  del->setLink(WLink(WLink::InternalPath,"/menu/schedule/delete"));
  del->setMargin(5, Left);
  addWidget(del);
  del->clicked().connect(this,&scheduleWidget::showDel);
}


/**
  @brief add button event
  @param void 
  @return void
  */
void scheduleWidget::showAdd(){
  clear();
WApplication::instance()->styleSheet().addRule(".selectss", "width:25%");
    WApplication::instance()->styleSheet().addRule(".white", "color:white");
    lightGroup= new WComboBox();
    lightGroup->setStyleClass("white");
    lightGroup->setStyleClass("selectss");   //comboxbox add attribute
    lightGroup->addItem("Light");
    lightGroup->addItem("Group");
    lightGroup->setMargin(10, Right);
    lightGroup->setCurrentIndex(0);
    WText *out1 = new WText();
    out1->addStyleClass("help-block");
    addWidget(lightGroup);
     addWidget(out1);
  

    
  addWidget(new WBreak());
   addWidget(new WText("<b style='color:white'>Choose Bridge</b>"));  //choose bridge

      addWidget(new WBreak());
    
    
    WApplication::instance()->styleSheet().addRule(".selectsss", "width:50%");
    bridgeList= new WComboBox();
    bridgeList->setStyleClass("selectsss");    //nothing when there is no bridge
    if(maxnumber==0)
    {
        bridgeList->addItem("Nothing");
    }
    
    else
    {  // display the bridges
        for(int f=1;f<=maxnumber;f++)
        {
            string namess= bridgeArray[f].getBridgeName();
            bridgeList->addItem(WString("{1}").arg(namess));
        }
    }
   bridgeList->setMargin(10, Right);
    bridgeList->setCurrentIndex(0);
    WText *out5 = new WText();
    out5->addStyleClass("help-block");
    
    addWidget(bridgeList);
    addWidget(out5);
    
    
    addWidget(new WBreak());

  WTable *info = new WTable();
  info->setWidth(WLength("100%"));
  info->addStyleClass("table form-inline");
  addWidget(info);
  info->elementAt(0, 0)->addWidget(new WText("<b style='color:white'>ID</b>"));
  info->elementAt(1, 0)->addWidget(new WText("<b style='color:white'>Schedule Name</b>"));
  info->elementAt(2, 0)->addWidget(new WText("<b style='color:white'>Description</b>"));

    IDs=new WLineEdit();   // two lineEdit and one textarea to receive the value
    scheName=new WLineEdit();
    descript=new WTextArea();
    WIntValidator *intValidator=new WIntValidator(0, 100000000);
    IDs->setValidator(intValidator);
    
    
  info->elementAt(0, 1)->addWidget(IDs);
  info->elementAt(1, 1)->addWidget(scheName);
  info->elementAt(2, 1)->addWidget(descript);
  addWidget(new WBreak());
  /*
   * Switch
   */

    switchs= new WComboBox();
     switchs->setStyleClass("white");    //on and off state
     switchs->setStyleClass("selectss");
     switchs->addItem("On");
     switchs->addItem("Off");
     switchs->setMargin(10, Right);
     switchs->setCurrentIndex(0);
    WText *out2 = new WText();
    out2->addStyleClass("help-block");
    addWidget(switchs);
    addWidget(out2);
    addWidget(new WBreak());
    
  /*
   * Color
   */
    addWidget(new WText("Color Selection"));
  addWidget(new WBreak());
    
    
    colors= new WComboBox();   //choose color
    colors->setStyleClass("white");
    colors->setStyleClass("selectss");
    colors->addItem("Indigo");
    colors->addItem("Blue");
     colors->addItem("Red");
     colors->addItem("Green");
     colors->addItem("Yellow");
    colors->setMargin(10, Right);
    colors->setCurrentIndex(0);
    WText *out3 = new WText();
    out1->addStyleClass("help-block");
    //out->setText(WString("You selected {1}.").arg(cb->currentText()));
    addWidget(colors);
    addWidget(out3);
  addWidget(new WBreak());

  /*
   * Brightness
   */
  br = new WSlider();   //choose the brightness
  br->resize(500, 50);
  br->setTickPosition(Wt::WSlider::TicksAbove);
  br->setTickInterval(20);
  br->setMinimum(0);
  br->setMaximum(254);
  br->setValue(177);

  addWidget(new WText("<b style='color:white'>Brightness</b>"));
  addWidget(new WBreak());
  addWidget(br);
    
 
  /*
   * Date & Time Pick
   */

  addWidget(new WBreak());
  addWidget(new WText("<b style='color:white'>Date</b>"));
  addWidget(new WBreak());

  WDate today = WDate::currentDate();
  calendar = new WCalendar(this);
  calendar->browseTo(today.addMonths(1));
  calendar->setSelectionMode(Wt::SingleSelection);
  addWidget(calendar);
  
  addWidget(new WBreak());
    addWidget(new WText("<b style='color:white'>Time</b>"));
  addWidget(new WBreak());
  
  te = new WTimeEdit();
  te->setTime(WTime::currentTime());
  addWidget(te);

//add button to handle data
  addWidget(new WBreak());
  addWidget(new WBreak());
  WPushButton *addB = new WPushButton("Add");
  addB->setLink(WLink(WLink::InternalPath,"/menu/schedule"));
  addB->setMargin(5, Left);
  addWidget(addB);

addB->clicked().connect(this,&scheduleWidget::display);

}


/**
  @brief method to add new schedule and display on the table that use all information input from the user
  @param void 
  @return void
  */
void scheduleWidget::addition()
{

    check=check+1;
    int a=(lightGroup->currentIndex());   //receive the input values from the add from the user
    int b=(switchs->currentIndex());
    int c=(colors->currentIndex());
    
    
    if(a=0)
    {
        choicesss="lights";
    }
    else if (a!=0)
    {
        choicesss="groups";
    }
    
    if(b=0)
    {
        states="true";
    }
    else
    {
        states="false";
    }
    if(c=0)
    {
        colorss="Indigo";
    }
    else if(c=1)
    {
        colorss="Blue";
    }
   else  if(c=2)
   {
       colorss="Red";
   }
   else  if(c=3)
   {
       colorss="Green";
   }
  else
    {
        colorss="Yellow";
                    }
 
    WString gIDs=IDs->text();
    std::string sGIDs=gIDs.toUTF8();
    std::stringstream str(sGIDs);
    str>>ids;
    
    WString gscheName=scheName->text();
    scheduleName=gscheName.toUTF8();
    
    WString gDescript=descript->text();
    descriptions=gDescript.toUTF8();
    
    
WString brightvalue= br->valueText();
  string sbrightvalue=brightvalue.toUTF8();
    std::stringstream strs(sbrightvalue);
    strs>>brightness;
    

    WTime wtimes=te->time();
    WString wtimeString=wtimes.toString();
    scheTimess=wtimeString.toUTF8();
    
    transitionTime=1237192;
    

    scheduleq.setScheduleTime(scheTimess);
    scheduleq.setScheduleName(scheduleName);
    scheduleq.setDescription(descriptions);
    scheduleq.setState(states);
    scheduleq.setScheduleID(ids);
    scheduleq.setBrightness(brightness);
    scheduleq.setTransitionTime(transitionTime);
}


/**
 @brief show update information of schedule
 @param void
 @return void
 */
void scheduleWidget::showUpdate(){

}

/**
 @brief show information of schedule
 @param void
 @return void
 */

void scheduleWidget::showDel(){
  clear();
  addWidget(new WText("<h4>Welcome Jane Doe</h4>"));
  WContainerWidget *deletion = new WContainerWidget();
  scheList = new WComboBox();
  scheList->addItem("Away");
  scheList->addItem("evening");
  scheList->addItem("morning");
  scheList->addItem("romantic");
  scheList->setMargin(10, Right);

  scheList->setCurrentIndex(1);
  addWidget(scheList);

  addWidget(new WBreak());

  WPushButton *dele = new WPushButton("Save");
  dele->setLink(WLink(WLink::InternalPath,"/menu/schedule"));
  dele->setMargin(5, Left);
  addWidget(dele);

  dele->clicked().connect(this,&scheduleWidget::display);
}


/**
  @brief show details information of schedule
  @param void
  @return void
  */
void scheduleWidget::showDetail(){

  WContainerWidget *d = new WContainerWidget();
  //choose light or group
  bg = new WButtonGroup();
  lig = new WRadioButton("Light");
    lig->setStyleClass("white");
  bg->addButton(lig);
  gro = new WRadioButton("Group");
    gro->setStyleClass("white");
  bg->addButton(gro);
  d->addWidget(lig);
  d->addWidget(gro);
  d->addWidget(new WBreak());
  d->addWidget(new WBreak());

  WTable *info = new WTable();
  info->setWidth(WLength("100%"));
  info->addStyleClass("table form-inline");
  d->addWidget(info);
  info->elementAt(0, 0)->addWidget(new WText("<b style='color:white'>ID</b>"));
  info->elementAt(1, 0)->addWidget(new WText("<b style='color:white'>Schedule Name</b>"));
  info->elementAt(2, 0)->addWidget(new WText("<b style='color:white'>Description</b>"));

  info->elementAt(0, 1)->addWidget(new WLineEdit());
  info->elementAt(1, 1)->addWidget(new WLineEdit());
  info->elementAt(2, 1)->addWidget(new WTextArea());
  d->addWidget(new WBreak());


  /*
   * Switch
   */
   d->addWidget(new WText("<b style='color:white'>Switch</b>"));
   d->addWidget(new WBreak());
   bg = new WButtonGroup();
   on = new WRadioButton("On");
    on->setStyleClass("white");
   bg->addButton(on);
   off = new WRadioButton("Off");
    off->setStyleClass("white");
   bg->addButton(off);
   d->addWidget(on);
   d->addWidget(off);
   d->addWidget(new WBreak());
   d->addWidget(new WBreak());

  /*
   * Color
   */
  d->addWidget(new WText("<b style='color:white'>Color</b>"));
  d->addWidget(new WBreak());
  toolBar = new WToolBar();

  toolBar->addButton(createColorButton("btn-primary","Indigo"));
  toolBar->addButton(createColorButton("btn-info","Blue"));
  toolBar->addButton(createColorButton("btn-danger","Red"));
  toolBar->addButton(createColorButton("btn-success","Green"));
  toolBar->addButton(createColorButton("btn-warning","Yellow"));

  d->addWidget(toolBar);
  d->addWidget(new WBreak());
  d->addWidget(new WBreak());

  /*
   * Brightness
   */
  br = new WSlider();
  br->resize(500, 50);
  br->setTickPosition(Wt::WSlider::TicksAbove);
  br->setTickInterval(20);
  br->setMinimum(0);
  br->setMaximum(254);
  br->setValue(177);

  d->addWidget(new WText("<b style='color:white'>Brightness</b>"));
  d->addWidget(new WBreak());
  d->addWidget(br);
 
  /*
   * Date & Time Pick
   */

  d->addWidget(new WBreak());
  d->addWidget(new WText("<b style='color:white'>Date</b>"));
  d->addWidget(new WBreak());

  WDate today = WDate::currentDate();
  calendar = new WCalendar(this);
  calendar->browseTo(today.addMonths(1));
  //calendar->select(today.addMonths(1).addDays(3));
  calendar->setSelectionMode(Wt::SingleSelection);
  d->addWidget(calendar);
  //calendar->selected().connect(this, &MyWidget::daySelected);
  
  d->addWidget(new WBreak());
  d->addWidget(new WText("<b style='color:white'>Time</b>"));
  d->addWidget(new WBreak());
  
  te = new WTimeEdit();
  te->setTime(WTime::currentTime());
  d->addWidget(te);
  WPushButton *save = new WPushButton("Save");
  save->setLink(WLink(WLink::InternalPath,"/menu/schedule"));
  save->setMargin(5, Left);
  d->addWidget(save);

  save->clicked().connect(this,&scheduleWidget::display);
  
  addWidget(d);

}




/**
  @brief Display existing schedule in the list and show the attributes of schedule information
  @param bridgeobj,newScheName,newScheTime,newDescription, choice, id, newState, newColor, newBrightness,newTransitionTime
  @return void
  */
void scheduleWidget::addSchedule(Bridge bridgeobj,string newScheName, string newScheTime,string newDescription,string choice,string id,string newState,string newColor,int newBrightness,int newTransitionTime){
    string url;
    url = Bridge::generateURL(bridgeobj)+"/schedules";
    Schedule scheduleobj(bridgeobj,newScheName,newScheTime,newDescription,choice,id,newState,newColor,newBrightness,newTransitionTime);
    schedules[schenum] = scheduleobj;
    Http::Client *create =new Http::Client(this);
    Http::Message msg;
    string text = Schedule::generateHttpMessage(scheduleobj);
    msg.addBodyText(text);
    create->setTimeout(15);
    create->setMaximumResponseSize(10*1024);
    create->done().connect(boost::bind(&scheduleWidget::handlePostHttpResponse,this,_1,_2));
    create->put(url,msg);
    schedules[schenum].setScheduleID(idnum);
    idnum++;
    schenum++;
}


/**
  @brief Display existing schedule in the list and show the attributes of schedule information
  @param string scheName
  @return bool true or false
  */
bool scheduleWidget::removeSchedule(string scheName){
    const int notfound = -1;
    int search = notfound;
    if(schenum == 0){
        return false;
    }
    for(int i=0;i<schenum && search==notfound;i++){
        if(schedules[i].getScheduleName()==scheName)
        {
            search = i;
        }
    }
    if(search==-1)
    {
        return false;
    }
    stringstream convert;
    int id=schedules[search].getScheduleID();
    convert << id;
    string url = Bridge::generateURL(schedules[search].bridge)+"/schedules/"+convert.str();
    Http::Client *remove =new Http::Client(this);
    Http::Message msg;
    msg.addBodyText("");
    remove->setTimeout(15);
    remove->setMaximumResponseSize(10*1024);
    remove->done().connect(boost::bind(&scheduleWidget::handleHttpResponse,this,_1,_2));
    
    remove->deleteRequest(url,msg);
    schedules[search]=schedules[schenum+1];
    convert.str("");
    schenum--;
    return true;
}


/**
  @brief Display existing schedule in the list and show the attributes of schedule information
  @param oldSchedule object newSchedule object
  @return void
  */
void scheduleWidget::updateSchedule(Schedule oldSchedule,Schedule newSchedule){
    string url;
    oldSchedule.setScheduleName(newSchedule.getScheduleName());
    oldSchedule.setScheduleTime(newSchedule.getScheduleTime());
    oldSchedule.setDescription(newSchedule.getDescription());
    oldSchedule.setAddress(newSchedule.getAddress());
    oldSchedule.setState(newSchedule.getState());
    oldSchedule.setBrightness(newSchedule.getBrightness());
    oldSchedule.setTransitionTime(newSchedule.getTransitionTime());
    oldSchedule.color = newSchedule.color;
    stringstream convert;
    int id = oldSchedule.getScheduleID();
    convert << id;
    url = Bridge::generateURL(oldSchedule.bridge)+"/schedules/"+convert.str();
    Http::Message msg;
    string text = Schedule::generateHttpMessage(oldSchedule);
    msg.addBodyText(text);
    Http::Client *edit = new Http::Client(this);
    edit->setTimeout(15);
    edit->setMaximumResponseSize(10*1024);
    edit->done().connect(boost::bind(&scheduleWidget::handleHttpResponse,this,_1,_2));
    
    edit->put(url,msg);
    convert.str("");
}


/**
  @brief handle the http response of the add request
  @param err response 
  @return void
  */
string scheduleWidget::handlePostHttpResponse(boost::system::error_code err,const Http::Message& response){
    string s="";
    string out;
    Json::Array data;
    Json::Object result;
    Json::Object element;
    WString a;
    if(err || response.status()!=200)
    {
        cerr<<"Error:"<<err.message()<<","<<response.status()<<endl;
    }
    else
    {
        out = response.body();
        Json::parse(out,data);
        result = data[0];
        element = result.get("success");
        a = element.get("id");
        s = a.toUTF8();
    }
    return s;
}


/**
  @brief the method of handling http response
  @param err response 
  @return void
  */
void scheduleWidget::handleHttpResponse(boost::system::error_code err, const Http::Message& response){
    if(err || response.status()!=200)
    {
        cerr<<"Error:"<<err.message()<<","<<response.status()<<endl;
    }
    else
    {
        cout<< response.body()<<endl;
    }
}
// }


