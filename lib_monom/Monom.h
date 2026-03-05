#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
class Monom {
private:
	int deg[3];
	double coeff;
public:
	Monom(const Monom& other);
	Monom(double coeff, int degX, int degY, int degZ);
	Monom() : coeff(0.0) { deg[0] = deg[1] = deg[2] = 0; }
	double getCoeff() const { return coeff; }
	int getDegX() const { return deg[0]; }
	int getDegY() const { return deg[1]; }
	int getDegZ() const { return deg[2]; }
	void setCoeff(double k) { coeff = k; }
	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;
	Monom operator+(const Monom& other) const;
	Monom operator-(const Monom& other) const;
	Monom operator*(const Monom& other) const;
	Monom operator/(const Monom& other) const;
	Monom& operator+=(const Monom& other);
	Monom& operator-=(const Monom& other);
	Monom& operator*=(const Monom& other);
	Monom& operator/=(const Monom& other);
	bool operator>(const Monom& other) const;
	Monom operator*(double k) const;
	Monom operator/(double k) const;
	Monom& operator*=(double k);
	Monom& operator/=(double k);
	Monom operator-() const;
	double value(double x, double y, double z) const;
	friend std::ostream& operator<<(std::ostream& os, const Monom& m);
	friend std::istream& operator>>(std::istream& is, Monom& m);




};