#pragma once
#ifndef BITSET_HEAD_H_2022_03_29
#define BITSET_HEAD_H_2022_03_29
#include <vector>
#include <cstdint>
#include <iosfwd>

class BitSet {
private:
    // класс BoolHolder - деталь реализации
    class BoolHolder;
public:
    BitSet() = default;
    BitSet(const BitSet& other) = default;
    BitSet(BitSet&& other) = default;
    ~BitSet() = default;
    BitSet& operator=(const BitSet& other) = default;
    BitSet& operator=(BitSet&& other) = default;
    BitSet(const int size, const bool val = false);
    int Size() const;
    void Resize(const int size);
    bool operator[](const int index) const;
    BoolHolder operator[](const int index);
    BitSet& operator|=(const BitSet& other);
    BitSet& operator&=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);
    BitSet operator~() const;

    // метод At - деталь реализации
    bool At(const int index) const; 
    // BoolHolder At(const int index);
private:
    // класс BoolHolder - деталь реализации
    class BoolHolder {
        BoolHolder& operator=(const BoolHolder& other);
        private:
            BoolHolder();
            unsigned char* ptr_;
    };
    std::vector<uint16_t> array_; 
    int size_ = 0;
    static const int BIT_SIZE = 16;
};

const BitSet operator^ (const BitSet& left, const BitSet& right);
const BitSet operator& (const BitSet& left, const BitSet& right);
const BitSet operator| (const BitSet& left, const BitSet& right);

std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);

#endif // #define BITSET_HEAD_H_2022_03_29
