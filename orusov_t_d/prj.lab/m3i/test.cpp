#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include "doctest.h"
#include "m3i.cpp"

using namespace details;

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
        for(int i = 0; i < d1; ++i) {
            for(int j = 0; j < d2; ++j) {
                for(int k = 0; k < d3; ++k) {
                    CHECK(m3i.At(i, j, k) == copy_m3i.At(i, j, k));
                }
            }
        }
        copy_m3i = m3i;
        for(int i = 0; i < d1; ++i) {
            for(int j = 0; j < d2; ++j) {
                for(int k = 0; k < d3; ++k) {
                    CHECK(m3i.At(i, j, k) == copy_m3i.At(i, j, k));
                }
            }
        }
    }
    SUBCASE("move")
    {
        int d1 = 2;
        int d2 = 3;
        int d3 = 4;
        M3i m3i(d1, d2, d3);
        M3i copy_m3i = m3i;
        M3i move_m3i(std::move(m3i));
        for(int i = 0; i < d1; ++i) {
            for(int j = 0; j < d2; ++j) {
                for(int k = 0; k < d3; ++k) {
                    CHECK(move_m3i.At(i, j, k) == copy_m3i.At(i, j, k));
                }
            }
        }
        M3i second_m3i(d1, d2, d3);
        move_m3i = std::move(second_m3i);
        for(int i = 0; i < d1; ++i) {
            for(int j = 0; j < d2; ++j) {
                for(int k = 0; k < d3; ++k) {
                    CHECK(move_m3i.At(i, j, k) == copy_m3i.At(i, j, k));
                }
            }
        }
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
    CHECK(copy.Size(0) == 3);
    CHECK(copy.Size(1) == 1);
    CHECK(copy.Size(2) == 5);
    for (int i = 0; i < m3i.Size(0); ++i) {
        for (int j = 0; j < m3i.Size(1); ++j) {
            for (int k = 0; k < m3i.Size(2); ++k) {
                CHECK(m3i.At(i, j, k) == copy.At(i, j, k));
            }
        }
    }
}

TEST_CASE("fill")
{
    M3i m3i = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    M3i copy = m3i;
    m3i.Fill(4);
    for (int i = 0; i < m3i.Size(0); ++i) {
        for (int j = 0; j < m3i.Size(1); ++j) {
            for (int k = 0; k < m3i.Size(2); ++k) {
                CHECK(m3i.At(i, j, k) == copy.At(i, j, k));
                CHECK(m3i.At(i, j, k) == 4);
            }
        }
    }
}
