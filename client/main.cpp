#include "GameManager.h"

int main() {
	GameManager game;
	//sf::Thread thread(&GameManager::parallel_send, &game);
	//thread.launch();
	game.play();

	return 0;
}