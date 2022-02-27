#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.cpp"
#include <random>
#include <sstream>


void CreateWithZeroNumerator() {
    Rational badNumber(1, 0);
}
TEST_CASE("create with zero numerator") {
    CHECK_THROWS(CreateWithZeroNumerator());
}

TEST_CASE("comparison operations") {
    Rational small_number(2, 3);
    Rational second_small_number(2, 3);
    Rational big_number(5, 6);
    CHECK(small_number == second_small_number);
    CHECK(small_number <= second_small_number);
    CHECK(small_number <= big_number);
    CHECK(small_number < big_number);
    CHECK(small_number != big_number);
    CHECK_FALSE(small_number > big_number);
    CHECK_FALSE(small_number >= big_number);
}

TEST_CASE("zero case") {
    Rational default_number;
    CHECK(default_number.num() == 0);
    CHECK(default_number.denum() == 1);
    Rational zero_number(0, 3);
    CHECK(zero_number == default_number);
}

TEST_CASE("same irreducible appearance case") {
    int a = rand() % 10000;
    int b = rand() % 10000 + 1;
    Rational number_1(a, b);
    Rational number_2(-a, -b);
    int c = rand() % 1000 + 2;
    Rational number_3(a * c, b * c);
    Rational number_4(-a * c, -b * c);
    CHECK(number_1 == number_2);
    CHECK(number_1 == number_3);
    CHECK(number_1 == number_4);
}

TEST_CASE("create") {
    int a = rand() % 10000;
    int b = rand() % 10000 + 1;
    Rational number_1(a, b);
    Rational number_2 = number_1;
    Rational number_3;
    int c = rand() % 10000 + 1;
    CHECK(number_1 == number_2);
    CHECK(number_1 != number_3);
    bool is_null_exception = false;
}



TEST_CASE("arithmetic operations") {
    int iterCount = 5;
    for (int i = 0; i < iterCount; ++i) {
        int a = rand() % 10000;
        int b = rand() % 10000 + 1;
        int c = rand() % 10000 + 1;
        int d = rand() % 10000 + 1;
        Rational number_1(a, b);
        Rational number_2(c, d);
        Rational sum(a * d + b * c, b * d);
        Rational mult(a * c, b * d);
        Rational diff(a * d - b * c, b * d);
        Rational div(a * d, b * c);
        CHECK(number_1 + number_2 == sum);
        CHECK(number_1 * number_2 == mult);
        CHECK(number_1 - number_2 == diff);
        CHECK(number_1 / number_2 == div);
    }
}

TEST_CASE("zero division case") {
    Rational dividend(1, 1);
    Rational zero_divisor;
    CHECK_THROWS(dividend / zero_divisor);
}

TEST_CASE("input/output") {
    Rational number;
    std::stringstream input_stream;
    input_stream << "15/9";
    input_stream >> number;
    CHECK(number == Rational(5, 3));
    std::stringstream output_stream;
    output_stream << number;
    std::string str_number;
    output_stream >> str_number;
    CHECK(str_number == "5/3");
}

void ZeroDenominatorInput() {
    Rational number;
    std::stringstream input_stream;
    input_stream << "15/0";
    input_stream >> number;
}

void InvalidInput() {
    Rational number;
    std::stringstream input_stream;
    input_stream << "15rd2";
    input_stream >> number;
}

TEST_CASE("invalid input") {
    CHECK_THROWS(ZeroDenominatorInput());
    CHECK_THROWS(InvalidInput());
}
