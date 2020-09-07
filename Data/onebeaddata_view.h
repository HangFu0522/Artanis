#ifndef ONEBEADDATA_VIEW_H
#define ONEBEADDATA_VIEW_H
#include"3rdpackage/matfile.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include <algorithm>
#include"Base/base.h"

#include"mat.h"
#include"matrix.h"
#include<QString>
class oneBeadData_view
{
    //oneBeadData_view包括控制data的分段、导出、选择、压缩
public:
    oneBeadData_view();
    ~oneBeadData_view();
    bool getMagPosSteps(void);
    bool selectData(const std::vector<selectItem>& selectGroup);
    void originData();

    size_t org_number = 0;
    double allTime=0;
    std::map<DataName,std::vector<double>*> ItemMap;
    std::vector<int> vec_MagSteps_begin, vec_MagSteps_end;
    std::vector<size_t> selectIndex;
    std::vector<aPiece> vec_Piece;
    std::vector<double>	vec_MagSteps_Pos,vec_force, vec_extension;
    int skip_begin = 200, skip_end = 0; //电机移动后忽略的点数,电机移动前忽略的点数
};

#endif // ONEBEADDATA_VIEW_H
