#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// Структура книги
struct Book {
    string udc_number;  // УДК (уникальный идентификатор)
    string author;      // Автор
    string title;       // Название
    int year;           // Год издания
    int copies;         // Количество копий

    Book(string udc, string auth, string ttl, int y, int c)
        : udc_number(udc), author(auth), title(ttl), year(y), copies(c) {}

    // Печать информации о книге
    void print() const {
        cout << "УДК: " << udc_number
             << ", Автор: " << author
             << ", Название: " << title
             << ", Год: " << year
             << ", Копии: " << copies << endl;
    }
};

// Структура пользователя с картой взятых книг
struct User {
    map<string, int> borrowedBooks;
};

// Основная структура библиотеки
struct Library {
    Book** books = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    User currentUser;
};

// Функции для работы с библиотекой
void freeLibrary(Library &lib) {
    for (size_t i = 0; i < lib.size; ++i)
        delete lib.books[i];
    delete[] lib.books;
    lib.books = nullptr;
    lib.size = 0;
    lib.capacity = 0;
}

void reserve(Library &lib, size_t new_capacity) {
    if (new_capacity <= lib.capacity) return;
    Book** new_books = new Book*[new_capacity];
    for (size_t i = 0; i < lib.size; ++i)
        new_books[i] = lib.books[i];
    delete[] lib.books;
    lib.books = new_books;
    lib.capacity = new_capacity;
}

bool bookExists(const Library &lib, const string &udc) {
    for (size_t i = 0; i < lib.size; ++i)
        if (lib.books[i]->udc_number == udc) return true;
    return false;
}

void addBook(Library &lib, Book *book) {
    if (bookExists(lib, book->udc_number)) {
        cout << "Ошибка: Книга с таким УДК уже есть!\n";
        delete book;
        return;
    }
    if (book->copies <= 0) {
        cout << "Ошибка: Количество копий должно быть > 0!\n";
        delete book;
        return;
    }
    if (lib.size == lib.capacity)
        reserve(lib, lib.capacity == 0 ? 10 : lib.capacity * 2);
    lib.books[lib.size++] = book;
}

void takeBook(Library &lib, const string &udc) {
    if (lib.currentUser.borrowedBooks.find(udc) != lib.currentUser.borrowedBooks.end() &&
        lib.currentUser.borrowedBooks[udc] > 0) {
        cout << "Ошибка: Эта книга уже у вас на руках!\n";
        return;
    }

    for (size_t i = 0; i < lib.size; ++i) {
        if (lib.books[i]->udc_number == udc) {
            if (lib.books[i]->copies <= 0) {
                cout << "Ошибка: Нет доступных копий этой книги!\n";
                return;
            }
            lib.books[i]->copies--;
            lib.currentUser.borrowedBooks[udc]++;
            cout << "Вы взяли книгу: " << lib.books[i]->title << "\n";
            return;
        }
    }
    cout << "Ошибка: Книга с таким УДК не найдена!\n";
}

void returnBook(Library &lib, const string &udc) {
    if (lib.currentUser.borrowedBooks.find(udc) == lib.currentUser.borrowedBooks.end() ||
        lib.currentUser.borrowedBooks[udc] <= 0) {
        cout << "Ошибка: Вы не брали эту книгу!\n";

        return;
    }

    for (size_t i = 0; i < lib.size; ++i) {
        if (lib.books[i]->udc_number == udc) {
            lib.books[i]->copies++;
            lib.currentUser.borrowedBooks[udc]--;
            cout << "Вы вернули книгу: " << lib.books[i]->title << "\n";
            return;
        }
    }
}

// Функция для вывода всех книг в строку
void printAllBooks(const Library &lib) {
    cout << "Список книг в библиотеке:\n";
    for (size_t i = 0; i < lib.size; ++i) {
        lib.books[i]->print(); // Используем метод print() для каждой книги
    }
}

int safeInputInt(const string &prompt, int min) {
    int choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        if (cin.fail() || choice < min) {
            cin.clear(); // Очистить ошибку ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорировать оставшийся ввод
            cout << "Ошибка: Введите целое число больше или равное " << min << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем оставшийся ввод
            return choice;
        }
    }
}

// Инициализация библиотеки и добавление книг
void initLibrary(Library &lib) {
    // Русская классика
    addBook(lib, new Book("82.311", "Толстой Л.Н.", "Война и мир", 1869, 5));
    addBook(lib, new Book("82.312", "Толстой Л.Н.", "Анна Каренина", 1877, 3));
    addBook(lib, new Book("82.313", "Достоевский Ф.М.", "Преступление и наказание", 1866, 4));
    addBook(lib, new Book("82.314", "Достоевский Ф.М.", "Идиот", 1869, 2));
    addBook(lib, new Book("82.315", "Гоголь Н.В.", "Мертвые души", 1842, 3));

    // Зарубежная литература
    addBook(lib, new Book("84.411", "Оруэлл Дж.", "1984", 1949, 4));
    addBook(lib, new Book("84.412", "Хемингуэй Э.", "Старик и море", 1952, 3));
    addBook(lib, new Book("84.413", "Ремарк Э.М.", "Три товарища", 1936, 2));
addBook(lib, new Book("2", "Книга", "ЯА", 1936, 1));
    // Научная фантастика
    addBook(lib, new Book("84.511", "Лем С.", "Солярис", 1961, 2));
    addBook(lib, new Book("84.512", "Азимов А.", "Я, робот", 1950, 3));
}


// Основная функция
int main() {
    Library library;
    initLibrary(library);

    cout << "=== Библиотечная система ===\n";
    cout << "Начальное состояние библиотеки:\n";
    printAllBooks(library);

    while (true) {
        cout << "\n=== Меню ===\n";
        cout << "1. Взять книгу\n";
        cout << "2. Вернуть книгу\n";
        cout << "3. Показать все книги\n";
        cout << "4. Выйти\n";

        int choice = safeInputInt("Выберите действие (1-4): ", 1);

        switch (choice) {
            case 1: {
                cout << "Введите УДК книги: ";
                string udc;
                cin >> udc;
                takeBook(library, udc);
                break;
            }
            case 2: {
                cout << "Введите УДК книги: ";
                string udc;
                cin >> udc;
                returnBook(library, udc);
                break;
            }
            case 3:
                printAllBooks(library);
                break;
            case 4:
                cout << "Выход из программы...\n";
                freeLibrary(library);
                return 0;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }
}
