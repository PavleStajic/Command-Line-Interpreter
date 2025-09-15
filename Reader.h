#ifndef READER_H
#define READER_H

#include<fstream>
#include<vector>
#include <iostream>
using namespace std;

// Base class for reading input from a stream (either file or console).
class Reader {
public:

	// Constructor that initializes the reader with the given input stream.
	Reader(istream& input);

	// Constructor that initializes the reader with a predefined list of strings.
	Reader(const vector<string>& lines);

	// Default constructor.
	Reader():m_input(cin) {}

	// Reads the next line from the input stream.
	string getNextLine() const;

	string getNextLineInList();

	// Checks if the end of the input stream has been reached.
	bool endOfRead() const;

	const vector<string>& getListOfCommands() const { return m_listOfCommands; }

	int getCounter() const { return m_counter; }
	void increseCounter() { m_counter++; }
	
protected:

	//Checks the length of the input line.
	//If the string is longer than 512 characters, it truncates it to the first 512 characters.
	string lineLength(string& line) const;

	istream& m_input;	// Pointer to the input stream
	vector<string> m_listOfCommands;	// Stores input lines
	int m_counter = 0;	// Counter to track the current position in the command list
};

// Derived class for reading input from a file.
class FileReader : public Reader {
public:
	// Constructor that initializes the FileReader with a specific file path.
	FileReader( const string& filepath);

private:
	ifstream m_filePath;
};

// Derived class for reading input from the console
class ConsoleReader : public Reader {
public:
	// Constructor that initializes the ConsoleReader for reading from standard input (cin).
	ConsoleReader();
};

#endif
