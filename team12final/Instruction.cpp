/**
 *@file doxygen.config
 *@author Martin Vieira, Yuhan Zhang Weizhi Chen
 *@date 28 Nov 2017
 *@brief Front end page that gives a new user information regarding the web application
 *
 *Information on how to use the web application is available to the user in the menu
 */

#include "Instruction.h"

using namespace Wt;

/**
 *@brief Instruction container widget
 *
 *A container widget that leads to information for new users
 *@param *parent A pointer object for the button widget
 */
InstructionWidget::InstructionWidget(WContainerWidget *parent):WContainerWidget(parent)
{
    WApplication::instance()->styleSheet().addRule(".white", "color:white;");
}

/**
 *@brief Displays the information to the user
 *
 *Outputs the information for the user on using the web application
 *@param none
 */
void InstructionWidget::update(){
    clear();

    addWidget(new WText("<h2><font color='white'>Instruction</font></h2>"));
    
    addWidget(new WText("<h4 style='color:white'>Welcome</h4>"));
    
    addWidget(new WBreak());
    
    WTabWidget *tabW = new WTabWidget();
    addWidget(tabW);
    
    tabW->addTab(new WText("<table border='1' width='100%'>"
                           "<tr>"
                           "<th style='color:white;'>Using our easy to use web browser platform you can have full control over the lights in your home. Change the color, switch on or off, or even change the brightness of any bulb with one click.</th>"
                           "</tr>"
                           "</table>"),
                 "Bridges");
    tabW->addTab(new WText("<table border='1' width='100%'>"
                           "<tr>"
                           "<th style='color:white;'>This is used to enable your bulbs to communicate with each other, allowing you to control all settings of the lights in your system.</th>"
                           "</tr>"
                           "</table>"),
                 "Lights");
    tabW->addTab(new WText("<table border='1' width='100%'>"
                           "<tr>"
                           "<th style='color:White;'>This is the output of the system. Lights create a mesh network with each other which enables each light to pass on messages to the next. They are connected to the bridge via an open standards protocol.</th>"
                           "</tr>"
                           "</table>"),
                 "Groups");
    tabW->setStyleClass("tabwidget white");
}


