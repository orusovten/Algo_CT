#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <bitset/bitset.h>
#include <sstream>

bool operator==(const BitSet& left, const BitSet& right) {
    if (left.Size() != right.Size()) {
        return false;
    }
    for (int i = 0; i < left.Size(); ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }
    return true;
}

TEST_CASE("constructor") {
    SUBCASE("simple init") {
        BitSet bitset();
    }
    SUBCASE("bad init") {
        CHECK_THROWS(BitSet(-1, true));
        CHECK_THROWS(BitSet(0, true));
    }
    SUBCASE("simple init with size") {
        int size = 40;
        BitSet bitset(size, true);
        CHECK(bitset.Size() == size);
        for (int i = 0; i < bitset.Size(); ++i) {
            CHECK(bitset[i]);
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
        for (int i = 0; i < size; i += 2) {
            bitset[i] = false;
        }
        BitSet old_bitset = bitset;
        int new_size = 60;
        bitset.Resize(new_size);
        CHECK(bitset.Size() == new_size);
        for (int i = 0; i < size; ++i) {
            CHECK(bitset[i] == old_bitset[i]);
        }
        for (int i = size; i < new_size; ++i) {
            CHECK_FALSE(bitset[i]);
        }
    }
    SUBCASE("resize to smaller") {
        int size = 40;
        BitSet bitset(size, true);
        for (int i = 0; i < size; i += 2) {
            bitset[i] = false;
        }
        BitSet old_bitset = bitset;
        int new_size = 22;
        bitset.Resize(new_size);
        CHECK(bitset.Size() == new_size);
        for (int i = 0; i < new_size; ++i) {
            CHECK(bitset[i] == old_bitset[i]);
        }
    }
    SUBCASE("bad resize") {
        int size = 40;
        BitSet bitset(size, true);
        CHECK_THROWS(bitset.Resize(0));
        CHECK_THROWS(bitset.Resize(-1));
    }
    SUBCASE("empty -> Resize + Fill")
	{
		BitSet first;
		CHECK(first.Size() == 0);
		first.Resize(10);
		CHECK(first.Size() == 10);
		first.Fill(true);
		for(int i = 0; i < first.Size(); ++i)
			CHECK(first[i]);
	}
}

TEST_CASE("fill") {
    int size = 40;
    BitSet positive_bitset(size, true);
    BitSet bitset = positive_bitset;
    BitSet minus_bitset(size, false);
    bitset.Fill(false);
    CHECK(minus_bitset == bitset);
    bitset.Fill(true);
    CHECK(positive_bitset == bitset);
}

TEST_CASE("operators") {
    SUBCASE("simple operator~") {
        int size = 40;
        BitSet bitset(size, true);
        auto minus_bitset = ~bitset;
        CHECK(minus_bitset.Size() == size);
        for (int i = 0; i < size; ++i) {
            CHECK_FALSE(minus_bitset[i]);
        }
        auto plus_bitset = ~minus_bitset;
        CHECK(plus_bitset.Size() == size);
        for (int i = 0; i < size; ++i) {
            CHECK(plus_bitset == bitset);
        }
    }
    SUBCASE("operator[] BitHolder") {
        int size = 40;
        BitSet bitset(size, true);
        for (int i = 0; i < size; ++i) {
            bitset[i] = false;
        }
        BitSet correct_bitset(size, false);
        CHECK(bitset == correct_bitset);
        CHECK_THROWS(bitset[-1]);
        CHECK_THROWS(bitset[size]);
    }
    SUBCASE("simple operators & and &=") {
        int size = 40;
        BitSet first(size, true);
        BitSet wrong_second(size + 1, true);
        CHECK_THROWS(first & wrong_second);
        CHECK_THROWS(first &= wrong_second);
        BitSet second(size, true);
        first[33] = 0;
        first[20] = 0;
        first[30] = 0;
        first[15] = 0;
        second[20] = 0;
        second[1] = 0;
        second[33] = 0;
        second[4] = 0;
        second[36] = 0;
        BitSet result(size, true);
        for (auto index : {1, 4, 15, 20, 30, 33, 36}) {
            result[index] = false;
        }
        auto res = first & second;
        CHECK(res == result);
        first &= second;
        CHECK(first == result);
    }
    SUBCASE("simple operators | and |=") {
        int size = 40;
        BitSet first(size, true);
        BitSet wrong_second(size + 1, true);
        CHECK_THROWS(first | wrong_second);
        CHECK_THROWS(first |= wrong_second);
        BitSet second(size, true);
        first[33] = 0;
        first[20] = 0;
        first[30] = 0;
        first[15] = 0;
        second[20] = 0;
        second[1] = 0;
        second[33] = 0;
        second[4] = 0;
        second[36] = 0;
        BitSet result(size, true);
        for (auto index : {20, 33}) {
            result[index] = false;
        }
        auto res = first | second;
        CHECK(res == result);
        first |= second;
        CHECK(first == result);
    }
    SUBCASE("simple operators ^ and ^=") {
        int size = 40;
        BitSet first(size, true);
        BitSet wrong_second(size + 1, true);
        CHECK_THROWS(first ^ wrong_second);
        CHECK_THROWS(first ^= wrong_second);
        BitSet second(size, true);
        first[33] = 0;
        first[20] = 0;
        first[30] = 0;
        first[15] = 0;
        second[20] = 0;
        second[1] = 0;
        second[33] = 0;
        second[4] = 0;
        second[36] = 0;
        BitSet result(size, false);
        for (auto index : {1, 4, 15, 30, 36}) {
            result[index] = true;
        }
        auto res = first ^ second;
        CHECK(res == result);
        first ^= second;
        CHECK(first == result);
    }
}   

TEST_CASE("input/output") {
    SUBCASE("good input/output") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "11111111000011110011";
        input_stream >> bitset;
        BitSet right_bitset(20, true);
        for (auto i : {8, 9, 10, 11, 16, 17}) {
            right_bitset[i] = false;
        }
        CHECK(bitset == right_bitset);
        std::stringstream output_stream;
        output_stream << bitset;
        std::string str_bitset;
        output_stream >> str_bitset;
        CHECK(str_bitset == "11111111000011110011");
    }
    SUBCASE("empty input") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "";
        input_stream >> bitset;
        CHECK(input_stream.fail());
    }
    SUBCASE("fail_1") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "10101010410101";
        input_stream >> bitset;
        CHECK(input_stream.fail());
    }
    SUBCASE("fail_2") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "10000100011ervnjh1123";
        input_stream >> bitset;
        CHECK(input_stream.fail());
    }
    SUBCASE("fail_3") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "111r000001";
        input_stream >> bitset;
        CHECK(input_stream.fail());
    }
    SUBCASE("eof") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "101010010111";
        input_stream >> bitset;
        CHECK(input_stream.eof());
    }
    SUBCASE("good") {
        BitSet bitset;
        std::stringstream input_stream;
        input_stream << "11110000111101 ";
        input_stream >> bitset;
        CHECK(input_stream.good());
    }
}
