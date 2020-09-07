#include "beadData.h"
#include"Analyze/analyze.h"
#include <fstream>
#include<iostream>
#include<map>

beadData::beadData(MagnetParameter _MagnetField)
{
    this->MagnetField = _MagnetField;
    ItemMap[DataName::Time]=&org_time;
    ItemMap[DataName::MagnetPosition]=&org_MagPos;
    ItemMap[DataName::MagnetAngle]=&org_MagAngle;
    ItemMap[DataName::reX]=&org_X_re;
    ItemMap[DataName::reY]=&org_Y_re;
    ItemMap[DataName::reZ]=&org_Z_re;

}

beadData::~beadData()
{

}

bool beadData::loadData(const std::string & filename)
{
	io::CSVReader<11> in(filename);

	//time/ms,X/nm,Y/nm,Z/um,X_re/nm,Y_re/nm,Z_re/um,MagPos/um,MagAngle/dec,StagePos/um,isMove
    try{
        in.read_header(io::ignore_extra_column, "time/ms", "X/nm", "Y/nm", "Z/um", "X_re/nm", "Y_re/nm", "Z_re/um", "MagPos/um", "MagAngle/dec", "StagePos/um", "isMove");
        //in.next_line()如果不想读取标题，可以用这句
        double time, X, Y, Z, X_re, Y_re, Z_re, MagPos, MagAngle, StagePos;
        int isMove;

        org_number=0;
        auto notFile_end=true;
        while (notFile_end) {
            try{
                notFile_end=in.read_row(time, X, Y, Z, X_re, Y_re, Z_re, MagPos, MagAngle, StagePos, isMove);
                org_time.push_back(time);
                org_dX.push_back(X - X_re);
                org_dY.push_back(Y - Y_re);
                org_dZ.push_back(Z - Z_re);
                org_X_re.push_back(X_re);
                org_Y_re.push_back(Y_re);
                org_Z_re.push_back(Z_re);
                org_MagPos.push_back(MagPos);
                org_MagAngle.push_back(MagAngle);
                org_StagePos.push_back(StagePos);
                org_isMove.push_back(isMove);
                selectIndex.push_back(org_number);
                org_number++;
            }catch (std::exception e) {
               }
        }
        allTime=org_time[org_number-1];
    }catch (std::exception e) {
        return false;
    }
	return true;
};

bool beadData::getMagPosSteps(void)
{
	//该函数主要将磁铁的位移分成步进的形式，返回磁铁每一步的开始时间，结束时间，坐标值
    auto it = selectIndex.begin(),it_end=selectIndex.end();
    auto last_it=*it;
	int beginPoint, endPoint;
	aPiece piece;
    for (it++; it !=it_end; it++)
	{
        if (org_isMove[*it] == 1)
		{
			beginPoint = static_cast<int>(last_it + skip_begin);
            endPoint = static_cast<int>(*it - skip_end);
			piece.beginPoint = last_it;
            piece.endPoint = *it;
			vec_Piece.push_back(piece);
			if ((endPoint - beginPoint) > 100)
			{
				vec_MagSteps_begin.push_back(beginPoint);
				vec_MagSteps_end.push_back(endPoint);
                vec_MagSteps_Pos.push_back(mean<double>(org_MagPos, beginPoint, endPoint));
			}
            last_it = *it;
		}
	}
	return true;
}

bool beadData::selectData(const std::vector<selectItem>& selectGroup)
{
    selectIndex.clear();
    std::vector<size_t>().swap(selectIndex);
    bool isChosen=true;
    for (size_t it = 0; it < org_number; it++)
    {
        isChosen=true;
        for(const auto& item:selectGroup)
        {
            if(item.isChecked)
            {
                auto data=(*ItemMap[item.name])[it];
                isChosen&=(item.isInverse!=(item.minValue < data && data < item.maxValue));
            }
        }
        if(isChosen) selectIndex.push_back(it);
    }
    return true;
}

bool beadData::exportFoeceExtension()
{
	auto num_points = vec_MagSteps_Pos.size();
	for (auto it = 0; it < num_points; it++)
	{
		vec_force.push_back(std::exp(fit_F_log(vec_MagSteps_Pos[it]/1000,MagnetField.a, MagnetField.b, MagnetField.M)));
        vec_extension.push_back(mean<double>(org_dZ, vec_MagSteps_begin[it], vec_MagSteps_end[it])+offsetmeasure);
	}
	return true;
}
bool beadData::exportFoeceExtensionToFile(const std::string exportFileName)
{
	std::ofstream outfile(exportFileName,std::ios::trunc);
    outfile << "Force(pN)," << "Extension(nm)," << "MP(um)"<<std::endl;
	auto number_point = vec_force.size();
	for (auto it = 0; it < number_point; it++)
	{
        outfile << vec_force [it]<< "," << vec_extension[it] << ","<<vec_MagSteps_Pos[it]<<std::endl;
	}
	outfile.close();
	return true;
}

bool beadData::exportSelectDataToTXT(const std::string exportFileName)
{
    std::ofstream outfile(exportFileName,std::ios::trunc);

    outfile << "time/ms,"
            << "X/nm,"
            << "Y/nm,"
            << "Z/um,"
            << "X_re/nm,"
            << "Y_re/nm,"
            << "Z_re/um,"
            << "MagPos/um,"
            << "MagAngle/dec,"
            << "StagePos/um,"
            << "isMove"
            <<std::endl;
    auto it_end = selectIndex.end();

    auto it = selectIndex.begin();

    for (it; it!=it_end; it++)
    {
        outfile << org_time[*it]<< ","
                << org_dX[*it]+ org_X_re[*it]<< ","
                << org_dY[*it]+ org_Y_re[*it] << ","
                << org_dZ[*it]+ org_Z_re[*it]<< ","
                << org_X_re[*it] << ","
                << org_Y_re[*it]<< ","
                << org_Z_re[*it]<< ","
                << org_MagPos[*it]<< ","
                << org_MagAngle[*it]<< ","
                << org_StagePos[*it] << ","
                << org_isMove[*it]
                <<std::endl;
    }
    outfile.close();
    return true;
}

bool beadData::exportTranDataToTXT(const std::string exportFileName)
{
    std::ofstream outfile(exportFileName,std::ios::trunc);
    outfile << "time/ms,"
            << "dX/nm,"
            << "dY/nm,"
            << "dZ/nm,"
            << "X_re/nm,"
            << "Y_re/nm,"
            << "Z_re/nm,"
            << "MagPos/um,"
            << "MagAngle/dec,"
            << "StagePos/um,"
            << "isMove"
            <<std::endl;
    auto it_end = selectIndex.end();

    auto it = selectIndex.begin();

    for (it; it!=it_end; it++)
    {
        outfile << org_time[*it]<< ","
                << org_dX[*it]<< ","
                << org_dY[*it] << ","
                << (org_dZ[*it])*Z_tran+offsetmeasure<< ","
                << org_X_re[*it] << ","
                << org_Y_re[*it]<< ","
                << org_Z_re[*it]<< ","
                << org_MagPos[*it]<< ","
                << org_MagAngle[*it]<< ","
                << org_StagePos[*it] << ","
                << org_isMove[*it]
                << std::endl;
    }
    outfile.close();
    return true;
}

bool beadData::exportTranDataToMat(const std::string exportFileName)
{

    std::vector<double> vec_Z_tran;
    for(const auto it:org_dZ)
    {
        vec_Z_tran.push_back(it*Z_tran+offsetmeasure);
    }

    matFile file(exportFileName.c_str(),"w");
    file.writeOneDoubleToMat(offsetmeasure,"offset");
    file.writeOneDoubleToMat(Z_tran,"z_tran");
    file.writeOneDoubleToMat(R_bead,"R_bead");
    file.writeDoubleVectorToMat(org_time,selectIndex,"t");
    file.writeDoubleVectorToMat(org_dX,selectIndex,"dX");
    file.writeDoubleVectorToMat(org_dY,selectIndex,"dY");
    file.writeDoubleVectorToMat(vec_Z_tran,selectIndex,"dZ");
    file.writeDoubleVectorToMat(org_X_re,selectIndex,"reX");
    file.writeDoubleVectorToMat(org_Y_re,selectIndex,"reY");
    file.writeDoubleVectorToMat(org_Z_re,selectIndex,"reZ");
    file.writeDoubleVectorToMat(org_MagPos,selectIndex,"magnetpos");
    file.writeIntVectorToMat(org_isMove,selectIndex,"isMove");
    file.writeDoubleVectorToMat(org_MagAngle,selectIndex,"MagAngle");
    file.writeDoubleVectorToMat(org_StagePos,selectIndex,"StagePos");
    return true;
}


bool beadData::setOffset(double offset)
{
    offsetmeasure=offset;
    return true;
}

bool beadData::setR_bead(double Rbead)
{
    R_bead=Rbead;
    return true;
}
bool beadData::setZ_tran(double Ztran)
{
    Z_tran=Ztran;
    return true;
}

double beadData::getZ_tran()
{
    return Z_tran;
}

double beadData::getOffset()
{
    return offsetmeasure;
}
void beadData::originData()
{
    selectIndex.clear();
    std::vector<size_t>().swap(selectIndex);

    for(size_t i=0;i<org_number;i++)
    {
        selectIndex.push_back(i);
    }
}

