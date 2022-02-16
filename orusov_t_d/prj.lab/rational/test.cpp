#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <rational.cpp>
#include <random>

TEST_CASE("create") {
    int a = rand() % 10000;
    int b = rand() % 10000 + 1;
    Rational number_1(a, b);
    Rational number_2 = number_1;
    Rational number_3;
    int c = rand() % 10000 + 1;
    Rational number_4(a * c, b * c);
    CHECK(number_1 == number_2);
    CHECK(number_1 != number_3);
    CHECK(number_1 == number_4);
    bool is_null_exception = false;
    try {
        Rational bad_number(a, 0);
    } catch (NullDenomException e) {
        is_null_exception = true;
    }
    CHECK(is_null_exception);
}


TEST_CASE("arithmetic operations") {
    int iter_count = 5;
    for (int i = 0; i < iter_count; ++i) {
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
    bool is_null_exception = false;
    try {
        Rational bad_1(1, 1);
        Rational bad_2(0, 1);
        bad_1 /= bad_2;
    } catch (NullDenomException e) {
        is_null_exception = true;
    }
    CHECK(is_null_exception);
}
