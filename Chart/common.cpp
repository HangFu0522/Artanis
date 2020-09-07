#include"Chart/common.h"
void drawOneChart(QChart* c,QLineSeries *s,std::vector<double> &vectX,std::vector<double> &vectY,std::vector<size_t> &selectIndex,double tran,double offset)
{
    QVector<QPointF> Points;

    double minX=std::numeric_limits<double>::max(),
           maxX=std::numeric_limits<double>::min(),
           minY=std::numeric_limits<double>::max(),
           maxY=std::numeric_limits<double>::min();
    double x,y;
    for(const auto& it: selectIndex)
    {
        x=vectX[it];
        y=vectY[it]*tran+offset;
        minY=(minY<y)?minY:y;
        maxY=(maxY>y)?maxY:y;

        minX=(minX<x)?minX:x;
        maxX=(maxX>x)?maxX:x;

        Points.append(QPointF(x,y));
    }
    s->replace(Points);

    auto axisX = c->axes(Qt::Horizontal);
    axisX.back()->setRange(minX,maxX);
    axisX.back()->setTitleText("time(s)");

    auto axisY = c->axes(Qt::Vertical);
    axisY.back()->setRange(minY,maxY);
    axisY.back()->setTitleText("axisY");
}


void drawOneChart(QChart* c,QLineSeries *s,std::vector<double> &vectX,std::vector<double> &vectY)
{
    QVector<QPointF> Points;

    double minX=std::numeric_limits<double>::max(),
           maxX=std::numeric_limits<double>::min(),
           minY=std::numeric_limits<double>::max(),
           maxY=std::numeric_limits<double>::min();
    double x,y;
    auto it_x =vectX.cbegin();
    auto it_y =vectY.cbegin();
    for(it_x=vectX.cbegin(),it_y=vectY.cbegin();it_x!=vectX.cend();it_x++,it_y++)
    {
        x=*it_x;
        y=*it_y;
        minY=(minY<y)?minY:y;
        maxY=(maxY>y)?maxY:y;

        minX=(minX<x)?minX:x;
        maxX=(maxX>x)?maxX:x;

        Points.append(QPointF(x,y));
    }
    s->replace(Points);

    auto axisX = c->axes(Qt::Horizontal);
    axisX.back()->setRange(minX,maxX);
    axisX.back()->setTitleText("time(s)");

    auto axisY = c->axes(Qt::Vertical);
    axisY.back()->setRange(minY,maxY);
    axisY.back()->setTitleText("axisY");
}

Chart* CreateChart(QLineSeries *s)
{
    Chart *chart = new Chart();
    chart->legend()->hide();
    chart->addSeries(s);
    chart->createDefaultAxes();
    return chart;
}
void initOneChart(QLineSeries *s,Chart *c,ChartView *cv)
{
    s = new QLineSeries();
    s->setUseOpenGL(true);
    c=CreateChart(s);
    cv->setChart(c);
    cv->setRenderHint(QPainter::Antialiasing);
}
