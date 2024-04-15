
//Инициализация глобальных ресурсов
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int SCREEN_WIDTH = 640;//Ширина окна
const int SCREEN_HEIGHT = 480;//высота окна

//The camera area
SDL_Rect camera = { 0, 0, SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 2 - 64 };

void Camera_step(int x, int y)
{
	camera.x = -x;
	camera.y = -y;
};