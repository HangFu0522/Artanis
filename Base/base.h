#pragma once
#include<vector>

enum class DataName {Time, MagnetPosition, MagnetAngle, reX, reY, reZ};
typedef struct _pieceData
{
    std::vector<double> time;
    std::vector<double> dX;
    std::vector<double> dY;
    std::vector<double> dZ;
    ~_pieceData()
    {
        time.clear();
        std::vector<double>().swap(time);
        dX.clear();
        std::vector<double>().swap(dX);
        dY.clear();
        std::vector<double>().swap(dY);
        dZ.clear();
        std::vector<double>().swap(dZ);
    }
}pieceData;

typedef struct _aPiece
{
    std::size_t beginPoint;
    std::size_t endPoint;
}aPiece;

typedef struct _selectItem
{
    double maxValue;
    double minValue;
    bool isChecked;
    bool isInverse;
    DataName name;
}selectItem;

typedef struct _WLCmodelParameter
{
	double Lp;
	double K;
	double bp_len;
	double num_bp;
} WLCmodelParameter;

typedef struct _MagnetParameter
{
	double a;
	double b;
	double M;
} MagnetParameter;

selectItem creatSelectItem(DataName _name,double _minValue,double _maxValue,bool _isChecked,bool _isInverse);
