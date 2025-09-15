#ifndef PIPE_H
#define PIPE_H

#include<string>
#include<vector>
using namespace std;

// Class Pipe handles parsing and executing a sequence of commands connected by pipes ("|").
// It breaks the input line into individual commands, validates their syntax,
// and manages the execution flow of piped commands.
class Pipe {
public:

	// Constructor that initializes the Pipe object with the given command line.
	// It stores the input pipe line, validates its syntax to ensure proper pipe format,
	// and then parses the line into individual commands ready for execution.
	Pipe(const string& line);

	// Executes a sequence of piped commands.
	// Each command in the pipeline is parsed and executed in order.
	// The output of each command is passed as the argument to the next one.
	// Lexical validation is performed on each step, and execution stops on error.
	void runPipe();

private:
	// Validates the syntax of the entire pipe line to ensure proper format.
	void validatePipe(const string& line);

	// Splits the full piped command line into individual command segments using '|' as a delimiter.
	// Each segment is trimmed of leading and trailing whitespace and stored in m_commandsInPipe.
	void parsPipe(const string& line);

	// Removes leading and trailing whitespace (spaces or tabs) from the given string.
	void eraseWhitespace(string& words);

	vector<string> m_commandsInPipe;	// Stores each command extracted from the pipe.
	string m_pipe;						// The original pipe command line input.
};

#endif 
