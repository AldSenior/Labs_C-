#include <cstring> // Для работы с C-строками (strlen, strstr, strcpy и т.д.)
#include <iostream>

using namespace std;

// Функция для проверки, содержит ли слово все символы подстроки
bool containsAllChars(const char *word, const char *substr) {
  for (int i = 0; substr[i] != '\0'; i++) {
    if (strchr(word, substr[i]) == nullptr) {
      return false; // Если символ подстроки не найден в слове
    }
  }
  return true; // Все символы подстроки найдены в слове
}

// Функция для формирования новой строки из слов, содержащих все символы
// подстроки
void formNewString(const char *input, const char *substr, char *result) {
  char temp[1000];     // Временный буфер для копирования строки
  strcpy(temp, input); // Копируем входную строку в temp
  result[0] = '\0';    // Инициализируем результирующую строку пустой

  char *word = strtok(temp, " "); // Разбиваем строку на слова
  while (word != nullptr) {
    if (containsAllChars(word, substr)) {
      strcat(result, word); // Добавляем слово в результат
      strcat(result, " ");  // Добавляем пробел после слова
    }
    word = strtok(nullptr, " "); // Переходим к следующему слову
  }
}

// Функция для перемещения первого слова, содержащего подстроку, в начало строки
void moveFirstWordToStart(char *input, const char *substr) {
  char temp[1000];     // Временный буфер для копирования строки
  strcpy(temp, input); // Копируем входную строку в temp

  char *firstWord = nullptr;    // Указатель на первое найденное слово
  char *restOfString = nullptr; // Указатель на оставшуюся часть строки

  char *word = strtok(temp, " "); // Разбиваем строку на слова
  while (word != nullptr) {
    if (strstr(word, substr) != nullptr) { // Если слово содержит подстроку
      firstWord = word;
      restOfString = strtok(nullptr, ""); // Оставшаяся часть строки
      break;
    }
    word = strtok(nullptr, " ");
  }

  if (firstWord != nullptr) {
    char newString[1000];
    strcpy(newString, firstWord);    // Начинаем новую строку с найденного слова
    strcat(newString, " ");          // Добавляем пробел
    strcat(newString, restOfString); // Добавляем оставшуюся часть строки
    strcpy(input, newString);        // Обновляем исходную строку
  }
}

int main() {
  char input[1000];
  char substr[100];
  char result[1000] = "";

  cout << "Введите строку: ";
  cin.getline(input, 1000); // Считываем строку с пробелами

  cout << "Введите подстроку: ";
  cin.getline(substr, 100); // Считываем подстроку

  // Задание 1
  formNewString(input, substr, result);
  cout << "Новая строка из слов, содержащих все символы подстроки: " << result
       << endl;

  // Задание 2
  moveFirstWordToStart(input, substr);
  cout << "Строка после перемещения первого слова с подстрокой в начало: "
       << input << endl;

  return 0;
}