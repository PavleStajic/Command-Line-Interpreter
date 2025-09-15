#ifndef DATE_H
#define DATE_H

#include "Command.h"

// Command that outputs the current system date.
class Date : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

#endif 
