#pragma once
#ifndef BITSET_HEAD_H_2022_03_29
#define BITSET_HEAD_H_2022_03_29
#include <vector>
#include <cstdint>
#include <iosfwd>

class BitSet {
private:
    // класс BitHolder - деталь реализации
    class BitHolder;
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
    void Fill(const bool val); // not done
    bool operator[](const int index) const;
    BitHolder operator[](const int index);
    BitSet& operator|=(const BitSet& other);
    BitSet& operator&=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);
    const BitSet operator~() const;
private:
    // класс BitHolder - деталь реализации
    class BitHolder {
        public:
            BitHolder(BitSet& bs, int index);
            BitHolder(const BitHolder& other) = default;
            BitHolder(BitHolder&& other) = default;
            ~BitHolder() = default;
            BitHolder& operator=(const BitHolder& other) = default;
            BitHolder& operator=(BitHolder&& other) = default;
            BitHolder& operator=(const bool val);
            operator bool() const;
        private:
            BitHolder();
            BitSet& bs_;
            int index_;
    };
    std::vector<uint16_t> array_; 
    int size_ = 0;
    static const int BIT_SIZE = 16;
};

const BitSet operator^ (const BitSet& left, const BitSet& right);
const BitSet operator& (const BitSet& left, const BitSet& right);
const BitSet operator| (const BitSet& left, const BitSet& right);

std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);
std::istream& operator<<(std::istream& istrm, BitSet& bs);

#endif // #define BITSET_HEAD_H_2022_03_29
