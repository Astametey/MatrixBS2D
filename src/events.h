#ifndef EVENTS_H
#define EVENTS_H

SDL_Event window_event;//События окна
bool App_Run = true;//Работа приложения
const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);


void KeyBoardEvent()
{
			player.speedx = 0;
			if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
				
				player.speedx = 4;
			}
			
			if (currentKeyStates[SDL_SCANCODE_LEFT]) {

				player.speedx = -4;
			}
			player.speedy = 0;
			if (currentKeyStates[SDL_SCANCODE_UP]) {

				player.speedy = -4;
			}
			
			if (currentKeyStates[SDL_SCANCODE_DOWN]) {

				player.speedy = +4;
			}

}

#endif