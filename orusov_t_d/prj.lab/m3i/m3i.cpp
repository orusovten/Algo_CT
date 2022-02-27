#include "m3i.h"

int min(int a, int b) {
    return a < b ? a : b;
}

void M3i::initialize() {
    arr_ = new int**[d1_];
    for (int i = 0; i < d1_; ++i) {
        arr_[i] = new int*[d2_];
        for (int j = 0; j < d2_; ++j) {
            arr_[i][j] = new int[d3_];
            for (int k = 0; k < d3_; ++k) {
                arr_[i][j][k] = int();
            }
        }
    }
}

M3i::M3i(int d1, int d2, int d3): d1_(d1), d2_(d2), d3_(d3) {
    initialize();
}

M3i::M3i(const il3int& list) {
    d1_ = list.size(); 
    d2_ = list.begin()->size();
    d3_ = list.begin()->begin()->size();
    initialize();
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
    for (int i = 0; i < d1_; ++i) {
        for (int j = 0; j < d2_; ++j) {
            delete[] arr_[i][j];
        }
        delete[] arr_[i];
    }
    delete[] arr_;
}

M3i::M3i(M3i&& other): 
    arr_(other.arr_), d1_(other.d1_), d2_(other.d2_), d3_(other.d3_) {
    other.arr_ = nullptr;
}

M3i& M3i::operator=(M3i&& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    arr_ = other.arr_;
    other.arr_ = nullptr;
    d1_ = other.d1_;
    d2_ = other.d2_;
    d3_ = other.d3_;
    return *this;
}

M3i::~M3i() {
    clear();
}

int& M3i::at(int i, int j, int k) {
    return arr_[i][j][k];
}
    
int M3i::at(int i, int j, int k) const {
    return arr_[i][j][k];
}

M3i M3i::clone() const {
    M3i copy(d1_, d2_, d3_);
    for (int i = 0; i < d1_; ++i) {
        for (int j = 0; j < d2_; ++j) {
            for (int k = 0; k < d3_; ++k) {
                copy.at(i, j, k) = arr_[i][j][k];
            }
        }
    }
    return copy;
}

M3i& M3i::resize(int d1, int d2, int d3) {
    int*** old_arr = arr_;
    int old_d1 = d1_;
    int old_d2 = d2_;
    int old_d3 = d3_;
    d1_ = d1;
    d2_ = d2;
    d3_ = d3;
    initialize();
    for (int i = 0; i < min(d1_, old_d1); ++i) {
        for (int j = 0; j < min(d2_, old_d2); ++j) {
            for (int k = 0; k < min(d3_, old_d3); ++k) {              
                arr_[i][j][k] = old_arr[i][j][k];
            }
        }
    }
    return *this;
}

int M3i::size(int dim) const {
    if (dim == 0) {
        return d1_;
    } else if (dim == 1) {
        return d2_;
    }
    return d3_;
}

void M3i::fill(int val) {
    for(int i = 0; i < d1_; ++i) {
        for(int j = 0; j < d2_; ++j) {
            for (int k = 0; k < d3_; ++k) {
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
