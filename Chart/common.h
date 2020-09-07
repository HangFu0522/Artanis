#ifndef COMMON_H
#define COMMON_H


#include"Chart/chart.h"
#include"Chart/chartview.h"
#include<vector>
#include<QLineSeries>
#include<QValueAxis>
void drawOneChart(QChart* c,QLineSeries *s,std::vector<double> &vectX,std::vector<double> &vectY,std::vector<size_t> &selectIndex,double tran=1,double offset=0);
void drawOneChart(QChart* c,QLineSeries *s,std::vector<double> &vectX,std::vector<double> &vectY);
Chart * CreateChart(QLineSeries *s);
void initOneChart(QLineSeries *s,Chart *c,ChartView *cv);
#endif // COMMON_H
