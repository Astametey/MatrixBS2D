#include "pngLoader_SDL2.h"
#include <math.h>

class Entity
{
private:
	
	SDL_Rect pos_entity;
	int id = 0;
	PngTexture t_texture;

public:
	float speedx = 0, speedy = 0;

	Entity()
	{

	};

	//void checkCollision(SDL_Rect obj_rect)
	//{
	//	
	//	if (pos_entity.x < obj_rect.x + obj_rect.w && pos_entity.y > obj_rect.y - 1 && pos_entity.y < obj_rect.y + obj_rect.h)
	//	{
	//		pos_entity.x -= speedx;
	//	};
	//}

	Entity(float X, float Y, PngTexture texture)
	{
		t_texture = texture;
		pos_entity.x = X; pos_entity.y = Y;
		t_texture.SetPosition(pos_entity.x, pos_entity.y);
	};

	void E_Draw()
	{
		t_texture.t_Draw();
	}

	PngTexture GetTexture()
	{
		return t_texture;
	}

	void E_Update()
	{
		t_texture.t_Update();
	}

	SDL_Rect GetPosition()
	{
		return pos_entity;
	}

	void SetPosition(float x, float y)
	{
		pos_entity.x = x;
		pos_entity.y = y;
	}

	float GetDist(float X, float Y)
	{
		return sqrt((X - pos_entity.x) * (X - pos_entity.x) + (Y - pos_entity.y) * (Y - pos_entity.y));
	};

	void MovePosition(float x, float y)
	{
		SetPosition(GetPosition().x + x, GetPosition().y + y);
	}

	void E_free()
	{
		t_texture.Free();
	}

	~Entity()
	{
		
	}

};