#pragma once
#ifndef BITSET_HEAD_H_2022_03_03
#define BITSET_HEAD_H_2022_03_03

class Bitset {
public:
    Bitset();
    Bitset(const Bitset& other);
    Bitset(Bitset&& other);
    ~Bitset();
    Bitset& operator=(const Bitset& other);
    Bitset& operator=(Bitset&& other);
    Bitset(const int size, const bool val = false);
    int Size() const;
    void Resize(const int size);
    bool operator[](const int index) const;
    Bitset& operator|(const Bitset& other);
    Bitset& operator&(const Bitset& other);
    Bitset& operator^(const Bitset& other);
    Bitset& operator~();
private:
    class BoolHolder {
        BoolHolder& operator=(const BoolHolder& other);
        private:
            BoolHolder();
            unsigned char* ptr_;
    };
};

#endif // #define BITSET_HEAD_H_2022_03_03
