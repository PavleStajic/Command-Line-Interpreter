#include "Reader.h"
#include<iostream>
#include<string>

//Class Reader

Reader::Reader(istream& input) : m_input(input) {}

Reader::Reader(const vector<string>& lines) : m_listOfCommands(lines), m_input(cin) {}

string Reader::getNextLineInList() {
	string line = "";
	line = m_listOfCommands[m_counter];
	increseCounter();
	lineLength(line);
	return line;
}

string Reader::getNextLine() const {
	string line = "";
	getline(m_input, line);
	line = lineLength(line);
	return line;
}

bool Reader::endOfRead() const {
	return m_input.eof();
}

string Reader::lineLength(string& line) const {
	if (line.length() > 512) { 
		line.erase(512); 
		line += "\"";
	}
	return line;
}

//Class FileReader

FileReader::FileReader(const string& filepath): Reader(m_filePath), m_filePath(filepath) {}

//Class ConsoleReader

ConsoleReader::ConsoleReader(): Reader(cin){}
