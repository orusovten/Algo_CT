#pragma once
#ifndef RATIONAL_RATIONAL_HEAD_H_2022_03_03
#define RATIONAL_RATIONAL_HEAD_H_2022_03_03

#include <string>
#include <exception>
#include <iosfwd>

class Rational {
public:
    class NullDenomException : public std::exception {};
	Rational() = default;
	Rational(const Rational& other) = default;
	Rational(Rational&& other) = default;
	Rational(int numerator);
	Rational(int numerator, int denominator);
	~Rational() = default;

	Rational& operator= (const Rational& other) = default;
	Rational& operator= (Rational&& other) noexcept = default;

	const Rational operator-() const;
	const Rational operator+() const;

	Rational& operator+= (const Rational& other);
	Rational& operator-= (const Rational& other);
	Rational& operator*= (const Rational& other);
	Rational& operator/= (const Rational& other);

	bool operator< (const Rational& other) const;
	bool operator== (const Rational& other) const;
	bool operator!= (const Rational& other) const;
	bool operator<= (const Rational& other) const;
	bool operator>= (const Rational& other) const;
	bool operator> (const Rational& other) const;

	int num() const;
    int denum() const;

	std::ostream& write_to(std::ostream& ostrm) const;
	std::istream& read_from(std::istream& istrm);
private:
	std::string to_string() const;
	int GCD(int left, int right) const; // поиск НОД
	void balance(); // приводит дробь к несократимому виду
private:
	int numerator_ = 0; // числитель
	int denominator_ = 1; // знаменатель, натуральное число
};

std::ostream& operator<< (std::ostream& out, const Rational& rational);
std::istream& operator>> (std::istream& in, Rational& rational);

const Rational operator+ (const Rational& left, const Rational& right);
const Rational operator* (const Rational& left, const Rational& right);
const Rational operator- (const Rational& left, const Rational& right);
const Rational operator/ (const Rational& left, const Rational& right);

#endif // #define RATIONAL_RATIONAL_HEAD_H_2022_03_03
