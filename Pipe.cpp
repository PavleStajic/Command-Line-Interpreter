#include "Pipe.h"
#include"CommandMenager.h"
#include"Parser.h"

Pipe::Pipe(const string& line){
	m_pipe = line;
	validatePipe(line);
	parsPipe(m_pipe);
}

void Pipe::runPipe(){
	if (m_pipe.empty()) return;

	vector<string> words = Parser::createVector(m_commandsInPipe[0]);
	int n = words.size();
	string command = words[0];
	string option = "";
	string argument = "";

	if (n > 1) if (words[1][0] == '-') option = words[1];        
	if (n > 1) argument = Parser::removeWords(m_commandsInPipe[0], option, command);

	int m = m_commandsInPipe.size();
	for (int i = 1; i < m; i++) {
		CommandMenager menager(command, option, argument);
		menager.manage();

		argument = menager.getCurrResult();
		words = Parser::createVector(m_commandsInPipe[i]);
		command = words[0];
		n = words.size();
		if (n > 1) if (words[1][0] == '-') option = words[1];
		else option = "";
		if(n > 1) argument += Parser::removeWords(m_commandsInPipe[i], option, command);
		
		Parser::catchLexicalErrors(m_pipe, command, option, argument, i);
		if (command.empty() && option.empty() && argument.empty()) return;
	}

	CommandMenager::flagOff();
	CommandMenager menager(command, option, argument);
	menager.manage();
}

void Pipe::validatePipe(const string& line){
	try {
		vector<int> errors = {};
		int end = line.rfind("|");

		for (int i = 0; i < end; i++) {
			if (line[i] == '>') {
				int end = line.find(".txt", i) + 3;
				while (i <= end) errors.push_back(i++);
			}
		}
		if (!errors.empty()) throw errors;
	}
	catch (const vector<int>& errors) {
		cout << "Error. Incorrect use of pipeline." << endl;
		cout << line << endl;
		Parser::printPointers(errors);
		
		m_pipe = "";
		return;
	}
}

void Pipe::parsPipe(const string& line){
	if (line.empty()) return;
	string words = "";
	for (const char c : line) {
		if (c != '|') words += c;
		else {
			eraseWhitespace(words);
			m_commandsInPipe.push_back(words);
			words = "";
		}
	}
	eraseWhitespace(words);
	m_commandsInPipe.push_back(words);
}

void Pipe::eraseWhitespace(string& words){
	for (const char c : words) {
		if (c == ' ' || c == '\t') words.erase(0, 1);
		else break;
	}
	for (int i = words.size() - 1; i > 0; i--) {
		if (words[i] == ' ' || words[i] == '\t') words.erase(i, words.size());
		else break;
	}
	return;
}
