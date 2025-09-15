#ifndef PROMPT_H
#define PROMPT_H

#include "Command.h"

// Command that sets a new shell prompt (custom input sign).
class Prompt : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

#endif
