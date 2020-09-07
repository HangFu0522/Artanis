#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include<QFileDialog>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QCheckBox>
#include<QDoubleSpinBox>
#include<QFileSystemModel>
#include<QStandardItemModel>
#include<QWidget>
#include"GUI/forceextensionchart.h"
#include"magneticfieldparameter.h"
#include"optiongui.h"
#include"Data/beadData.h"
#include"GUI/piecegui.h"
#include"Base/base.h"
#include"Chart/chart.h"
#include"Chart/chartview.h"
#include"Chart/chartcontrol.h"
QT_CHARTS_USE_NAMESPACE

class beadData;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
   void importData(void);
   void selectDir(void);
   void selectDirEX(void);
   void selectFile(void);
   void selectData(void);
   void OriginData(void);
   void setOption();
   void exportData();
   void exportStepData();
   void exportTranData();
   void exportSelectData();
   void setMagneticFieldGradient();


private slots:
   void on_action_openFile_triggered();
   void on_pushButton_show_clicked();
   void on_pushButton_show_2_clicked();

private:


    chartControl cm;
    QFileSystemModel filePathModel;

    Ui::MainWindow *ui;

    QLineSeries *series_dX_t,*series_dY_t,*series_dZ_t,*series_dMagnetPos_t,*series_1,*series_2;
    Chart *Chart_dX_t,*Chart_dY_t,*Chart_dZ_t,*Chart_dMagnetPos_t,*Chart_1,*Chart_2;

    QString dir,fileName,dirEx,fileNameEx;

    beadData *bead=nullptr;
    QLabel statusMsg;
    bool fristImportData=true;

    optionGUI *optGUI=nullptr;


    forceExtensionChart *wForceExtensionChart;
    QHBoxLayout *hBoxLayoutForceExtensionChart;

    pieceGUI *wPieceGUI;
    QHBoxLayout *hBoxLayoutPieceGUI;



    void drawChart();
    void drawZChart();

    void initMagneticFieldGradient();
    void initChart();
    std::function<void(int)> creatCheckConnectFunction(QDoubleSpinBox *minDoubleSpinBox,QDoubleSpinBox *maxDoubleSpinBox);

    void selectFilePath(const QModelIndex &index);
    void fastOpenFile(const QModelIndex &index);


};



#endif // MAINWINDOW_H
