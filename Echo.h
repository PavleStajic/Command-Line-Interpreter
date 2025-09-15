#ifndef ECHO_H
#define ECHO_H

#include "Command.h"

// Command that prints the provided argument as-is.
class Echo : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

//Inline definition.

inline void Echo::execut(string& argument, string& option, string& filepath) {
	print(filepath, argument);
}

#endif 
