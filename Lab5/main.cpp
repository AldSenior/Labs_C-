#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
public:
  string udc_number; // Номер УДК
  string author;     // Фамилия автора
  string title;      // Название книги
  int year;          // Год издания
  int copies;        // Количество экземпляров

  Book(string udc, string auth, string ttl, int y, int c)
      : udc_number(udc), author(auth), title(ttl), year(y), copies(c) {}

  void print() const {
    cout << udc_number << ": " << author << ", " << title << " (" << year
         << "), Копий: " << copies << "\n";
  }
};

class Library {

public:
  vector<Book> books;
  // Добавление книги в библиотеку
  void addBook(const Book &book) { books.push_back(book); }

  // Взятие книги
  void takeBook(const string &udc_number) {
    for (auto &book : books) {
      if (book.udc_number == udc_number) {
        if (book.copies > 0) {
          book.copies--;
          cout << "Взята книга: " << book.title << "\n";
        } else {
          cout << "Копий этой книги на данный момент нет.\n";
        }
        return;
      }
    }
    cout << "Книга не найдена.\n";
  }

  // Возврат книги
  void returnBook(const string &udc_number) {
    for (auto &book : books) {
      if (book.udc_number == udc_number) {
        book.copies++;
        cout << "Книга возвращена: " << book.title << "\n";
        return;
      }
    }
    cout << "Книга не найдена.\n";
  }

  // Вывод информации о всех книгах
  void listBooks() const {
    if (books.empty()) {
      cout << "В библиотеке нет книг.\n";
    } else {
      for (const auto &book : books) {
        book.print();
      }
    }
  }
};

int main() {
  Library library;
  library.listBooks();

  while (true) {
    int op;
    string udc_number; // Номер УДК
    string author;     // Фамилия автора
    string title;      // Название книги
    int year;          // Год издания
    int copies;        // Количество экземпляров

    cout << "Введите число для выполнения действия:\n";
    cout << "1 - взять книгу\n";
    cout << "2 - вернуть книгу\n";
    cout << "3 - добавить книгу в библиотеку\n";
    cout << "4 - посмотреть все книги\n";
    cout << "5 - выйти\n";
    cin >> op;

    switch (op) {
    case 1:
      if (library.books.size() == 0) {
        cout << " Нет книг в библиотеке\n";
        break;
      }
      cout << "Введите номер УДК книги, которую хотите взять:\n";
      cin >> udc_number;
      library.takeBook(udc_number);
      break;
    case 2:
      cout << "Введите номер УДК книги, которую хотите вернуть:\n";
      cin >> udc_number;
      library.returnBook(udc_number);
      break;
    case 3:
      cout << "Введите номер УДК книги:\n";
      cin >> udc_number;
      cout << "Введите фамилию автора книги:\n";
      cin.ignore();
      getline(cin, author);
      cout << "Введите название книги:\n";
      getline(cin, title);
      cout << "Введите год издания книги:\n";
      cin >> year;
      cout << "Введите количество экземпляров книги:\n";
      cin >> copies;
      library.addBook(Book(udc_number, author, title, year, copies));
      break;
    case 4:
      library.listBooks();
      break;
    case 5:
      cout << "Выход из программы.\n";
      return 0;
    default:
      cout << "Ошибка: Неверная операция. Попробуйте снова.\n";
    }
  }

  return 0;
}