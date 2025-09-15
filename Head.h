#ifndef HEAD_H
#define HEAD_H

#include "Command.h"

// Command that prints the first N lines of input.
class Head : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;

	void catchOptionError(string& argument, const string& option, const string& filepath);
};

#endif