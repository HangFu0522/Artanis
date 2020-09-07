#ifndef CHARTCONTROL_H
#define CHARTCONTROL_H
#include<vector>
#include<QString>
#include<map>
#include <QObject>
#include<Chart/chartview.h>
class chartControl : public QObject
{
    Q_OBJECT
public:
    explicit chartControl(QObject *parent = nullptr);

    bool addChartView(QString chartName,ChartView* cv_prt);
    bool updataChartView(QString chartName);
    bool updataAllChartView(void);
signals:

public slots:


private:
    std::map<QString,ChartView*> chartNameView_map;
    std::map<QString,ChartView*> chartNamedata_map;
    std::vector<ChartView*> ChartViewVec;
};

#endif // CHARTCONTROL_H
