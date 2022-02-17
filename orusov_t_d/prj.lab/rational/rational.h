#include <iostream>
#include <string>


class Rational {
public:
	class NullDenomException : public std::exception {};
    class InvalidInputException : public std::exception {};
	Rational() = default;
	Rational(const Rational& other) = default;
	Rational(Rational&& other) = default;
	Rational(int numerator, int denominator);
	~Rational() = default;

	Rational& operator= (const Rational& other) = default;
	Rational& operator= (Rational&& other) noexcept = default;

	Rational operator-() const;
	Rational operator+() const;

	Rational& operator+= (const Rational& other);
	Rational& operator-= (const Rational& other);
	Rational& operator*= (const Rational& other);
	Rational& operator/= (const Rational& other);

    int GetNumerator() const;
    int GetDenominator() const;

	std::string ToString() const;
private:
	int GCD(int left, int right) const; // поиск НОД
	void Balance(); // приводит дробь к несократимому виду
private:
	int numerator_ = 0; // числитель
	int denominator_ = 1; // знаменатель, натуральное число
};

bool operator< (const Rational& left, const Rational& right);
bool operator== (const Rational& left, const Rational& right);
bool operator!= (const Rational& left, const Rational& right);
bool operator<= (const Rational& left, const Rational& right);
bool operator>= (const Rational& left, const Rational& right);
bool operator> (const Rational& left, const Rational& right);

const Rational operator+ (const Rational& left, const Rational& right);
const Rational operator* (const Rational& left, const Rational& right);
const Rational operator- (const Rational& left, const Rational& right);
const Rational operator/ (const Rational& left, const Rational& right);
