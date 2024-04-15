#include "game.h"

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


			if (window_event.type == SDL_KEYDOWN) {
				if (window_event.key.keysym.sym == SDLK_RIGHT) {
					player.MovePosition(player.speed, 0);
				}

				if (window_event.key.keysym.sym == SDLK_LEFT) {
					player.MovePosition(-player.speed, 0);
				}

				if (window_event.key.keysym.sym == SDLK_UP) {
					player.MovePosition(0, -player.speed);
				}

				if (window_event.key.keysym.sym == SDLK_DOWN) {
					player.MovePosition(0, player.speed);
				}

				if (window_event.key.keysym.sym == SDLK_p) {
					system("cls");
					std::cout << "posPLx: " << player.GetPosition().x << std::endl;
					std::cout << "posPLy: " << player.GetPosition().y << std::endl;
					std::cout << "posCamx: " << camera.x << std::endl;
					std::cout << "posCamy: " << camera.y << std::endl;
					std::cout << "dist: " << player.GetDist(camera.x, camera.y) << std::endl;
					
				}
				
			}
		}

		Game_Step();

		Game_Draw();
	}

	

	//SDL_Delay(2000);

	Game_Exit();//Завершение программы
	return 0;
}

