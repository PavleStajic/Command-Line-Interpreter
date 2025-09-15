#ifndef TOUCH_H
#define TOUCH_H

#include "Command.h"

// Command that creates a new empty file.
// Displays an error if the file already exists.
class Touch : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;

	// Checks if the file already exists.
	bool fileExists(const string& filepath);
};

#endif // !TOUCH_H
