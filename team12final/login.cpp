/**
 * @file doxygen.config
 * @author Weizhi Chen, Jisoo Lee
 * @date Nov 28th, 2017
 * @brief functions for LogIn class
 *
 * Contains various functions associated with LogIn WContainerWidget Class.
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WTextArea>
#include <Wt/WTextEdit>
#include <Wt/WTemplate>
#include <Wt/WString>
#include <Wt/WLabel>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <Wt/WServer>
#include <cstdlib>
#include <ctime>

#include "user.h"
#include "login.h"
#include "authentication.h"

using namespace Wt;
using namespace std;

User user_profile;   // global variable defined

/**
 * @brief basic constructor for LogIn object
 *
 * This constructor initializes LogIn object with parent WContainerWidget to continue from previous session.
 * @parameters *parent: pointer to WContainerWidget parent
 * @returns LogIn object
 */
LogIn::LogIn(WContainerWidget *parent):WContainerWidget(parent) {
};

/**
 * @brief displays interface for user
 *
 * Displays a form for users to put their infomration to create log in to their user account.
 * @parameters none
 * @returns none
 */
void LogIn::display(){
    clear();
    // clears previous element
    // Style properties
    WApplication::instance()->styleSheet().addRule(".username", "width:15%;margin-left:42.5%;");
    WApplication::instance()->styleSheet().addRule(".password", "width:15%;margin-left:42.5%;-webkit-text-security:disc;");
    WApplication::instance()->styleSheet().addRule(".nothing1", "display:none;");
    WApplication::instance()->styleSheet().addRule(".loginButton", "width:5%;margin-left:46.675%;margin-top:0.5vh;");
    
    //Declare mainstack
    mainstack = new WStackedWidget();
    main = new WContainerWidget();
        
    main->addWidget(new WText("<h1 style='text-align:center;color:white;'>Log In</h1>"));
        main->addWidget(new WBreak());

        WTemplate *result = new WTemplate(WString::tr("lineEdit-template"));
        result->addFunction("id", &WTemplate::Functions::id);

        //User input: Username
        main->addWidget(new WText("<center style='color:white;'>Username: </center>"));
        main->addWidget(userName = new WLineEdit());
        userName->setStyleClass("username");
        main->addWidget(new WBreak());
        //User input: Password
        main->addWidget(new WText("<center style='color:white;'>Password: </center>"));
        main->addWidget(password = new WLineEdit());
        password->setStyleClass("password");
        main->addWidget(new WBreak());

        // Button that links to login function
        main->addWidget(log_in = new WPushButton("Log In"));
        log_in->setStyleClass("loginButton");
        log_in->clicked().connect(this, &LogIn::login);
        log_in->setLink(WLink(WLink::InternalPath,"/menu"));
        
        mainstack->addWidget(main);
        addWidget(mainstack);

};

/**
 * @brief function that logs user in to access user accout
 *
 * Checks the user inputs from the WLineEdit pointers, if the username and password matches from the associated
 * user account, program will render menu page with user account. Else, it shows approporiate message with problems.
 * @parameters none
 * @returns none
 */
void LogIn::login() {

    // Convert all user input to string
    string un = userName->text().toUTF8();
    string pw= password->text().toUTF8();
    
    Authentication loggin; //Declare authentication
        if (loggin.findUser(un)) { //if username exists, continue to password checking
                if (loggin.checkPassword(un, pw)) {
                        user_profile = loggin.login(un); // get user information from database to global variable
                        addWidget(new WBreak());
                        WApplication::instance()->internalPathChanged().connect(this,&LogIn::handleInternalPath);
                        mainstack->addWidget(main);
                        addWidget(mainstack);
                }
                else { //otherwise, print approporiate message
                        addWidget(new WBreak());
                        addWidget(new WText("<center style='color:white;'>Password is incorrect.</center>"));
                }
        }
        else { //otherwise, print approporiate message
                addWidget(new WBreak());
                addWidget(new WText("<center style='color:white;'>Username does not exist.</center>"));
        }

};

/**
 * @brief handles internal pathing
 *
 * handles traversing from one widget to another
 * @parameters const std:: string &internalPath
 * @returns none
 */
void LogIn::handleInternalPath(const std::string &internalPath){
   if(internalPath == "/menu"){
     showMenu();
   }
};

/**
 * @brief displays menu form
 *
 * Displays a Menu WContainerWidget Object from menu.h.
 * @parameters none
 * @returns none
 */
void LogIn::showMenu(){

  m = new menu();
  mainstack->addWidget(m);
  mainstack->setCurrentWidget(m);
  m->display();
};
