#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include "../lib_monom/Monom.h"
#include "polinom.h"
#include "../lib_list/DoubleList.h"
Polynom::Polynom() {
	monoms = ListDoubly<Monom>();
}
Polynom::Polynom(const Polynom& other) {
	monoms = other.monoms;
}
Polynom::Polynom(const std::string& s) {
	std::string str = s;
	for (int i = 0; i < s.size(); ++i) {
		if (str[i] == '-') {
			str.insert(i, "+");
			++i;
		}
	}
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, '+')) {
		if (token.empty()) continue;
		double coeff = 1;
		int degX = 0; int degY = 0; int degZ = 0;
		std::stringstream t(token);
		if (std::isdigit(token[0]) || token[0] != '-') {
			t >> coeff;
		}
		char c;
		while (t >> c) {
			if (c == 'x') {
				if (t.peek() == '^') {
					t.get(); t >> degX;
				}
				else { degX = 1; }
			}
			if (c == 'y') {
				if (t.peek() == '^') {
					t.get(); t >> degY;
				}
				else { degY = 1; }
			}
			if (c == 'z') {
				if (t.peek() == '^') {
					t.get(); t >> degZ;
				}
				else { degZ = 1; }
			}
		}
		addMonom(Monom(coeff, degX, degY, degZ));
	}
}
void Polynom::addMonom(const Monom& m) {
	if (m.getCoeff() == 0.0)
		return;
	int pos = 0;
	for (auto it = monoms.begin(); it != monoms.end(); ++it, ++pos) {
		if (it->getDegX() == m.getDegX() &&
			it->getDegY() == m.getDegY() &&
			it->getDegZ() == m.getDegZ()) {

			*it += m;

			if (it->getCoeff() == 0.0)
				monoms.erase(pos);

			return;
		}
		if (m > *it) {
			monoms.insert(pos, m);
			return;
		}
	}

	monoms.push_back(m);
}
Polynom Polynom::operator+(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().begin(); ++it) {
		result.addMonom(*it);
	}
	return result;
}
Polynom Polynom::operator-(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().begin(); ++it) {
		Monom neg = *it;
		neg.setCoeff(-neg.getCoeff());
		result.addMonom(neg);
	}
	return result;
}
Polynom Polynom::operator*(const Polynom& other) {
	Polynom result;
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().begin(); ++it1) {
		for (auto it2 = other.getMonoms().begin(); it2 != other.getMonoms().end(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(), it1->getDegX() + it2->getDegX(), it1->getDegY() + it2->getDegY(), it1->getDegZ() + it2->getDegZ());
			result.addMonom(m);
		}
	}
	return result;
}
Polynom& Polynom::operator*=(const Polynom& other) {
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().begin(); ++it1) {
		for (auto it2 = other.getMonoms().begin(); it2 != other.getMonoms().end(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(), it1->getDegX() + it2->getDegX(), it1->getDegY() + it2->getDegY(), it1->getDegZ() + it2->getDegZ());
			addMonom(m);
		}
	}
	return *this;
}
Polynom& Polynom::operator+=(const Polynom& other) {
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().begin(); ++it) {
		addMonom(*it);
	}
	return *this;
}
Polynom& Polynom::operator-=(const Polynom& other) {
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().begin(); ++it) {
		Monom neg = *it;
		neg.setCoeff(-neg.getCoeff());
		addMonom(neg);
	}
	return *this;
}
Polynom Polynom::operator/(const Polynom& other) {
	throw std::logic_error("Polynomial division is not implemented");
}

Polynom& Polynom::operator/=(const Polynom& other) {
	throw std::logic_error("Polynomial division is not implemented");
}
Polynom Polynom::operator*(double k) const {
	Polynom result;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		result.addMonom(m);
	}
	return result;
}
Polynom& Polynom::operator*=(double k) {
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		addMonom(m);
	}
	return *this;
}
Polynom Polynom::operator/(double k) const {
	if (k == 0) throw std::logic_error("Division by zero");
	Polynom result;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		result.addMonom(m);
	}
	return result;
}
Polynom& Polynom::operator/=(double k) {
	if (k == 0) throw std::logic_error("Division by zero");
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		addMonom(m);
	}
	return *this;
}
double Polynom::value(double x, double y, double z) const {
	double result = 0.0;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		result += it->value(x, y, z);
	}
	return result;
}