#ifndef PARSER_H
#define PARSER_H

#include<memory>
#include"Reader.h"
#include"CommandMenager.h"
#include<vector>


// Parser class is responsible for parsing input data, reading it from a Reader object,
// and interpreting the command-line arguments. It transforms the input into a CommandMenager
// that can be further processed to execut commands.
class Parser {
public:
	//Constructor.
	Parser(unique_ptr<Reader> reader);

	// Constructor that initializes the parser with a copy of a Reader object.
	// Typically used for parsing a predefined list of commands.
	Parser(unique_ptr<Reader> reader, bool forList);

	// Reads the next line of input from the reader, sends it to the parsLine function for processing,
	// and returns the resulting CommandMenager object.
	CommandMenager pars();

	// Parses a single line of input and returns a CommandMenager object.
	CommandMenager parsLine(const string& line);

	// Parses all lines from a Reader object initialized with a predefined list of commands.
	// Returns a CommandMenager containing all parsed commands.
	CommandMenager parsList();

private:

	// Checks for lexical errors in the command line input, including pipes, redirections, and quotes.
	// Throws error positions if invalid syntax is found, then prints errors and clears inputs.
	// 'pipe' indicates which pipe segment to check (0 if none).
	static void catchLexicalErrors(const string& line, string& command, string& option, string& argument, int pipe);

	// Handles lexical errors related to file names, marking invalid characters before ".txt".
	// Used as a helper function within the main lexical error checking routine.
	static void helperF(const string& line, int& i, vector<int>& errors);

	// Prints visual indicators (like '^' or similar markers) at positions of lexical errors.
	static void printPointers(const vector<int>& errors);

	// Validates whether the provided argument is appropriate for the given command and option.
	static void validateArgument(string& command, string& option, string& argument);
	
	// Removes option and command from a given line.
	static string removeWords(string line, const string& word1, const string& word2);

	// Creates a vector of strings(words) from input line.
	static vector<string> createVector(const string& line);

	// Checks if the provided command is the command which needs argument.
	static bool isNotFastCommand(const string& command);

	// Continuously reads lines from the reader until the end of the input is reached, 
	// and appends each line to the provided argument string.
	string createArgument(string argument);

	
	unique_ptr<Reader> m_reader;	    // Pointer to the Reader object used for reading input data.
	unique_ptr<Reader> m_readerOfList;	// Reader used specifically for parsing command lists
	int m_num = 0;

	friend class Pipe;
};

#endif
