/**
 * @file doxygen.config
 * @authoer Weizei Chen, Heija Tang
 * @date Nov 28th, 2017
 * @brief display of options
 *
 * Displays various options for user to interact with.
 */

#include "menu.h"

using namespace Wt;

/**
 * @brief basic constructor for menu object
 *
 * This constructor initializes menu object with parent WContainerWidget to continue from previous session.
 * @parameters *parent: pointer to WContainerWidget parent
 * @returns menu object
 */
menu::menu(WContainerWidget *parent):WContainerWidget(parent)
{
}

/**
 * @brief displays menu interface for user
 *
 * Displays a menu bar for users to interact with various options such as instruction, profile, bridge, groups,
 * light, schedule, and logout.
 * @parameters none
 * @returns none
 */
void menu::display(){
    clear();// clears previous elements
    
    //declare mainstack
    mainstack = new WStackedWidget;
    box = new WBoxLayout(Wt::WBoxLayout::LeftToRight);
    WApplication::instance()->styleSheet().addRule(".white", "color:white;");
    WStackedWidget *contents = new WStackedWidget();
 
    //Declare a menu
    WMenu *m=new WMenu(contents);
    // Styles for menu
    m->setStyleClass("nav nav-pills nav-stacked white");
    m->setWidth(150);
    
    //Options for menu
    m->addItem("Instruction")->setLink(WLink(WLink::InternalPath,"/menu/instruction"));
    m->addItem("User Profile")->setLink(WLink(WLink::InternalPath,"/menu/profile"));
    WApplication::instance()->internalPathChanged().connect(this,&menu::handleInternalPath);
    m->addItem("Bridge")->setLink(WLink(WLink::InternalPath,"/menu/bridge"));
    m->addItem("Groups")->setLink(WLink(WLink::InternalPath,"/menu/groups"));
    m->addItem("Light")->setLink(WLink(WLink::InternalPath,"/menu/light"));
    m->addItem("Schedule")->setLink(WLink(WLink::InternalPath,"/menu/schedule"));
    m->addItem("Log Out")->setLink(WLink(WLink::InternalPath,"/menu/logout"));
    addWidget(m);
    addWidget(mainstack);
    box->addWidget(m);
    box->addWidget(mainstack,1);
    this->setLayout(box);
    
}

/**
 * @brief handles internal pathing
 *
 * handles traversing from one widget to another
 * @parameters const std:: string &internalPath
 * @returns none
 */
void menu::handleInternalPath(const std::string &internalPath){
   if(internalPath == "/menu/profile"){
     menu::showProfile();
   }else if(internalPath == "/menu/bridge"){
     menu::showBridge();
   }
   else if(internalPath =="/menu/light"){
     menu::showLight();
   }else if(internalPath =="/menu/instruction"){
      menu::showInstruction();
   }else if(internalPath =="/menu/logout"){
      menu::showLogout();
   }else if(internalPath =="/menu/groups"){
      menu::showGroups();
   }
   else if(internalPath =="/menu/schedule"){
       menu::showSchedule();
    }
}

/**
 * @brief displays profile form
 *
 * Displays a profilWidget WContainerWidget Object from profileWidget.h.
 * @parameters none
 * @returns none
 */
void menu::showProfile(){
    profile = new profileWidget();
    mainstack->addWidget(profile);
    mainstack->setCurrentWidget(profile);
    //hbox->addWidget(std::move(profile));
    profile->display();
}

/**
 * @brief displays bridge form
 *
 * Displays a bridgeWidget WContainerWidget Object from bridgeWidget.h.
 * @parameters none
 * @returns none
 */
void menu::showBridge(){
    bridge = new bridgeWidget();
    mainstack->addWidget(bridge);
    mainstack->setCurrentWidget(bridge);
    bridge->display();
}

/**
 * @brief displays light form
 *
 * Displays a lightWidget WContainerWidget Object from lightWidget.h.
 * @parameters none
 * @returns none
 */
void menu::showLight(){
    light = new lightWidget();
    mainstack->addWidget(light);
    mainstack->setCurrentWidget(light);
    light->display();
}

/**
 * @brief displays group form
 *
 * Displays a groupWidget WContainerWidget Object from groupWidget.h.
 * @parameters none
 * @returns none
 */
void menu::showGroups(){
    groups = new groupWidget();
    mainstack->addWidget(groups);
    mainstack->setCurrentWidget(groups);
    groups->display();
}

/**
 * @brief displays instruction form
 *
 * Displays a InstructionWidget WContainerWidget Object from InstructionWidget.h.
 * @parameters none
 * @returns none
 */
void menu::showInstruction(){
    ins = new InstructionWidget();
    mainstack->addWidget(ins);
    mainstack->setCurrentWidget(ins);
    ins->update();
}

/**
 * @brief displays logout form
 *
 * Displays a logout WContainerWidget Object from logout.h.
 * @parameters none
 * @returns none
 */
void menu::showLogout(){
    out = new logout();
    mainstack->addWidget(out);
    mainstack->setCurrentWidget(out);
    out->display();
}

/**
 * @brief displays schedule form
 *
 * Displays a scheduleWidget WContainerWidget Object from scheduleWidget.h.
 * @parameters none
 * @returns none
 */
void menu::showSchedule(){
    schedule = new scheduleWidget();
    mainstack->addWidget(schedule);
    mainstack->setCurrentWidget(schedule);
    schedule->display();
}











