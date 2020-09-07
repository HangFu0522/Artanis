#include "GUI/forceextensionchart.h"
#include "ui_forceextensionchart.h"

forceExtensionChart::forceExtensionChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forceExtensionChart)
{
    ui->setupUi(this);
}

forceExtensionChart::~forceExtensionChart()
{
    delete ui;
}
