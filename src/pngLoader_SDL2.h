#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>

//Инициализация глобальных ресурсов
SDL_Color textColor = { 225,0,0 };
TTF_Font* gFont;

class PngTexture
{
private:


	float w, h;
    int frame = 0;

    SDL_Surface* temp_surf = NULL;
    SDL_Texture* t_texture = NULL;
    SDL_Renderer* r_ren = NULL;
    SDL_Rect rect_texture;
    SDL_Rect pos_texture;
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL; //начальная позиция

public:
    PngTexture()
    {
        t_texture = NULL;
    };

	PngTexture(std::string path_to_file, float X, float Y, float W, float H, SDL_Renderer* ren)
	{
        r_ren = ren;
        rect_texture.x = X;
        rect_texture.y = Y;
        rect_texture.w = W;
        rect_texture.h = H;
        
        pos_texture.x = X;
        pos_texture.y = Y;
        pos_texture.w = W;
        pos_texture.h = H;
        
        w = W;
        h = h;

        temp_surf = IMG_Load(path_to_file.c_str());
        if (temp_surf == NULL) {
            std::cout << "Can't load image: " << IMG_GetError() << std::endl;
        }
        t_texture = SDL_CreateTextureFromSurface(ren, temp_surf);
        if (t_texture == NULL) {
            std::cout << "Can't create texture from surface: " << SDL_GetError() << std::endl;
        }

	}

    void t_Draw()
    {
        SDL_RenderCopy(r_ren, t_texture, &rect_texture, &pos_texture);//Вывод изображения
    }

    void t_Update()
    {
        frame += 1;
        if (frame > 11)
        {
            frame = 0;
        }
        rect_texture.x = w * frame;

    }

    void Set_TextureRect(float x, float y)
    {
        rect_texture.x = x;
        rect_texture.y = y;
    }

    SDL_Rect GetRect()
    {
        return rect_texture;
    }


    void Set_TextureSize(float w, float h)
    {
        pos_texture.w = w;
        pos_texture.h = h;
    };
    
    SDL_Rect GetPosition()
    {
        return pos_texture;
    }

    void SetPosition(float x, float y, SDL_Rect view)
    {
        pos_texture.x = view.x + x;
        pos_texture.y = view.y + y;
    }

    void SetPosition(float x, float y)
    {
        pos_texture.x = x;
        pos_texture.y = y;
    }
    
    void MovePosition(float x, float y)
    {
        SetPosition(GetPosition().x + x, GetPosition().y + y);
    }

    void Free()
    {
        SDL_DestroyTexture(t_texture);
        t_texture = NULL;
    }

    ~PngTexture()
    {
        SDL_FreeSurface(temp_surf);
        temp_surf = NULL;
    }

};

class TTFLoad_SDL2
{
private:


    float x, y;

    SDL_Surface* text_surf = NULL;
    
    SDL_Texture* t_texture = NULL;
    SDL_Renderer* r_ren = NULL;
    SDL_Rect pos_text;
    SDL_Rect rect_text;



public:
    TTFLoad_SDL2()
    {
        t_texture = NULL;
    };

    TTFLoad_SDL2(std::string text, float x, float y, SDL_Renderer* ren)
    {
        r_ren = ren;
        if (gFont == NULL) {
            std::cout << "Failed to load font! SDL_ttf Error: \n" << TTF_GetError() << std::endl;
        }
        else
        {
            text_surf = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
            if (text_surf == NULL) {
                std::cout << "Unable to render text surface! SDL_ttf Error: \n" << TTF_GetError() << std::endl;
            }
            else
            {
                t_texture = SDL_CreateTextureFromSurface(ren, text_surf);
                if (t_texture == NULL) {
                    std::cout << "Unable to create texture from rendered text! SDL Error: \n" << SDL_GetError() << std::endl;
                }
            }
            pos_text.x = x;
            pos_text.y = y;
            pos_text.w = text_surf->w;
            pos_text.h = text_surf->h;

            rect_text.w = text_surf->w;
            rect_text.h = text_surf->h;
            rect_text.x = 0;
            rect_text.y = 0;

            

            std::cout << "text w:" << pos_text.w << std::endl;
            std::cout << "text h:" << pos_text.h << std::endl;
            
        }

        

    }

    void t_Draw()
    {
        SDL_RenderCopy(r_ren, t_texture, &rect_text, &pos_text);//Вывод строки
    }

    void t_Update()
    {
       

    }


    void Set_TextureSize(float w, float h)
    {
        pos_text.x = w;
        pos_text.y = h;
    };

    SDL_Rect GetPosition()
    {
        return pos_text;
    }

    void SetPosition(float x, float y)
    {
        pos_text.x = x;
        pos_text.y = y;
    }

    void MovePosition(float x, float y)
    {
        SetPosition(GetPosition().x + x, GetPosition().y + y);
    }

    void Free()
    {
        SDL_DestroyTexture(t_texture);
        t_texture = NULL;
    }

    ~TTFLoad_SDL2()
    {
        SDL_FreeSurface(text_surf);
        text_surf = NULL;
    }

};






