#include <iostream>
using namespace std;

// Node structure for Book
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    Book* next;
};

// Head (First Node) of the linked list
Book* head = nullptr;

// Function used to create a new book node
Book* createBook(int id, string title, string author) {
    Book* newBook = new Book();
    newBook->id = id;
    newBook->title = title;
    newBook->author = author;
    newBook->isIssued = false;
    newBook->next = nullptr;
    return newBook;
}

// Add book to end of list
void addBook(int id, string title, string author) {
    Book* newBook = createBook(id, title, author);
    if (head == nullptr) {
        head = newBook;
    } else {
        Book* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newBook;
    }
    cout << "Book added successfully.\n";
}

// Display all the books
void displayBooks() {
    if (head == nullptr) {
        cout << "No books in the library.\n";
        return;
    }
    Book* temp = head;
    cout << "\n    Book List    \n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id << "\n Title: " << temp->title 
             << "\n Author: " << temp->author 
             << "\n Status: " << (temp->isIssued ? "Issued" : "Available") << endl;
        temp = temp->next;
    }
}

// Search a book by ID
Book* searchBook(int id) {
    Book* temp = head;
    while (temp != nullptr) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Issue a book
void issueBook(int id) {
    Book* book = searchBook(id);
    if (book == nullptr) {
        cout << "Book not found.\n";
    } else if (book->isIssued) {
        cout << "Book is already issued.\n";
    } else {
        book->isIssued = true;
        cout << "Book issued successfully.\n";
    }
}

// Return a book
void returnBook(int id) {
    Book* book = searchBook(id);
    if (book == nullptr) {
        cout << "Book not found.\n";
    } else if (!book->isIssued) {
        cout << "Book is not issued.\n";
    } else {
        book->isIssued = false;
        cout << "Book returned successfully.\n";
    }
}

// Delete a book
void deleteBook(int id) {
    if (head == nullptr) {
        cout << "Library is empty.\n";
        return;
    }

    if (head->id == id) {
        Book* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Book deleted successfully.\n";
        return;
    }

    Book* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Book not found.\n";
    } else {
        Book* toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
        cout << "Book deleted successfully.\n";
    }
}

// Main menu
void showMenu() {
    cout << "\n      Library Management System      \n";
    cout << "1. Add Book\n";
    cout << "2. Display Books\n";
    cout << "3. Search Book\n";
    cout << "4. Issue Book\n";
    cout << "5. Return Book\n";
    cout << "6. Delete Book\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    int choice, id;
    string title, author;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                addBook(id, title, author);
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                {
                    Book* book = searchBook(id);
                    if (book != nullptr) {
                        cout << "Book Found: \n Title: " << book->title
                             << "\n Author: " << book->author
                             << "\n Status: " << (book->isIssued ? "Issued" : "Available") << endl;
                    } else {
                        cout << "Book not found.\n";
                    }
                }
                break;

            case 4:
                cout << "Enter Book ID to issue: ";
                cin >> id;
                issueBook(id);
                break;

            case 5:
                cout << "Enter Book ID to return: ";
                cin >> id;
                returnBook(id);
                break;

            case 6:
                cout << "Enter Book ID to delete: ";
                cin >> id;
                deleteBook(id);
                break;

            case 7:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
