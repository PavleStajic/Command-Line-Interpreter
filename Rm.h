#ifndef RM_H
#define RM_H

#include "Command.h"

// Command that deletes the specified file.
class Rm : public Command {
private:
	void execut(string& argument, string& option, string& filepath) override;
};

inline void Rm::execut(string& argument, string& option, string& filepath) {
	remove(filepath.c_str());
}

#endif 
