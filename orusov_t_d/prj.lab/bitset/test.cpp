#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <bitset/bitset.h>
#include <sstream>

bool operator==(const BitSet& left, const BitSet& right) {
    if (left.Size() != right.Size()) {
        return false;
    }
    for (int i = 0; i < left.Size(); ++i) {
        if (left.At(i) != right.At(i)) {
            return false;
        }
    }
    return true;
}

TEST_CASE("constructor") {
    SUBCASE("simple init") {
        BitSet bitset();
    }
    SUBCASE("simple init with size") {
        int size = 40;
        BitSet bitset(size, true);
        CHECK(bitset.Size() == size);
        for (int i = 0; i < bitset.Size(); ++i) {
            CHECK(bitset.At(i));
        }
    }
    SUBCASE("copy constructor") {
        int size = 40;
        BitSet bitset(size, true);
        BitSet other = bitset;
        CHECK(other == bitset);
    }
    SUBCASE("move constructor") {
        int size = 40;
        BitSet bitset(size, true);
        BitSet other_copy = bitset;
        BitSet other = std::move(bitset);
        CHECK(other == other_copy);
    }
    SUBCASE("copy operator") {
        int size = 40;
        BitSet bitset(size, true);
        BitSet other;
        other = bitset;
        CHECK(other == bitset);
    }
    SUBCASE("move operator") {
        int size = 40;
        BitSet bitset(size, true);
        BitSet other_copy = bitset;
        BitSet other;
        other = std::move(bitset);
        CHECK(other == other_copy);
    }
}



TEST_CASE("resize") {
    SUBCASE("resize to bigger") {
        int size = 40;
        BitSet bitset(size, true);
        int new_size = 44;
        bitset.Resize(new_size);
        CHECK(bitset.Size() == new_size);
        for (int i = 0; i < size; ++i) {
            CHECK(bitset.At(i));
        }
        for (int i = size; i < new_size; ++i) {
            CHECK_FALSE(bitset.At(i));
        }
    }
    SUBCASE("resize to smaller") {
        int size = 40;
        BitSet bitset(size, true);
        int new_size = 22;
        bitset.Resize(new_size);
        CHECK(bitset.Size() == new_size);
        for (int i = 0; i < new_size; ++i) {
            CHECK(bitset.At(i));
        }
    }
}

TEST_CASE("operators") {
    SUBCASE("simple operator~") {
        int size = 40;
        BitSet bitset(size, true);
        auto minus_bitset = ~bitset;
        CHECK(minus_bitset.Size() == size);
        for (int i = 0; i < size; ++i) {
            CHECK_FALSE(minus_bitset.At(i));
        }
        auto plus_bitset = ~minus_bitset;
        CHECK(plus_bitset.Size() == size);
        for (int i = 0; i < size; ++i) {
            CHECK(plus_bitset == bitset);
        }
    }
}
