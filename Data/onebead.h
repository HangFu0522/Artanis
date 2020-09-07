#ifndef ONEBEAD_H
#define ONEBEAD_H
#include<QString>
#include<Data/onebeaddata_org.h>
#include<Data/onebeaddata_view.h>
#include<vector>
class oneBead
{
public:
    oneBead();

    bool getMagPosSteps(void);
    bool selectData(const std::vector<selectItem>& selectGroup);
    void originData();
    bool setOffset(double offset);
    bool setR_bead(double Rbead);
    double getOffset(void);
    double getR_bead(void);
    bool exportFoeceExtension();
    bool exportFoeceExtensionToFile(const QString exportFileName);
    bool exportSelectDataToTXT(const QString exportFileName);
    bool exportTranDataToTXT(const QString exportFileName);
    bool exportTranDataToMat(const QString exportFileName);
private:
    double offsetmeasure = 0;
    double R_bead = 1400;
};

#endif // ONEBEAD_H
