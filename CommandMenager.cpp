#include "CommandMenager.h"
#include "Reader.h"
#include<iostream>
#include<algorithm>

//Class CommandMenager
CommandMenager::CommandMenager(const string& command, const string& option, const string&argument): m_command(command), m_option(option){

	m_argument = argument;

	// check if the argument is a file path.
	if (isFilePath(argument) && !realArgument(argument)) {
		m_filepath = isRedirect(argument);
	}
}

bool CommandMenager::m_pipeFlag = false;

void CommandMenager::manage(){
	if (m_command == "") return;
	CommandMap commandMap;
	try {
	Command* cur = commandMap.getCom(m_command);
	if (cur == nullptr) throw m_command;
	cur->execut(m_argument, m_option, m_filepath);
	m_currResult = cur->getResult();
	}
	catch (const string& m_command) {
		cout << "Error. Command >> " << m_command << " << does not exist." << endl;
	}
}

bool CommandMenager::realArgument(const string& argument) const {
    if (argument[0] == '"' && argument[argument.size() - 1] == '"') return true;
    else return false;
}

string CommandMenager::isRedirect(string fileName) {
    string inputFile = "";
    string outputFile = "";
    bool appendMode = false;
	m_argument = "";

    int inputPos = fileName.find('<');
    int appendPos = fileName.find(">>");
    int outputPos = (appendPos != string::npos) ? appendPos : fileName.find('>');

	fileName.erase(remove(fileName.begin(), fileName.end(), '\t'), fileName.end());
	string cleaned = fileName;

    if (outputPos != string::npos) {
        appendMode = (appendPos != string::npos);
        int start = outputPos + (appendMode ? 2 : 1);
        start = fileName.find_first_not_of(" ", start);
        int end = fileName.find_first_of(" ", start);
        outputFile = fileName.substr(start, end - start);
		removeSubstring(cleaned, outputFile);
    }

    if (inputPos != string::npos) {
        int start = fileName.find_first_not_of(" ", inputPos + 1);
        int end = fileName.find_first_of(" ", start);
        inputFile = fileName.substr(start, end - start);
		removeSubstring(cleaned, inputFile);
    }

	if (!inputFile.empty()) {
		m_argument = read(inputFile, m_command);
		if(m_command != "tr") m_argument = "\"" + m_argument + "\"";
	}
	if (isFilePath(cleaned)) {
		fileName.erase(fileName.find(".txt") + 4);
		m_argument = read(fileName, m_command);
		if (m_command != "tr") m_argument = "\"" + m_argument + "\"";
		removeSubstring(cleaned, fileName);
	}
	
	
	for (int i = 0; i < cleaned.size(); i++) {
		if (cleaned[i] == '>' || cleaned[i] == '<') cleaned.erase(i--, 1);
	}

	while (!cleaned.empty() && isspace(cleaned.back())) cleaned.pop_back();
	while (!cleaned.empty() && isspace(cleaned.front())) cleaned.erase(0, 1);
	
	if (m_argument.empty()) m_argument = cleaned;
	else if (!cleaned.empty()) m_argument += " " + cleaned;
	
    if (!outputFile.empty()) {
        return (appendMode ? ">>" : ">") + outputFile;
    }
    if (!inputFile.empty()) {
        return inputFile;
    }
	else {
		return fileName.erase(fileName.find(".txt") + 4);
	}
}

void CommandMenager::removeSubstring(string& str, const string& toRemove) {
	int pos = str.find(toRemove);
	if (pos != string::npos) {
		str.erase(pos, toRemove.length());
	}
}

bool CommandMenager::isFilePath(const string& argument) const {
	if (argument == "" || argument.size() <= 4) return false;
	if (argument.find(".txt") != string::npos) return true;
	else return false;
}

bool CommandMenager::fileExists(const string& filepath) const {
	std::ifstream file(filepath);
	return file.good();
}

string CommandMenager::read(const string& filepath, const string& command) const {
	string argument = "";
	if (command == "touch") return argument;
    if (command == "tr") return filepath;
	if (!fileExists(filepath)) {
		cout << "Error: File doesn't exist." << endl;
		return argument;
	}

	auto reader = make_unique<FileReader>(filepath);

	while (!reader->endOfRead()) argument += reader->getNextLine() + "\n";
	argument.pop_back();
	
	return argument;
}