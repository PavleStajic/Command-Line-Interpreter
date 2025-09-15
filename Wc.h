#ifndef WC_H
#define WC_H

#include "Command.h"

// Command that counts characters (-c) or words (-w) in the input.
class Wc : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;

	void catchOptionErrors(string& argument, const string& option, const string& filepath);
};

#endif
