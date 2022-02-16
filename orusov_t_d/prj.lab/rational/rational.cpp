#include <iostream>
#include <exception>
#include <string>

class NullDenomException : public std::exception {
};


class Rational {
public:
	Rational() = default;
	Rational(const Rational& other) = default;
	Rational(Rational&& other) = default;
	Rational(long long _numerator, long long _denominator = 1) :
		numerator(_numerator), denominator(_denominator) {
		// check that denominator > 0 and nod(num, den) == 1
		if (denominator == 0) {
			throw NullDenomException();
		}
		if (denominator < 0) {
			denominator *= -1;
			numerator *= -1;
		}
		balance();
	}
	~Rational() = default;
	friend bool operator< (const Rational& left, const Rational& right);
	friend bool operator== (const Rational& left, const Rational& right);
	Rational& operator= (const Rational& other);
	Rational& operator= (Rational&& other) noexcept;
	Rational operator-() const;
	Rational operator+() const;
	Rational& operator+= (const Rational& other);
	Rational& operator-= (const Rational& other);
	Rational& operator*= (const Rational& other);
	Rational& operator/= (const Rational& other);
	std::string toString() const;
private:
	int GCD(int left, int right) const; // поиск НОД
	void balance(); // приводит дробь к несократимому виду
private:
	int numerator = 0; // числитель
	int denominator = 1; // знаменатель, натуральное число
};

Rational& Rational::operator=(const Rational& other) {
	if (this == &other)
		return *this;
	numerator = other.numerator;
	denominator = other.denominator;
	return *this;
}

Rational& Rational::operator=(Rational&& other) noexcept{
	if (this == &other)
		return *this;
	numerator = other.numerator;
	denominator = other.denominator;
	return *this;
}

int Rational::GCD(int left, int right) const {
	left = left < 0 ? -left : left;
	right = right < 0 ? -right : right;
	while (left != 0 && right != 0) {
		if (left > right) {
			left %= right;
		}
		else {
			right %= left;
		}
	}
	return right + left;
}

bool operator< (const Rational& left, const Rational& right) {
	if (left.denominator == right.denominator) {
		return left.numerator < right.numerator;
	}
	return left.numerator * right.denominator < left.denominator * right.numerator;
}
bool operator== (const Rational& left, const Rational& right) {
	return left.numerator == right.numerator && left.denominator == right.denominator;
}
bool operator!= (const Rational& left, const Rational& right) {
	return !(left == right);
}
bool operator<= (const Rational& left, const Rational& right) {
	return (left < right) || (left == right);
}
bool operator>= (const Rational& left, const Rational& right) {
	return !(left < right);
}
bool operator> (const Rational& left, const Rational& right) {
	return (left != right) && (left >= right);
}

void Rational::balance() {
	int gcd = GCD(denominator, numerator);
	if (gcd != 1) {
		denominator /= gcd;
		numerator /= gcd;
	}
}

Rational Rational::operator+() const {
	return *this;
}

Rational Rational::operator-() const {
	return Rational(-numerator, denominator);
}

const Rational operator+ (const Rational& left, const Rational& right) {
	return Rational(left) += right;
}

const Rational operator- (const Rational& left, const Rational& right) {
	return Rational(left) -= right;
}

const Rational operator* (const Rational& left, const Rational& right) {
	return Rational(left) *= right;
}

const Rational operator/ (const Rational& left, const Rational& right) {
	return Rational(left) /= right;
}

Rational& Rational::operator+= (const Rational& other) {
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator *= other.denominator;
	balance();
	return *this;
}

Rational& Rational::operator-= (const Rational& other) {
	numerator = numerator * other.denominator - other.numerator * denominator;
	denominator *= other.denominator;
	balance();
	return *this;
}

Rational& Rational::operator*= (const Rational& other) {
	numerator *= other.numerator;
	denominator *= other.denominator;
	balance();
	return *this;
}

Rational& Rational::operator/= (const Rational& other) {
	numerator *= other.denominator;
	denominator *= other.numerator;
	balance();
	return *this;
}

std::string Rational::toString() const {
	std::string str;
	str.append(std::to_string(numerator));
	if (denominator != 1) {
		str += "/" + std::to_string(denominator);
	}
	return str;
}

std::ostream& operator<< (std::ostream& out, const Rational& rational) {
	out << rational.toString();
	return out;
}

std::istream& operator>> (std::istream& in, Rational& rational) {
	int numerator;
	int denominator;
	in >> numerator;
	in >> denominator;
	rational = Rational(numerator, denominator);
	return in;
}
