#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для хранения информации о транспорте
struct Transport {
    string type;   // Тип транспорта (автомобиль, автобус и т.д.)
    string brand;  // Бренд
    int year;      // Год выпуска
    double price;  // Цена
};

// Функция для чтения данных из файла и их отображения
vector<Transport> loadAndDisplayData(const string& filename) {
    vector<Transport> transports;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << filename << endl;
        return transports;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Transport t;
        getline(ss, t.type, ',');
        getline(ss, t.brand, ',');
        ss >> t.year;
        ss.ignore(); // Пропустить запятую
        ss >> t.price;
        transports.push_back(t);
    }

    file.close();

    // Отобразим данные после загрузки
    if (transports.empty()) {
        cout << "Данные отсутствуют." << endl;
    } else {
        cout << "Данные загружены из файла " << filename << ":\n";
        cout << left << setw(10) << "Тип" 
             << setw(15) << "Бренд" 
             << setw(10) << "Год" 
             << setw(10) << "Цена" << endl;
        cout << string(45, '-') << endl;

        for (const auto& t : transports) {
            cout << left << setw(10) << t.type 
                 << setw(15) << t.brand 
                 << setw(10) << t.year 
                 << setw(10) << t.price << endl;
        }
    }

    return transports;
}

// Функция для редактирования записи
void editData(vector<Transport>& transports) {
    int index;
    cout << "Введите номер записи для редактирования (начиная с 1): ";
    cin >> index;

    if (index < 1 || index > transports.size()) {
        cout << "Неверный номер записи!" << endl;
        return;
    }

    Transport& t = transports[index - 1];
    cout << "Редактирование записи: " << t.type << ", " << t.brand 
         << ", " << t.year << ", " << t.price << endl;
    cout << "Введите новый тип: ";
    cin >> t.type;
    cout << "Введите новый бренд: ";
    cin >> t.brand;
    cout << "Введите новый год: ";
    cin >> t.year;
    cout << "Введите новую цену: ";
    cin >> t.price;
    cout << "Запись обновлена!" << endl;
}

// Функция для добавления новой записи
void addData(vector<Transport>& transports) {
    Transport t;
    cout << "Введите тип: ";
    cin >> t.type;
    cout << "Введите бренд: ";
    cin >> t.brand;
    cout << "Введите год: ";
    cin >> t.year;
    cout << "Введите цену: ";
    cin >> t.price;
    transports.push_back(t);
    cout << "Запись добавлена!" << endl;
}

// Функция для удаления записи
void deleteData(vector<Transport>& transports) {
    int index;
    cout << "Введите номер записи для удаления (начиная с 1): ";
    cin >> index;

    if (index < 1 || index > transports.size()) {
        cout << "Неверный номер записи!" << endl;
        return;
    }

    transports.erase(transports.begin() + index - 1);
    cout << "Запись удалена!" << endl;
}

// Функция для вычисления средней цены
void calculateAveragePrice(const vector<Transport>& transports) {
    if (transports.empty()) {
        cout << "Нет данных для вычисления средней цены." << endl;
        return;
    }

    double totalPrice = 0;
    for (const auto& t : transports) {
        totalPrice += t.price;
    }

    double averagePrice = totalPrice / transports.size();
    cout << "Средняя цена транспорта: " << averagePrice << endl;
}

// Функция для сохранения данных в файл
void saveToFile(const vector<Transport>& transports, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << filename << " для записи." << endl;
        return;
    }

    for (const auto& t : transports) {
        file << t.type << "," << t.brand << "," << t.year << "," << t.price << endl;
    }

    file.close();
    cout << "Данные успешно сохранены в файл " << filename << endl;
}

// Основное меню программы
void menu() {
    vector<Transport> transports;
    bool dataLoaded = false;
    string filename = "1.txt";

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Загрузить и просмотреть данные из файла\n";
        cout << "2. Редактировать запись\n";
        cout << "3. Добавить запись\n";
        cout << "4. Удалить запись\n";
        cout << "5. Вычислить среднюю цену\n";
        cout << "6. Сохранить данные в файл\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            transports = loadAndDisplayData(filename);
            dataLoaded = !transports.empty();
            break;
        case 2:
            if (dataLoaded) editData(transports);
            else cout << "Сначала загрузите данные!" << endl;
            break;
        case 3:
            addData(transports);
            break;
        case 4:
            if (dataLoaded) deleteData(transports);
            else cout << "Сначала загрузите данные!" << endl;
            break;
        case 5:
            calculateAveragePrice(transports);
            break;
        case 6:
            if (dataLoaded) {
                string newFilename;
                cout << "Введите имя нового файла: ";
                cin >> newFilename;
                saveToFile(transports, newFilename);
            } else {
                cout << "Сначала загрузите данные!" << endl;
            }
            break;
        case 0:
            cout << "Выход из программы." << endl;
            return;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}

