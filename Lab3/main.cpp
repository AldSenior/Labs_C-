
#include <iostream>
#include <random>
using namespace std;
int getRandomNumber() {
  static random_device rd;  // Инициализация генератора случайных чисел
  static mt19937 gen(rd()); // Генератор Mersenne Twister
  uniform_int_distribution<> distrib(-10, 10);
  return distrib(gen);
}
void remove_mass_element(int *array, int &n, int index) {
  n--; // уменьшаем размер массива

  // сдвигаем элементы правее index влево
  for (int i = index; i < n; i++) {
    array[i] = array[i + 1];
  }
}
int findMin(int *mass, int size) {
  int min_value = mass[0];
  for (int i = 1; i < size; i++) {
    if (mass[i] < min_value) {
      min_value = mass[i];
    }
  }

  int **min_mass = new int *[size];
  int min_count = 0;

  for (int i = 0; i < size; i++) {
    if (mass[i] == min_value) {
      min_mass[min_count] = &mass[i];
      min_count++; // увеличиваем счетчик
    }
  }

  // Вывести минимальные числа
  cout << "\nАдреса минимального числа (" << min_value << ") :";
  for (int i = 0; i < min_count; i++) {
    cout << min_mass[i] << " ";
  }
  cout << "\n";

  delete[] min_mass;
}

void inAscendingOrder(int **matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    bool isAscending = true;

    for (int j = 0; j < cols - 1; j++) {
      cout << matrix[i][j] << " ";
      if (matrix[i][j] >= matrix[i][j + 1]) {
        isAscending = false;
      }
    }
    // Выводим последний элемент в строке
    cout << matrix[i][cols - 1] << " ";

    if (isAscending) {
      cout << "-> строка в порядке возрастания" << "\n";
    } else {
      cout << "-> строка не в порядке возрастания." << "\n";
    }
  }
}

int main() {
  // int size;

  // cout << "Введите длину массива: ";

  // cin >> size;
  // int *mass = new int[size];

  // cout << "Исходный массив: " << "\n";
  // for (int i = 0; i < size; i++) {
  //   mass[i] = getRandomNumber();
  //   cout << mass[i] << " ";
  // }

  // findMin(mass, size);

  // delete[] mass;

  //
  int size_column_matrix;
  int size_row_matrix;

  cout << "Введите количество строк двумерного массива:";
  cin >> size_row_matrix;
  cout << "Введите количество колонок двумерного массива:";
  cin >> size_column_matrix;

  int **matrix = new int *[size_row_matrix];
  for (int i = 0; i < size_row_matrix; ++i) {
    matrix[i] = new int[size_column_matrix];
  }
  cout << "Сгенерированная матрица: \n";
  for (int i = 0; i < size_row_matrix; i++) {
    for (int j = 0; j < size_column_matrix; j++) {
      matrix[i][j] = getRandomNumber();
      // cout << matrix[i][j] << " ";
    }
  }

  inAscendingOrder(matrix, size_row_matrix, size_column_matrix);

  // Освобождение памяти
  for (int i = 0; i < size_row_matrix; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;

  return 0;
}