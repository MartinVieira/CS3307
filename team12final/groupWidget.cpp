/**
  *@file doxygen_c.h
  *@author Martin Vieira & Hejia Tang & Weizhi Chen
  *@date 28 Nov 2017
  *@brief Contains methods that show the group page and add, edit, delete methods send the data to API
  * 
  *Uses Wt widget to display all the groups and control panel   
  *Uses http get, post, and put requests to change the value of a group of bulbs's id, name, brightness, color and state
  */

#include "groupWidget.h"


using namespace Wt;
using namespace std;
// create a color button
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

int gId = 0;

/**
  *@brief Basic constructor for a groupWidget object
  *
  *This contructor initializes a group page with the parent widget
  *@param the parent widget
  *@return void
  */
groupWidget::groupWidget(WContainerWidget *parent):WContainerWidget(parent)
{
}

/**
  *@brief the method to display all the groups
  *
  *@param none
  *@return void
  */
void groupWidget::display(){
  clear();
  
  addWidget(new WText("<h2><font color='white'>Groups</font></h2>"));
  // the tabel to show all the group attrubites
  WTable *group = new WTable();
  group->setWidth(WLength("75%"));
  group->addStyleClass("table form-inline");
  addWidget(group);
    group->elementAt(0, 0)->addWidget(new WText("<b style='color:white;'>Light Name</b>"));
    group->elementAt(0, 1)->addWidget(new WText("<b style='color:white;'>State</b>"));
    group->elementAt(0, 2)->addWidget(new WText("<b style='color:white;'>Brightness</b>"));
    group->elementAt(0, 3)->addWidget(new WText("<b style='color:white;'>Colour</b>"));
    
    
    group->elementAt(1, 0)->addWidget(new WText("<h5 style='color:white;'>default1</h5>"));
    group->elementAt(1, 1)->addWidget(new WText("<h5 style='color:white;'>Off</h5>"));
    group->elementAt(1, 2)->addWidget(new WText("<h5 style='color:white;'>5</h5>"));
    group->elementAt(1, 3)->addWidget(new WText("<h5 style='color:white;'>Red</h5>"));

  //the button direct user to the control panel
  WPushButton *button = new WPushButton("Control");
  button->setLink(WLink(WLink::InternalPath,"/menu/groups/control"));
  button->setMargin(5, Left);
  addWidget(button);
  button->clicked().connect(this,&groupWidget::select);

  WPushButton *buttAdd = new WPushButton("Add");
  buttAdd->setLink(WLink(WLink::InternalPath,"/menu/groups/add"));
  buttAdd->setMargin(5, Left);
  addWidget(button);
  buttAdd->clicked().connect(this,&groupWidget::add);

  WPushButton *buttDele = new WPushButton("Delete");
  buttDele->setLink(WLink(WLink::InternalPath,"/menu/groups/delete"));
  buttDele->setMargin(5, Left);
  buttDele->clicked().connect(this,&groupWidget::deletee);
  addWidget(button);
  addWidget(buttAdd);
  addWidget(buttDele);
  //button->clicked().connect(this,&groupWidget::deletee);
}


/**
  *@brief the method to display the group list
  *
  *@param none
  *@return void
  */
void groupWidget::select(){

   clear();

    // the combo box to show all the groups exist
    cb = new WComboBox();
    cb->addItem("default1");
    cb->addItem("default2");
    cb->addItem("livingRoom1");
    cb->addItem("frontDoor1");
    cb->addItem("default3");
    cb->setMargin(10, Right);

    cb->setCurrentIndex(1);

    addWidget(cb);
    //once user select the group they want to control
    //they are no longer able to select 
    cb->activated().connect(cb, &Wt::WComboBox::disable);
    //pass the data to group
    cb->activated().connect(this, &groupWidget::control);
 
}


/**
  *@brief the method to display the control panel
  *
  *@param none
  *@return void
  */
void groupWidget::control(){

  WApplication::instance()->styleSheet().addRule(".tableheight","height:40vh;");
  WApplication::instance()->styleSheet().addRule(".white","color:white;");

  //the container to contain all the attributes
  WContainerWidget *attri = new WContainerWidget();
  attri->setHeight(400);
  attri->setStyleClass("tableheight");
  attri->addWidget(new WBreak());

  /*
   * Switch
   */
    attri->setStyleClass("white");
  attri->addWidget(new WText("Switch"));
  attri->addWidget(new WBreak());
  bg = new WButtonGroup();
  on = new WRadioButton("On");
  bg->addButton(on);
  off = new WRadioButton("Off");
  bg->addButton(off);
  attri->addWidget(on);
  attri->addWidget(off);
  attri->addWidget(new WBreak());
  attri->addWidget(new WBreak());

  /*
   * Color
   */
  attri->addWidget(new WText("Color"));
  attri->addWidget(new WBreak());
  toolBar = new WToolBar();

  toolBar->addButton(createColorButton("btn-primary","Purple"));
  toolBar->addButton(createColorButton("btn-info","Blue"));
  toolBar->addButton(createColorButton("btn-danger","Red"));
  toolBar->addButton(createColorButton("btn-success","Green"));
  toolBar->addButton(createColorButton("btn-warning","Yellow"));

  attri->addWidget(toolBar);
  attri->addWidget(new WBreak());
  attri->addWidget(new WBreak());

  /*
   * Brightness
   */
  br = new WSlider();
  br->resize(500, 50);
  br->setTickPosition(Wt::WSlider::TicksAbove);
  br->setTickInterval(1);
  br->setMinimum(0);
  br->setMaximum(10);
  br->setValue(5);

  attri->addWidget(new WText("Brightness"));
  attri->addWidget(new WBreak());
  attri->addWidget(br);

  WPushButton *save = new WPushButton("Save");
  save->setLink(WLink(WLink::InternalPath,"/menu/groups"));
  save->setMargin(15, Left);
  save->setMargin(0, Top);
  addWidget(save);
    
  save->clicked().connect(this,&groupWidget::display); 
    
  addWidget(attri);
  
}

/**
  *@brief the widget for user to add the light
  *
  *asks user's input, the light's name and choose which bridge belonging
  *@param none
  *@return void
  */
void groupWidget::add(){
    clear();
    //the table asks user for input 
    a = new WTable();
    a->setWidth(WLength("100%"));
    a->addStyleClass("table form-inline");

    a->elementAt(0, 0)->addWidget(new WText("<b style='color:white'>#</b>"));
    a->elementAt(0, 1)->addWidget(new WText("<b style='color:white'>Name</b>"));

    //auto give the id of light to the user
    a->elementAt(1, 0)->addWidget(new WText(WString("<font color='white'>{1}</font>").arg(gId)));
    a->elementAt(1, 1)->addWidget(gNames = new WLineEdit());

    WString gN = gNames->text();
    string gname = gN.toUTF8();
    groups[gId] = gname;

    addWidget(new WBreak());

    WPushButton *button1 = new WPushButton("Add");

    button1->clicked().connect(this,&groupWidget::display);

    addWidget(a);
    addWidget(new WBreak());
    addWidget(button1);

}

void groupWidget::deletee(){
    clear();

    delett = new WComboBox();

  //show all groups the user hava so far
  if(gId==0)
    {
    delett->addItem("Nothing");
    }
    
    else
    {
    
        for(int q=1;q<=gId;q++)
    {
      
      delett->addItem(WString("{1}").arg(groups[q]));
    }

    }

  addWidget(delett);

  addWidget(new WBreak());

  WPushButton *button2 = new WPushButton("Delete");

  addWidget(button2);
  button2->clicked().connect(this, &groupWidget::display);
}


