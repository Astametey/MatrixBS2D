#include <string>


class PngTexture
{
private:
	float x, y, w, h;
    SDL_Surface* temp_surf = NULL;
    SDL_Texture* t_texture = NULL;
    SDL_Renderer* r_ren = NULL;
    SDL_Rect rect_texture;
    SDL_Rect pos_texture;

public:
    PngTexture()
    {
    
    };

	PngTexture(std::string str, float X, float Y, float W, float H, SDL_Renderer* ren)
	{
        r_ren = ren;
        rect_texture.x = X;
        rect_texture.y = Y;
        rect_texture.w = 32;
        rect_texture.h = 32;
        
        pos_texture.x = X;
        pos_texture.y = Y;
        pos_texture.w = W;
        pos_texture.h = H;
        
        temp_surf = IMG_Load(str.c_str());
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


    void Set_PosX(float x)
    {
        pos_texture.x = x;
    }
    void Set_PosY(float y)
    {
        pos_texture.y = y;
    }

    void Set_TextureRect(float x, float y)
    {
        rect_texture.x = x;
        rect_texture.y = y;
    }

    void Set_TextureSize(float w, float h)
    {
        pos_texture.w = w;
        pos_texture.h = h;
    };

    float Get_PosX()
    {
        return pos_texture.x;
    };

    float Get_PosY()
    {
        return pos_texture.y;
    };

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