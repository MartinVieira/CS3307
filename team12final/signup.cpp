/**
 * @file doxygen.config
 * @authoer Weizhi Chen, Jisoo Lee
 * @date Nov 28th, 2017
 * @brief functions for SignUp class
 *
 * Contains various functions associated with SignUp WContainerWidget Class.
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

#include "signup.h"
#include "authentication.h"

using namespace Wt;
using namespace std;

/**
 * @brief basic constructor for SignUp object
 *
 * This constructor initializes SignUp object with parent WContainerWidget to continue from previous session.
 * @parameters *parent: pointer to WContainerWidget parent
 * @returns SignUp object
 */
SignUp::SignUp(WContainerWidget *parent):WContainerWidget(parent) {
};

/**
 * @brief displays interface for user
 *
 * Displays a form for users to put their infomration to create user account.
 * @parameters none
 * @returns none
 */
void SignUp::display() {
    clear();// clears previous elements
    // Style properties

    WApplication::instance()->styleSheet().addRule(".fn", "width:13%;margin-left:43%;");
    WApplication::instance()->styleSheet().addRule(".ln", "width:13%;margin-left:43%;");
    WApplication::instance()->styleSheet().addRule(".un", "width:13%;margin-left:43%;");
    WApplication::instance()->styleSheet().addRule(".pass", "width:13%;margin-left:43%;-webkit-text-security:disc;");
    WApplication::instance()->styleSheet().addRule(".conpas", "width:13%;margin-left:43%;-webkit-text-security:disc;");
    WApplication::instance()->styleSheet().addRule(".securquest", "width:13%;margin-left:43%;");
    WApplication::instance()->styleSheet().addRule(".securan", "width:13%;margin-left:43%;");
    WApplication::instance()->styleSheet().addRule(".signupButton", "width:5%;margin-left:47.25%;");
    WApplication::instance()->styleSheet().addRule(".llogButton", "width:5%;margin-left:47.25%;");
    
        // Declare mainstack
        mainstack = new WStackedWidget();
    addWidget(new WText("<center><h1 style='color:white;'>Sign Up</h1></center>"));
        addWidget(new WBreak());

    //User input: First name
    addWidget(new WText("<center style='color:white;'>Firstname:</center> "));
    addWidget(firstName = new WLineEdit());
    firstName->setStyleClass("fn");
    addWidget(new WBreak());
    //User input: Last name
    addWidget(new WText("<center style='color:white;'>Lastname:</center> "));
    addWidget(lastName = new WLineEdit());
    lastName->setStyleClass("ln");
    addWidget(new WBreak());
    //User input: Username
    addWidget(new WText("<center style='color:white;'>Username:</center> "));
    addWidget(userName = new WLineEdit());
    userName->setStyleClass("un");
    addWidget(new WBreak());
    //User input: Password
    addWidget(new WText("<center style='color:white;'>Password:</center> "));
    addWidget(password = new WLineEdit());
    password->setStyleClass("pass");
    addWidget(new WBreak());
    //User input: Confirmation Password
    addWidget(new WText("<center style='color:white;'>Confirm password:</center> "));
    addWidget(confirmation = new WLineEdit());
    confirmation->setStyleClass("conpas");
    addWidget(new WBreak());
    //User input: Security Question
    addWidget(new WText("<center style='color:white;'>Security Question:</center> "));
    addWidget(secQues = new WLineEdit());
    secQues->setStyleClass("securquest");
    addWidget(new WBreak());
    //User input: Security Answer
    addWidget(new WText("<center style='color:white;'>Security Answer:</center> "));
    addWidget(secAns = new WLineEdit());
    secAns->setStyleClass("securan");
    addWidget(new WBreak());

    //Button that links to function accountCreation
    addWidget(sign_up = new WPushButton("Sign Up"));
    sign_up->clicked().connect(this, &SignUp::accountCreation);
    sign_up->setStyleClass("signupButton");
};

/**
 * @brief function that creates user accout
 *
 * Checks the user inputs from the WLineEdit pointers, if the password and confirmation match, and username is not
 * taken, create account and show user button to log in. Else, show them proper message saying there was problem.
 * @parameters none
 * @returns none
 */
void SignUp::accountCreation() {

    // Convert all user inputs to string
    string fn = firstName->text().toUTF8();
    string ln = lastName->text().toUTF8();
    string un = userName->text().toUTF8();
    string sq = secQues->text().toUTF8();
    string sa = secAns->text().toUTF8();
    string pw= password->text().toUTF8();
    string cp= confirmation->text().toUTF8();

    // Ask user to put all information in
    if (un == "" || ln == "" || un == "" || sq == "" || sa == "" || pw == "" || cp == "") {
        addWidget(new WBreak());
        addWidget(new WText("<center style='color:white;'>Please fill in all information</center>"));
    }
    else if (pw == cp) { // Go check if username already exists if password and confirmation matches
        Authentication create;  //Declare authentication object
        
        if (!create.findUser(un)) {   //user name is not taken, create account
            create.createAccount(fn, ln, un, pw, sq, sa);   //create new user account
            addWidget(new WBreak());
            addWidget(new WText("<center style='color:white;'>Account created, log in please</center>"));
            addWidget(new WBreak());
            // Button to log in
            addWidget(log_in = new WPushButton("Log In"));
            log_in->setStyleClass("llogButton");
            log_in->setLink(WLink(WLink::InternalPath,"/login"));
        }
        else {  //username is taken. Send message saying name is already taken
            addWidget(new WBreak());
            addWidget(new WText("<center style='color:white;'>Username already exists</center>"));
        }
        
    }
    else {  // They do not match, message user saying it was incorrect
        addWidget(new WBreak());
        addWidget(new WText("<center style='color:white;'>Passwords does not match.</center>"));
    }
};

/**
 * @brief displays log in form
 *
 * Displays a LogIn WContainerWidget Object from login.h.
 * @parameters none
 * @returns none
 */
void SignUp::showLogIn() {
        loginForm = new LogIn();
        mainstack->addWidget(loginForm);
        mainstack->setCurrentWidget(loginForm);
        loginForm->display();
};

/**
 * @brief handles internal pathing
 *
 * handles traversing from one widget to another
 * @parameters const std:: string &internalPath
 * @returns none
 */
void SignUp::handleInternalPath(const std:: string &internalPath) {
        if (internalPath == "/login") {
                showLogIn();
        }
};
