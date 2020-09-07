#pragma once
#include<vector>
#include<Base/base.h>
template<typename T>
double mean(const std::vector<T>& data,size_t begin,size_t end)
{
	double sum=0;
	double _ = 1 / static_cast<double>(end - begin);
	for (auto i = begin; i < end + 1; i++)
	{
		sum += static_cast<double>(data[i]) * _;
	}
	return sum;
}


double var(const std::vector<double>& data,size_t begin,size_t end,double mean)
{
    double sum=0;
    double _ = 1 / static_cast<double>(end - begin);
    for (auto i = begin; i < end + 1; i++)
    {
        sum += static_cast<double>(data[i]-mean)*static_cast<double>(data[i]-mean) * _;
    }
    return sum;
}


double fit_F_log(double x, double a, double b, double M)
{
	return a * x*x + b * x + M;
}

double WLC_force_to_length(double F,WLCmodelParameter elasticity, double temperature)
{
	temperature = temperature;
	auto KbT = 138 * (273 + temperature) / 10000;
	return elasticity.num_bp*elasticity.bp_len * (1 - 0.5*std::sqrt(KbT / (F*elasticity.Lp)) + F / elasticity.K);
};
