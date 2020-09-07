#include "matfile.h"


matFile::matFile(const char *filename,const char *mode)
{
    pMatFile = matOpen(filename, mode);
}

matFile::~matFile()
{
    matClose(pMatFile);
}

bool matFile::writeDoubleVectorToMat(const std::vector<double> &data,const std::vector<size_t> &selectIndex,const char *varName)
{
    if (!pMatFile) return false;
    int len = static_cast<int>(selectIndex.size());


    double * pData;

    mxArray *pMxArray = mxCreateDoubleMatrix(len, 1, mxREAL);
    if (!pMxArray) return false;

    pData = (double *)mxCalloc(len, sizeof(double));
    if (!pData) return false;


    int it=0;
    for (it; it<len; it++)
    {
        pData[it] = data[selectIndex[it]];

    }
    mxSetData(pMxArray, pData);
    matPutVariable(pMatFile, varName, pMxArray);

    mxFree(pData);
    return true;
}


bool matFile::writeIntVectorToMat(const std::vector<int> &data,const std::vector<size_t> &selectIndex,const char *varName)
{
    if (!pMatFile) return false;
    int len = static_cast<int>(selectIndex.size());


    double * pData;

    mxArray *pMxArray = mxCreateDoubleMatrix(len, 1, mxREAL);
    if (!pMxArray) return false;

    pData = (double *)mxCalloc(len, sizeof(double));
    if (!pData) return false;

    int it=0;
    for (it; it<len; it++)
    {
        pData[it] = static_cast<double>(data[selectIndex[it]]);

    }
    mxSetData(pMxArray, pData);
    matPutVariable(pMatFile, varName, pMxArray);

    mxFree(pData);
    return true;
}


bool matFile::writeOneDoubleToMat(double data,const char *varName)
{

    if (!pMatFile) return false;

    double * pData;

    mxArray *pMxArray = mxCreateDoubleMatrix(1, 1, mxREAL);
    if (!pMxArray) return false;

    pData = (double *)mxCalloc(1, sizeof(double));
    if (!pData) return false;

    pData[0] = static_cast<double>(data);

    mxSetData(pMxArray, pData);
    matPutVariable(pMatFile, varName, pMxArray);

    mxFree(pData);
    return true;
}
