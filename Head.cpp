#include "Head.h"

//Class Head

void Head::execut(string& argument, string& option, string& filepath) {
	catchOptionError(argument, option, filepath);
	if (argument == "") return;

	int n = stoi(option.erase(0, 2));

	int i = 0;
	string line = "";
	string lines = "";
	for (char c : argument) {
		if (c != '\n' && c != EOF) line += c;
		else {
			i++;
			lines += line + '\n';
			line = "";
			if (i == n) break;
		}
	}
	if (line != "") lines += line;
	lines.pop_back();
	lines = lines + "\"";
	print(filepath, lines);
}

void Head::catchOptionError(string& argument, const string& option, const string& filepath){
	try {
		vector<int> errors = {};

		int foundN = 2;
		for (int i = 1; i < option.size(); i++) {
			if (option[i] != 'n') errors.push_back(i + 5);
			else {
				foundN = i + 1;
				break;
			}
		}
		bool flag = false;
		for (int i = foundN; i < option.size(); i++) {
			if (isdigit(option[i]) && !flag) {
				while (isdigit(option[i]) && i < option.size()) i++;
				i--;
				flag = true;
			}
			else errors.push_back(i + 5);
		}
		if (!errors.empty()) throw errors;
	}
	catch (const vector<int>& errors) {
		cout << "Error - incorect option." << endl;
		if (!filepath.empty()) cout << "head " << option << " " << filepath << endl;
		else {
			for (int i = 0; i < argument.size(); i++) if (argument[i] == '\n') argument[i] = ' ';
			cout << "head " << option << " " << argument << endl;
		}

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
		argument = "";
		return;
	}
}
