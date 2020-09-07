#ifndef MATFILE_H
#define MATFILE_H

#include"mat.h"
#include"matrix.h"
#include<vector>

class matFile
{
public:
    matFile(const char *filename,const char *mode);
    ~matFile();
    bool writeDoubleVectorToMat(const std::vector<double> &data,const std::vector<size_t> &selectIndex,const char *varName);
    bool writeIntVectorToMat(const std::vector<int> &data,const std::vector<size_t> &selectIndex,const char *varName);
    bool writeOneDoubleToMat(double data,const char *varName);



private:
    MATFile * pMatFile;
};

#endif // MATFILE_H
