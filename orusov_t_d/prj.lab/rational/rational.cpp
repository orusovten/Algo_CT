#include <rational/rational.h>
#include <iostream>

Rational::Rational(int numerator):
	numerator_(numerator), denominator_(1) {}

Rational::Rational(int numerator, int denominator = 1) :
	numerator_(numerator), denominator_(denominator) {
	// check that denominator > 0 and nod(num, den) == 1
	if (denominator_ == 0) {
		throw NullDenomException();
	}
	balance();
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

int Rational::num() const {
	return numerator_;
}
int Rational::denum() const {
	return denominator_;
}

bool Rational::operator< (const Rational& other) const {
	if (denominator_ == other.denominator_) {
		return numerator_ < other.numerator_;
	}
	return numerator_ * other.denominator_ < denominator_ * other.numerator_;
}
bool Rational::operator== (const Rational& other) const {
	return numerator_ == other.numerator_ && denominator_ == other.denominator_;
}
bool Rational::operator!= (const Rational& other) const {
	return !(*this == other);
}
bool Rational::operator<= (const Rational& other) const {
	return (*this < other) || (*this == other);
}
bool Rational::operator>= (const Rational& other) const {
	return !(*this < other);
}
bool Rational::operator> (const Rational& other) const {
	return (*this != other) && (*this >= other);
}

void Rational::balance() {
	int gcd = GCD(denominator_, numerator_);
	if (gcd != 1) {
		denominator_ /= gcd;
		numerator_ /= gcd;
	}
	if (denominator_ < 0) {
		denominator_ *= -1;
		numerator_ *= -1;
	}
}

const Rational Rational::operator+() const {
	return *this;
}

const Rational Rational::operator-() const {
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
	balance();
	return *this;
}

Rational& Rational::operator-= (const Rational& other) {
	numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
	denominator_ *= other.denominator_;
	balance();
	return *this;
}

Rational& Rational::operator*= (const Rational& other) {
	numerator_ *= other.numerator_;
	denominator_ *= other.denominator_;
	balance();
	return *this;
}

Rational& Rational::operator/= (const Rational& other) {
	if (other.numerator_ == 0) {
		throw NullDenomException();
	}
	numerator_ *= other.denominator_;
	denominator_ *= other.numerator_;
	balance();
	return *this;
}

std::string Rational::to_string() const {
	std::string str = std::to_string(numerator_) + "/" + std::to_string(denominator_);
	return str;
}

std::ostream& Rational::write_to(std::ostream& ostrm) const {
	ostrm << to_string();
	return ostrm;
}

std::istream& Rational::read_from(std::istream& istrm) {
	char c;
	int numerator;
	int denominator;
	istrm >> numerator >> std::noskipws >> c >> denominator >> std::skipws;
	if (istrm.rdstate() == std::ios_base::failbit) {
		return istrm;
	}
	if (c != '/' || denominator <= 0) {
		istrm.setstate(std::ios_base::failbit);
		return istrm;
	}
	*this = Rational(numerator, denominator);
	return istrm;
}

std::ostream& operator<< (std::ostream& out, const Rational& rational) {
	return rational.write_to(out);
}

std::istream& operator>> (std::istream& in, Rational& rational) {
	return rational.read_from(in);
}
