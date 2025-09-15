#ifndef TRUNCATE_H
#define TRUNCATE_H

#include "Command.h"
#include <fstream>

// Command that truncates (clears) the contents of a file.
class Truncate : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

inline void Truncate::execut(string& argument, string& option, string& filepath) {
	ofstream file(filepath, ios::trunc);
}

#endif // !TRUNCATE_H
