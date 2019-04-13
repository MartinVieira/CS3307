/**
 * @file doxygen.config
 * @author Weizhi Chen, Jisoo Lee
 * @date Nov 28th, 2017
 * @Header file for brief functions for Retrieve class
 *
 * Contains various functions associated with Retrieve WContainerWidget Class.
 */

#ifndef RETRIEVE_H_
#define RETRIEVE_H_
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WIntValidator>
#include <Wt/WStackedWidget>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WTable>
#include <Wt/WTableCell>
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

/**
 * @brief WContaingerWidget Class that shows an password retrival form for user.
 *
 * Contains function that lets user reset the password for the case they forget their password.
 */
class Retrieve: public WContainerWidget
{
        public:
                Retrieve(WContainerWidget *parent=0);
                void display();
                void displayQuestion();
                void displayReset();
                void handleInternalPath(const std::string &internalPath);
                void showRetrieve();
                void displayLogin();
                void showLogIn();
    
    
        private:
                // Text boxes for user input
                WLineEdit *userName;
                WLineEdit *secAnswer;
                WLineEdit *newPassword;
                WLineEdit *confirmPassword;
    
                // Buttons
                WPushButton *subButtonU;
                WPushButton *subButtonA;
                WPushButton *subButtonR;
    
                WStackedWidget *mainstack;
                WContainerWidget *main;
                Retrieve *r;
                LogIn *loginForm;
                WPushButton *log_in;
};

#endif
