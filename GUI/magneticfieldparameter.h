#ifndef MAGNETICFIELDPARAMETER_H
#define MAGNETICFIELDPARAMETER_H
#include<QString>
class magneticFieldGradient
{

public:
    explicit magneticFieldGradient();
    ~magneticFieldGradient();
    static double a;
    static double b;
    static double M;
    bool importMagneticFieldGradientFromFile(QString filename);
};

#endif // MAGNETICFIELDPARAMETER_H
