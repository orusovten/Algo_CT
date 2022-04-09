#include <bitset/bitset.h>
// #include "bitset.h"
#include <stdexcept>
#include <iostream>

BitSet::BitHolder::BitHolder(BitSet& bs, int index): 
    bs_(bs), index_(index)
{}

BitSet::BitHolder::operator bool() const {
    uint16_t mask = 1;
    int array_index = index_ / bs_.BIT_SIZE;
    return (bs_.array_[array_index] >> (index_ % bs_.BIT_SIZE)) & mask;
}

BitSet::BitHolder& BitSet::BitHolder::operator=(const bool val) {
    int array_index = index_ / bs_.BIT_SIZE;
    uint16_t mask = (1 << (index_ % bs_.BIT_SIZE)) ^ UINT16_MAX;
    if (val) {
        mask = ~mask;
        bs_.array_[array_index] |= mask;
    }
    else {
        bs_.array_[array_index] &= mask;
    }
    return *this;
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
    if (size <= 0) {
        throw std::invalid_argument("size should be positive");
    }
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

void BitSet::Fill(const bool val) {
    uint16_t value = val ? UINT16_MAX : 0; 
    for (int i = 0; i < size_ / BIT_SIZE; ++i) {
        array_[i] = value;
    }
    int rest = size_ % BIT_SIZE;
    if (rest > 0) {
        array_[array_.size() - 1] = value >> (BIT_SIZE - rest);
    }
}

bool BitSet::operator[](const int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("out of range");
    }
    uint16_t mask = 1;
    int array_index = index / BIT_SIZE;
    return (array_[array_index] >> (index % BIT_SIZE)) & mask;
}

BitSet::BitHolder BitSet::operator[](const int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("out of range");
    }
    return BitHolder(*this, index);
}

BitSet& BitSet::operator|=(const BitSet& other) {
    if (size_ != other.size_) {
        throw std::invalid_argument("sizes must be the same");
    }
    for (int i = 0; i < array_.size(); ++i) {
        array_[i] |= other.array_[i];
    }
    return *this;
}

BitSet& BitSet::operator&=(const BitSet& other) {
    if (size_ != other.size_) {
        throw std::invalid_argument("sizes must be the same");
    }
    for (int i = 0; i < array_.size(); ++i) {
        array_[i] &= other.array_[i];
    }
    return *this;
}

BitSet& BitSet::operator^=(const BitSet& other) {
    if (size_ != other.size_) {
        throw std::invalid_argument("sizes must be the same");
    }
    for (int i = 0; i < array_.size(); ++i) {
        array_[i] ^= other.array_[i];
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
        ostrm << bs[i];
    }
    return ostrm;
}

std::istream& operator>>(std::istream& istrm, BitSet& bs) {
    std::string bs_str;
    istrm >> bs_str;
    if (istrm.rdstate() == std::ios_base::failbit) {
		return istrm;
	}
    int size = bs_str.size();
    if (size == 0) {
        istrm.setstate(std::ios_base::failbit);
		return istrm;
    }
    bs = BitSet(size);
    for (int i = 0; i < size; ++i) {
        if (bs_str[i] == '1') {
            bs[i] = true;
        }
        else if (bs_str[i] != '0') {
            istrm.setstate(std::ios_base::failbit);
            return istrm; 
        }
	}
    return istrm;
}
