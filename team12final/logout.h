/**
 * @file doxygen.config
 * @author Weizhi Chen, Hejia Tang
 * @date Nov 28th, 2017
 * @brief functions for Logout class
 *
 */
#include <Wt/WContainerWidget>
#include <Wt/WTextArea>
#include <Wt/WText>
#include <Wt/WMenuItem>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>

using namespace Wt;

class logout: public WContainerWidget
{
 public:
     logout(WContainerWidget *parent=0); 
     void display();
     void logOut();
};
