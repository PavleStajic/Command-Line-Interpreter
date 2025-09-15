#include "Batch.h"
#include "Parser.h"

void Batch::execut(string& argument, string& option, string& filepath) {
	argument = removeQuotes(argument);
	m_listOfCommands = makeList(argument);
	findExit(m_listOfCommands);
	eraseBatch(m_listOfCommands);

	int n = m_listOfCommands.size();

	auto reader = make_unique<Reader>(m_listOfCommands);
	Parser parserOfLines(move(reader), true);

	while (m_counterBatch < n) {
		CommandMenager(parserOfLines.parsList()).manage();
		m_counterBatch++;
	}
}

vector<string> Batch::makeList(const string& argument) {
	vector<string> listOfCommands = {};

	string command = "";
	for (char c : argument) {
		if (c != '\n') {
			command += c;
		}
		else {
			listOfCommands.push_back(command);
			command = "";
		}
	}
	listOfCommands.push_back(command);

	return listOfCommands;
}

void Batch::findExit(vector<string>& list) {
	int n = list.size();
	for (int i = 0; i < n; i++) {
		if (list[i] == "exit" && i != (n - 1)) {
			list.erase(list.begin() + i + 1, list.end());
			break;
		}
	}
	return;
}

void Batch::eraseBatch(vector<string>& list) {
	int n = list.size();
	for (int i = 0; i < n; i++) {
		if (list[i] == "batch") {
			list.erase(list.begin() + i, list.begin() + i + 1);
			break;
		}
	}
	return;
}
