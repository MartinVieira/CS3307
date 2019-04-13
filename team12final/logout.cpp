/**
 * @file doxygen.config
 * @author Weizhi Chen, Hejia Tang
 * @date Nov 28th, 2017
 * @brief functions for LogIn class
 *
 * Contains various functions associated with LogIn WContainerWidget Class.
 */



#include "logout.h"


using namespace Wt;

logout::logout(WContainerWidget *parent):WContainerWidget(parent)
{
}

void logout::display(){
    clear();

    addWidget(new WText("<h2><font color='white'>Log Out</font></h2>"));
    
    addWidget(new WText("<font style='color:white;'>Do you want to log out?</font>"));
    
    WPushButton *y = new WPushButton("Yes");
    y->setLink(WLink("http://localhost:8080/"));
    y->setMargin(5, Left);
    y->clicked().connect(this,&logout::logOut);
    addWidget(y);
    
    WPushButton *n = new WPushButton("No");
    n->setLink(WLink(WLink::InternalPath,"/menu"));
    n->setMargin(5, Left);
    addWidget(n);
    
}

void logout::logOut(){
    
}

