#ifndef TR_H
#define TR_H

#include "Command.h"

// Command that replaces occurrences of a string with another in the input.
class Tr : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;

	// Parses conditions for replacement: text, target string, and replacement.
	vector<string> getConditions(string argument, const int count, const string& filePath);

	// Reads file content line-by-line into a single string.
	string read(const string& filepath) const;

	//Used when a text file and what are given.
	void twoQuotations(vector<string>& conditions, string& argument);

	//Used when a text file, what, and with are given, or when text and what are provided.
	void fourQuotations(vector<string>& conditions, string& argument, const string& filePath);

	//Used when text, what, and with are given.
	void sixQuotations(vector<string>& conditions, string& argument);

	//Used when the text itself contains quotation marks.
	void countlessQuotation(vector<string>& conditions, string& argument);
};

#endif 
