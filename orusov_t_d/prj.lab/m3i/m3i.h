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
    M3i(const M3i&);
    // легкая копия(подсчет ссылок)
    M3i& operator=(const M3i&);

    M3i(M3i&& other); // done
    M3i& operator=(M3i&& other); // done

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
    void initialize();
    void clear();
    int*** arr_;
    int d1_;
    int d2_;
    int d3_;
};

std::istream& operator>>(std::istream& istrm, M3i& m);
std::ostream& operator<<(std::ostream& ostrm, const M3i& m); // done
