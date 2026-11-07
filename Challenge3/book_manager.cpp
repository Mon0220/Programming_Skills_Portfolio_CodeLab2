#include <iostream> // Allows input and output
#include <fstream> // Allows reading files
#include <sstream> // Allows splitting each line of book data into separate values using commas
#include <string>
#include <vector> // Store multyple jokes
using namespace std;

// Class to store information about a book
class Book {
public:
    
    // Variables to store the book's information
    string title, author, id;
    int pages;
    bool borrowed;

    // Setting up information for each book
    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    
    // Function to dispay the book's indormation
    void display() {
        cout << "\nID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nPages: " << pages;

        // Shows the book status - borrowed or avaible
        cout << "\nStatus: " << (borrowed ? "Borrowed" : "Available");
        cout << "\n";
    }
};

int main() {

    //Create a vector to store all books
    vector<Book> books;

    //Open the text file
    ifstream file("bookData.txt");
    string line;

    // Check if the file opened
    if (!file.is_open()) {
        cout << "Error: Could not open bookData.txt\n";
        return 1;
    }

    // Read book information from the file
    while (getline(file, line)) {

        // Separate the book information
        stringstream ss(line);
        string title, author, pages, id, status;

        
        // Split the information using commas
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, status);

        //Skip the line if information is missing
        if (title.empty() || author.empty() ||
            pages.empty() || id.empty() || status.empty()) {
            continue;
        }

        int pageNumber = stoi(pages); // Convert the page number from text to an integer
        bool isBorrowed = (status == "true"); // Checking the book status

        //Create a book object and add it to the vector
        books.push_back(Book(title, author, pageNumber,
                             id, isBorrowed));
    }
    file.close();

    if (books.empty()) {
        cout << "No books found.\n";
        return 1;
    }

    int choice = 0;
    string searchID;

    // Display menu until the user chooses Quit
    do {
        cout << "\n=== Library Book Manager ===\n";
        cout << "1. View all books\n";
        cout << "2. View individual book\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {  // Check if the user entered invalid menu choice
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        if (choice == 1) {
            for (Book book : books) {
                book.display();
            }
        }
        else if (choice >= 2 && choice <= 4) {
            cout << "Enter book ID (e.g. 001): ";
            cin >> searchID;

            int found = -1;

            // Search for the book by ID
            for (int i = 0; i < (int)books.size(); i++) {
                if (books[i].id == searchID) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                cout << "Book not found.\n";
            }
            else if (choice == 2) {
                books[found].display();
            }
            else {
                if (choice == 3 && books[found].borrowed) {
                    cout << "This book is already borrowed.\n";
                }
                else if (choice == 4 && !books[found].borrowed) {
                    cout << "This book is already available.\n";
                }
                else {
                    bool newStatus = (choice == 3);
                    ofstream saveFile("bookData.txt");

                    if (!saveFile.is_open()) {
                        cout << "Error: Could not save book data.\n";
                    }
                    else {
                        books[found].borrowed = newStatus; //Update the selected book's status

                        // Save all book information back to the file
                        for (Book book : books) {
                            saveFile << book.title << ","
                                     << book.author << ","
                                     << book.pages << ","
                                     << book.id << ","
                                     << (book.borrowed ? "true" : "false")
                                     << "\n";
                        }

                        saveFile.close();

                        if (saveFile.fail()) {
                            cout << "Error while saving book data.\n";
                        }
                        else {
                            cout << "Book status updated successfully!\n";
                        }
                    }
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
