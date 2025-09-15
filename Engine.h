#include <string>
#ifndef ENGINE_H
#define ENGINE_H


//Represents the engine that starts and manages the command line interpreter.
class Engine {
public:

	// Returns a reference to the singleton instance of the Engine class.
	// This ensures that only one instance of Engine exists throughout the application.
	static Engine& getInstance() {
		static Engine instance;
		return instance;
	}

	// Starts the engine, initiating the main loop of the program.
	// It continually processes user input by reading commands, parsing them,
	// and executing the corresponding actions until the program is terminated.
	void start();

private:
	// Private constructor to prevent direct instantiation from outside the class.
	Engine(){}

	// Deleted copy constructor to prevent copying of the singleton instance.
	Engine(const Engine&) = delete;

	// Deleted assignment operator to prevent assignment of the singleton instance.
	void operator=(const Engine&) = delete;

	// The prompt symbol displayed before each user command input.
	std::string m_sign = "$ ";

	// Allows the Prompt class to access private members of Engine.
	friend class Prompt;
};

#endif

