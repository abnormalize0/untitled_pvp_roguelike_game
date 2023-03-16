#include "GameManager.h"

#define SERVER 1
#define CLIENT 0

int main() {
	GameManager game(CLIENT);
	game.play();

	return 0;
}