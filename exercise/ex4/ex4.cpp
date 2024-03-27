#include "ex4.h"
#include <iostream>

// Part 1: bookInventory class implementation
// Default constructor
bookInventory::bookInventory() : numBooks(0) {
  for (int i = 0; i < MAX_BOOKS; i++) {
    books[i] = Book();
  }
}

// Add a book to the inventory
void bookInventory::addBook(const Book &book) {
  if (numBooks >= (unsigned int)MAX_BOOKS) {
    throw Exception("The inventory is full");
  }
  books[numBooks++] = book;
}

// Search for a book in the inventory
int bookInventory::searchBook(const std::string &title) const {
  for (unsigned int i = 0; i < numBooks; i++) {
    if (books[i].title == title) {
      return (int)(i + 1);
    }
  }
  throw Exception("Book " + title + " not found.");

  return 0;
}

// Updates the details of a book at a specific ID.
void bookInventory::setBook(const Book &book, int ID) {
  if (ID < 1 || (unsigned int)ID > numBooks) {
    throw Exception("Invalid book ID.");
  } else if(books[ID-1].title == "") {
    // Add the book into the next empty slot
    for(unsigned int i = 0; i < numBooks; i++){
      if(books[i].title == "")
        books[i] = book;
    }
    numBooks++;
  } else {
    books[ID-1] = book;
  }
}

// Returns a book from the inventory
Book bookInventory::viewBook(int ID) const {
  if (ID < 1 || (unsigned int)ID > numBooks) {
    throw Exception("Invalid book ID.");
  }
  return books[ID-1];
}

// Remove a book from the inventory
void bookInventory::removeBook(int ID) {
  if (ID < 1 || (unsigned int)ID > numBooks) {
    throw Exception("Invalid book ID.");
  }
  for (unsigned int i = ID - 1; i < numBooks - 1; i++) {
    books[i] = books[i + 1];
  }
  numBooks--;
}

// Print the inventory
void bookInventory::printInventory() const {
    if (numBooks == 0) 
        throw Exception("The inventory is empty.");

    for (unsigned int i = 0; i < numBooks; i++) {
        std::cout << "Book ID: " << i+1 << std::endl;
        std::cout << "Title: " << books[i].title << std::endl;
        std::cout << "Author: " << books[i].author << std::endl;
        if(books[i].isAvailable)
            std::cout << "Status: available" << std::endl;
        else
            std::cout << "Status: not available" << std::endl;
    }
}

// Part 2: Library class implementation
// Default constructor
library::library() : bookInventory() {}

// Borrow a book from the library
void library::borrowBook(int ID) {
  if (ID < 1 || (unsigned int)ID > numBooks) {
    throw Exception("Invalid book ID.");
  } else if (!books[ID-1].isAvailable) {
    throw Exception("Book " + books[ID-1].title + " is not available.");
  }
  books[ID-1].isAvailable = false;
}

// Return a book to the library
void library::returnBook(int ID) {
  if (ID < 1 || (unsigned int)ID > numBooks) {
    throw Exception("Invalid book ID.");
  } else if (books[ID-1].isAvailable) {
    throw Exception("Book " + books[ID-1].title + " is already available.");
  }
  books[ID-1].isAvailable = true;
}

// list all the books that are currently borrowed
void library::listBorrowed() const {
    bool borrowed = false;
    for (unsigned int i = 0; i < numBooks; i++) {
        if (!books[i].isAvailable) {
            std::cout << "Book ID: " << i+1 << std::endl;
            std::cout << "Title: " << books[i].title << std::endl;
            std::cout << "Author: " << books[i].author << std::endl;
            borrowed = true;
        }
    }
    if (!borrowed) {
        throw Exception("All books are available.");
    }
}