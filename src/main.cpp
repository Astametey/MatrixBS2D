#include "game.h"
#include "events.h"

int main(int argc, char** args)
{
	if (!Game_Init())
	{
		printf("Failed to initialize!\n");
	}
	else 
	{
		Game_LoadMedia();
	}
	
	while (App_Run)
	{

		while (SDL_PollEvent(&window_event) != 0) {
			if (window_event.type == SDL_QUIT) {
				App_Run = false;
			}
			KeyBoardEvent();
		}
		

		Game_Step();

		Game_Draw();

		if (currentKeyStates[SDL_SCANCODE_P]) {
			system("cls");
			std::cout << "posPLx: " << player.GetPosition().x << std::endl;
			std::cout << "posPLy: " << player.GetPosition().y << std::endl;

		}
	}

	

	//SDL_Delay(2000);

	Game_Exit();//Завершение программы
	return 0;
}

