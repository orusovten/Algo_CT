#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <doctest/doctest.h.
#include <m3i/m3i.h>
#include <sstream>

using namespace details;

bool operator== (const M3i& left, const M3i& right) {
    if ((left.Size(0) != right.Size(0)) || (left.Size(1) != right.Size(1)) || 
                                            (left.Size(2) != right.Size(2))) {
        return false;
    }
    for(int i = 0; i < left.Size(0); ++i) {
        for(int j = 0; j < left.Size(1); ++j) {
            for(int k = 0; k < left.Size(2); ++k) {
                if (left.At(i, j, k) != right.At(i, j, k)) {
                    return false;
                }                
            }
        }
    }
    return true;
}

TEST_CASE("init")
{
    SUBCASE("simple init")
    {
        int d1 = 2;
        int d2 = 3;
        int d3 = 4;
        M3i m3i(d1, d2, d3);
        CHECK(m3i.Size(0) == d1);
        CHECK(m3i.Size(1) == d2);
        CHECK(m3i.Size(2) == d3);
        CHECK_THROWS(m3i.Size(3));
        for(int i = 0; i < d1; ++i) {
            for(int j = 0; j < d2; ++j) {
                for(int k = 0; k < d3; ++k) {
                    CHECK(m3i.At(i, j, k) == int());
                }
            }
        }
    }
    SUBCASE("copy")
    {
        int d1 = 2;
        int d2 = 3;
        int d3 = 4;
        M3i m3i(d1, d2, d3);
        M3i copy_m3i(m3i);
        CHECK(copy_m3i == m3i);
        copy_m3i = m3i;
        CHECK(copy_m3i == m3i);
    }
    SUBCASE("move")
    {
        int d1 = 2;
        int d2 = 3;
        int d3 = 4;
        M3i m3i(d1, d2, d3);
        M3i copy_m3i = m3i;
        M3i move_m3i(std::move(m3i));
        CHECK(move_m3i == copy_m3i);
        M3i second_m3i(d1, d2, d3);
        move_m3i = std::move(second_m3i);
        CHECK(move_m3i == copy_m3i);
    }
    SUBCASE("init by list")
    {
        M3i m3i = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
        CHECK(m3i.Size(0) == 2);
        CHECK(m3i.Size(1) == 2);
        CHECK(m3i.Size(2) == 3);
        for (int i = 0; i < m3i.Size(0); ++i) {
            for (int j = 0; j < m3i.Size(1); ++j) {
                for (int k = 0; k < m3i.Size(2); ++k) {
                    CHECK(m3i.At(i, j, k) == 1 + i * m3i.Size(2) * m3i.Size(1) + j * m3i.Size(2)  + k);
                }
            }
        }
    }
}

TEST_CASE("resize")
{
    M3i m3i = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    M3i copy = m3i;
    m3i.Resize(3, 1, 5);
    CHECK(m3i.Size(0) == 3);
    CHECK(m3i.Size(1) == 1);
    CHECK(m3i.Size(2) == 5);
    // то, что должно получиться после Resize
    M3i right_resized_m3i = {{{1, 2, 3, 0, 0}}, {{7, 8, 9, 0, 0}}, {{0, 0, 0, 0, 0}}};
    for (int i = 0; i < m3i.Size(0); ++i) {
        for (int j = 0; j < m3i.Size(1); ++j) {
            for (int k = 0; k < m3i.Size(2); ++k) {
                CHECK(m3i.At(i, j, k) == right_resized_m3i.At(i, j, k));
            }
        }
    }
    CHECK(copy == m3i);
}

TEST_CASE("fill")
{
    M3i m3i = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    M3i copy = m3i;
    m3i.Fill(4);
    for (int i = 0; i < m3i.Size(0); ++i) {
        for (int j = 0; j < m3i.Size(1); ++j) {
            for (int k = 0; k < m3i.Size(2); ++k) {
                CHECK(m3i.At(i, j, k) == 4);
            }
        }
    }
    CHECK(copy == m3i);
}

TEST_CASE("input/output") {
    M3i m3i;
    std::stringstream input_stream;
    input_stream << "2 2 3\n 1 2 3\n 4 5 6\n 7 8 9\n 10 11 12\n";
    input_stream >> m3i;
    M3i right_m3i = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    CHECK(m3i == right_m3i);
    std::stringstream output_stream;
    output_stream << m3i;
    std::string str_m3i;
    output_stream >> str_m3i;
    CHECK(str_m3i == "size:");
    int d1;
    int d2;
    int d3;
    output_stream >> d1;
    output_stream >> d2;
    output_stream >> d3;
    CHECK(d1 == 2);
    CHECK(d2 == 2);
    CHECK(d3 == 3);
    for(int i = 0; i < d1; ++i) {
        for(int j = 0; j < d2; ++j) {
            for(int k = 0; k < d3; ++k) {
                int number;
                output_stream >> number;
                CHECK(right_m3i.At(i, j, k) == number);    
            }
        }
    }
}
