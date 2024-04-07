#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "pngLoader_SDL2.h"

//Инициализация глобальных ресурсов

const int SCREEN_WIDTH = 640;//Ширина окна
const int SCREEN_HEIGHT = 480;//высота окна

bool App_Run = true;//Работа приложения


SDL_Window* window = NULL;//Окно приложения
SDL_Surface* screen_surface = NULL;//Поверхность окна для рисования
SDL_Renderer* Main_render = NULL;//главный рендер

SDL_Event window_event;//События окна
PngTexture t_test;
PngTexture t_test2;

bool Game_Init()
{
    //Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {

        //Создание окна
        window = SDL_CreateWindow("MatrixBS2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            //Инициализация модуля png
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                return false;
            }
            else
            {

                Main_render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if (Main_render == NULL) {
                    std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
                }
                SDL_SetRenderDrawColor(Main_render, 0xFF, 0xFF, 0xFF, 0xFF);

                screen_surface = SDL_GetWindowSurface(window);
            }
            
        }
    }

    t_test = PngTexture("resources/Off.png", 64, 0, 32, 32, Main_render);
    t_test.Set_PosX(64);

    t_test2 = PngTexture("resources/Off.png", 0, 0, 32, 32, Main_render);
    t_test2.Set_PosX(0);
    t_test2.Set_PosY(0);

	return true;
}


void Game_Step()
{

}

void Game_Draw()
{
	
    SDL_RenderClear(Main_render);//Очистка рендера
    
    for (int i = 0; i < (SCREEN_WIDTH / 32); i++)
    {
        for (int j = 0; j < (SCREEN_HEIGHT / 32); j++)
        {
            t_test2.t_Draw();
            t_test2.Set_PosX(i * 32);
            t_test2.Set_PosY(j * 32);
        }
    }

    t_test.t_Draw();

    
    SDL_RenderPresent(Main_render);//обновление экрана
}


void Game_Exit()
{
    t_test2.Free();
    t_test.Free();

	SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(Main_render);
    Main_render = NULL;

	SDL_Quit();
    IMG_Quit();
}