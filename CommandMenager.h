#ifndef CCOMMANDMENAGER_H
#define CCOMMANDMENAGER_H

#include<string>
#include "CommandMap.h"

using namespace std;

// Handles command execution along with its option and argument.
// Supports file input/output redirection and result management.
class CommandMenager {
public:
	// Initializes the command manager with given values.
	// Detects if argument is a file and processes redirection
	CommandMenager(const string& command, const string& option, const string& argument);

	// Main function to manage the execution of the command.
	void manage();

	const string& getCurrResult() const { return m_currResult; }

	static bool getFlag() { return m_pipeFlag; }
	static void flagOn() { m_pipeFlag = true; }
	static void flagOff() { m_pipeFlag = false; }
	
private:
	// Removes a substring from a given string.
	void removeSubstring(string& str, const string& toRemove);

	// Determines whether the argument is fail or not.
	bool realArgument(const string& argument) const;

	// Handles redirection and returns the output filename if present.
	string isRedirect(string fileName);

	// Checks if the given argument represents a file path.
	bool isFilePath(const string& argument) const;

	// Checks if the file at the given file path exists.
	bool fileExists(const string& failpath) const;

	// Reads content from file if it exists and returns it as a string.
	string read(const string& filepath, const string& command) const;
	
	string m_filepath = "";  // File used for redirection or reading.
	string m_command;        // Command to be executed.
	string m_option;         // Optional argument modifier
	string m_argument;		 // Text or file-based input.
	string m_currResult;	 // Stores output of the command.
	static bool m_pipeFlag;  // Tracks if execution is part of a pipe.
};

 
#endif 

