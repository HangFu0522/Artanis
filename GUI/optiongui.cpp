#include "optiongui.h"
#include "ui_optiongui.h"

optionGUI::optionGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionGUI)
{
    ui->setupUi(this);
}

optionGUI::~optionGUI()
{
    delete ui;
}
