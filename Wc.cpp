#include "Wc.h"

void Wc::execut(string& argument, string& option, string& filepath) {
	catchOptionErrors(argument, option, filepath);
	if (argument == "") return;

	argument = removeQuotes(argument);

	if (argument.empty()) {
		print(filepath, "0");
		return;
	}

	int i = 1;
	if (option == "-w") {
		for (char c : argument) {
			if (isspace(c)) i++;
		}
		print(filepath, to_string(i));
	}
	else {
		print(filepath, to_string(argument.length()));
	}
}

void Wc::catchOptionErrors(string& argument, const string& option, const string& filepath){
	try {
		vector<int> errors = {};
		if (option.find("w") < option.find("c")) {
			for (int i = 1; i < option.size(); i++) {
				if (option[i] != 'w') errors.push_back(i + 3);
			}
		}
		else {
			for (int i = 1; i < option.size(); i++) {
				if (option[i] != 'c') errors.push_back(i + 3);
			}
		}
		if (!errors.empty()) throw errors;
	}
	catch (const vector<int>& errors) {
		cout << "Error - incorect option." << endl;
		if (!filepath.empty()) cout << "wc " << option << " " << filepath << endl;
		else {
			for (int i = 0; i < argument.size(); i++) if (argument[i] == '\n') argument[i] = ' ';
			cout << "wc " << option << " " << argument << endl;
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
