#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Laptop {
  string model;
  double width, height, depth; // габариты в см
  double weight;               // вес в кг
  double price;                // цена в $
};

string read_file(ifstream &file) {
  string result;
  char ch;
  while (file.get(ch)) {
    result += ch;
  }
  return result;
}
// Функция переворота строки
void reverse_string(string &str) {
  int left = 0;
  int right = str.length() - 1;
  while (left < right) {
    swap(str[left], str[right]);
    left++;
    right--;
  }
}

// Функция для извлечения числового значения из строки с единицами измерения
double extractValue(const string &s) {
  istringstream iss(s);
  double value;
  iss >> value;
  return value;
}

// Функция чтения данных о ноутбуках из файла
vector<Laptop> readLaptops(const string &filename) {
  vector<Laptop> laptops;
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "Ошибка открытия файла!" << endl;
    return laptops;
  }

  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    Laptop temp;
    string widthStr, heightStr, depthStr, weightStr, priceStr;

    if (iss >> temp.model >> widthStr >> heightStr >> depthStr >> weightStr >>
        priceStr) {
      temp.width = extractValue(widthStr);
      temp.height = extractValue(heightStr);
      temp.depth = extractValue(depthStr);
      temp.weight = extractValue(weightStr);
      temp.price = extractValue(priceStr);
      laptops.push_back(temp);
    }
  }

  file.close();
  return laptops;
}

// Функция вывода всех ноутбуков
void printLaptops(const vector<Laptop> &laptops) {
  if (laptops.empty()) {
    cout << "Список ноутбуков пуст." << endl;
    return;
  }

  cout << "Список всех ноутбуков:" << endl;
  for (const auto &laptop : laptops) {
    cout << "Модель: " << laptop.model << endl;
    cout << "Габариты: " << laptop.width << "x" << laptop.height << "x"
         << laptop.depth << " см" << endl;
    cout << "Вес: " << laptop.weight << " кг" << endl;
    cout << "Цена: " << laptop.price << " $" << endl;
    cout << "------------------------" << endl;
  }
}

// Функция поиска по модели
void searchByModel(const vector<Laptop> &laptops, const string &targetModel) {
  vector<Laptop> foundLaptops;
  for (const auto &laptop : laptops) {
    if (laptop.model == targetModel) {
      foundLaptops.push_back(laptop);
    }
  }

  if (foundLaptops.empty()) {
    cout << "Ноутбуки с моделью '" << targetModel << "' не найдены." << endl;
    return;
  }

  cout << "Найдено ноутбуков: " << foundLaptops.size() << endl;
  for (const auto &laptop : foundLaptops) {
    cout << "Модель: " << laptop.model << endl;
    cout << "Габариты: " << laptop.width << "x" << laptop.height << "x"
         << laptop.depth << " см" << endl;
    cout << "Вес: " << laptop.weight << " кг" << endl;
    cout << "Цена: " << laptop.price << " $" << endl;
    cout << "------------------------" << endl;
  }
}

// Функция поиска по числовому параметру (с поддержкой единиц измерения)
void searchByNumeric(const vector<Laptop> &laptops, const string &inputValue,
                     const string &paramName, double(Laptop::*param)) {
  double targetValue = extractValue(inputValue);
  vector<Laptop> foundLaptops;
  for (const auto &laptop : laptops) {
    if (abs(laptop.*param - targetValue) < 0.01) { // учет погрешности
      foundLaptops.push_back(laptop);
    }
  }

  if (foundLaptops.empty()) {
    cout << "Ноутбуки с " << paramName << " = " << inputValue << " не найдены."
         << endl;
    return;
  }

  cout << "Найдено ноутбуков: " << foundLaptops.size() << endl;
  for (const auto &laptop : foundLaptops) {
    cout << "Модель: " << laptop.model << endl;
    cout << "Габариты: " << laptop.width << "x" << laptop.height << "x"
         << laptop.depth << " см" << endl;
    cout << "Вес: " << laptop.weight << " кг" << endl;
    cout << "Цена: " << laptop.price << " $" << endl;
    cout << "------------------------" << endl;
  }
}

// Функция для задания 1 - работа с ноутбуками
void task1() {
  cout << "\nЗадание 1: Работа с ноутбуками" << endl;
  vector<Laptop> laptops = readLaptops("note.txt");

  printLaptops(laptops);

  // Интерактивное меню для поиска
  while (true) {
    cout << "\nВыберите параметр для поиска (0 для возврата в главное меню):"
         << endl;
    cout << "1. Модель" << endl;
    cout << "2. Ширина" << endl;
    cout << "3. Высота" << endl;
    cout << "4. Глубина" << endl;
    cout << "5. Вес" << endl;
    cout << "6. Цена" << endl;
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0)
      break;

    string inputValue;
    switch (choice) {
    case 1: {
      string model;
      cout << "Введите модель: ";
      cin >> model;
      searchByModel(laptops, model);
      break;
    }
    case 2: {
      cout << "Введите ширину (например, 30.5cm): ";
      cin >> inputValue;
      searchByNumeric(laptops, inputValue, "шириной", &Laptop::width);
      break;
    }
    case 3: {
      cout << "Введите высоту (например, 21.5cm): ";
      cin >> inputValue;
      searchByNumeric(laptops, inputValue, "высотой", &Laptop::height);
      break;
    }
    case 4: {
      cout << "Введите глубину (например, 1.5cm): ";
      cin >> inputValue;
      searchByNumeric(laptops, inputValue, "глубиной", &Laptop::depth);
      break;
    }
    case 5: {
      cout << "Введите вес (например, 1.4kg): ";
      cin >> inputValue;
      searchByNumeric(laptops, inputValue, "весом", &Laptop::weight);
      break;
    }
    case 6: {
      cout << "Введите цену (например, 1300$): ";
      cin >> inputValue;
      searchByNumeric(laptops, inputValue, "ценой", &Laptop::price);
      break;
    }
    default:
      cout << "Неверный выбор. Попробуйте снова." << endl;
    }
  }
}

// Функция для задания 2 - переписывание файла в обратном порядке
void task2() {
  cout << "\nЗадание 2: Переписывание текста" << endl;
  string inputFile = "text.txt";
  string outputFile = "output.txt";

  ifstream inFile(inputFile);
  if (!inFile.is_open()) {
    cout << "Ошибка открытия входного файла!" << endl;
    return;
  }

  string file_content = read_file(inFile);
  inFile.close();

  reverse_string(file_content);

  // Открываем выходной файл
  ofstream outFile(outputFile);
  if (!outFile.is_open()) {
    cout << "Ошибка открытия выходного файла!" << endl;
    return;
  }

  // Записываем перевернутую строку
  outFile << file_content;
  outFile.close();

  cout << "Файл переписан в обратном порядке в " << outputFile << endl;
}

int main() {

  while (true) {
    cout << "\nВыберите задание для выполнения:" << endl;
    cout << "1. Задание 1: Работа с ноутбуками" << endl;
    cout << "2. Задание 2: Переписывание текста в обратном порядке" << endl;
    cout << "0. Выход" << endl;
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0)
      break;

    switch (choice) {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      cout << "Неверный выбор. Попробуйте снова." << endl;
    }
  }

  cout << "Программа завершена." << endl;
  return 0;
}
