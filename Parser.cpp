#include "Parser.h"
#include<string>
#include<stack>
#include "Reader.h"
#include"Pipe.h"
using namespace std;

//Class Parser

Parser::Parser(std::unique_ptr<Reader> reader) : m_reader(move(reader)) {}
Parser::Parser(std::unique_ptr<Reader> reader, bool forList) : m_readerOfList(move(reader)) {}

CommandMenager Parser::pars(){
	string line = m_reader->getNextLine();
	if (line.find("|") != string::npos) {
		CommandMenager::flagOn();
		Pipe pipe(line);
		pipe.runPipe();
		return CommandMenager("", "", "");
	}
	CommandMenager::flagOff();
	return parsLine(line);
}

CommandMenager Parser::parsList() {
	return parsLine(m_readerOfList->getNextLineInList());
}

CommandMenager Parser::parsLine(const string& line){

	vector<string> words = createVector(line);
	int n = words.size();
	string command = words[0];
	string option = "";
	string argument = "";

	if (n > 1) if (words[1][0] == '-') option = words[1];         //Checks for option.
	if (n > 1) argument = removeWords(line, option, command);     //Checks for argument.

	if (argument == "" && isNotFastCommand(command)) argument = "\"" + createArgument(argument) + "\"";
	if (command == "tr" && count(argument.begin(), argument.end(), '"') == 2) {
		string newArgument = "";
		argument += " \"" + createArgument(newArgument) + "\"";
	}

	catchLexicalErrors(line, command, option, argument, 0);
	validateArgument(command, option, argument);

	return CommandMenager(command, option, argument);
}

void Parser::catchLexicalErrors(const string& line, string& command, string& option, string& argument, int pipe){
	try {
		vector<int> errors = {};
		if (!pipe) {
			if (!isNotFastCommand(command)) {
				if (argument != "" && argument.find('>') == string::npos) {
					int n = argument.size();
					for (int i = 0; i < n; i++) errors.push_back(i + command.size() + 1);
					throw errors;
				}
				else {
					for (int i = command.size() + 1; i < line.size(); i++) {
						if (isalpha(line[i])) {
							helperF(line, i, errors);
						}
					}
					if (!errors.empty()) throw errors;
				}
			}
			bool hasArgumentTxt = false;
			bool inside = false;
			int i = command.size() + option.size() + 1;
			for (i; i < line.size(); i++) {
				if (line[i] == '<' || line[i] == '>') {
					if (line.find(".txt", i) == string::npos) {
						errors.push_back(i);
						continue;
					}
					if (line[i] == '<');
					helperF(line, i, errors);
					hasArgumentTxt = true;
					continue;
				}
				if (line[i] == '"' && !hasArgumentTxt) { 
					inside = !inside;
				}
				if (isalpha(line[i]) && !inside) {
					helperF(line, i, errors);
				}
			}
			if (!errors.empty()) throw errors;
		}
		else {
			int start = 0;
			int end = 0;
			for (int i = 0; i <	pipe + 1; i++) {
				size_t pos = line.find('|', end + 1);
				end = (pos != string::npos) ? pos : line.size();
			}
			for (int i = 0; i < pipe; i++) start = line.find('|', start) + 1;
			bool inside = false;
			int i = command.size() + option.size() + 1 + start;
			for (i; i < end; i++) {
				if (line[i] == '<' || line[i] == '>') {
					if (line.find(".txt", i) == string::npos) {
						errors.push_back(i);
						continue;
					}
					if (line[i] == '<')
					helperF(line, i, errors);
					continue;
				}
				if (line[i] == '"') inside = !inside;
				if (isalpha(line[i]) && !inside) {
					helperF(line, i, errors);
				}
			}
			if (!errors.empty()) throw errors;
		}
	}
	catch (const vector<int>& errors) {
		
		cout << "Error - unexpected characters:" << endl;
		cout << line << endl;
		printPointers(errors);

		command = "";
		argument = "";
		option = "";
		
	}
}

void Parser::helperF(const string& line, int& i, vector<int>& errors){
	if (line.find(".txt", i) != string::npos) {
		int end = line.find(".txt", i);
		for (int j = i; j < line.size(); j++) {
			if (line[j] == '|') break;
			if (isalpha(line[j]) || line[j] == '/') continue;
			else if (j == end) {
				i = end + 3;
				break;
			}
			else {
				for (i; i < j; i++) errors.push_back(i);
				break;
			}
		}
	}
	else errors.push_back(i);
}

void Parser::printPointers(const vector<int>& errors){
	string pointers = "";
	int i = 0, j = 0;
	while (i <= errors[errors.size() - 1]) {
		if (i == errors[j]) {
			pointers += '^';
			i++;
			j++;
		}
		else {
			pointers += ' ';
			i++;
		}
	}
	cout << pointers << endl;
}

void Parser::validateArgument(string& command, string& option, string& argument){
	try {
		vector <int> errors = {};
		int txtCount = 0;
		size_t pos = 0;
		while ((pos = argument.find(".txt", pos)) != string::npos) {
			txtCount++;
			pos += 4;
		}
		if (argument.find(">") == string::npos && argument.find('"') == string::npos &&
			txtCount > 1) {
			int start = argument.find(".txt", 0) + 4;
			for (int i = start; i < argument.size(); i++) 
				if (argument[i] != ' ') errors.push_back(i + command.size() + 1 + option.size());
		}
		if (!errors.empty()) throw errors;
	}
	catch (vector <int> errors) {
		bool haveOption = false;
		if (option != "") haveOption = true;
		cout << "Error - unexpected characters:" << endl;
		if (haveOption) cout << command << " " << option << " " << argument << endl;
		else cout << command << " " << argument << endl;

		printPointers(errors);

		command = "";
		argument = "";
		option = "";
	}
}

string Parser::removeWords(string line, const string& word1, const string& word2){
	if (line.find(word1) != string::npos) line.erase(line.find(word1), word1.length());
	line.erase(line.find(word2), word2.length() + 1);
	if (line[0] == ' ') line.erase(0, 1);
	return line;
}

vector<string> Parser::createVector(const string& line){
	string word = "";
	vector<string> words = {};

	for (char c : line) {
		if (c == ' ' || c == '\t') {
			words.push_back(word);
			word = "";
			continue;
		}
		word += c;
	}
	if (word != "") words.push_back(word);

	return words;
}

bool Parser::isNotFastCommand(const string& command){
	if (command == "time" || command == "date" || command == "exit") return false;
	else return true;
}

string Parser::createArgument(string argument){
	while (true) {
		string l = m_reader->getNextLine();
		if (m_reader->endOfRead()) break;
		if(l != "") argument += l + '\n';
		if (l == "batch") {
			argument = createArgument(argument) + '\n';
			cin.clear();
		}
	}
	argument.erase(argument.length() - 1, 1);

	return argument;
}
