#include "rational.h"

Rational::Rational(int numerator, int denominator = 1) :
	numerator_(numerator), denominator_(denominator) {
	// check that denominator > 0 and nod(num, den) == 1
	if (denominator_ == 0) {
		throw NullDenomException();
	}
	if (denominator_ < 0) {
		denominator_ *= -1;
		numerator_ *= -1;
	}
	Balance();
}

int Rational::GCD(int left, int right) const {
	left = left < 0 ? -left : left;
	right = right < 0 ? -right : right;
	while (left != 0 && right != 0) {
		if (left > right) {
			left %= right;
		} else {
			right %= left;
		}
	}
	return right + left;
}

int Rational::GetNumerator() const {
	return numerator_;
}
int Rational::GetDenominator() const {
	return denominator_;
}

bool operator< (const Rational& left, const Rational& right) {
	if (left.GetDenominator() == right.GetDenominator()) {
		return left.GetNumerator() < right.GetNumerator();
	}
	return left.GetNumerator() * right.GetDenominator() < left.GetDenominator() * right.GetNumerator();
}
bool operator== (const Rational& left, const Rational& right) {
	return left.GetNumerator() == right.GetNumerator() && left.GetDenominator() == right.GetDenominator();
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

void Rational::Balance() {
	int gcd = GCD(denominator_, numerator_);
	if (gcd != 1) {
		denominator_ /= gcd;
		numerator_ /= gcd;
	}
}

Rational Rational::operator+() const {
	return *this;
}

Rational Rational::operator-() const {
	return Rational(-numerator_, denominator_);
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
	numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
	denominator_ *= other.denominator_;
	Balance();
	return *this;
}

Rational& Rational::operator-= (const Rational& other) {
	numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
	denominator_ *= other.denominator_;
	Balance();
	return *this;
}

Rational& Rational::operator*= (const Rational& other) {
	numerator_ *= other.numerator_;
	denominator_ *= other.denominator_;
	Balance();
	return *this;
}

Rational& Rational::operator/= (const Rational& other) {
	if (other.numerator_ == 0) {
		throw NullDenomException();
	}
	numerator_ *= other.denominator_;
	denominator_ *= other.numerator_;
	Balance();
	return *this;
}

std::string Rational::ToString() const {
	std::string str;
	str.append(std::to_string(numerator_));
	str += "/" + std::to_string(denominator_);
	// std::cout << str << std::endl;
	return str;
}

std::ostream& operator<< (std::ostream& out, const Rational& rational) {
	out << rational.ToString();
	return out;
}

std::istream& operator>> (std::istream& in, Rational& rational) {
	char c;
	int numerator;
	int denominator;
	in >> numerator >> std::noskipws >> c >> std::skipws >> denominator;
	if (c != '/') {
		throw Rational::InvalidInputException();
	}
	rational = Rational(numerator, denominator);
	return in;
}
