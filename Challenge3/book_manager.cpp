
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Class to store information about one book
class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    void display() {
        cout << "\nID: " << id
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPages: " << pages
             << "\nStatus: "
             << (borrowed ? "Borrowed" : "Available")
             << "\n";
    }
};

// Read books from the text file
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("bookData.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open bookData.txt\n";
        return books;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pages, id, status;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, status, ',');

        if (title.empty() || author.empty() ||
            pages.empty() || id.empty()) {
            continue;
        }

        try {
            books.push_back(Book(title, author, stoi(pages),
                                 id, status == "true"));
        } catch (...) {
            cout << "Skipping invalid book record.\n";
        }
    }

    file.close();
    return books;
}

// Save updated borrowing status to the file
void saveBooks(const vector<Book>& books) {
    ofstream file("bookData.txt");

    if (!file.is_open()) {
        cout << "Error: Could not save book data.\n";
        return;
    }

    for (const Book& book : books) {
        file << book.title << "," << book.author << ","
             << book.pages << "," << book.id << ","
             << (book.borrowed ? "true" : "false") << "\n";
    }

    file.close();
}

// Find a book using its ID
int findBook(const vector<Book>& books, string id) {
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "No books loaded. Program ending.\n";
        return 1;
    }

    int choice;
    string id;

    do {
        cout << "\n=== Library Book Manager ===\n";
        cout << "1. View all books\n";
        cout << "2. View individual book\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 5.\n";
            continue;
        }

        if (choice == 1) {
            for (Book& book : books) {
                book.display();
            }
        }
        else if (choice >= 2 && choice <= 4) {
            cout << "Enter book ID (e.g. 001): ";
            cin >> id;

            int index = findBook(books, id);

            if (index == -1) {
                cout << "Book not found.\n";
            }
            else if (choice == 2) {
                books[index].display();
            }
            else if (choice == 3) {
                if (books[index].borrowed) {
                    cout << "This book is already borrowed.\n";
                } else {
                    books[index].borrowed = true;
                    saveBooks(books);
                    cout << "Book borrowed successfully!\n";
                }
            }
            else if (choice == 4) {
                if (!books[index].borrowed) {
                    cout << "This book is already available.\n";
                } else {
                    books[index].borrowed = false;
                    saveBooks(books);
                    cout << "Book returned successfully!\n";
                }
            }
        }
        else if (choice == 5) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
