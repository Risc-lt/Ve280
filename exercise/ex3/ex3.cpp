#include "cipher.h"
#include <iostream>
#include <cstdlib>

using namespace std;

string deleteleadingSpaces(string message);
string encrypt(string message, string outputMode);
string decrypt(string message, string outputMode);
int map(char c);
char unmap(int num);

int main(int argc, char *argv[]) {

    // Parse the command line arguments
    if (argc < 2) {
        cout << "No option!" << endl;
        return 1;
    } else if (argc > 3) {
        cout << "Too many options!" << endl;
        return 1;
    } else {
        string command = argv[1];
        string outputMode = "--compact";
        if (argc > 2) {
            outputMode = argv[2];
        }
        if (command == "-e" || command == "--encrypt") {
            string message;
            getline(cin, message);
            message = deleteleadingSpaces(message);
            cout << encrypt(message, outputMode) << endl;
        } else if (command == "-d" || command == "--decrypt") {
            string message;
            getline(cin, message);
            message = deleteleadingSpaces(message);
            cout << decrypt(message, outputMode) << endl;
        } else if (command == "-h" || command == "--help") {
            printHelp();
        } else {
            cout << "Invalid option!" << endl;
            return 1;
        }
    }

    return 0;
}

// Remove any leading or trailing spaces from the input message
string deleteleadingSpaces(string message) {
    string result = "";
    bool leadingSpaces = true;

    for (uint i = 0; i < message.length(); i++) {
        if (message[i] != ' ') {
            leadingSpaces = false;
        }
        if (!leadingSpaces) {
            result += message[i];
        }
    }

    return result;
}

// Implement decrypt/encrypt functions here
string encrypt(string message, string outputMode) {
    string result = "";

    for (uint i = 0; i < message.length(); i++) {
        if (message[i] == ' ') {
            result += "000";
        } else {
            result += to_string(map(message[i]));
        }
    }

    if (outputMode == "-s" || outputMode == "--sparse") {
        string temp = "";
        for (uint i = 0; i < result.length(); i++) {
            if (i % 3 == 0 && i != 0) {
                temp += " ";
            }
            temp += result[i];
        }
        result = temp;
    }
    
    return result;
}

string decrypt(string message, string outputMode) {
    string result = "";

    for (uint i = 0; i < message.length(); i += 3) {
        int num = stoi(message.substr(i, 3));
        
        if (num == 0) {
            result += " ";
        } else {
            result += unmap(num);
        }

        if (outputMode == "-s" || outputMode == "--sparse")
            i++;
    }

    return result;
}


// Implement map/unmap functions here
int map(char c) {
    if (c == 'J') {
        return 100;
    } else if (c == 'j') {
        return 200;
    } else {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (c == uppercaseSquare[i][j]) {
                    return 100 + (i+1) * 10 + (j+1);
                } else if (c == lowercaseSquare[i][j]) {
                    return 200 + (i+1) * 10 + (j+1);
                }
            }
        }
    }

    return 0;
}

char unmap(int num) {
    if (num == 100) {
        return 'J';
    } else if (num == 200) {
        return 'j';
    } else {
        int i = (num / 10) % 10 - 1;
        int j = num % 10 - 1;
        if (num < 200) {
            return uppercaseSquare[i][j];
        } else {
            return lowercaseSquare[i][j];
        }
    }
}