#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

// ================== ОБЩИЕ ФУНКЦИИ ==================

// Проверка наличия всех символов подстроки в слове (без учета порядка)
bool containsAllChars(const char *word, const char *substr) {
  if (!substr || !*substr)
    return true;
  if (!word)
    return false;

  // Создаем копии, чтобы не изменять исходные указатели
  string wordStr(word);
  string substrStr(substr);

  // Для каждого символа в подстроке проверяем его наличие в слове
  for (char c : substrStr) {
    auto pos = wordStr.find(c);
    if (pos == string::npos)
      return false; // символ не найден
    wordStr.erase(pos, 1);
  }
  return true;
}

// Проверка наличия подстроки в слове (с учетом регистра и порядка)
bool containsSubstring(const char *word, const char *substr) {
  if (!substr || !*substr)
    return true;
  return strstr(word, substr) != nullptr;
}

// ================== ЗАДАЧА 1 ==================

void createFilteredString(char *&result, const char *input,
                          const char *substr) {
  size_t inputLen = strlen(input);
  result = new char[inputLen + 1];
  result[0] = '\0';
  char *buffer = new char[inputLen + 1];
  strcpy(buffer, input);

  char *word = strtok(buffer, " ");
  while (word) {
    if (containsAllChars(word, substr)) {
      strcat(result, word);
      strcat(result, " ");
    }
    word = strtok(nullptr, " ");
  }

  if (result[0]) {
    result[strlen(result) - 1] = '\0';
  }

  delete[] buffer;
}

void moveFirstSubstringWord(char *&input, const char *substr) {
  char **words = nullptr;
  size_t wordCount = 0;
  char *firstMatch = nullptr;
  char *context = nullptr;

  size_t inputLen = strlen(input);
  char *tempInput = new char[inputLen + 1];
  strcpy(tempInput, input);

  // Первый проход: подсчет количества слов
  char *word = strtok_r(tempInput, " ", &context);
  while (word) {
    if (!firstMatch && containsSubstring(word, substr)) {
      firstMatch = new char[strlen(word) + 1];
      strcpy(firstMatch, word);
    } else {
      wordCount++;
    }
    word = strtok_r(nullptr, " ", &context);
  }

  // Выделение памяти для слов
  if (wordCount > 0) {
    words = new char *[wordCount];
  }

  // Второй проход: сохранение слов
  strcpy(tempInput, input);
  context = nullptr;
  word = strtok_r(tempInput, " ", &context);
  size_t index = 0;
  while (word) {
    if (firstMatch && strcmp(word, firstMatch) == 0) {
      // Пропускаем первое совпадающее слово
      word = strtok_r(nullptr, " ", &context);
      continue;
    }
    if (index < wordCount) {
      words[index] = new char[strlen(word) + 1];
      strcpy(words[index], word);
      index++;
    }
    word = strtok_r(nullptr, " ", &context);
  }

  // Сборка результата
  size_t newLen = (firstMatch ? strlen(firstMatch) : 0);
  for (size_t i = 0; i < wordCount; i++) {
    newLen += strlen(words[i]) + 1;
  }

  char *newInput = new char[newLen + 1];
  newInput[0] = '\0';

  if (firstMatch) {
    strcat(newInput, firstMatch);
    for (size_t i = 0; i < wordCount; i++) {
      strcat(newInput, " ");
      strcat(newInput, words[i]);
    }
  }

  // Освобождение памяти и замена указателя
  delete[] input;
  input = newInput;

  delete[] tempInput;
  if (firstMatch) {
    delete[] firstMatch;
  }
  for (size_t i = 0; i < wordCount; i++) {
    delete[] words[i];
  }
  delete[] words;
}

void task1() {
  int inp_size = 1000;
  int substr_size = 100;
  char *input = new char[inp_size];
  char *substr = new char[substr_size];
  char *result = nullptr;

  cout << "=== Обработка Char-строк ===" << endl;
  cout << "Входная строка: ";
  cin.getline(input, inp_size);

  cout << "Целевая подстрока: ";
  cin.getline(substr, substr_size);

  // Фильтрация по наличию всех символов
  createFilteredString(result, input, substr);
  cout << "\nРезультат фильтрации: "
       << (result && result[0] ? result : "<пусто>") << endl;

  // Перемещение первого слова с подстрокой
  char *modified = new char[strlen(input) + 1];
  strcpy(modified, input);
  moveFirstSubstringWord(modified, substr);

  if (strcmp(modified, input) != 0) {
    cout << "После перемещения: " << modified << endl;
  } else {
    cout << "Подходящие слова не найдены" << endl;
  }

  // Освобождение памяти
  delete[] input;
  delete[] substr;
  if (result)
    delete[] result;
  delete[] modified;
}

// ================== ЗАДАЧА 2 ==================

string *splitString(const char *str, size_t *wordCount) {
  *wordCount = 0;
  if (!str || !*str)
    return nullptr;

  // Первый проход: подсчет количества слов
  size_t count = 0;
  bool inWord = false;
  for (const char *p = str; *p; ++p) {
    if (*p != ' ') {
      if (!inWord) {
        ++count;
        inWord = true;
      }
    } else {
      inWord = false;
    }
  }

  if (count == 0)
    return nullptr;

  string *words = new string[count];

  // Второй проход: заполнение массива словами
  size_t index = 0;
  const char *wordStart = nullptr;
  inWord = false;

  for (const char *p = str;; ++p) {
    if (*p && *p != ' ') {
      if (!inWord) {
        wordStart = p;
        inWord = true;
      }
    } else {
      if (inWord) {
        words[index++] = string(wordStart, p);
        inWord = false;
      }
      if (!*p)
        break;
    }
  }

  *wordCount = count;
  return words;
}
void task2() {
  cout << "\n=== Разбиение строки ===" << endl;

  string input;
  cout << "Введите строку: ";
  getline(cin, input);

  size_t wordCount = 0;
  string *words = splitString(input.c_str(), &wordCount);

  if (words) {
    cout << "Полученные слова (" << wordCount << "):" << endl;
    for (size_t i = 0; i < wordCount; i++) {
      cout << "[" << i + 1 << "] " << words[i] << endl;
    }

    delete[] words;
  } else {
    cout << "Строка пуста!" << endl;
  }
}
// ================== ГЛАВНОЕ МЕНЮ ==================
int main() {
  int choice;
  do {
    cout << "\nМеню:\n"
         << "1. Обработка Char-строк\n"
         << "2. Разбиение строки\n"
         << "0. Выход\n"
         << "Выбор: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    case 0:
      cout << "Завершение работы." << endl;
      break;
    default:
      cout << "Неверный выбор!" << endl;
    }
  } while (choice != 0);

  return 0;
}