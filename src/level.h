#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include <iostream>
#include <sstream>
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
	std::vector<int> tileGID;
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

	
	//Загрузка номеров тайлов в вектор из прямоугольников изображений (TextureRect)

	GetTileSize.w = tileWidth;
	GetTileSize.h = tileHeight;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			SDL_Rect rect;
			rect.x = j * tileWidth;
			rect.y = i * tileHeight;
			rect.w = tileWidth;
			rect.h = tileHeight;
			num_tile.push_back(rect);

		}

	}


	// работа со слоями

	// Получить все элементы слоя ("layer")
	
	std::vector<TiXmlElement*> layerElements;
	for (TiXmlElement* layerElement = map->FirstChildElement("layer"); layerElement != nullptr; layerElement = layerElement->NextSiblingElement("layer"))
	{
		layerElements.push_back(layerElement);
	}
	// Для каждого слоя
	for (auto layerElement : layerElements)
	{
		Layer layer;
		
		
		// Получить данные слоя (значения тайлов)
		TiXmlElement* dataElement = layerElement->FirstChildElement("data");
		const char* data = dataElement->GetText();
		
		// Разбить данные на отдельные значения тайлов
		
		int buffer_0 = 0;
		
		std::vector<int> tileGIDs;
		std::stringstream ss(data);
		int tileGID = 0;
		char delimiter;
		while (ss >> tileGID)
		{
			ss >> delimiter; // Пропустить запятую
			tileGIDs.push_back(tileGID);
			layer.tileGID.push_back(tileGID);
		}
		
		
		
		std::cout << "Number of layer:" << layers.size() << std::endl;

		std::cout << "layer name: " << layerElement->Attribute("name") << std::endl;
		// Вывести значения тайлов
		for (int i = 0; i < layer.tileGID.size(); i++)
		{
			std::cout << layer.tileGID[i] << " ";
			if ((i + 1) % height == 0)
			{
				std::cout << std::endl;
			}
		}

		layers.push_back(layer);
		std::cout << std::endl;
	}


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
	
	
	for (int l = 0; l < layers.size(); l++)
	{
		int h = 0;
		int w = 0;
		for (int i = 0; i < (layers[l].tileGID.size()); i++)
		{

			if (layers[l].tileGID[i] != 0)
			{
				GetTileSize = num_tile[layers[l].tileGID[i] - 1];
				tileMap_texture.Set_TextureRect(GetTileSize);

				tileMap_texture.SetPosition((w * tileWidth) + SCREEN_WIDTH / 2, (h * tileHeight) + SCREEN_HEIGHT / 2, camera);
				tileMap_texture.t_Draw();
			};
			w++;
			if ((i + 1) % height == 0)
			{
				w = 0;
				h++;
			}
		}
	};

	
	/// Рисование уровня
	/*
	GetTileSize = num_tile[layers[0].tileGID[71] - 1];

	tileMap_texture.Set_TextureRect(GetTileSize);

	tileMap_texture.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, camera);
	tileMap_texture.t_Draw();
	*/
}


void Level::L_Free()
{
	tileMap_texture.Free();
	// удаление массивов    
	


}
#endif