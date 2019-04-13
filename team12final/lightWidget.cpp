/**
  *@file doxygen_c.h
  *@author Martin Vieira & Hejia Tang & Weizhi Chen
  *@date 28 Nov 2017
  *@brief Contains methods that show the light page and add, edit, delete methods send the data to API
  * 
  *Uses Wt widget to display all the lights and add, delete, edit pages.   
  *Uses http get, post, and put requests to change the value of a bulb's id, name, brightness, color and state
  */

#include "lightWidget.h"
extern Bridge bridgeArray[100];
extern int maxnumber;

using namespace Wt;
using namespace std;

// iD is a global variable to give a light its id
//starts from 0
int iD = 0;


/**
  *@brief Basic constructor for a LightWidget object
  *
  *This contructor initializes a light page with the parent widget
  *@param the parent widget
  *@return void
  */
lightWidget::lightWidget(WContainerWidget *parent):WContainerWidget(parent)
{
WApplication::instance()->styleSheet().addRule(".white", "color:white;");
}

/**
  *@brief the method to display all the lights
  *
  *@param none
  *@return void
  */
void lightWidget::display(){
  clear();

  addWidget(new WText("<h2><font color='white'>Lights</font></h2>"));
  //v is the table to view all the lights
	v = new WTable();

  v->setWidth(WLength("100%"));
  v->addStyleClass("table form-inline");
  v->elementAt(0, 0)->addWidget(new WText("<b style='color:white'>#</b>"));
  v->elementAt(0, 1)->addWidget(new WText("<b style='color:white'>Name</b>"));
  v->elementAt(0, 2)->addWidget(new WText("<b style='color:white'>Brightness</b>"));
  v->elementAt(0, 3)->addWidget(new WText("<b style='color:white'>Color</b>"));
  v->elementAt(0, 4)->addWidget(new WText("<b style='color:white'>State</b>"));

  //in order to print all the lights
  //check the number of lights got
  if(iD > 0){

    //i is the counter to make sure print out all the lights
     int i = 1;
     
     while(i <= iD){

      //stringstream to convert int to string
      stringstream ss;
      ss<<iD;
      string id = ss.str();
      
      //print all the lights's information out on the screen
      v->elementAt(i+1, 0)->addWidget(new WText(WString("<font color='white'>{1}</font>").arg(i)));
      lightBulb[i].getBulbName();
      lightBulb[i].getBrightness();
      lightBulb[i].getColor();
      lightBulb[i].getState();

      i=i+1;

     }
  }

    addWidget(v);

  // add buttons direct to other functional pages
    WPushButton *button = new WPushButton("Add");
    button->clicked().connect(this,&lightWidget::add);
    addWidget(button);
    WPushButton *butt = new WPushButton("Edit");
    butt->clicked().connect(this,&lightWidget::edit);
    addWidget(butt);
    WPushButton *bu = new WPushButton("Delete");
    bu->clicked().connect(this, &lightWidget::delet);
    addWidget(bu);
}

/**
  *@brief the widget for user to add the light
  *
  *asks user's input, the light's name and choose which bridge belonging
  *@param none
  *@return void
  */
void lightWidget::add(){
    clear();
    //the table asks user for input 
    a = new WTable();
    a->setWidth(WLength("100%"));
    a->addStyleClass("table form-inline");

    a->elementAt(0, 0)->addWidget(new WText("<b style='color:white'>#</b>"));
    a->elementAt(0, 1)->addWidget(new WText("<b style='color:white'>Name</b>"));

    //auto give the id of light to the user
    a->elementAt(1, 0)->addWidget(new WText(WString("<font color='white'>{1}</font>").arg(iD)));
    a->elementAt(1, 1)->addWidget(lightName = new WLineEdit());

    WString lName = lightName->text();
    string lN = lName.toUTF8();
    lights[iD] = lN;

    addWidget(new WBreak());
    //get data from bridge 
    //and print out the bridge list
    bridgeList = new WComboBox();
    if(maxnumber==0)
    {
        bridgeList->addItem("Nothing");
    }
    
    else
    {
        for(int q=1;q<=maxnumber;q++)
        {
            string namess= bridgeArray[q].getBridgeName();
            bridgeList->addItem(WString("{1}").arg(namess));
        }
    }
    bridgeList->setMargin(10, Right);
    bridgeList->setCurrentIndex(0);

    //once the user choose one, they are not able to choose again
    bridgeList->activated().connect(bridgeList, &Wt::WComboBox::disable);

    //user comfirm the addtion, and pass the data to the addition method
    //and user return to the display page
    WPushButton *button1 = new WPushButton("Add");
    button1->clicked().connect(this,&lightWidget::addition);
    button1->clicked().connect(this,&lightWidget::display);

    addWidget(a);
    addWidget(new WBreak());
    addWidget(new WText("<font color='white'>Bridge</font>"));
    addWidget(bridgeList);
    addWidget(button1);

}

/**
  *@brief the method that pass user input data, and create a light object
  *
  *uses user's input, create a light object using their data
  *@param none
  *@return void
  */
void lightWidget::addition(){

  int bri = 120;
  string col = "yellow";

  WString lNa = lightName->text();
  string lName2 = lNa.toUTF8();

  lightBulb[iD].setId(iD);
  lightBulb[iD].setTable(v);


  //set the name to the object
  lightBulb[iD].setBulbName(lName2);  
  //send the msg to API
  lightBulb[iD].setBrightness(bri);
  lightBulb[iD].setColor(col);
  lightBulb[iD].setState(false);

  iD++;
}

/**
  *@brief the widget for user to edit the light
  *
  *asks user to choose which light they would like to change
  *users are able to change attributs in this page
  *@param none
  *@return void
  */
void lightWidget::edit(){
  clear();

  //attribute

    /*
    * Light Choices
    */
    lightList = new WComboBox();
    lightList->addItem("default1");
    lightList->addItem("default2");
    lightList->addItem("livingRoom1");
    lightList->addItem("frontDoor1");
    lightList->addItem("default3");
    lightList->setMargin(10, Right);

    lightList->setCurrentIndex(1);
    addWidget(lightList);
    addWidget(new WBreak());

    lightList->activated().connect(lightList, &Wt::WComboBox::disable);

    /*
    * Switch
    */
    addWidget(new WText("<font color='white'>Switch</font>"));
    addWidget(new WBreak());

    switcH = new WComboBox();
    switcH->addItem("On");
    switcH->addItem("Off");
    switcH->activated().connect(switcH, &Wt::WComboBox::disable);

    addWidget(switcH);
    addWidget(new WBreak());
    addWidget(new WBreak());


  /*
   * Color
   */
  addWidget(new WText("<font color='white'>Color</font>"));
  addWidget(new WBreak());
  colo = new WComboBox();

  colo->addItem("Purple");
  colo->addItem("Blue");
  colo->addItem("Red");
  colo->addItem("Green");
  colo->addItem("Yellow");

  addWidget(colo);
  addWidget(new WBreak());
  addWidget(new WBreak());

  /*
   * Brightness
   */
  br = new WSlider();
  br->resize(500, 50);
  br->setTickPosition(Wt::WSlider::TicksAbove);
  br->setTickInterval(20);
  br->setMinimum(0);
  br->setMaximum(254);
  br->setValue(120);

  addWidget(new WText("<font color='white'>Brightness</font>"));
  addWidget(new WBreak());
  addWidget(br);

  //after user comfirm the change
  //pass the data to save method
  //and user return to display page
  WPushButton *butto = new WPushButton("Save");
  butto->clicked().connect(this,&lightWidget::display);
  addWidget(butto);
  
}


/**
  *@brief the method deal with user's changes
  *
  *uses user's chanes to update light's attributs
  *@param none
  *@return void
  */
void lightWidget::save(){

  //switch change method
  int s = (switcH->currentIndex());
  if (s == 0){
    lightBulb[iD].setState(true);
  }else if( s == 1){
    lightBulb[iD].setState(false);
  }


}

/**
  *@brief the method delete light obeject
  *
  *user choose the light obj that they want to delete
  *@param none
  *@return void
  */
void lightWidget::delet(){
  clear();

  delett = new WComboBox();

  //show all lights the user hava so far
  if(iD==0)
    {
    delett->addItem("Nothing");
    }
    
    else
    {
    
        for(int q=1;q<=iD;q++)
    {
      
      delett->addItem(WString("{1}").arg(lights[q]));
    }

    }

  addWidget(delett);

  addWidget(new WBreak());

  WPushButton *button2 = new WPushButton("Delete");

  addWidget(button2);
  button2->clicked().connect(this, &lightWidget::display);

}


