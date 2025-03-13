#include <cctype>
#include <iostream>
#include <locale>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace {
double apply_operation(double const a, double const b, char const op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    if (b == 0)
      throw runtime_error("Ошибка: Деление на ноль!");
    return a / b;
  default:
    throw runtime_error("Ошибка: Неверная операция.");
  }
}

static int precedence(char const op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

static double evaluate_expression(const vector<double> &numbers,
                                  const vector<char> &operations) {
  stack<double> values;
  stack<char> ops;

  for (size_t i = 0; i < numbers.size(); ++i) {
    // Добавляем число в стек значений
    values.push(numbers[i]);

    // Если это не последнее число, обрабатываем операцию
    if (i < operations.size()) {
      while (!ops.empty() &&
             precedence(ops.top()) >= precedence(operations[i])) {
        double const b = values.top();
        values.pop();
        double const a = values.top();
        values.pop();
        char const op = ops.top();
        ops.pop();
        values.push(apply_operation(a, b, op));
      }
      ops.push(operations[i]);
    }
  }

  // Обрабатываем оставшиеся операции
  while (!ops.empty()) {
    double const b = values.top();
    values.pop();
    double const a = values.top();
    values.pop();
    char const op = ops.top();
    ops.pop();
    values.push(apply_operation(a, b, op));
  }

  return values.top(); // Последнее значение в стеке — это результат
}

static bool is_valid_input(const string &arg) {
  // Проверка на число
  if (isdigit(arg[0]) || (arg[0] == '-' && arg.size() > 1)) {
    return true;
  }
  // Проверка на оператор
  if (arg.length() == 1 &&
      (arg[0] == '+' || arg[0] == '-' || arg[0] == '*' || arg[0] == '/')) {
    return true;
  }
  return false;
}
} // namespace
int main(int const argc, char *argv[]) {
  // Проверяем, что передано достаточно аргументов
  if (argc < 2) {
    cout << "Ошибка: необходимо ввести выражение." << "\n";
    return 1;
  }

  try {
    vector<double> numbers;
    vector<char> operations;
    // Переменная для отслеживания последнего ввода
    bool last_was_number = false;

    for (int i = 1; i < argc; ++i) {
      string arg = argv[i];

      // Проверяем валидность ввода
      if (!is_valid_input(arg)) {
        throw runtime_error("Ошибка: Неверный ввод. Пожалуйста используйте "
                            "числа и символы (+,-,*,/).");
      }

      // Если это число
      if (isdigit(arg[0]) || (arg[0] == '-' && arg.size() > 1)) {
        double number = stod(arg); // Преобразуем строку в число
        numbers.push_back(number);
        last_was_number = true; // Устанавливаем флаг, что последнее было числом

      }
      // Если это операция
      else if (arg.length() == 1 && (arg[0] == '+' || arg[0] == '-' ||
                                     arg[0] == '*' || arg[0] == '/')) {

        // Проверяем, что перед операцией действительно есть число
        if (!last_was_number) {
          if (!isdigit(arg[0]))
            throw runtime_error("Ошибка:"
                                "Выражение не может начинаться с символа.");

          throw runtime_error("Ошибка: символ не может следовать за"
                              "символом.");
        }
        operations.push_back(arg[0]);
        last_was_number =
            false; // Устанавливаем флаг, что последнее было операцией
      }
    } // Проверяем, что есть хотя бы одно число
    if (numbers.empty()) {
      cout << "Ошибка: Не введено ни одно"
              " число."
           << "\n";
      return 1;
    }

    // Проверяем, что количество чисел и операций корректно
    if (operations.size() != numbers.size() - 1 || operations.empty()) {
      cout << "Ошибка: Неверное количество символов."
           << "\n";
      return 1;
    }

    // Проверяем, что последнее введенное значение - это число

    if (!last_was_number) {
      cout << "Ошибка: Выражение не может заканчиваться символом." << "\n";
      return 1;
    }

    // Вычисляем результат
    double const result = evaluate_expression(numbers, operations);
    cout << "Результат: " << result << "\n";

  } catch (const exception &e) {
    cout << e.what() << "\n";
    return 1;
  }

  return 0;
}
