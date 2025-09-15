#include"Engine.h"

int main() {

	Engine& engine = Engine::getInstance();
	engine.start();
	return 0;
}