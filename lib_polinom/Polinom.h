//#pragma once
//#include <iostream>
//#include <stdexcept>
//#include <cmath>
//#include "../lib_monom/Monom.h"
//#include "../lib_list/DoubleList.h"
//
//class Polynom {
//private:
//	DoubleList<Monom> monoms;
//public:
//	Polynom();
//	Polynom(const Polynom& other);
//	Polynom(const std::string& str);
//	void addMonom(const Monom& m);
//	Polynom operator+(const Polynom& other);
//	Polynom operator-(const Polynom& other);
//	Polynom operator*(const Polynom& other);
//	Polynom operator/(const Polynom& other);
//	Polynom& operator+=(const Polynom& other);
//	Polynom& operator-=(const Polynom& other);
//	Polynom& operator*=(const Polynom& other);
//	Polynom& operator/=(const Polynom& other);
//	Polynom operator*(double k) const;
//	Polynom operator/(double k) const;
//	Polynom& operator*=(double k);
//	Polynom& operator/=(double k);
//	double value(double x, double y, double z) const;
//	const DoubleList<Monom>& getMonoms() const { return monoms; }
//};