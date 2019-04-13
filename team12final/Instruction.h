/**
 * @file doxygen.config
 * @author Weizhi Chen, Martin, Hejia Tang
 * @date Nov 28th, 2017
 * @brief functions for LogIn class
 *
 * Contains various functions associated with LogIn WContainerWidget Class.
 */

#include <Wt/WContainerWidget>
#include <Wt/WTextArea>
#include <Wt/WText>
#include <Wt/WMenuItem>
#include <Wt/WTabWidget>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WBreak>
#include <Wt/WApplication>
using namespace Wt;

class InstructionWidget: public WContainerWidget
{
 public:
       InstructionWidget(WContainerWidget *parent=0);
       void update();
};
