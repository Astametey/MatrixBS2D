#include <iostream>

#include "Entity.h"
#include "camera.h"

//Инициализация глобальных ресурсов

bool App_Run = true;//Работа приложения

SDL_Window* window = NULL;//Окно приложения
SDL_Surface* screen_surface = NULL;//Поверхность окна для рисования
SDL_Surface* View_surface = NULL;//view surface
SDL_Renderer* Main_render = NULL;//главный рендер



SDL_Event window_event;//События окна
PngTexture t_player;
PngTexture t_test2;

Entity player;

TTFLoad_SDL2 gTextTexture;


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
                    std::cout << "Can't create renderer! Main_render: " << SDL_GetError() << std::endl;
                }
                SDL_SetRenderDrawColor(Main_render, 225, 0xFF, 0xFF, 0xFF);

                screen_surface = SDL_GetWindowSurface(window);
                View_surface = SDL_GetWindowSurface(window);
                
                //Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    return false;
                }

            }
            
        }
    }

    
    
	return true;
}

void Game_LoadMedia()
{
    t_player = PngTexture("resources/Entities/little_demon_col.png", 0, 0, 12, 20, Main_render);
    player = Entity(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, t_player);
    player.SetPosition(0, 0);

    t_test2 = PngTexture("resources/Off.png", 0, 0, 32, 32, Main_render);
    t_test2.SetPosition(0, 0);

   
        //load text
    gFont = TTF_OpenFont("resources/Times_New_Roman.ttf", 24);
    gTextTexture = TTFLoad_SDL2("Player", 32, 100, Main_render);
        
}

void Game_Step()
{

    Camera_step(player.GetPosition().x, player.GetPosition().y);
    player.E_Update();


    gTextTexture.SetPosition(SCREEN_WIDTH / 2 - 6, SCREEN_HEIGHT / 2 - 22);
}

void Game_Draw()
{
    
    SDL_RenderClear(Main_render);//Очистка рендера
    
    /// Рисование уровня
    for (int i = 0; i < (LEVEL_WIDTH / 32) + 3 ; i++)
    {
        for (int j = 0; j < (LEVEL_HEIGHT / 32) + 3; j++)
        {

            if (i == 0 || i == (LEVEL_WIDTH / 32) + 2 || j == 0 || j == (LEVEL_HEIGHT / 32) + 2)
            {
                t_test2.Set_TextureRect(64, 0);
            }
            else
            {
                t_test2.Set_TextureRect(0, 0);
            }

            t_test2.SetPosition((i * 32 + (SCREEN_WIDTH / 2)), (j * 32 + (SCREEN_HEIGHT / 2)), camera);
            if ((i * 32) > player.GetPosition().x - camera.w && (i * 32) < player.GetPosition().x + camera.w &&
                (j * 32) > player.GetPosition().y - camera.h && (j * 32) < player.GetPosition().y + camera.h)
            {
               t_test2.t_Draw();
            }
                
            
            
        }
    }

    player.E_Draw();//Игрок
    gTextTexture.t_Draw();//Текst

    SDL_RenderPresent(Main_render);//обновление экрана
}


void Game_Exit()
{
    t_test2.Free();
    t_player.Free();
    gTextTexture.Free();

    player.E_free();

    TTF_CloseFont(gFont);
    gFont = NULL;

	SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(Main_render);
    Main_render = NULL;

    View_surface = NULL;

    TTF_Quit();
	SDL_Quit();
    IMG_Quit();
}