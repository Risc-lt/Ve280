#include "ex2.h"

Library initLibrary(){
    // Effects: Returns a Library with no books (i.e., numBooks is 0).
    Library lib;
    lib.numBooks = 0;
    return lib;
}


void addBook(Library &lib, string title, string author){
    // Requires: lib is not full.
    // Modifies: lib .
    // Effects: Adds a book with the given title and author to lib . Each new book is
    // assigned an ID, which is its index in the books array plus one. If lib is full, prints
    // "The library is full." followed by a newline.
    if(lib.numBooks < MAX_BOOKS){
        lib.numBooks++;
        lib.books[lib.numBooks].ID = lib.numBooks;
        lib.books[lib.numBooks].title = title;
        lib.books[lib.numBooks].author = author;
        lib.books[lib.numBooks].isAvailable = true;
    } else{
        cout << "The library is full." << endl;
    }
}


void borrowBook(Library &lib, int ID){
    // Requires: ID is a valid book ID.
    // Modifies: lib .
    // Effects: Sets the availability of the book with the given ID to false if the book is
    // available and prints "Book <title> is borrowed." followed by a newline; otherwise,
    // prints "Book <title> is not available." followed by a newline
    if(lib.books[ID].isAvailable){
        lib.books[ID].isAvailable = false;
        cout << "Book " << lib.books[ID].title << " is borrowed." << endl;
    } else{
        cout << "Book " << lib.books[ID].title << " is not available." << endl;
    }
}


void returnBook(Library &lib, int ID){
    // Requires: ID is a valid book ID.
    // Modifies: lib .
    // Effects: Sets the availability of the book with the given ID to true if the book is not
    // available and prints "Book <title> is returned." followed by a newline; otherwise,
    // prints "Book <title> is already available." followed by a newline.
    if(!lib.books[ID].isAvailable){
        lib.books[ID].isAvailable = true;
        cout << "Book " << lib.books[ID].title << " is returned." << endl;
    } else{
        cout << "Book " << lib.books[ID].title << " is already available." << endl;
    }
}


void printLibrary(const Library &lib){
    // Effects: Prints all books in lib with their IDs, titles, authors, and availability followed
    // by a newline; if lib is empty, prints "The library is empty." followed by a newline.
    if(lib.numBooks == 0){
        cout << "The library is empty." << endl;
    } else{
        for(int i = 1; i <= lib.numBooks; i++){
            cout << "Book ID: " << lib.books[i].ID << endl;
            cout << "Title: " << lib.books[i].title << endl;
            cout << "Author: " << lib.books[i].author << endl;
            if(lib.books[i].isAvailable){
                cout << "Status: available" << endl;
            } else{
                cout << "Status: not available" << endl;
            }
        }
    }
}