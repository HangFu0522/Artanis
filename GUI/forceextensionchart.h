#ifndef FORCEEXTENSIONCHART_H
#define FORCEEXTENSIONCHART_H

#include <QWidget>

namespace Ui {
class forceExtensionChart;
}

class forceExtensionChart : public QWidget
{
    Q_OBJECT

public:
    explicit forceExtensionChart(QWidget *parent = 0);
    ~forceExtensionChart();

private:
    Ui::forceExtensionChart *ui;
};

#endif // FORCEEXTENSIONCHART_H
