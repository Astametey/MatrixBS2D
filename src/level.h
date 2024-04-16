#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include <iostream>
#include "tinyxml/tinyxml.h"
#include "camera.h"

Entity player;

struct Object
{
	int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;//объявили переменную name типа string
	std::string type;//а здесь переменную type типа string
	std::map<std::string, std::string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый
};
struct Layer//слои
{
	int opacity;//непрозрачность слоя
};


class Level//главный класс - уровень
{
public:
	PngTexture tileMap_texture;
	SDL_Renderer* r_ren = NULL;
	bool LoadFromFile(std::string filename, std::string tileset_path, SDL_Renderer* l_ren);//возвращает false если не получилось загрузить
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
	std::vector<SDL_Rect> num_tile;
	SDL_Rect GetTileSize;//получаем размер тайла
	int** tileGID = { new int* [width] };//Vector tile gid // выделяем память под двухмерный массив
	
	void Draw();
	Level();
	void L_Free();
private:
	int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
	int firstTileID;//получаем айди первого тайла
	std::vector<Object> objects;//массив типа Объекты, который мы создали
	std::vector<Layer> layers;
};
///////////////////////////////////////
int Object::GetPropertyInt(std::string name)//возвращаем номер свойства в нашем списке
{
	return atoi(properties[name].c_str());
}
float Object::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}
std::string Object::GetPropertyString(std::string name)//получить имя в виде строки.вроде понятно
{
	return properties[name];
}
bool Level::LoadFromFile(std::string filename, std::string tileset_path, SDL_Renderer* l_ren)//двоеточия-обращение к методам класса вне класса 
{
	r_ren = l_ren;
	TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument
	// загружаем XML-карту
	if (!levelFile.LoadFile())//если не удалось загрузить карту
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
		return false;
	}
	// работаем с контейнером map
	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");
	// пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	std::cout << "width level = " << width << std::endl;
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	std::cout << "height level = " << height << std::endl;
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	std::cout << "tile Width = " << tileWidth << std::endl;
	tileHeight = atoi(map->Attribute("tileheight"));
	std::cout << "tile Height = " << tileHeight << std::endl;
	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	for (unsigned i{}; i < width; i++)
	{
		tileGID[i] = new int[height] {};
	}

	

	// source - путь до картинки в контейнере image
	//TiXmlElement* image;
	//image = tilesetElement->FirstChildElement("image");
	//std::string imagepath = image->Attribute("source");
	// пытаемся загрузить тайлсет
	
	tileMap_texture = PngTexture(tileset_path.c_str(), 0, 0, tileWidth, tileHeight, r_ren);

	// получаем количество столбцов и строк тайлсета
	int columns = tileMap_texture.GetStartRect().w / tileWidth;
	int rows = tileMap_texture.GetStartRect().h / tileHeight;
	std::cout << "columns = " << columns << std::endl;
	std::cout << "rows = " << rows << std::endl;

	// вектор из прямоугольников изображений (TextureRect)
	GetTileSize.w = tileWidth;
	GetTileSize.h = tileHeight;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			SDL_Rect rect;
			rect.x = i * tileWidth;
			rect.y = j * tileHeight;
			rect.w = tileWidth;
			rect.h = tileHeight;
			num_tile.push_back(rect);
			
		}
		
	}

	//Загрузка номеров тайлов
	
	// работа со слоями
	/*
	
	while (layerElement)
	{
		Layer layer;
		// если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}
		//  контейнер <data> 
		
		//  контейнер <tile> - описание тайлов каждого слоя
		
		int x = 0;
		int y = 0;
		
		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;
			// Устанавливаем TextureRect каждого тайла
			tileElement = tileElement->NextSiblingElement("tile");
			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}
		layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");
	}
	
	// работа с объектами
	TiXmlElement* objectGroupElement;
	// если есть слои объектов
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		
	}
	else
	{
		std::cout << "No object layers found..." << std::endl;
	}
	return true;
	*/

	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");

	TiXmlElement* layerDataElement;
	layerDataElement = layerElement->FirstChildElement("data");
	if (layerDataElement == NULL)
	{
		std::cout << "Bad map. No layer information found." << std::endl;
	}

	TiXmlElement* tileElement;
	tileElement = layerDataElement->FirstChildElement("tile");
	if (tileElement == NULL)
	{
		std::cout << "Bad map. No tile information found." << std::endl;
		return false;
	}
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int element = atoi(tileElement->Attribute("gid"));
			
			tileElement = tileElement->NextSiblingElement("tile");
			tileGID[i][j] = element - 1;
			std::cout << tileGID[i][j];
		}
		std::cout << std::endl;
	};
	
}

/*
Object Level::GetObject(std::string name)
{
	// только первый объект с заданным именем
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}
std::vector<Object> Level::GetObjects(std::string name)
{
	// все объекты с заданным именем
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);
	return vec;
}
std::vector<Object> Level::GetAllObjects()
{
	return objects;
};
*/
Level::Level()
{
	
};

void Level::Draw()
{
	// рисуем все тайлы (объекты не рисуем!)
	/// Рисование уровня
	
	for (int i = 0; i < (width); i++)
	{
		for (int j = 0; j < (height); j++)
		{
			
			
			GetTileSize = num_tile[tileGID[i][j]];
			tileMap_texture.Set_TextureRect(GetTileSize);
			


			tileMap_texture.SetPosition((j * tileHeight) + SCREEN_WIDTH / 2,  (i * tileWidth) + SCREEN_HEIGHT / 2, camera);
			if ((j * 32) > player.GetPosition().x - camera.w && (j * 32) < player.GetPosition().x + camera.w &&
				(i * 32) > player.GetPosition().y - camera.h && (i * 32) < player.GetPosition().y + camera.h)
			{
			tileMap_texture.t_Draw();
			}
		}
	};
}


void Level::L_Free()
{
	tileMap_texture.Free();
	// удаление массивов    
	for (unsigned i{}; i < width; i++)
	{
		delete[] tileGID[i];
	}
	delete[] tileGID;
		
}
#endif