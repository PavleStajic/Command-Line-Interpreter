#include "Prompt.h"
#include "Engine.h"

void Prompt::execut(string& argument, string& option, string& filepath) {
	Engine& engine = Engine::getInstance();
	argument = removeQuotes(argument);
	engine.m_sign = argument + " ";
}