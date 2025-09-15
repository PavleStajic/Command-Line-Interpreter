#include "Command.h"
#include "CommandMenager.h"

void Command::print(string& filePath, string output){
	if (CommandMenager::getFlag()) {
		m_result = output;
		return;
	}
	output = removeQuotes(output);
	if (filePath.find(">") == string::npos) cout << output << endl;
	else if (filePath[1] == '>') {
		filePath.erase(0, 2);
		ofstream file(filePath, ios::app);
		file << output;
		file.close();
	}
	else {
		filePath.erase(0, 1);
		ofstream file(filePath, ios::out | ios::trunc);
		file << output;
		file.close();
	}
}

string Command::removeQuotes(string& argument){
	if (argument != "") {
		if (argument[0] == '"') argument.erase(0, 1);
		if (argument[argument.length() - 1] == '"') argument.pop_back();
	}
	return argument;
}
