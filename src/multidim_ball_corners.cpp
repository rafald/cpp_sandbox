/*
 exercise: C++ rewrite of following python snippet

    from scipy.special import gamma
    from math import pi

    def unit_sphere_volume(n): 
        return pi**(0.5*n)/gamma(0.5*n + 1)

    def unit_cube_volume(n): 
        return 2**n

    def ratio(n):
        return unit_sphere_volume(n) / unit_cube_volume(n)

    print( [ratio(n) for n in range(1, 20)] )
[1.0, 
 0.78539816339744828, 0.52359877559829893, 0.30842513753404244, 0.16449340668482262, 0.080745512188280771, 0.036912234143214068, 0.015854344243815498, 0.006442400200661536, 0.0024903945701927198, 0.00091997259735834955, 0.00032599188692738996, 0.00011116073666788121, 3.6576204182177239e-05, 1.1640725122781505e-05, 3.5908604485915088e-06, 1.0756004861231918e-06, 3.1336168903781201e-07, 8.8923646984269195e-08]     
*/

#include <cmath>       /* pow */
#include <ctgmath> //TODO

#include <iostream>

#include <boost/math/special_functions/gamma.hpp>
//#include <boost/math/special_functions/pow.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
//#include <boost/multiprecision/float128.hpp> // float128

using boost::math::constants::pi;
using boost::math::tgamma;

boost::multiprecision::cpp_dec_float_50 const my_pi("3.14159265358979323846264338327950288419716939937510");

template <unsigned PREC>
using dec_float = boost::multiprecision::number< boost::multiprecision::cpp_dec_float<PREC> >;

template <class Number>
auto
unit_sphere_volume(unsigned dim) -> Number { 
	auto nom = pow( pi<Number>(), Number(0.5)*dim);
	auto denom = tgamma(Number(0.5)*dim + 1);
	return nom / denom;
}

template <class Number>
auto
unit_cube_volume(Number n) -> Number {
	return pow( 2, n );
}

int main()
{
	std::cout << "[" << std::setprecision(17);
	for( unsigned dim = 1 ; dim != 20 ; ++dim)
	{
		//long double is good enough
		//dec_float<19> is OK but dec_float<19> is not
		std::cout << unit_sphere_volume<long double>(dim) / unit_cube_volume(dim) << ", ";
	}
	std::cout << "]";
	return 0;
}
/*
double:
 0.99999999999999989, SHOULD be 1.0
 0.78539816339744828, 0.52359877559829893, 0.30842513753404244, 0.16449340668482265, 0.080745512188280771, 0.036912234143214068, 0.015854344243815498, 0.006442400200661536, 0.0024903945701927198, 0.00091997259735834955, 0.00032599188692739001, 0.00011116073666788124, 3.6576204182177246e-05, 1.1640725122781507e-05, 3.5908604485915093e-06, 1.0756004861231918e-06, 3.1336168903781206e-07, 8.8923646984269208e-08
 0.78539816339744828, 0.52359877559829893, 0.30842513753404244, 0.16449340668482262, 0.080745512188280771, 0.036912234143214068, 0.015854344243815498, 0.006442400200661536, 0.0024903945701927198, 0.00091997259735834955, 0.00032599188692738996, 0.00011116073666788121, 3.6576204182177239e-05, 1.1640725122781505e-05, 3.5908604485915088e-06, 1.0756004861231918e-06, 3.1336168903781201e-07, 8.8923646984269195e-08]     
py ^

float is better then double but only for first number/dimention: 1 !!!
 0.78539818525314331, 0.52359873056411743, 0.30842512845993042, 0.16449339687824249, 0.080745510756969452, 0.036912236362695694, 0.015854345634579659, 0.0064424010924994946, 0.0024903947487473488, 0.00091997254639863968, 0.0003259919467382133, 0.0001111607562052086, 3.6576213460648432e-05, 1.1640728189377114e-05, 3.5908612971979892e-06, 1.0756008350654156e-06, 3.1336173833551584e-07, 8.8923670205076633e-08 
 0.78539816339744828, 0.52359877559829893, 0.30842513753404244, 0.16449340668482262, 0.080745512188280771, 0.036912234143214068, 0.015854344243815498, 0.006442400200661536, 0.0024903945701927198, 0.00091997259735834955, 0.00032599188692738996, 0.00011116073666788121, 3.6576204182177239e-05, 1.1640725122781505e-05, 3.5908604485915088e-06, 1.0756004861231918e-06, 3.1336168903781201e-07, 8.8923646984269195e-08]     

long double
 0.78539816339744831, 0.52359877559829887, 0.30842513753404246, 0.16449340668482264, 0.080745512188280782, 0.036912234143214072, 0.015854344243815501, 0.0064424002006615369, 0.0024903945701927202, 0.00091997259735834973, 0.00032599188692739001, 0.00011116073666788124, 3.6576204182177251e-05, 1.1640725122781509e-05, 3.5908604485915101e-06, 1.0756004861231921e-06, 3.1336168903781215e-07, 8.8923646984269229e-08
 0.78539816339744828, 0.52359877559829893, 0.30842513753404244, 0.16449340668482262, 0.080745512188280771, 0.036912234143214068, 0.015854344243815498, 0.006442400200661536, 0.0024903945701927198, 0.00091997259735834955, 0.00032599188692738996, 0.00011116073666788121, 3.6576204182177239e-05, 1.1640725122781505e-05, 3.5908604485915088e-06, 1.0756004861231918e-06, 3.1336168903781201e-07, 8.8923646984269195e-08]     

dec_float<19>  
 0.78539816339744831, 0.52359877559829887, 0.30842513753404246, 0.16449340668482264, 0.080745512188280782, 0.036912234143214072, 0.015854344243815501, 0.0064424002006615369, 0.0024903945701927202, 0.00091997259735834973, 0.00032599188692739001, 0.00011116073666788124, 3.6576204182177251e-05, 1.1640725122781509e-05, 3.5908604485915101e-06, 1.0756004861231921e-06, 3.1336168903781215e-07, 8.8923646984269229e-08
 0.78539816339744828, 0.52359877559829893, 0.30842513753404244, 0.16449340668482262, 0.080745512188280771, 0.036912234143214068, 0.015854344243815498, 0.006442400200661536, 0.0024903945701927198, 0.00091997259735834955, 0.00032599188692738996, 0.00011116073666788121, 3.6576204182177239e-05, 1.1640725122781505e-05, 3.5908604485915088e-06, 1.0756004861231918e-06, 3.1336168903781201e-07, 8.8923646984269195e-08]     
   
*/
