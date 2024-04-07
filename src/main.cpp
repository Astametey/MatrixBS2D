#include "game.h"

int main(int argc, char** args)
{
	if (!Game_Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{

	}
	
	while (App_Run)
	{
		while (SDL_PollEvent(&window_event) != 0) {
			if (window_event.type == SDL_QUIT) {
				App_Run = false;
			}

			if (window_event.type == SDL_KEYDOWN) {
				if (window_event.key.keysym.sym == SDLK_RIGHT) {
					t_test.Set_PosX(t_test.Get_PosX() + 32);
				}
				if (window_event.key.keysym.sym == SDLK_LEFT) {
					t_test.Set_PosX(t_test.Get_PosX() - 32);
				}
				if (window_event.key.keysym.sym == SDLK_UP) {
					t_test.Set_PosY(t_test.Get_PosY() - 32);
				}
				if (window_event.key.keysym.sym == SDLK_DOWN) {
					t_test.Set_PosY(t_test.Get_PosY() + 32);
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

