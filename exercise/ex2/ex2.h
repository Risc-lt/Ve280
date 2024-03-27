#ifndef MAX_BOOKS
#define MAX_BOOKS 10   // Maximum number of books in the library.
#include <string>
#include <iostream>

using namespace std;

struct Book {
    int ID;             // Unique identifier for the book.
    string title;       // Title of the book.
    string author;      // Author of the book.
    bool isAvailable;   // 1 for available, 0 for not available.
};

struct Library {
    Book books[MAX_BOOKS];  // Array of books in the library.
    int numBooks;           // Number of books in the library.
};

Library initLibrary();  // Returns a Library with no books.
void addBook(Library &lib, string tilte, string author); // Adds a book to the library.
void borrowBook(Library &lib, int ID);  // Borrows a book from the library.
void returnBook(Library &lib, int ID);  // Returns a book to the library.
void printLibrary(const Library &lib);   // Prints all the books in the library.

#endif
