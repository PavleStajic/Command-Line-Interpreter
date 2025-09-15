#ifndef TIME_H
#define TIME_H

#include "Command.h"

// Command that outputs the current system time.
class Time : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

#endif 
