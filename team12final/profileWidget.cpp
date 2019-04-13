/**
 * @file doxygen.config
 * @authoer Weizei Chen, Heija Tang, Jisoo Lee
 * @date Nov 28th, 2017
 * @brief functions for profileWidget class
 *
 * Contains various functions associated with profileWidget WContainerWidget Class.
 */

#include "profileWidget.h"
#include "authentication.h"
#include <Wt/WApplication>
extern User user_profile;

using namespace Wt;

/**
 * @brief basic constructor for profileWidget object
 *
 * This constructor initializes profileWidget object with parent WContainerWidget to continue from previous session.
 * @parameters *parent: pointer to WContainerWidget parent
 * returns profileWidget object
 */
profileWidget::profileWidget(WContainerWidget *parent):WContainerWidget(parent)
{
};

/**
 * @brief displays profile interactions for user
 *
 * Displays a table which allows user to interact with profile. Users can view and edit profile.
 * @parameters none
 * @returns none
 */
void profileWidget::display(){
    clear(); // clears previous elements
    WApplication::instance()->styleSheet().addRule(".white", "color:white;");
    addWidget(new WText("<h2><font color='White'>Profile</font></h2>"));
    
    // Declare a table
    WTable *info = new WTable();
    info->setWidth(WLength("75%"));
    info->addStyleClass("table form-inline");
    addWidget(info);
    info->setStyleClass("white");
    // Table elements
    info->elementAt(0, 0)->addWidget(new WText("<b>First Name</b>"));
    info->elementAt(1, 0)->addWidget(new WText("<b>Last Name</b>"));
    info->elementAt(2, 0)->addWidget(new WText("<b>Address</b>"));
    info->elementAt(3, 0)->addWidget(new WText("<b>City</b>"));
    info->elementAt(4, 0)->addWidget(new WText("<b>Province</b>"));
    // User information as table elemtns
    info->elementAt(0, 1)->addWidget(new WText(user_profile.getFirstName()));
    info->elementAt(1, 1)->addWidget(new WText(user_profile.getLastName()));
    info->elementAt(2, 1)->addWidget(new WText(user_profile.getAddress()));
    info->elementAt(3, 1)->addWidget(new WText(user_profile.getCity()));
    info->elementAt(4, 1)->addWidget(new WText(user_profile.getProvince()));
    
    // button to edit function
    WPushButton *button = new WPushButton("Edit");
    button->setLink(WLink(WLink::InternalPath,"/menu/profile/edit"));
    button->setMargin(5, Left);
    addWidget(button);
    
    button->clicked().connect(this,&profileWidget::edit);
};

/**
 * @brief displays edit form for profile
 *
 * Displays a form which allows user to input a value to change their user account profile.
 * @parameters none
 * @returns none
 */
void profileWidget::edit(){
    clear(); // clears previous elements
    
    //Declare a table
    WTable *mod = new WTable();
    mod->setWidth(WLength("100%"));
    mod->addStyleClass("table form-inline");
    addWidget(mod);
    
    // Table elements
    mod->elementAt(0, 0)->addWidget(new WText("<b>First Name</b>"));
    mod->elementAt(1, 0)->addWidget(new WText("<b>Last Name</b>"));
    mod->elementAt(2, 0)->addWidget(new WText("<b>Address</b>"));
    mod->elementAt(3, 0)->addWidget(new WText("<b>City</b>"));
    mod->elementAt(4, 0)->addWidget(new WText("<b>Province</b>"));
    // Text box with user information with in them, so when they don't input anything, the previous information
    // is being saved.
    mod->elementAt(0, 1)->addWidget(firstName = new WLineEdit());
    firstName->setText(user_profile.getFirstName());
    mod->elementAt(1, 1)->addWidget(lastName = new WLineEdit());
    lastName->setText(user_profile.getLastName());
    mod->elementAt(2, 1)->addWidget(address = new WLineEdit());
    address->setText(user_profile.getAddress());
    mod->elementAt(3, 1)->addWidget(city = new WLineEdit());
    city->setText(user_profile.getCity());
    mod->elementAt(4, 1)->addWidget(province = new WLineEdit());
    province->setText(user_profile.getProvince());
    
    // button to save function
    WPushButton *button = new WPushButton("Save");
    button->setMargin(5, Left);
    addWidget(button);
    button->setLink(WLink(WLink::InternalPath,"/menu/profile"));
    button->clicked().connect(this,&profileWidget::saveEdit);
};

/**
 * @brief saves the user input
 *
 * Converts all the WTextLine to a string and set it to user profile, then access into database to save the changes.
 * @parameters none
 * returns none
 */
void profileWidget::saveEdit() {
    
    // Convert all WTextLine to string
    string fn = firstName->text().toUTF8();
    string ln = lastName->text().toUTF8();
    string addr = address->text().toUTF8();
    string ct = city->text().toUTF8();
    string prov = province->text().toUTF8();
    
    // Use setter to save the data
    user_profile.setName(fn, ln);
    user_profile.setAddress(addr);
    user_profile.setCity(ct);
    user_profile.setProvince(prov);
    
    Authentication edit; // Declare Authentication
    
    // Save changes to database
    edit.resetProfile(user_profile.getUserName(), user_profile.getFirstName(), user_profile.getLastName(), user_profile.getAddress(), user_profile.getCity(), user_profile.getProvince());
    
    // Display changed profile.
    display();
    
}

