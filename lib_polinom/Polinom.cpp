#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include "../lib_monom/Monom.h"
#include "polinom.h"
#include "../lib_list/DoubleList.h"
 
Polynom::Polynom() {
	monoms = DoubleList<Monom>();
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

		std::string work = token;
		if (!work.empty() && work[0] == '-') {
			if (work.size() == 1 || std::isalpha(static_cast<unsigned char>(work[1]))) {
				coeff = -1;
				work = work.substr(1);
			}
		}
		if (!work.empty() && (std::isdigit(static_cast<unsigned char>(work[0])) ||
			(work.size() > 1 && work[0] == '-' && std::isdigit(static_cast<unsigned char>(work[1])))))
		{
			std::stringstream tnum(work);
			tnum >> coeff;
			std::string rest;
			std::getline(tnum, rest);
			work = rest;
		}

		std::stringstream t(work);
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

	for (auto it = monoms.begin_iter(); it != monoms.end_iter(); ++it, ++pos) {
		if (it->getDegX() == m.getDegX() &&
			it->getDegY() == m.getDegY() &&
			it->getDegZ() == m.getDegZ())
		{
			*it += m;
			if (it->getCoeff() == 0.0)
				monoms.erase(pos);

			return;
		}
		if (m > *it) {
			monoms.insert(m, pos);
			return;
		}
	}
	monoms.push_back(m);
}

Polynom Polynom::operator+(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin_iter(); it != other.getMonoms().end_iter(); ++it) {
		result.addMonom(*it);
	}
	return result;
}
Polynom Polynom::operator-(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin_iter(); it != other.getMonoms().end_iter(); ++it) {
		Monom neg = *it;
		neg.setCoeff(-neg.getCoeff());
		result.addMonom(neg);
	}
	return result;
}
Polynom Polynom::operator*(const Polynom& other) {
	Polynom result;
	for (auto it1 = this->getMonoms().begin_iter(); it1 != this->getMonoms().end_iter(); ++it1) {
		for (auto it2 = other.getMonoms().begin_iter(); it2 != other.getMonoms().end_iter(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(), it1->getDegX() + it2->getDegX(), it1->getDegY() + it2->getDegY(), it1->getDegZ() + it2->getDegZ());
			result.addMonom(m);
		}
	}
	return result;
}
Polynom& Polynom::operator*=(const Polynom& other) {
	Polynom copy = *this;
	*this = Polynom();
	for (auto it1 = copy.getMonoms().begin_iter(); it1 != copy.getMonoms().end_iter(); ++it1) {
		for (auto it2 = other.getMonoms().begin_iter(); it2 != other.getMonoms().end_iter(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(), it1->getDegX() + it2->getDegX(), it1->getDegY() + it2->getDegY(), it1->getDegZ() + it2->getDegZ());
			addMonom(m);
		}
	}
	return *this;
}
Polynom& Polynom::operator+=(const Polynom& other) {
	for (auto it = other.getMonoms().begin_iter(); it != other.getMonoms().end_iter(); ++it) {
		addMonom(*it);
	}
	return *this;
}
Polynom& Polynom::operator-=(const Polynom& other) {
	for (auto it = other.getMonoms().begin_iter(); it != other.getMonoms().end_iter(); ++it) {
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
	for (auto it = this->getMonoms().begin_iter(); it != this->getMonoms().end_iter(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		result.addMonom(m);
	}
	return result;
}
Polynom& Polynom::operator*=(double k) {
	DoubleList<Monom> old = this->monoms;
	this->monoms = DoubleList<Monom>();
	for (auto it = old.begin_iter(); it != old.end_iter(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		addMonom(m);
	}
	return *this;
}
Polynom Polynom::operator/(double k) const {
	if (k == 0) throw std::logic_error("Division by zero");
	Polynom result;
	for (auto it = this->getMonoms().begin_iter(); it != this->getMonoms().end_iter(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		result.addMonom(m);
	}
	return result;
}
Polynom& Polynom::operator/=(double k) {
	if (k == 0) throw std::logic_error("Division by zero");
	DoubleList<Monom> old = this->monoms;
	this->monoms = DoubleList<Monom>();
	for (auto it = old.begin_iter(); it != old.end_iter(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		addMonom(m);
	}
	return *this;
}
double Polynom::value(double x, double y, double z) const {
	double result = 0.0;
	for (auto it = this->getMonoms().begin_iter(); it != this->getMonoms().end_iter(); ++it) {
		result += it->value(x, y, z);
	}
	return result;
}