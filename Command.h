#ifndef COMMAND_H
#define COMMAND_H

#include<iostream>
#include<vector>
#include<string>
#include<cstdio>

using namespace std;

//Abstract base class representing a generic command.
class Command {
public:
	//Pure virtual function. 
	//It defines the logic for executing the command using the provided arguments.
	virtual void execut(string& argument, string& option, string& filepath) = 0;
	
	// Returns the result of the executed command.
	const string& getResult () const { return m_result; }

protected:

	// Final method that can be used by derived classes to print output.
	virtual void print(string& filePath, string output) final;

	// Utility method that removes surrounding quotes from a string argument.
	string removeQuotes(string& argument);

private:

	string m_result;	// Stores the result of command execution.
};

#endif