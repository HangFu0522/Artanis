#pragma once
#include"3rdpackage/csv.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include <algorithm>
#include"Base/base.h"
#include"3rdpackage/matfile.h"
#include"mat.h"
#include"matrix.h"
class matFile;

class beadData
{
public:
    beadData(MagnetParameter _MagnetField);

	~beadData();
	bool loadData(const std::string &filename);
    bool getMagPosSteps(void);
    bool selectData(const std::vector<selectItem>& selectGroup);
    void originData();
	bool exportFoeceExtension();
	bool exportFoeceExtensionToFile(const std::string exportFileName);
    bool exportSelectDataToTXT(const std::string exportFileName);
    bool exportTranDataToTXT(const std::string exportFileName);
    bool exportTranDataToMat(const std::string exportFileName);
    bool setOffset(double offset);
    bool setR_bead(double Rbead);
    bool setZ_tran(double Ztran);
    double getOffset(void);
    double getR_bead(void);
    double getZ_tran(void);
    size_t org_number = 0;
    double allTime=0;



    std::vector<double> org_time,
                        org_dX, org_dY, org_dZ,
                        org_X_re, org_Y_re, org_Z_re,
                        org_MagPos, org_MagAngle, org_StagePos;

    std::vector<int> org_isMove;
    std::vector<size_t> selectIndex;
    std::vector<double>	vec_MagSteps_Pos,vec_force, vec_extension;
private:
    std::map<DataName,std::vector<double>*> ItemMap;
	std::vector<int> vec_MagSteps_begin, vec_MagSteps_end;

	std::vector<aPiece> vec_Piece;

	MagnetParameter MagnetField;

	double offsetmeasure = 0;
    double R_bead = 500;
    double Z_tran = 0.875;
	int skip_begin = 200, skip_end = 0; //电机移动后忽略的点数,电机移动前忽略的点数
};

