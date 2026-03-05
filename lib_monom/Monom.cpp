#include <iostream>
#include <stdexcept>
#include <cmath>
#include "monom.h"
Monom::Monom(double c, int degX, int degY, int degZ) {
	coeff = c;
	deg[0] = degX;
	deg[1] = degY;
	deg[2] = degZ;
}

Monom::Monom(const Monom& other) {
	for (int i = 0; i < 3; i++) {
		deg[i] = other.deg[i];
	}
	coeff = other.coeff;
}
bool Monom::operator==(const Monom& other) const {
	return coeff == other.getCoeff() && deg[0] == other.getDegX() && deg[1] == other.getDegY() && deg[2] == other.getDegZ();

}
bool Monom::operator!=(const Monom& other) const {
	return !(*this == other);
}
Monom Monom::operator+(const Monom& other) const {
	if (deg[0] != other.getDegX() || deg[1] != other.getDegY() || deg[2] != other.getDegZ()) {
		throw std::invalid_argument("Cannot add monoms with different degrees");
	}
	return Monom(coeff + other.getCoeff(), deg[0], deg[1], deg[2]);
}
Monom Monom::operator-(const Monom& other) const {
	if (deg[0] != other.getDegX() || deg[1] != other.getDegY() || deg[2] != other.getDegZ()) {
		throw std::invalid_argument("Cannot subtract monoms with different degrees");

	}
	return Monom(coeff - other.getCoeff(), deg[0], deg[1], deg[2]);
}
Monom Monom::operator*(const Monom& other) const {
	return Monom(coeff * other.getCoeff(), deg[0] + other.getDegX(), deg[1] + other.getDegY(), deg[2] + other.getDegZ());
}
Monom Monom::operator/(const Monom& other) const {
	if (other.getCoeff() == 0.0) {
		throw std::invalid_argument("Cannot divide by monom with zero coefficient");
	}

	if (deg[0] < other.getDegX() ||
		deg[1] < other.getDegY() ||
		deg[2] < other.getDegZ()) {
		throw std::invalid_argument("Resulting monom has negative degree");
	}

	return Monom(coeff / other.getCoeff(),
		deg[0] - other.getDegX(),
		deg[1] - other.getDegY(),
		deg[2] - other.getDegZ());
}
Monom& Monom::operator+=(const Monom& other) {
	if (deg[0] != other.getDegX() || deg[1] != other.getDegY() || deg[2] != other.getDegZ()) { throw std::invalid_argument("Cannot add monoms with different degrees"); }
	coeff += other.getCoeff();
	return *this;
}
Monom& Monom::operator-=(const Monom& other) {
	if (deg[0] != other.getDegX() || deg[1] != other.getDegY() || deg[2] != other.getDegZ()) { throw std::invalid_argument("Cannot subtract monoms with different degrees"); }
	coeff -= other.getCoeff();
	return *this;
}
Monom& Monom::operator*=(const Monom& other) {
	deg[0] += other.getDegX();
	deg[1] += other.getDegY();
	deg[2] += other.getDegZ();
	coeff *= other.getCoeff();
	return *this;
}
Monom& Monom::operator/=(const Monom& other) {
	deg[0] -= other.getDegX();
	deg[1] -= other.getDegY();
	deg[2] -= other.getDegZ();
	if (other.getCoeff() == 0.0) {
		throw std::invalid_argument("Cannot divide by monom with zero coefficient");
	}
	if (deg[0] < 0 || deg[1] < 0 || deg[2] < 0) {
		throw std::invalid_argument("Resulting monom has negative degree");
	}
	coeff /= other.getCoeff();
	return *this;
}
Monom& Monom::operator*=(double k) {
	coeff *= k;
	return *this;
}
Monom Monom::operator*(double k) const {
	return Monom(coeff * k, deg[0], deg[1], deg[2]);
}
Monom Monom::operator/(double k) const {
	if (k == 0.0) {
		throw std::invalid_argument("Cannot divide by zero");
	}
	return Monom(coeff / k, deg[0], deg[1], deg[2]);
}
Monom& Monom::operator/=(double k) {
	if (k == 0.0) {
		throw std::invalid_argument("Cannot divide by zero");
	}
	coeff /= k;
	return *this;
}
Monom Monom::operator-() const {
	return Monom(-coeff, deg[0], deg[1], deg[2]);
}
double Monom::value(double x, double y, double z) const {
	return coeff * std::pow(x, deg[0]) * std::pow(y, deg[1]) * std::pow(z, deg[2]);
}
std::ostream& operator<<(std::ostream& os, const Monom& m) {
	os << m.coeff << " * x^" << m.deg[0] << " * y^" << m.deg[1] << " * z^" << m.deg[2];
	return os;
}
std::istream& operator>>(std::istream& is, Monom& m) {
	std::cout << "Enter coefficient: ";
	is >> m.coeff;
	std::cout << "Enter degree for x: ";
	is >> m.deg[0];
	std::cout << "Enter degree for y: ";
	is >> m.deg[1];
	std::cout << "Enter degree for z: ";
	is >> m.deg[2];
	return is;
}
bool Monom::operator>(const Monom& other) const {
	if (deg[0] != other.getDegX()) {
		return deg[0] > other.getDegX();
	}
	if (deg[1] != other.getDegY()) {
		return deg[1] > other.getDegY();
	}
	if (deg[2] != other.getDegZ()) {
		return deg[2] > other.getDegZ();
	}
	return coeff > other.getCoeff();
}