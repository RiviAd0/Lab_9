#include <iostream>
#include "Nums.h"

int main() {
    using namespace std;
    setlocale(LC_ALL, "ru");
    int tusknum;
    do {
        cout << "\nВыберите номер задания.\n";
        cin >> tusknum;
        switch (tusknum) {
        case 1: doNum1();
            break;
        case 2: doNum2();
            break;
        case 3: doNum3();
            break;
        case 4: doNum4();
            break;

        default: cout << "Нет задачи с номером " << tusknum << ".\n";
        }
    } while (tusknum != 0);
    return 0;
}