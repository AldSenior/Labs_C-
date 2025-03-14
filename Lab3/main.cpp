#include <iostream>
#include <random>
using namespace std;

// Функция для генерации случайного числа в диапазоне от -100 до 100
int getRandomNumber() {
  static random_device rd;  // Инициализация генератора случайных чисел
  static mt19937 gen(rd()); // Генератор Mersenne Twister
  uniform_int_distribution<> distrib(-10, 10);
  return distrib(gen);
}

// Функция для удаления элемента из массива по индексу
void remove_mass_element(int *array, int &n, int index) {
  n--; // уменьшаем размер массива

  // Сдвигаем элементы правее index влево
  for (int i = index; i < n; i++) {
    array[i] = array[i + 1];
  }
}

// Функция для поиска минимального значения в массиве и вывода его адресов
void findMin(int *mass, int size) {
  int min_value = mass[0]; // Предполагаем, что первый элемент минимальный
  for (int i = 1; i < size; i++) {
    if (mass[i] < min_value) {
      min_value = mass[i]; // Обновляем минимальное значение
    }
  }

  // Создаем массив для хранения адресов минимальных элементов
  int **min_mass = new int *[size];
  int min_count = 0;

  // Заполняем массив адресами минимальных элементов
  for (int i = 0; i < size; i++) {
    if (mass[i] == min_value) {
      min_mass[min_count] = &mass[i];
      min_count++; // Увеличиваем счетчик найденных минимальных элементов
    }
  }

  // Выводим адреса минимальных элементов
  cout << "\nАдреса минимального числа (" << min_value << ") :";
  for (int i = 0; i < min_count; i++) {
    cout << min_mass[i] << " ";
  }
  cout << "\n";

  delete[] min_mass; // Освобождаем память
}

// Функция для проверки, упорядочена ли строка по возрастанию
bool isRowAscending(int *row, int cols) {
  for (int j = 0; j < cols - 1; j++) {
    if (row[j] >= row[j + 1]) {
      return false; // Если текущий элемент больше или равен следующему, строка
                    // не упорядочена
    }
  }
  return true; // Если все элементы упорядочены, возвращаем true
}

// Функция для вывода матрицы и проверки каждой строки на упорядоченность
void printCheckMatrix(int **matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    cout << "Строка " << i + 1 << ": ";
    for (int j = 0; j < cols; j++) {
      cout << matrix[i][j] << " "; // Выводим элементы строки
    }

    // Проверяем, упорядочена ли строка по возрастанию
    if (isRowAscending(matrix[i], cols)) {
      cout << "-> строка в порядке возрастания" << "\n";
    } else {
      cout << "-> строка не в порядке возрастания." << "\n";
    }
  }
}

int main() {
  int choice;
  cout << "Выберите задание (1 - массив, 2 - матрица): ";
  cin >> choice;

  if (choice == 1) {
    // Работа с одномерным массивом
    int size;
    cout << "Введите длину массива: ";
    cin >> size;
    if (size < 0) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Длина массива не может быть отрицательной! \n";
      return 0;
    } else if (size == 0) {
      cout << "Масив Пустой!" << "\n";
      return 0;
    }

    int *mass = new int[size]; // Динамическое выделение памяти для массива

    cout << "Исходный массив: " << "\n";
    for (int i = 0; i < size; i++) {
      mass[i] = getRandomNumber(); // Заполняем массив случайными числами
      cout << mass[i] << " (" << &mass[i]
           << ") \n"; // Выводим элемент и его адрес
    }

    findMin(mass, size); // Находим минимальные элементы и их адреса

    delete[] mass; // Освобождаем память
  } else if (choice == 2) {
    // Работа с двумерным массивом (матрицей)
    int size_column_matrix;
    int size_row_matrix;

    cout << "Введите количество строк двумерного массива: ";
    cin >> size_row_matrix;
    cout << "Введите количество колонок двумерного массива, не равное "
            "количеству строк: ";
    cin >> size_column_matrix;
    while (size_column_matrix == size_row_matrix) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Введите количество колонок двумерного массива, не равное "
              "количеству строк: ";
      cin >> size_column_matrix; // Проверка, чтобы количество строк и столбцов
                                 // не совпадало
    }

    // Динамическое выделение памяти для матрицы
    int **matrix = new int *[size_row_matrix];
    for (int i = 0; i < size_row_matrix; ++i) {
      matrix[i] = new int[size_column_matrix];
    }

    cout << "Сгенерированная матрица: \n";
    for (int i = 0; i < size_row_matrix; i++) {
      for (int j = 0; j < size_column_matrix; j++) {
        matrix[i][j] =
            getRandomNumber(); // Заполняем матрицу случайными числами
      }
    }

    printCheckMatrix(matrix, size_row_matrix,
                     size_column_matrix); // Проверяем строки матрицы

    // Освобождение памяти
    for (int i = 0; i < size_row_matrix; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  } else {
    cout << "Неверный выбор. Пожалуйста, выберите 1 или 2." << "\n";
  }

  return 0;
}