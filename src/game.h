#include <iostream>

#include "Entity.h"
#include "level.h"


//Инициализация глобальных ресурсов



SDL_Window* window = NULL;//Окно приложения
SDL_Surface* screen_surface = NULL;//Поверхность окна для рисования
SDL_Surface* View_surface = NULL;//view surface
SDL_Renderer* Main_render = NULL;//главный рендер

Level level_test;

PngTexture t_player;

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
    

    //load level file
    level_test.LoadFromFile("resources/testmap.tmx", "resources/tile set.png", Main_render);
    //player.SetPosition(level_test.GetObject("obj_player").rect.x, level_test.GetObject("obj_player").rect.y);

        //load text
    gFont = TTF_OpenFont("resources/Times_New_Roman.ttf", 24);
    gTextTexture = TTFLoad_SDL2("Player", 32, 100, Main_render);
        
   
}

void Game_Step()
{
    Camera_step(player.GetPosition().x, player.GetPosition().y);
    player.E_Update();
   
    player.MovePosition(player.speedx, player.speedy);
    //player.checkCollision(level_test.GetObject("solid").rect);
    


    gTextTexture.SetPosition(SCREEN_WIDTH / 2 - 6, SCREEN_HEIGHT / 2 - 22);
}

void Game_Draw()
{
    
    SDL_RenderClear(Main_render);//Очистка рендера
    
    /// Рисование уровня
    level_test.Draw();

    
    player.E_Draw();//Игрок
    gTextTexture.t_Draw();//Текst

    SDL_RenderPresent(Main_render);//обновление экрана
}


void Game_Exit()
{
    t_player.Free();
    gTextTexture.Free();

    player.E_free();

    level_test.L_Free();

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