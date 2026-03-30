#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//проверка существования файла
bool fileExists(const std::string& filename) {
    using namespace std;
    ifstream file(filename, ios::binary);
    return file.is_open();
}

//чтение элементов файла
std::vector<double> readFile(const std::string& filename) {
    using namespace std;
    vector<double> data;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Не удалось открыть файл " << filename << "\n";
        return data;
    }
    double value;
    while (fin.read(reinterpret_cast<char*>(&value), sizeof(double))) {
        data.push_back(value);
    }
    return data;
}

//запись двух элементов в новый файл
void writeElements(const std::string& filename, double first, double last) {
    using namespace std;
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Не удалось открыть файл " << filename << "\n";
        return;
    }
    fout.write(reinterpret_cast<const char*>(&first), sizeof(double));
    fout.write(reinterpret_cast<const char*>(&last), sizeof(double));
}



void filed() {
    using namespace std;
    vector<double> numbers = { 3.7, 2.718, 36.45, 36.09, 1.414 };

    // ЗАПИСЬ
    ofstream out("4.bin", ios::binary);
    if (out.is_open()) {
        // Записываем весь массив сразу
        out.write(reinterpret_cast<char*>(numbers.data()), numbers.size() * sizeof(double));
        out.close();
    }

    // ЧТЕНИЕ
    ifstream in("4.bin", ios::binary);
    if (in.is_open()) {
        double temp;
        while (in.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
            cout << "n: " << temp << "\n";
        }
        in.close();
    }
}


void doNum1() {
    using namespace std;
    filed();
    string filename1, filename2;
    cout << "Введите имена двух файлов: ";
    cin >> filename1 >> filename2;

    bool file1Exists = fileExists(filename1);
    bool file2Exists = fileExists(filename2);

    string existingFile, missingFile;

    //определяем существующий и отсутствующий файлы
    if (file1Exists && !file2Exists) {
        existingFile = filename1;
        missingFile = filename2;
    }
    else if (file2Exists && !file1Exists) {
        existingFile = filename2;
        missingFile = filename1;
    }
    else {
        cerr << "Условие не выполнено: должен существовать один файл, и один отсутствовать.\n";
        return;
    }

    //чтение существующего файла
    vector<double> data = readFile(existingFile);

    if (data.empty()) {
        cerr << "Существующий файл пуст или не удалось его прочитать.\n";
        return;
    }

    //первый и последний элементы
    double firstElement = data.front();
    double lastElement = data.back();

    //создание отсутствующего файла, запись в него эл-тов
    writeElements(missingFile, firstElement, lastElement);

    cout << "В файл " << missingFile << " записаны элементы: "
        << firstElement << " и " << lastElement << "." << "\n";

}

// функция для чтения всех целых чисел из двоичного файла
std::vector<int> readBinaryFile(const std::string& filename) {
    using namespace std;
    vector<int> numbers;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return numbers;
    }

    int num;
    while (fin.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        numbers.push_back(num);
    }

    fin.close();
    return numbers;
}

// функция для записи чисел в двоичный файл
void writeBinaryFile(const std::string& filename, const std::vector<int>& numbers) {
    using namespace std;
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    for (int n : numbers) {
        fout.write(reinterpret_cast<const char*>(&n), sizeof(int));
    }

    fout.close();
}

// функция уменьшения файла до 50 элементов
void trimFileTo50(const std::string& filename) {
    using namespace std;
    vector<int> numbers = readBinaryFile(filename);
    if (numbers.size() > 50) {
        numbers.resize(50);
        writeBinaryFile(filename, numbers);
        cout << "Файл усечен до 50 элементов." << endl;
    }
    else {
        cout << "В файле меньше или равно 50 элементов, ничего не изменено." << endl;
    }
}


void filed2() {
    using namespace std;
    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 50, 51, 52 };

    ofstream out("numbers2.bin", ios::binary);
    if (out.is_open()) {

        out.write(reinterpret_cast<char*>(numbers.data()), numbers.size() * sizeof(int));
        out.close();
    }

    ifstream in("numbers2.bin", ios::binary);
    if (in.is_open()) {
        in.close();
    }
}


void doNum2() {
    using namespace std;
    filed2();
    string filename = "numbers2.bin";
    trimFileTo50(filename);
}



// функция для вывода содержимого файла
void printFile(const std::string& filename) {
    using namespace std;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return;
    }

    double num;
    cout << "Содержимое файла " << filename << ":" << endl;
    while (fin.read(reinterpret_cast<char*>(&num), sizeof(double))) {
        cout << num << " ";
    }
    cout << endl;
    fin.close();
}

// функция для чтения файла в вектор
std::vector<double> readFileToVector(const std::string& filename) {
    using namespace std;
    vector<double> nums;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return nums;
    }
    double num;
    while (fin.read(reinterpret_cast<char*>(&num), sizeof(double))) {
        nums.push_back(num);
    }
    fin.close();
    return nums;
}

// объединение трех отсортированных по убыванию векторов в один также по убыванию
std::vector<double> mergeDescending(const std::vector<double>& v1, const std::vector<double>& v2, const std::vector<double>& v3) {
    using namespace std;
    vector<double> result;
    size_t i1 = v1.size(), i2 = v2.size(), i3 = v3.size();

    // объединение с конца, пока есть элементы
    while (i1 > 0 || i2 > 0 || i3 > 0) {
        double max_val = -1e308;
        size_t idx_max = 0;

        if (i1 > 0 && v1[i1 - 1] > max_val) {
            max_val = v1[i1 - 1];
            idx_max = 1;
        }
        if (i2 > 0 && v2[i2 - 1] > max_val) {
            max_val = v2[i2 - 1];
            idx_max = 2;
        }
        if (i3 > 0 && v3[i3 - 1] > max_val) {
            max_val = v3[i3 - 1];
            idx_max = 3;
        }

        result.push_back(max_val);
        if (idx_max == 1)
            i1--;
        else if (idx_max == 2)
            i2--;
        else
            i3--;
    }

    return result;
}

// запись в файл
void writeVectorToFile(const std::string& filename, const std::vector<double>& data) {
    using namespace std;
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Не удалось открыть файл " << filename << " для записи." << endl;
        return;
    }
    for (double num : data) {
        fout.write(reinterpret_cast<const char*>(&num), sizeof(double));
    }
}

void doNum3() {
    using namespace std;
    string S1 = "S1.bin";
    string S2 = "S2.bin";
    string S3 = "S3.bin";
    string S4 = "S4.bin";

    // вывод содержимого трех файлов
    printFile(S1);
    printFile(S2);
    printFile(S3);

    // чтение файлов
    vector<double> v1 = readFileToVector(S1);
    vector<double> v2 = readFileToVector(S2);
    vector<double> v3 = readFileToVector(S3);

    // объединение
    vector<double> merged = mergeDescending(v1, v2, v3);

    // запись итогового файла
    writeVectorToFile(S4, merged);

    // вывод итогового файла
    printFile(S4);
}

#include <cctype>

int evaluate_recursive(const std::string& s, size_t pos) {
    if (pos == 0) {
        return s[0] - '0'; // преобразовать символ в цифру
    }

    if (s[pos] == '+' || s[pos] == '-') {
        int left_value = evaluate_recursive(s, pos - 1);

        // преобразовать следующий символ в цифру
        int right_digit = s[pos + 1] - '0';

        if (s[pos] == '+') {
            return left_value + right_digit;
        }
        else {
            return left_value - right_digit;
        }
    }

    return evaluate_recursive(s, pos - 1);
}

int calculations(const std::string& expr) {
    if (expr.empty()) {
        return 0;
    }

    if (expr.length() % 2 == 0) {
        return 0;
    }

    return evaluate_recursive(expr, expr.length() - 1);
}

int main() {
    using namespace std;
    string expr;
    cout << "Введите выражение: ";
    cin >> expr;

    int result = calculations(expr);
    cout << "Результат: " << result << endl;

    return 0;
}

