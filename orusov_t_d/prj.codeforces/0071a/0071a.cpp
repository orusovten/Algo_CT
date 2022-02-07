// Простая задача

#include <iostream>
 
void cut_to_abbreviation(const std::string& str) {
    int len = str.size();
    if (len <= 10) {
        std::cout << str << std::endl;
        return;
    }
    std::cout << str[0];
    std::cout << len - 2;
    std::cout << str[len - 1] << std::endl;
}
 
int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        cut_to_abbreviation(str);
    }
}
