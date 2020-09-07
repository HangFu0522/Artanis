#include"mainwindow.h"
#include "ui_mainwindow.h"
#include "forceextensionchart.h"
#include<QFileInfo>
#include<qobject.h>
#include"QString"
#include"customtabstyle.h"
#include<functional>
#include"magneticfieldparameter.h"
#include<limits>
#include"optiongui.h"
#include<Chart/common.h>
QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    magneticFieldGradient::a=0.038822435993575974;
    magneticFieldGradient::b=-0.14755065554053148;
    magneticFieldGradient::M=-5.614652197914152;        //myone20180831
	
    ui->setupUi(this);
    ui->doubleSpinBox_offset->setEnabled(false);

    hBoxLayoutForceExtensionChart=new QHBoxLayout(ui->widgetFEC);
    wForceExtensionChart=new forceExtensionChart();
    hBoxLayoutForceExtensionChart->addWidget(wForceExtensionChart);


    hBoxLayoutPieceGUI=new QHBoxLayout(ui->widgetPieceGUI);
    wPieceGUI=new pieceGUI(bead);
    hBoxLayoutPieceGUI->addWidget(wPieceGUI);



    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

     //设置状态栏
    statusBar()->addWidget(&statusMsg);

    //设置树形目录
    QDir defaultWorkPath("D:/CO");
    if(!defaultWorkPath.exists())
    {
        filePathModel.setRootPath("");
    }
    else
    {
        filePathModel.setRootPath("D:/CO");
        statusMsg.setText("Use Default Work Path");
    }
    ui->treeView_DirTree->setModel(&filePathModel);
    ui->treeView_DirTree->setAnimated(true);
    ui->treeView_DirTree->setSortingEnabled(true);


    //初始化磁场梯度
    initMagneticFieldGradient();


    //初始化所有的图表
    initChart();

    QObject::connect(ui->treeView_DirTree, &QTreeView::clicked,this,&MainWindow::selectFilePath);
    QObject::connect(ui->treeView_DirTree, &QTreeView::doubleClicked,this,&MainWindow::fastOpenFile);
    QObject::connect(ui->pushButton_Import, &QPushButton::clicked,this,&MainWindow::importData);
    QObject::connect(ui->pushButton_Export, &QPushButton::clicked,this,&MainWindow::exportData);
    QObject::connect(ui->pushButton_SelectDir, &QPushButton::clicked,this,&MainWindow::selectDir);
    QObject::connect(ui->pushButton_SelectDirEX, &QPushButton::clicked,this,&MainWindow::selectDirEX);
    QObject::connect(ui->pushButton_SelectFile, &QPushButton::clicked,this,&MainWindow::selectFile);
    QObject::connect(ui->pushButton_Select,&QPushButton::clicked,this,&MainWindow::selectData);
    QObject::connect(ui->pushButtonOrigin,&QPushButton::clicked,this,&MainWindow::OriginData);
    QObject::connect(ui->doubleSpinBox_offset,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[&](double offset){bead->setOffset(offset);drawZChart();});
    QObject::connect(ui->doubleSpinBox_Rbead,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[&](double Rbead){bead->setR_bead(Rbead);});
    QObject::connect(ui->doubleSpinBox_Ztran,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[&](double Ztran){bead->setZ_tran(Ztran);drawZChart();});


    QObject::connect(ui->action_option,&QAction::triggered,this,&MainWindow::setOption);

    QObject::connect(ui->checkBox_Time, &QCheckBox::stateChanged,MainWindow::creatCheckConnectFunction(ui->minTime,ui->maxTime));
    QObject::connect(ui->checkBox_MP, &QCheckBox::stateChanged,MainWindow::creatCheckConnectFunction(ui->minMP,ui->maxMP));
    QObject::connect(ui->checkBox_MA, &QCheckBox::stateChanged,MainWindow::creatCheckConnectFunction(ui->minMA,ui->maxMA));
    QObject::connect(ui->checkBox_reX, &QCheckBox::stateChanged,MainWindow::creatCheckConnectFunction(ui->min_reX,ui->max_reX));
    QObject::connect(ui->checkBox_reY, &QCheckBox::stateChanged,MainWindow::creatCheckConnectFunction(ui->min_reY,ui->max_reY));
    QObject::connect(ui->checkBox_reZ, &QCheckBox::stateChanged,MainWindow::creatCheckConnectFunction(ui->min_reZ,ui->max_reZ));
}

void MainWindow::selectFilePath(const QModelIndex &index)
{
    ui->lineEdit_FileName->setText(index.data().toString());
    //QFileSystemModel* model=static_cast<QFileSystemModel*>(ui->treeView_DirTree->model());
    statusMsg.setText(QString::number(index.column(), 10));
}

void MainWindow::fastOpenFile(const QModelIndex &index)
{
    ui->lineEdit_FileName->setText(index.data().toString());
    //QFileSystemModel* model=static_cast<QFileSystemModel*>(ui->treeView_DirTree->model());
    statusMsg.setText(QString::number(index.column(), 10));
    importData();
}


void MainWindow::initChart()
{

    series_dX_t = new QLineSeries();
    series_dX_t->setUseOpenGL(true);
    Chart_dX_t=CreateChart(series_dX_t);
    ui->dX_t->setChart(Chart_dX_t);
    ui->dX_t->setRenderHint(QPainter::Antialiasing);

    series_dY_t = new QLineSeries();
    series_dY_t->setUseOpenGL(true);
    Chart_dY_t=CreateChart(series_dY_t);
    ui->dY_t->setChart(Chart_dY_t);
    ui->dY_t->setRenderHint(QPainter::Antialiasing);

    series_dZ_t = new QLineSeries();
    series_dZ_t->setUseOpenGL(true);
    Chart_dZ_t=CreateChart(series_dZ_t);
    ui->dZ_t->setChart(Chart_dZ_t);
    ui->dZ_t->setRenderHint(QPainter::Antialiasing);

    series_dMagnetPos_t = new QLineSeries();
    series_dMagnetPos_t->setUseOpenGL(true);
    Chart_dMagnetPos_t=CreateChart(series_dMagnetPos_t);
    ui->dMP_t->setChart(Chart_dMagnetPos_t);
    ui->dMP_t->setRenderHint(QPainter::Antialiasing);


    series_1 = new QLineSeries();
    series_1->setUseOpenGL(true);
    Chart_1=CreateChart(series_1);
    ui->XY_plot1->setChart(Chart_1);
    ui->XY_plot1->setRenderHint(QPainter::Antialiasing);

    series_2 = new QLineSeries();
    series_2->setUseOpenGL(true);
    Chart_2=CreateChart(series_2);
    ui->XY_plot2->setChart(Chart_2);
    ui->XY_plot2->setRenderHint(QPainter::Antialiasing);


    //initOneChart(series_dX_t,Chart_dX_t,ui->dX_t);
    //initOneChart(series_dY_t,Chart_dY_t,ui->dY_t);
    //initOneChart(series_dZ_t,Chart_dZ_t,ui->dZ_t);
    //initOneChart(series_dMagnetPos_t,Chart_dMagnetPos_t,ui->dMP_t);
    cm.addChartView(QString("dX-t"),ui->dX_t);
    cm.addChartView(QString("dY-t"),ui->dY_t);
    cm.addChartView(QString("dZ-t"),ui->dZ_t);
    cm.addChartView(QString("dMP-t"),ui->dMP_t);
}

void MainWindow::importData(void)
{
    if(ui->lineEdit_FileName->text().isEmpty()) return;
    QString fileName=ui->lineEdit_Dir->text()+"/"+ui->lineEdit_FileName->text();
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists())
    {
        std:: string inFileName=fileName.toStdString();
        MagnetParameter MagnetField = { magneticFieldGradient::a,
                                        magneticFieldGradient::b,
                                        magneticFieldGradient::M };

        if(bead!=nullptr)
        {
            delete bead;
        }
        bead=new beadData(MagnetField);
        statusMsg.setText("正在导入...");
        ui->pushButton_Import->setEnabled(false);
        bead->loadData(inFileName);
        statusMsg.setText("文件打开成功");
        ui->maxTime->setMaximum(bead->allTime);
        ui->doubleSpinBox_offset->setEnabled(true);
        ui->doubleSpinBox_Rbead->setEnabled(true);
        ui->doubleSpinBox_Ztran->setEnabled(true);
        bead->setOffset(ui->doubleSpinBox_offset->value());
        bead->setR_bead(ui->doubleSpinBox_Rbead->value());
        bead->setZ_tran(ui->doubleSpinBox_Ztran->value());\

        bead->getMagPosSteps();
        bead->exportFoeceExtension();

        drawChart();
        ui->pushButton_Import->setEnabled(true);
    }
    else
    {
        statusMsg.setText("No File");
    }


}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::selectDir()
{
    QString rootdir=ui->lineEdit_Dir->text();
    QDir Dir(rootdir);
    if (!Dir.exists()) rootdir="C:/";

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),rootdir ,
                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    dirEx=dir+"/export/";
    ui->lineEdit_DirEx->setText(dirEx);
    ui->lineEdit_Dir->setText(dir);
    filePathModel.setRootPath(dir);
    statusMsg.setText(filePathModel.rootPath());
    ui->treeView_DirTree->setRootIndex(filePathModel.index(filePathModel.rootPath()));

}


void MainWindow::selectDirEX(void)
{
    QString rootdir=ui->lineEdit_Dir->text();
    QDir Dir(rootdir);
    if (!Dir.exists()) rootdir="C:/";

    dirEx = QFileDialog::getExistingDirectory(this, tr("Open Directory"),rootdir ,
                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    dirEx=dirEx+"/";
    ui->lineEdit_DirEx->setText(dirEx);
}
void MainWindow::selectFile()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dir,
                                            tr("Data (*.txt)"));

    QStringList strlist=fileName.split("/");
    if(strlist.size()>1)
    {
        auto it=strlist.begin();
        auto it_end=strlist.end();
        QString newdir=""+(*it);
        it++;
        for(;it!=it_end-1;it++)
        {
            newdir=newdir.append("/"+(*it));
        }
        dir=newdir;
        ui->lineEdit_Dir->setText(newdir);
        ui->lineEdit_DirEx->setText(newdir+"/export/");
        ui->lineEdit_FileName->setText(*it);
        ui->lineEdit_FilenameEx->setText("exportFE_"+(*it));
    }
}



std::function<void(int)> MainWindow::creatCheckConnectFunction(QDoubleSpinBox *minDoubleSpinBox,QDoubleSpinBox *maxDoubleSpinBox)
{
    std::function<void(int)> f=[minDoubleSpinBox,maxDoubleSpinBox](int state)
    {
        if (state==Qt::Unchecked)
        {
            minDoubleSpinBox->setEnabled(false);
            maxDoubleSpinBox->setEnabled(false);
        }
        if (state==Qt::Checked)
        {
            minDoubleSpinBox->setEnabled(true);
            maxDoubleSpinBox->setEnabled(true);
        }
    };
    return f;
}



void MainWindow::drawChart()
{ 
    drawOneChart(Chart_dX_t,series_dX_t,bead->org_time,bead->org_dX,bead->selectIndex);
    drawOneChart(Chart_dY_t,series_dY_t,bead->org_time,bead->org_dY,bead->selectIndex);
    drawOneChart(Chart_dMagnetPos_t,series_dMagnetPos_t,bead->org_time,bead->org_MagPos,bead->selectIndex);
    drawZChart();




}


void MainWindow::drawZChart()
{
    auto offset=bead->getOffset();
    auto Z_tran=bead->getZ_tran();
    drawOneChart(Chart_dZ_t,series_dZ_t,bead->org_time,bead->org_dZ,bead->selectIndex,Z_tran,offset);
}
void MainWindow::selectData()
{
    auto f=[&](double minvalue,double maxvalue)->double
    {
      if(minvalue>maxvalue)
          return std::numeric_limits<double>::max();
      return maxvalue;
    };

    std::vector<selectItem> selectGroup;

    selectGroup.push_back(creatSelectItem(DataName::Time,ui->minTime->value(),f(ui->minTime->value(),ui->maxTime->value()),ui->checkBox_Time->checkState()==Qt::Checked,ui->checkBoxInverseTime->checkState()==Qt::Checked));
    selectGroup.push_back(creatSelectItem(DataName::MagnetPosition,ui->minMP->value(),f(ui->minMP->value(),ui->maxMP->value()),ui->checkBox_MP->checkState()==Qt::Checked,ui->checkBoxInverseMP->checkState()==Qt::Checked));
    selectGroup.push_back(creatSelectItem(DataName::MagnetAngle,ui->minMA->value(),f(ui->minMA->value(),ui->maxMA->value()),ui->checkBox_MA->checkState()==Qt::Checked,ui->checkBoxInverseMA->checkState()==Qt::Checked));
    selectGroup.push_back(creatSelectItem(DataName::reX,ui->min_reX->value(),f(ui->min_reX->value(),ui->max_reX->value()),ui->checkBox_reX->checkState()==Qt::Checked,ui->checkBoxInverseX_re->checkState()==Qt::Checked));
    selectGroup.push_back(creatSelectItem(DataName::reX,ui->min_reY->value(),f(ui->min_reY->value(),ui->max_reY->value()),ui->checkBox_reY->checkState()==Qt::Checked,ui->checkBoxInverseY_re->checkState()==Qt::Checked));
    selectGroup.push_back(creatSelectItem(DataName::reX,ui->min_reZ->value(),f(ui->min_reZ->value(),ui->max_reZ->value()),ui->checkBox_reZ->checkState()==Qt::Checked,ui->checkBoxInverseZ_re->checkState()==Qt::Checked));
    bead->selectData(selectGroup);
    drawChart();
}
void MainWindow::OriginData()
{
    bead->originData();
    drawChart();
}


void MainWindow::setOption()
{
    optGUI=new optionGUI();
    optGUI->show();
}

void MainWindow::exportData()
{
    if(ui->radioButton_ExportTran->isChecked()) exportTranData();
    if(ui->radioButton_ExportStep->isChecked()) exportStepData();
    if(ui->radioButton_ExportSelect->isChecked()) exportSelectData();
}


void MainWindow::exportStepData()
{
    QDir DirEx(ui->lineEdit_DirEx->text());
    if(!DirEx.exists())
    {
        statusMsg.setText("指定文件夹不存在");
    }
    else
    {
        bead->getMagPosSteps();
        bead->exportFoeceExtension();
        std::string outFileName=ui->lineEdit_DirEx->text().toStdString()+ui->lineEdit_FilenameEx->text().toStdString();
        statusMsg.setText("正在导出...");
        bead->exportFoeceExtensionToFile(outFileName);
        statusMsg.setText("导出结束");
    }

}


void MainWindow::exportSelectData()
{
    QDir DirEx(ui->lineEdit_DirEx->text());
    if(!DirEx.exists())
    {
        statusMsg.setText("指定文件夹不存在");
    }
    else
    {
        QString outFileName=ui->lineEdit_DirEx->text()+ui->lineEdit_FilenameEx->text();
        QStringList strlist=outFileName.split(".");
        if(strlist.size()>1)
        {
            auto it=strlist.begin();
            auto it_endLast=strlist.end();
            it_endLast--;
            outFileName="";
            for(;it!=it_endLast;it++) outFileName=outFileName.append(*it);

            QString TXToutFileName=outFileName+".txt";
            statusMsg.setText("正在导出TXT...");
            bead->exportSelectDataToTXT(TXToutFileName.toStdString());
            statusMsg.setText("导出结束");

        }
    }
}


void MainWindow::exportTranData()
{
    QDir DirEx(ui->lineEdit_DirEx->text());
    if(!DirEx.exists())
    {
        statusMsg.setText("指定文件夹不存在");
    }
    else
    {
        QString outFileName=ui->lineEdit_DirEx->text()+ui->lineEdit_FilenameEx->text();
        QStringList strlist=outFileName.split(".");
        if(strlist.size()>1)
        {
            auto it=strlist.begin();
            auto it_endLast=strlist.end();
            it_endLast--;
            outFileName="";
            for(;it!=it_endLast;it++) outFileName=outFileName.append(*it);

            if(ui->checkBox_TXT->checkState()==Qt::Checked)
            {
                QString TXToutFileName=outFileName+".txt";
                statusMsg.setText("正在导出TXT...");
                bead->exportTranDataToTXT(TXToutFileName.toStdString());
                statusMsg.setText("导出结束");
            }

            if(ui->checkBox_MatFile->checkState()==Qt::Checked)
            {
                QString MatoutFileName=outFileName+".mat";
                statusMsg.setText("正在导出Mat...");
                bead->exportTranDataToMat(MatoutFileName.toStdString());
                statusMsg.setText("导出结束");
            }
        }
    }
}



void MainWindow::setMagneticFieldGradient()
{
    magneticFieldGradient::a=ui->doubleSpinBox_a_2->value();
    magneticFieldGradient::b=ui->doubleSpinBox_b_2->value();
    magneticFieldGradient::M=ui->doubleSpinBox_M_2->value();
}

void MainWindow::initMagneticFieldGradient()
{
    ui->doubleSpinBox_a_2->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox_b_2->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox_M_2->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox_a_2->setMinimum(-std::numeric_limits<double>::max());
    ui->doubleSpinBox_b_2->setMinimum(-std::numeric_limits<double>::max());
    ui->doubleSpinBox_M_2->setMinimum(-std::numeric_limits<double>::max());
    ui->doubleSpinBox_a_2->setDecimals(15);
    ui->doubleSpinBox_b_2->setDecimals(15);
    ui->doubleSpinBox_M_2->setDecimals(15);
    ui->doubleSpinBox_a_2->setValue(magneticFieldGradient::a);
    ui->doubleSpinBox_b_2->setValue(magneticFieldGradient::b);
    ui->doubleSpinBox_M_2->setValue(magneticFieldGradient::M);
    QObject::connect(ui->pushButtonMGSet_2,&QPushButton::clicked,this,&MainWindow::setMagneticFieldGradient);
}



void MainWindow::on_action_openFile_triggered()
{
    selectFile();
    importData();
}

void MainWindow::on_pushButton_show_clicked()
{
    bead->getMagPosSteps();
    drawOneChart(Chart_1,series_1,bead->vec_MagSteps_Pos,bead->vec_extension);
}
void MainWindow::on_pushButton_show_2_clicked()
{
    bead->getMagPosSteps();
    drawOneChart(Chart_2,series_2,bead->vec_MagSteps_Pos,bead->vec_extension);
}
