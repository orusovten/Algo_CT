#include "m3i.h"

int min(int a, int b) {
    return a < b ? a : b;
}

void M3i::initialize(int*** arr, int d1, int d2, int d3) {
    arr = new int**[d1];
    for (int i = 0; i < d1; ++i) {
        arr[i] = new int*[d2];
        for (int j = 0; j < d2; ++j) {
            arr[i][j] = new int[d3];
            for (int k = 0; k < d3; ++k) {
                arr[i][j][k] = int();
            }
        }
    }
}

M3i::M3i(int d1, int d2, int d3): 
    d1_(new int(d1)), d2_(new int(d2)), d3_(new int(d3)), count_(new int(1))
{
    initialize(arr_, *d1_, *d2_, *d3_);
}

M3i::M3i(const il3int& list) {
    d1_ = new int(list.size());
    d2_ = new int (list.begin()->size());
    d3_ = new int(list.begin()->begin()->size());
    count_ = new int(1);
    initialize(arr_, *d1_, *d2_, *d3_);
    int i = 0;
    int j = 0;
    int k = 0;
    for (const auto& sublist: list) {
        j = 0;
        for (const auto& subsublist: sublist) {
            k = 0;
            for (const auto& elem: subsublist) {
                arr_[i][j][k] = elem;
                ++k;
            }
            ++j;
        }
        ++i;
    }
}

void M3i::clear() {
    for (int i = 0; i < *d1_; ++i) {
        for (int j = 0; j < *d2_; ++j) {
            delete[] arr_[i][j];
        }
        delete[] arr_[i];
    }
    delete[] arr_;
}

M3i::M3i(const M3i& other): 
    arr_(other.arr_), d1_(other.d1_), d2_(other.d2_), d3_(other.d3_), count_(other.count_)
{
    ++(*count_);
}

M3i& M3i::operator=(const M3i& other) {
    if (this == &other) {
        return *this;
    }
    arr_ = other.arr_;
    d1_ = other.d1_;
    d2_ = other.d2_;
    d3_ = other.d3_;
    count_ = other.count_;
    ++(*count_);
    return *this;
}
 
M3i::M3i(M3i&& other): 
    arr_(other.arr_), d1_(other.d1_), d2_(other.d2_), d3_(other.d3_), count_(other.count_) {
    other.arr_ = nullptr;
    other.d1_ = nullptr;
    other.d2_ = nullptr;
    other.d3_ = nullptr;
    other.count_ = nullptr;
}

M3i& M3i::operator=(M3i&& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    arr_ = other.arr_;
    other.arr_ = nullptr;
    count_ = other.count_;
    other.count_ = nullptr;
    d1_ = other.d1_;
    d2_ = other.d2_;
    d3_ = other.d3_;
    return *this;
}

M3i::~M3i() {
    if (--(*count_) == 0) {
        clear();
        delete d1_;
        delete d2_;
        delete d3_;
        delete count_;
    }
}

int& M3i::at(int i, int j, int k) {
    return arr_[i][j][k];
}
    
int M3i::at(int i, int j, int k) const {
    return arr_[i][j][k];
}

M3i M3i::clone() const {
    M3i copy(*d1_, *d2_, *d3_);
    for (int i = 0; i < *d1_; ++i) {
        for (int j = 0; j < *d2_; ++j) {
            for (int k = 0; k < *d3_; ++k) {
                copy.at(i, j, k) = arr_[i][j][k];
            }
        }
    }
    return copy;
}

M3i& M3i::resize(int d1, int d2, int d3) {
    int*** new_arr;
    initialize(new_arr, d1, d2, d3);
    for (int i = 0; i < min(*d1_, d1); ++i) {
        for (int j = 0; j < min(*d2_, d2); ++j) {
            for (int k = 0; k < min(*d3_, d3); ++k) {              
                new_arr[i][j][k] = arr_[i][j][k];
            }
        }
    }
    clear();
    arr_ = new_arr;
    delete d1_;
    delete d2_;
    delete d3_;
    d1_ = new int(d1);
    d2_ = new int(d2);
    d3_ = new int(d3);
    return *this;
}

int M3i::size(int dim) const {
    if (dim == 0) {
        return *d1_;
    } else if (dim == 1) {
        return *d2_;
    }
    return *d3_;
}

void M3i::fill(int val) {
    for(int i = 0; i < *d1_; ++i) {
        for(int j = 0; j < *d2_; ++j) {
            for (int k = 0; k < *d3_; ++k) {
                arr_[i][j][k] == val;
            }
        }
    }
}


std::ostream& operator<<(std::ostream& ostrm, const M3i& m) {
    for(int i = 0; i < m.size(0); ++i) {
        for(int j = 0; j < m.size(1); ++j) {
            for (int k = 0; k < m.size(2); ++k) {
                ostrm << m.at(i, j, k) << " ";
            }
            ostrm << std::endl;
        }
        ostrm << std::endl;
    }
    return ostrm;
}
