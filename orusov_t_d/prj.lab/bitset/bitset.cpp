#include <bitset/bitset.h>
// #include "bitset.h"
#include <stdexcept>
#include <iostream>


int min(int a, int b) {
    return a < b ? a : b;
}

BitSet::BitSet(const int size, const bool val) {
    if (size <= 0) {
        throw std::invalid_argument("size should be positive");
    }
    size_ = size;
    uint16_t value = val ? UINT16_MAX : 0; 
    array_ = std::vector<uint16_t>(size / BIT_SIZE, value);
    int rest = size % BIT_SIZE;
    if (rest > 0) {
        array_.push_back(value >> (BIT_SIZE - rest));
    }
}

int BitSet::Size() const {
    return size_;
}

void BitSet::Resize(const int size) {
    std::vector<uint16_t> new_array = std::vector<uint16_t>(size / BIT_SIZE, 0);
    if (size < size_) {
        for (int i = 0; i < new_array.size(); ++i) {
            new_array[i] = array_[i];
        }
        int rest = size % BIT_SIZE;
        if (rest > 0) {
            new_array.push_back(array_[new_array.size()] >> (BIT_SIZE - rest));
        }
    } else {
        for (int i = 0; i < array_.size(); ++i) {
            new_array[i] = array_[i];
        }
    }
    array_ = new_array;
    size_ = size;
}

bool BitSet::At(const int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("out of range");
    }
    uint16_t mask = 1;
    int array_index = index / BIT_SIZE;
    return (array_[array_index] >> (index % BIT_SIZE)) & mask;
}

bool BitSet::operator[](const int index) const {
    return At(index);
}

BitSet& BitSet::operator|=(const BitSet& other) {
    for (int i = 0; i < min(array_.size(), other.array_.size()); ++i) {
        array_[i] |= other.array_[i];
    }
    // for (int i = other.array_.size(); i < array_.size(); ++i) {
    //     do nothing;
    // }
    for (int i = array_.size(); other.array_.size(); ++i) {
        array_.push_back(other.array_[i]);
    }
    return *this;
}

BitSet& BitSet::operator&=(const BitSet& other) {
    for (int i = 0; i < min(array_.size(), other.array_.size()); ++i) {
        array_[i] &= other.array_[i];
    }
    for (int i = other.array_.size(); i < array_.size(); ++i) {
        array_[i] = 0;
    }
    for (int i = array_.size(); other.array_.size(); ++i) {
        array_.push_back(0);
    }
    return *this;
}

BitSet& BitSet::operator^=(const BitSet& other) {
    for (int i = 0; i < min(array_.size(), other.array_.size()); ++i) {
        array_[i] ^= other.array_[i];
    }
    // for (int i = other.array_.size(); i < array_.size(); ++i) {
    //     do nothing;
    // }
    for (int i = array_.size(); other.array_.size(); ++i) {
        array_.push_back(other.array_[i]);
    }
    return *this;
}

const BitSet BitSet::operator~() const {
    BitSet new_bs = *this;
    for (int i = 0; i < size_ / BIT_SIZE; ++i) {
        new_bs.array_[i] = ~array_[i];
    }
    int rest = size_ % BIT_SIZE;
    if (rest > 0) {
        uint16_t mask = UINT16_MAX >> (BIT_SIZE - rest);
        new_bs.array_[array_.size() - 1] = mask & ~array_[array_.size() - 1];
    }
    return new_bs;
}

const BitSet operator^ (const BitSet& left, const BitSet& right) {
    return BitSet(left) ^= right;
}

const BitSet operator& (const BitSet& left, const BitSet& right) {
    return BitSet(left) &= right;
}

const BitSet operator| (const BitSet& left, const BitSet& right) {
    return BitSet(left) |= right;
}

std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs) {
    for (int i = 0; i < bs.Size(); ++i) {
        ostrm << bs.At(i);
    }
    return ostrm;
}

