#include "Tr.h"
#include "Reader.h"

void Tr::execut(string& argument, string& option, string& filepath) {
	vector<string> textWhatWith = { "", "", "" };
	int count = std::count(argument.begin(), argument.end(), '"');
	string curr = argument;
	string filePath = curr.erase(curr.find(".txt") + 4);
	textWhatWith = getConditions(argument, count, filePath);
	string text = textWhatWith[0];
	string what = textWhatWith[1];
	string with = textWhatWith[2];

	removeQuotes(what);

	int pos = 0;
	while ((pos = text.find(what, pos)) != string::npos) {
		text.replace(pos, what.length(), with);
		pos += with.length();
	}
	text = "\"" + text + "\"";
	print(filepath, text);
}

vector<string> Tr::getConditions(string argument, const int count, const string& filePath) {

	vector<string> conditions = { "", "", "" };
	if (count == 2) {
		twoQuotations(conditions, argument);
	}
	else if (count == 4) {
		fourQuotations(conditions, argument, filePath);
	}
	else if (count == 6) {
		sixQuotations(conditions, argument);
	}
	else if (count > 6) {
		countlessQuotation(conditions, argument);
	}
	return conditions;
}

string Tr::read(const string& filepath) const {
	string argument = "";

	auto reader = make_unique<FileReader>(filepath);

	while (!reader->endOfRead()) argument += reader->getNextLine() + "\n";
	argument.pop_back();

	return argument;
}

void Tr::twoQuotations(vector<string>& conditions, string& argument){
	int firstQuote = argument.find('"');
	int secondQuote = argument.find('"', firstQuote + 1);
	conditions[1] = argument.substr(firstQuote + 1, secondQuote - firstQuote - 1);
	conditions[0] = read(argument.substr(0, firstQuote - 1));
}

void Tr::fourQuotations(vector<string>& conditions, string& argument, const string& filePath){
	if (filePath.find(".txt") == string::npos) {
		int firstQuote = argument.find('"', 1);
		conditions[0] = argument.substr(1, firstQuote - 1);
		conditions[1] = argument.substr(firstQuote + 3, argument.size() - firstQuote - 4);
		if (conditions[0].size() < conditions[1].size()) {
			string curr = conditions[0];
			conditions[0] = conditions[1];
			conditions[1] = curr;
		}
	}
	else {
		int firstQuote = argument.find('"');
		conditions[0] = read(filePath);
		int secondQuote = argument.find('"', firstQuote + 1);
		conditions[1] = argument.substr(firstQuote + 1, secondQuote - firstQuote - 1);
		conditions[2] = argument.substr(secondQuote + 3, argument.size() - secondQuote - 4);
	}
}

void Tr::sixQuotations(vector<string>& conditions, string& argument){
	int firstQuote = argument.find('"');
	int secondQuote = argument.find('"', firstQuote + 1);
	conditions[0] = argument.substr(firstQuote + 1, secondQuote - firstQuote - 1);

	int thirdQuote = argument.find('"', secondQuote + 1);
	int fourthQuote = argument.find('"', thirdQuote + 1);
	conditions[1] = argument.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);

	int fifthQuote = argument.find('"', fourthQuote + 1);
	int sixthQuote = argument.find('"', fifthQuote + 1);
	conditions[2] = argument.substr(fifthQuote + 1, sixthQuote - fifthQuote - 1);
}

void Tr::countlessQuotation(vector<string>& conditions, string& argument){
	reverse(argument.begin(), argument.end());
	int firstQuote = argument.find('"');
	int secondQuote = argument.find('"', firstQuote + 1);
	conditions[2] = argument.substr(firstQuote + 1, secondQuote - firstQuote - 1);
	reverse(conditions[2].begin(), conditions[2].end());

	int thirdQuote = argument.find('"', secondQuote + 1);
	int fourthQuote = argument.find('"', thirdQuote + 1);
	conditions[1] = argument.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);
	reverse(conditions[1].begin(), conditions[1].end());

	int fifthQuote = argument.find('"', fourthQuote + 1);
	conditions[0] = argument.substr(fifthQuote + 1, argument.size() - fifthQuote - 2);
	reverse(conditions[0].begin(), conditions[0].end());
}
