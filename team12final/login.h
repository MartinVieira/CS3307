/**
 * @file doxygen.config
 * @author Weizhi Chen, Jisoo Lee
 * @date Nov 28th, 2017
 * @brief functions for LogIn class
 *
 * Contains various functions associated with LogIn WContainerWidget Class.
 */

#ifndef LOGIN_H_
#define LOGIN_H_
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
#include "menu.h"

using namespace Wt;
using namespace std;

/**
 * @brief WContaingerWidget Class that shows an log in form for user to log in to his/her user account.
 *
 * Contains functions relating with log in and internal pathing. Also contains private variables
 * dealing with text boxes for user to fill in, and buttons for them to interact with.
 */
class LogIn: public WContainerWidget
{
        public:
                LogIn(WContainerWidget *parent=0);
                void login();
                void display();
                void handleInternalPath(const std::string &internalPath);
                void showMenu();
        private:
                // Text boxes for user input
                WLineEdit *userName;
                WLineEdit *password;
    
                WPushButton *log_in;
                WStackedWidget *mainstack;
                WContainerWidget *main;
     			menu *m;
};

#endif //LOGIN_H_
