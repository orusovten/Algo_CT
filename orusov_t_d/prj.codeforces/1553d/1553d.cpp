#include <iostream>

int main() {
    int q;
    std::cin >> q;
    while (q--) {
        std::string s;
        std::string t;

        std::cin >> s >> t;

        int sp = s.size() - 1;
        int tp = t.size() - 1;

        while (tp >= 0 && sp >= 0) {
            if (t[tp] == s[sp]) {
                --tp;
                --sp;
            }
            else {
                sp -= 2;
            }
        }

        if (tp < 0) {
            std::cout << "YES\n";
        }
        else {
            std::cout << "NO\n";
        }
    }
}
