#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"
#include "game.h"
#include "editMap.h"

int volume_sound_effect = 1;//перемнная звуковых эффектов
int volume_music = 1;//переменная музыки

Music backgroundMusic;

void setting(RenderWindow &window, Sound tap);
void playSE(Sound tap);

bool menu(RenderWindow &window) {
	window.setSize(Vector2u(800, 600));
	SoundBuffer tapBuffer; //создаём буфер для звука
	tapBuffer.loadFromFile("tap.ogg"); //загружаем в него звук
	Sound tap(tapBuffer); //создаем звук и загружаем в него звук из буфера
	//tap.setVolume(100.0f);

	backgroundMusic.openFromFile("background.wav");
	backgroundMusic.setVolume(volume_music*5.0f);
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	
	setlocale(LC_ALL, "rus"); //Для проверки (Отключить НАДО!!!!!!!!!)
	Texture menuTextureGround, menuTextureStart, menuTextureSettings, menuTextureTablicaRecords, menuTextureExit;
	menuTextureGround.loadFromFile("images/Menu/background.png"); //Фон
	menuTextureStart.loadFromFile("images/Menu/NewGame.png"); //Кнопка - "Новая игра"
	menuTextureSettings.loadFromFile("images/Menu/Settings.png"); //Кнопка - "Настройки"
	menuTextureTablicaRecords.loadFromFile("images/Menu/TablicaRecords.png"); //Кнопка - "Редактор карт"
	menuTextureExit.loadFromFile("images/Menu/Exit.png"); //Кнопка - "Выход"
	Sprite menuSta(menuTextureStart), menuTab(menuTextureTablicaRecords), menuSet(menuTextureSettings), menuEx(menuTextureExit), ground(menuTextureGround);
	menuSta.setPosition(275, 125);//Установка начальной позиции кнопки "Новая Игра"
	menuTab.setPosition(280, 200);//Установка начальной позиции кнопки "Редактор карт"
	menuSet.setPosition(300, 245);//Установка начальной позиции кнопки "Настройки"
	menuEx.setPosition(335, 310);//Установка начальной позиции кнопки "Выход"
	ground.setPosition(0, 0);

	bool exitMenu = true;//Переменная для выхода из цикла меню - выход из игры
	int numberMenu = -1;//Переменная для прослеживания выбранного пункта

	while (exitMenu && window.isOpen())//Цикл отрисовки и взаимодействия с меню
	{
		Event event; // Проверяем все события окна, которые были вызваны с последней итерации цикла
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // Закрываем окно, в случае получения управляющего события
				window.close();
			if (event.type == sf::Event::LostFocus)
			{
				bool pause = true;
				while (pause)
				{
					window.pollEvent(event);
					if (event.type == sf::Event::GainedFocus) pause = false;
				}
			}
		}

		menuSta.setColor(Color::White);//Установка  цвета кнопки "Новая игра"
		menuTab.setColor(Color::White);//Установка цвета кнопки "Редактор карт"
		menuSet.setColor(Color::White);//Установка цвета кнопки "Настройки"
		menuEx.setColor(Color::White);//Установка цвета кнопки "Выход"

		//Проверка на нахождения мыши на поле. При нахождении мышки на одной из кнопок, кнопка перекрашивается в красный
		if (IntRect(0, 0, 800, 600).contains(Mouse::getPosition(window))) { numberMenu = -1; }
		if (IntRect(275, 115, 245, 50).contains(Mouse::getPosition(window))) { menuSta.setColor(Color::Red); numberMenu = 1; }
		if (IntRect(280, 180, 245, 50).contains(Mouse::getPosition(window))) { menuTab.setColor(Color::Red); numberMenu = 2; }
		if (IntRect(300, 235, 205, 50).contains(Mouse::getPosition(window))) { menuSet.setColor(Color::Red); numberMenu = 3; }
		if (IntRect(335, 290, 125, 50).contains(Mouse::getPosition(window))) { menuEx.setColor(Color::Red); numberMenu = 0; }

		if (Mouse::isButtonPressed(Mouse::Left)) //проверка на нажатие одной из кнопок
		{
			//if (numberMenu != -1) playSound(tap);
			if (numberMenu == 1) { 
				backgroundMusic.pause();
				playSE(tap);
				game(window, volume_music, volume_sound_effect); backgroundMusic.play(); }
			if (numberMenu == 2) { backgroundMusic.pause(); playSE(tap); editMap(window,volume_sound_effect, volume_music);backgroundMusic.pause();}
			if (numberMenu == 3) { playSE(tap); setting(window, tap); }
			if (numberMenu == 0) { playSE(tap); sleep(seconds(0.1f)); exitMenu = false; }
			numberMenu = -1;
		}

		//Отрисовка кнопок и фона
		window.draw(ground);
		window.draw(menuSta);
		window.draw(menuTab);
		window.draw(menuSet);
		window.draw(menuEx);
		window.display();
	}
	return false;
}

void setting(RenderWindow &window, Sound tap) {
	Texture  background, sound_effect, music, music_minus, music_plus, music_plus_20, back;
	background.loadFromFile("images/MenuSound/background.png"); //фон
	sound_effect.loadFromFile("images/MenuSound/sound_effect.png"); //надпись "звуковые эффекты"
	music.loadFromFile("images/MenuSound/music.png"); //надпись "музыка"
	music_minus.loadFromFile("images/MenuSound/music_minus.png"); //стрелочка -
	music_plus.loadFromFile("images/MenuSound/music_plus.png"); //стрелочка +
	music_plus_20.loadFromFile("images/MenuSound/music_plus_20.png");  //палочка +20% звука
	back.loadFromFile("images/MenuSound/back.png"); //кнопка назад
	Sprite bg(background), se(sound_effect), m(music), mm1(music_minus), mp1(music_plus), mm2(music_minus), mp2(music_plus), mp20(music_plus_20), b(back);
	bg.setPosition(0, 0);//фон
	se.setPosition(210, 230);//звуковые эффекты
	mm2.setPosition(378, 235);//звуковые эффекты -
	mp2.setPosition(485,235);//звуковые эффекты +
	m.setPosition(220, 300); //музыка
	mm1.setPosition(378, 305);//музыка -
	mp1.setPosition(485, 305);//музыка +
	b.setPosition(190, 350);//назад

	bool exitMenuSettings = true;
	int numberMenuSettings = -1;

	while (exitMenuSettings  && window.isOpen())
	{
		Event event; // Проверяем все события окна, которые были вызваны с последней итерации цикла
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // Закрываем окно, в случае получения управляющего события
				window.close();
			if (event.type == sf::Event::LostFocus)
			{
				bool pause = true;
				while (pause)
				{
					window.pollEvent(event);
					if (event.type == sf::Event::GainedFocus) pause = false;
				}
			}

			mm1.setColor(Color::White);
			mm2.setColor(Color::White);
			mp1.setColor(Color::White);
			mp2.setColor(Color::White);
			b.setColor(Color::White);

			if (IntRect(0, 0, 800, 600).contains(Mouse::getPosition(window))) { numberMenuSettings = -1; }
			if (IntRect(378, 305, 31, 27).contains(Mouse::getPosition(window))) { mm1.setColor(Color::Red); numberMenuSettings = 1; }
			if (IntRect(478, 305, 31, 27).contains(Mouse::getPosition(window))) { mp1.setColor(Color::Red); numberMenuSettings = 2; }
			if (IntRect(378, 235, 31, 27).contains(Mouse::getPosition(window))) { mm2.setColor(Color::Red); numberMenuSettings = 3; }
			if (IntRect(478, 235, 31, 27).contains(Mouse::getPosition(window))) { mp2.setColor(Color::Red); numberMenuSettings = 4; }
			if (IntRect(190, 350, 169, 36).contains(Mouse::getPosition(window))) { b.setColor(Color::Red); numberMenuSettings = 0; }

			if (Mouse::isButtonPressed(Mouse::Left))
			{

				//if (numberMenuSettings != -1) playSound(tap);
				if (numberMenuSettings == 0) { playSE(tap); exitMenuSettings = false; }
				if (numberMenuSettings == 1 && volume_music != 0) { playSE(tap); volume_music--; 
				backgroundMusic.setVolume(volume_music*5.0f);
				cout << volume_music; }
				if (numberMenuSettings == 2 && volume_music != 5) { playSE(tap); volume_music++; 
				backgroundMusic.setVolume(volume_music*5.0f);
				cout << volume_music; }
				if (numberMenuSettings == 3 && volume_sound_effect != 0) { volume_sound_effect--;cout << volume_sound_effect; playSE(tap); }
				if (numberMenuSettings == 4 && volume_sound_effect != 5) { volume_sound_effect++; cout << volume_sound_effect; playSE(tap); }
				numberMenuSettings = -1;
			}

			window.draw(bg);
			window.draw(se);
			window.draw(m);
			window.draw(b);
			window.draw(mm1);
			window.draw(mm2);
			window.draw(mp1);
			window.draw(mp2);

			float start = 410;
			for (int i = 0; i < volume_sound_effect; i++, start += 15.0)
			{
				Sprite  mp20(music_plus_20);
				mp20.setPosition(start, 235);
				window.draw(mp20);
			}
			float start2 = 410;
			for (int i = 0; i < volume_music; i++, start2 += 15.0)
			{
				Sprite  mp20(music_plus_20);
				mp20.setPosition(start2, 305);
				window.draw(mp20);
			}

			window.display();
		}
	}
}

void playSE(Sound tap) {
	tap.setVolume(volume_sound_effect*5.0f);
	tap.play();
	sleep(seconds(0.2f));
}

