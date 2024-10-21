#include <iostream>
#include<Windows.h>


using namespace std;

int ugad(int n, int k)
{
    
        cout << "Доступно попыток: " << k << endl;
        while (k > 0)
        {
            int chis;
            cout << "Введите число: ";
            cin >> chis;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "Вы ввели некорректное число! Попробуйте снова." << endl;
                continue;
            }
            if (chis > n)
            {
                cout << "Загаданное число меньше" << endl;
                --k;
            }
            else if (chis < n)
            {
                cout << "Загаданное число больше" << endl;
                --k;
            }
            else if (chis == n)
            {
                cout << "Вы угадали!" << endl;
                return chis;
            }
        }
        cout << endl << "Вы не смогли угадать число " << n << endl;
        return 0;
    
    
}
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");
    int k = 3; //кол-во попыток
    int n = 4; //загаданное число
    ugad(n, k);
}

