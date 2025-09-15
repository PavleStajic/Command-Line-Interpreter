#include "Engine.h"
#include "Reader.h"
#include"Parser.h"
#include<iostream>
#include <memory>
using namespace std;

//Class Engine

void Engine::start(){

	auto consoleReader = make_unique<ConsoleReader>();
	Parser parser(move(consoleReader));

	while (true) {
		cout << m_sign;
		parser.pars().manage();
		cin.clear();
	}
}


