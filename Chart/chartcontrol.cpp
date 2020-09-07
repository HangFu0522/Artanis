#include "chartcontrol.h"

chartControl::chartControl(QObject *parent) : QObject(parent)
{

}
bool chartControl::addChartView(QString chartName,ChartView* cv_prt)
{
     auto iter1 = chartNameView_map.find(chartName);
     if(iter1==chartNameView_map.end())
     {
         //元素已存在
     }
     chartNameView_map[chartName]=cv_prt;
     return true;
}
