#ifndef EXIT_H
#define EXIT_H

#include "Command.h"

//Exit the program.
class Exit : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

inline void Exit::execut(string& argument, string& option, string& filepath) {
	exit(0);
}

#endif // !EXIT_H
