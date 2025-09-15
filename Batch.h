#ifndef BATCH_H
#define BATCH_H

#include "Command.h"

// Command that executes a batch of commands line by line.
class Batch : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;

	// Parses a batch argument into a list of command lines.
	vector<string> makeList(const string& argument);

	// Truncates command list after the first "exit", if present.
	void findExit(vector<string>& list);

	// Removes the "batch" command itself from the list (deal with recursion).
	void eraseBatch(vector<string>& list);

	int m_counterBatch = 0;
	vector<string> m_listOfCommands;
};

#endif // !BATCH_H
