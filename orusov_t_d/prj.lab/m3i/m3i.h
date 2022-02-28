#include <iostream>
#include <initializer_list>
typedef std::initializer_list<std::initializer_list<std::initializer_list<int>>> il3int;

class M3i {
public:
    M3i() = default; // done
    M3i(int d1, int d2, int d3); // done
    // мой вариант конструктора от std::initializer_list
    M3i(const il3int& list); // done
    // легкая копия(подсчет ссылок)
    M3i(const M3i& other); // done, but questions
    // легкая копия(подсчет ссылок)
    M3i& operator=(const M3i& other); // done, but questions

    M3i(M3i&& other); // done, but questions
    M3i& operator=(M3i&& other); // done, but questions

    ~M3i(); // done
    
    // полная копия данных
    M3i clone() const; // done

    M3i& resize(int d1, int d2, int d3); // done

    // доступ к элементу
    int& at(int i, int j, int k); // done
    int at(int i, int j, int k) const; // done

    // получение размера по измерению 0, 1, 2
    int size(int dim) const; // done
    // заполнение значениями
    void fill(int val); // done
private:
    void initialize(int*** arr, int d1, int d2, int d3); // заполнение arr значениями по умолчанию
    void clear(); // очистка данных
    int*** arr_; // буфер
    int* d1_; // измерение 1
    int* d2_; // измерение 2
    int* d3_; // измерение 3
    int* count_; // кол-во ссылок
};

std::istream& operator>>(std::istream& istrm, M3i& m);
std::ostream& operator<<(std::ostream& ostrm, const M3i& m); // done
