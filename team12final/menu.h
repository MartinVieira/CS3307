/**
 * @file doxygen.config
 * Header file for menu
 * @authoer Weizei Chen, Heija Tang
 * @date Nov 28th, 2017
 * @brief display of options
 *
 * Displays various options for user to interact with.
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WTextArea>
#include <Wt/WBootstrapTheme>
#include <Wt/WAnchor>
#include <Wt/WBoxLayout>
#include "scheduleWidget.h"
#include "profileWidget.h"
#include "bridgeWidget.h"
#include "lightWidget.h"
#include "Instruction.h"
#include "groupWidget.h"
#include "logout.h"


using namespace Wt;

/**
 * @brief WContaingerWidget Class that shows various options as an logged in user.
 *
 * Contains various options for users to interact with. They can interact with instruction, profile, bridge,
 * lights, groups, and logout
 */
class menu: public WContainerWidget
{
  public:
     menu(WContainerWidget *parent=0);
     void handleInternalPath(const std::string &internalPath);
     void display();
     void showProfile();
     void showBridge();
     void showLight();
     void showInstruction();
     void showGroups();
     void showLogout();
    void showSchedule();
  private:
     WStackedWidget *mainstack;
    
    // Options
     profileWidget  *profile;
     bridgeWidget  *bridge;
     lightWidget  *light;
     InstructionWidget *ins;
     groupWidget *groups;
     logout *out;
     scheduleWidget *schedule;
    
     WBoxLayout *box;
};
