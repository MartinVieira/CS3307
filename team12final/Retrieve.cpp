/**
 * @file doxygen.config
 * @author Weizhi Chen, Jisoo Lee
 * @date Nov 28th, 2017
 * @brief functions for Retrieve class
 *
 * Contains various functions associated with Retrieve WContainerWidget Class.
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

#include "Retrieve.h"
#include "authentication.h"

using namespace Wt;
using namespace std;

/**
 * @brief basic constructor for Retrieve object
 *
 * This constructor initializes Retrieve object with parent WContainerWidget to continue from previous session.
 * @parameters *parent: pointer to WContainerWidget parent
 * @returns Retrieve object
 */
Retrieve::Retrieve(WContainerWidget *parent):WContainerWidget(parent) {
};

/**
 * @brief displays interface for users for retriving password.
 *
 * Displays a form for user to put their username, then press submit to proceeed to next step
 * @parameters none
 * @returns none
 */
void Retrieve::display() {
    clear(); // clear previous elements
    // Style properties
    WApplication::instance()->styleSheet().addRule(".user", "margin-top:1.5vh;margin-left:42%;");
    WApplication::instance()->styleSheet().addRule(".sea", "margin-top:1.5vh;margin-left:42%;");
    WApplication::instance()->styleSheet().addRule(".submitButton", "margin-top:0.8vh;width:5%;margin-left:47.25%;");
    
        // Declare mainstack
        mainstack = new WStackedWidget();
        addWidget(new WText("<center><h1 style='color:white;'>Retrieve Password</h1></center>"));
        addWidget(new WBreak());

        WTemplate *result = new WTemplate(WString::tr("lineEdit-template"));
        result->addFunction("id", &WTemplate::Functions::id);
    
        //User input: Username
        addWidget(new WText("<center style='color:white;'>Please Enter Your UserName:</center> "));
        addWidget(userName = new WLineEdit());
        userName->setStyleClass("user");
        addWidget(new WBreak());

        //Button to next step, which shows security question
        addWidget(subButtonU = new WPushButton("Submit"));
        subButtonU->setStyleClass("submitButton");
        addWidget(new WBreak());
         subButtonU->clicked().connect(this, &Retrieve::displayQuestion);
}

/**
 * @brief displays another text and text boxes
 *
 * Displays security question associated with the username and text box where user inputs a security answer based
 * on security question
 * @parameters none
 * @returns none
 */
void Retrieve::displayQuestion()
{
    // convert text box content to string
    string un = userName->text().toUTF8();
    
    Authentication retrieve; // Declare Authentication
    
    if (retrieve.findUser(un)) { // if user exists, then show security question with text box for answer
        //Security question
        addWidget(new WText("<center style='color:white;'>" + retrieve.getSecQues(un) + "</center> "));
        
        //User input: Security Answer
        addWidget(secAnswer = new WLineEdit());
        secAnswer->setStyleClass("sea");
        addWidget(new WBreak());
        
        //Button to next step, which allows user to reset their password
        addWidget(subButtonA = new WPushButton("Submit"));
        subButtonA ->setStyleClass("submitButton");
        addWidget(new WBreak());
        subButtonA->clicked().connect(this, &Retrieve::displayReset);
    }
    else { //otherwise, send proper message
        addWidget(new WText("<center style='color:white;'>Username does not exist.</center> "));
    }


}

/**
 * @brief display another text boxes
 *
 * Displays text boxes for users, where they input a new password they wish to change to, and confirmation
 * password.
 * @parameters none
 * @returns none
 */
void Retrieve::displayReset()
{
    // convert text box content to string
    string un = userName->text().toUTF8();
    string sa = secAnswer->text().toUTF8();
    
    Authentication retrieve; // Declare Authentication
    
    if (retrieve.getSecAns(un) == sa) { // if user answer was correct, allow user to enter in values
        //User Input: New Password
        addWidget(new WText("<center style='color:white;'>Please enter your new password:</center> "));
        addWidget(newPassword= new WLineEdit());
        newPassword->setStyleClass("sea");
        addWidget(new WBreak());
        //User Input: Confirmation Password
        addWidget(new WText("<center style='color:white;'>Confirm the entered password:</center> "));
        addWidget(confirmPassword= new WLineEdit());
        confirmPassword->setStyleClass("sea");
        addWidget(new WBreak());
        
        // Button to next step, which displays them button to log in
        addWidget(subButtonR = new WPushButton("Submit"));
        subButtonR->setStyleClass("submitButton");
        addWidget(new WBreak());
        subButtonR->clicked().connect(this, &Retrieve::displayLogin);
    }
    else { // otherwise, send proper message
        addWidget(new WText("<center style='color:white;'>That is an incorrect answer.</center> "));
    }
    
}

/**
 * @brief display another text and button
 *
 * Displays text for user, and a button that links to the log in form.
 * @parameters none
 * @returns none
 */
void Retrieve::displayLogin()
{
    // convert text box content to string
    string un = userName->text().toUTF8();
    string pw = newPassword->text().toUTF8();
    string cpw = confirmPassword->text().toUTF8();
    
    Authentication retrieve; // Declare Authentication
    
    if (pw == cpw) { // if password and confirmation password matches, show user button to log in
        retrieve.resetPassword(un, pw); //reset password
        addWidget(new WText("<center style='color:white;'>Password changed, log in please</center>"));
        addWidget(new WBreak());
        //Button to log in
        addWidget(log_in = new WPushButton("Log In"));
        log_in->setStyleClass("submitButton");
        log_in->setLink(WLink(WLink::InternalPath,"/login"));
    }
    else { // otherwise, send proper message
        addWidget(new WText("<center style='color:white;'>Confirmation password does not match new password.</center> "));
    }
};

/**
 * @brief handles internal pathing
 *
 * handles traversing from one widget to another
 * @parameters const std:: string &internalPath
 * @returns none
 */
void Retrieve::handleInternalPath(const std:: string &internalPath) {
    if (internalPath == "/login") {
        showLogIn();
    }
};

/**
 * @brief displays log in form
 *
 * Displays a LogIn WContainerWidget Object from login.h.
 * @parameters none
 * @returns none
 */
void Retrieve::showLogIn() {
    loginForm = new LogIn();
    mainstack->addWidget(loginForm);
    mainstack->setCurrentWidget(loginForm);
    loginForm->display();
};
