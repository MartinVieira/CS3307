#include <Wt/WContainerWidget>
#include <Wt/WTextArea>
#include <Wt/WText>
#include <Wt/WMenuItem>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WString>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WAnchor>
#include "user.h"

using namespace Wt;

/**
 * @brief WContaingerWidget Class that shows profile interactions for user
 *
 * Shows interaction for the user profile, where you can view or edit the user profile.
 */
class profileWidget: public WContainerWidget
{
public:
    profileWidget(WContainerWidget *parent=0);
    void handleInternalPath(const std::string &internalPath);
    void display();
    void edit();
    void saveEdit();
private:
    // Text boxes for user inputs
    WLineEdit *firstName;
    WLineEdit *lastName;
    WLineEdit *address;
    WLineEdit *city;
    WLineEdit *province;
};

