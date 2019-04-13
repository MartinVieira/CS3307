/**
 * @file doxygen.config
 * @authoer Weizhi Chen Jisoo Lee
 * @date Nov 28th, 2017
 * @brief main application page
 *
 * Main WApplication page that gives options for user to interact with log in, sign up, or retrival of password
 */
#include <Wt/WApplication>
#include <Wt/WBorderLayout>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WIntValidator>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WTable>
#include <Wt/WAnchor>
#include <Wt/WStackedWidget>
#include <Wt/WTableCell>
#include <Wt/WBootstrapTheme>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <Wt/WServer>
#include <cstdlib>
#include <ctime>
#include <Wt/WImage>
#include <Wt/WTextArea>
#include <Wt/WTemplate>
#include <Wt/WCssDecorationStyle>
#include <Wt/WTextEdit>
#include "login.h"
#include "signup.h"
#include "user.h"
#include "Retrieve.h"

using namespace Wt;
Wt::WImage *img;

/**
 * @brief WApplication Class that shows various options for user
 *
 * Contains various options for user to interact with. Such as log in, sign up, and retrieve password.
 */

class welcomePage : public WApplication {

        public:
                welcomePage(const WEnvironment& env);
                void handleInternalPath(const std::string &internalPath);
        private:
                WStackedWidget *mainstack;
                LogIn *loginForm;
                SignUp *signupForm;
             Retrieve *retrieveForm;
    // buttons for options
            WPushButton *log_in;
                WPushButton *sign_up;
                WPushButton *retrieve;
    // Options for user

                void showLogIn();
                void showSignUp();
                void showRetrieve();
    // background image
               Wt::WImage *background;
};

/**
 * @brief constructor for WApplication welcomePage
 *
 * Main page which will show user logo, background image, options, and description of what this project is. Options
 * include log in, sign up, retrieve password which are all being interacted with buttons.
 * @parameters const WEnvironment& env
 * @returns WelcomePage WApplication object
 */


welcomePage::welcomePage(const WEnvironment& env):WApplication(env) {
    // Style properties
    WApplication::instance()->styleSheet().addRule(".loginbox", "width:5%;margin-left:39%;");
    WApplication::instance()->styleSheet().addRule(".signupbox", "width:8%;margin-left:38%;margin-right:2%");
     WApplication::instance()->styleSheet().addRule(".retrieve", "width:8%;");
    WApplication::instance()->styleSheet().addRule(".logo", "margin-left:31.5%;margin-top:-3%;margin-bottom:-5%;height:40%;width:35%");
    WApplication::instance()->styleSheet().addRule(".nothing", "display:none;");
    WApplication::instance()->styleSheet().addRule(".background", "width:100%;height:200vh;margin-bottom:-185vh;background-image:url(https://images8.alphacoders.com/424/thumb-1920-424604.jpg);");
    
    
    // Declare mainstack
    mainstack = new WStackedWidget;
        setTitle("Limelite");
        setTheme(new WBootstrapTheme());
       // Declare background image
    background=new WImage("",root());
    background->setStyleClass("background");
   
     // Declare logo image
    root()->addWidget(new WText("<center style='margin-top:1%'><h1 style='font-size:8vh;text-align:center;color:white;'>Welcome To</h1></center>"));
    img=new Wt::WImage("https://c1.staticflickr.com/5/4576/26829747359_8c7176a359_o.png", root());
    img->setStyleClass("logo centered");
    img->setAlternateText("lol");
   
    
    root()->addWidget(new WText("<center style='text-align:center;margin-top:1.5%;margin-left:30%;margin-right:30%;margin-bottom:2.5%;color:white;'>Philips Hue is your personal wireless lighting system that lets you easily control your light and create the right ambiance  for every moment. Bring your smart home to life with the most connected light in the world.</center>"));
    
    //Log in option
    WPushButton *log_in = new WPushButton("Log In");
         log_in->setLink(WLink(WLink::InternalPath, "/login"));
       log_in->setStyleClass("loginbox");
      mainstack->addWidget(log_in);
      log_in->setMargin(660,Left);
      log_in->setMargin(40,Top);
    
    
    
 //Sign Up option
        WPushButton *sign_up = new WPushButton("Sign Up");
        sign_up->setLink(WLink(WLink::InternalPath, "/signup"));
       sign_up->setStyleClass("signupbox");
        root()->addWidget(sign_up);
    //Retrieve option
   WPushButton *retrieve = new WPushButton("Lost Password");
    retrieve->setLink(WLink(WLink::InternalPath, "/Retrieve"));
    retrieve->setStyleClass("retrieve");
    root()->addWidget(retrieve);
    
//internal path handling
        WApplication::instance()->internalPathChanged().connect(this, &welcomePage::handleInternalPath);

        root()->addWidget(mainstack);
}

/**
 * @brief handles internal pathing
 *
 * handles traversing from one widget to another
 * @parameters const std:: string &internalPath
 * @returns none
 */

void welcomePage::handleInternalPath(const std:: string &internalPath) {
        if (internalPath == "/signup") {
            
                showSignUp();
        }
        else if (internalPath == "/login") {
            
                showLogIn();
        }
       else if (internalPath =="/Retrieve")
       {
             showRetrieve();
       }
}
/**
 * @brief displays log in form
 *
 * Displays a LogIn WContainerWidget Object from login.h.
 * @parameters none
 * @returns none
 */
void welcomePage::showLogIn() {
    
    img->setStyleClass("nothing");
        loginForm = new LogIn();
        mainstack->addWidget(loginForm);
        mainstack->setCurrentWidget(loginForm);
        loginForm->display();
   
  
}
/**
 * @brief displays sign up form
 *
 * Displays a LogIn WContainerWidget Object from signup.h.
 * @parameters none
 * @returns none
 */

void welcomePage::showSignUp() {
        img->setStyleClass("nothing");
        signupForm = new SignUp();
        mainstack->addWidget(signupForm);
        mainstack->setCurrentWidget(signupForm);
        signupForm->display();
}
/**
 * @brief displays retrieve form
 *
 * Displays a LogIn WContainerWidget Object from retrieve.h.
 * @parameters none
 * @returns none
 */
void welcomePage::showRetrieve(){
     img->setStyleClass("nothing");
    retrieveForm=new Retrieve();
    mainstack->addWidget(retrieveForm);
    mainstack->setCurrentWidget(retrieveForm);
    retrieveForm->display();
    
}
/**
 * @brief creates a new WApplication
 *
 * Displays WelcomePage WApplication Object
 * @parameters const WEnvironment& env
 * @returns WApplication WelcomePage(env)
 */

WApplication *createApplication(const WEnvironment& env){
        return new welcomePage(env);
}
/**
 * @brief runs the application
 *
 * Runs a WApplication using createApplication
 * @parameters int argc
 *             char **argv
 * returns integer value to see if createApplication ran or not
 */
int main(int argc, char **argv)
{
        return WRun(argc, argv, &createApplication);
}
