#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include <Windows.h>

using namespace sf;
using namespace std;

int main()
{
	FreeConsole();
	RenderWindow window(VideoMode(800, 600), "Pacman", Style::None | Style::Close);
	window.setFramerateLimit(96);
	Image icon;
	if (!icon.loadFromFile("images/Menu/icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());

	
	menu(window);

}