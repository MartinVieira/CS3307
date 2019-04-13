/**
 * @file doxygen.config
 * @author Weizhi Chen, Jisoo Lee
 * @date Nov 28th, 2017
 * @brief functions for signUp class
 *
 * Contains various functions associated with LogIn WContainerWidget Class.
 */



#ifndef SIGNUP_H_
#define SIGNUP_H_
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WIntValidator>
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

#include "login.h"
#include "authentication.h"

using namespace Wt;
using namespace std;

/**
 * @brief WContaingerWidget Class that shows an sign up form for user to create an user account.
 *
 * Contains functions relating with account creation and internal pathing. Also contains private variables
 * dealing with text boxes for user to fill in, and buttons for them to interact with.
 */
class SignUp: public WContainerWidget
{
        public:
                SignUp(WContainerWidget *parent=0);
                void display();
                void accountCreation();
                void handleInternalPath(const std:: string &internalPath);
                void showLogIn();
        private:
                // Text boxes for user input
                WLineEdit *firstName;
                WLineEdit *lastName;
                WLineEdit *userName;
                WLineEdit *password;
                WLineEdit *confirmation;
                WLineEdit *secQues;
                WLineEdit *secAns;
                WPushButton *sign_up;

                WStackedWidget *mainstack;
                LogIn *loginForm;
                WPushButton *log_in;
};

#endif //SIGHUP_H_
