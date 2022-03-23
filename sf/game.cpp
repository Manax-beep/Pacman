#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <list>
#include "menu.h"
#include "game.h"
#include "map1.h"

bool gameover = false;
bool back = false;
Music musicStart;
Music siren;

struct Mob
{
	void SetPosition(float x, float y)
	{
		_x = x;
		_y = y;
		_sprite.setPosition(_x, _y);
	}
	void Update(float time)
	{
		float sposX = _smove(time).x;
		float sposY = _smove(time).y;
		int msposX = sposX / _cellSize; //map simulation position (0,0)
		int msposY = sposY / _cellSize;
		int msposX2 = (sposX + 31) / _cellSize; // (31,31)
		int msposY2 = (sposY + 31) / _cellSize;

		if (0 <= msposX &&  //�����
			msposX < _mapWidth &&
			0 <= msposY &&
			msposY < _mapHeight &&
			TileMap[msposY][msposX] == '@') //���� ������
		{
			
			TileMap[msposY][msposX] == ' ';
			gameover = true; //����
		}
		while (msposX < 0 ||  //���� ��� ������
			_mapWidth < msposX||
			msposY < 0 || 
			_mapHeight < msposY ||
			((_isUp ||_isLeft) &&
				!(TileMap[msposY][msposX] == ' ' ||
			TileMap[msposY][msposX] == 'm' ||
			TileMap[msposY][msposX] == '-')) ||
			((_isDown || _isRight) &&
			!(TileMap[msposY2][msposX2] == ' ' ||
			TileMap[msposY2][msposX2] == '@' ||
			TileMap[msposY2][msposX2] == 'm' ||
			TileMap[msposY2][msposX2] == '-')))
		{
			_setRandomDir();
			sposX = _smove(time).x;
			sposY = _smove(time).y;
			msposX = sposX / _cellSize;
			msposY = sposY / _cellSize;
			msposX2 = (sposX + 16) / _cellSize;
			msposY2 = (sposY + 16) / _cellSize;
		}
		//cout << msposX << " " << msposY  << "\n";
		SetPosition(sposX, sposY);
	}
	void Draw(sf::RenderWindow &window)
	{
		window.draw(_sprite);
	}
	Mob(float x, float y, float speed, float cellSize, sf::Sprite sprite, sf::String *pMap, int mapWidth, int mapHeight)
	{
		_pMap = pMap;
		_mapWidth = mapWidth;
		_mapHeight = mapHeight;
		_sprite = sprite;
		SetPosition(x, y);
		_cellSize = cellSize;
		_speed = speed;
		_isUp = true;
	}

	float _x, _y;
	float _cellSize;
	float _speed;
	sf::Sprite _sprite;
	bool _isUp = false;
	bool _isLeft = false;
	bool _isDown = false;
	bool _isRight = false;
	sf::String *_pMap;
	int _mapWidth;
	int _mapHeight;
	
	Vector2f _smove(float time) //���������� ������ �� ������ �� �����
	{
		Vector2f spos(_x, _y);
		float offset = _speed * time;
		if (_isUp) spos.y -= offset;
		if (_isLeft) spos.x -= offset;
		if (_isDown) spos.y += offset;
		if (_isRight) spos.x += offset;
		return spos;
	}

	void _setRandomDir()
	{
		int random = rand() % 4;
		_isUp = random == 0;
		_isLeft = random == 1;
		_isDown = random == 2;
		_isRight = random == 3;
	}
};

struct MobManager
{
	void AddMob(const Mob &mob)
	{
		_mobList.push_back(mob); //�������� ���� � ������
	}

	void Update(float time) //��������� ���� ���������� �����
	{
		for (std::list<Mob>::iterator bItr = _mobList.begin(), end = _mobList.end(); 
			bItr != end; ++bItr)
		{
			bItr->Update(time);
		}
	}
	void Draw(sf::RenderWindow &window)
	{
		for (std::list<Mob>::iterator bItr = _mobList.begin(), end = _mobList.end();
			bItr != end; ++bItr)
		{
			bItr->Draw(window);
		}
	}
	std::list<Mob> _mobList;
};

int game(RenderWindow &window, int volume_music, int volume_sound_effect) 
{
	window.clear();
	SoundBuffer eatBuffer; //������ ����� ��� �����
	eatBuffer.loadFromFile("eating.wav"); //��������� � ���� ����
	Sound eat(eatBuffer); 

	gameover = false;
	back = false;
	bool start = true;
	bool m = false;
	sf::Font font;
	font.loadFromFile("Peace Sans Webfont.ttf");
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(26);
	score.setFillColor(sf::Color::Yellow);
	score.setPosition(70, 253);


	musicStart.openFromFile("start.wav");//��������� ����
	siren.openFromFile("Siren.wav");
	siren.setVolume(volume_music*5.0f);
	siren.setLoop(true);
	window.clear();
	int money = 0;
	
	cout << "���� ��������!";
	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/txr2.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������
	
	Image n_image;
	n_image.loadFromFile("images/numbers.png");
	Texture n;
	n.loadFromImage(n_image);
	Sprite s_n;
	s_n.setTexture(n);


	Clock clock; //������� ���������� �������, �.�. �������� �� �������(� �� �������������/�������� ����������).
	float CurrentFrame = 0;//������ ������� ����
	Texture herotexture, Scoretexture;
	herotexture.loadFromFile("images/pacman.png");
	Scoretexture.loadFromFile("images/score.png");

	Sprite herosprite, Scoresprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 26, 26));//������ �������
	Scoresprite.setTexture(Scoretexture);
	Scoresprite.setPosition(0, 256);
	float x = 385;
	float y = 385;
	herosprite.setPosition(x, y); //������� ������ � ������� x y 
	bool up = false, down = false, right = false, left = false; //��� �������� �� �������� ������

	sf::Texture mobTexture;
	mobTexture.loadFromFile("images/enemy.png");
	sf::Sprite mobSprite(mobTexture);
	mobSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	//mobSprite.setColor(sf::Color::Red);
	Mob testMob(385.f, 320.f, 0.1f, 32.f, mobSprite, &TileMap[0], WIDTH_MAP, HEIGHT_MAP);
	MobManager mobManager;
	mobManager.AddMob(testMob);
	mobManager.AddMob(testMob);
	mobManager.AddMob(testMob);
	mobManager.AddMob(testMob);

	//GAMEPLAY
	while (!back && window.isOpen())
	{
		
		if (m==true) { siren.play(); m = false; }
		//���� ������ ������ ...
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { left = true; right = false; }
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) { right = true; left = false; }
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { up = true; down = false; }
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { down = true; up = false; }

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 800; //�������� ����
		//cout << time <<"\n";
		
		if ((Keyboard::isKeyPressed(Keyboard::B))) money = 188; //��� �� �������
		
		float sx = x;
		float sy = y;

		if (left)
		{ 			
			sx += (-0.1*time);
		}
		if (right)
		{
			sx += (0.1*time);
		}
		if (up)
		{
			sy += (-0.1*time);
		}
		if (down)
		{
			sy += (0.1*time);
		}

		//�������� �� �����/�������/���������
		if (left)
		{
			int cellX = sx / 32;
			for (int i = sy / 32; i < (sy + 26) / 32; i++)
			{
				if (TileMap[i][cellX] == '0' || 
					TileMap[i][cellX] == '1' || 
					TileMap[i][cellX] == '<' || 
					TileMap[i][cellX] == '>' || 
					TileMap[i][cellX] == '5' || 
					TileMap[i][cellX] == '6' || 
					TileMap[i][cellX] == '.' || 
					TileMap[i][cellX] == ']' || 
					TileMap[i][cellX] == 'q' || 
					TileMap[i][cellX] == 'z' || 
					TileMap[i][cellX] == '0' || 
					TileMap[i][cellX] == 'w' || 
					TileMap[i][cellX] == 'a' || 
					TileMap[i][cellX] == 's' || 
					TileMap[i][cellX] == 'd')
				{
					left = false;
					break;
				}
				if (TileMap[i][cellX] == 't') {
					x = 735; y = 325;//��������������� ����
					herosprite.setPosition(x, y);//������������
					break;
				}
				if (TileMap[i][cellX] == 'm') { //���� ������� �������:
					TileMap[i][cellX] = ' ';//������� �������
					money++;
					eat.setVolume(volume_sound_effect*5.0f);
					eat.play();
					//sleep(seconds(0.2f));
					break;
				}
			}
		}
		if (right)
		{
			int cellX = (sx + 26) / 32;
			for (int i = sy / 32; i < (sy + 26) / 32; i++)
			{
				if (TileMap[i][cellX] == '0' ||
					TileMap[i][cellX] == '1' ||
					TileMap[i][cellX] == '<' ||
					TileMap[i][cellX] == '>' ||
					TileMap[i][cellX] == '5' ||
					TileMap[i][cellX] == '6' ||
					TileMap[i][cellX] == '.' ||
					TileMap[i][cellX] == ']' ||
					TileMap[i][cellX] == 'q' ||
					TileMap[i][cellX] == 'z' ||
					TileMap[i][cellX] == '0' ||
					TileMap[i][cellX] == 'w' ||
					TileMap[i][cellX] == 'a' ||
					TileMap[i][cellX] == 's' ||
					TileMap[i][cellX] == 'd')
				{
					right = false;
					break;
				}
				if (TileMap[i][cellX] == 'p') {
					x = 35; y = 325;//��������������� ����
					herosprite.setPosition(x, y);//������������
					break;
				}
				if (TileMap[i][cellX] == 'm') { //���� ������� �������:
					TileMap[i][cellX] = ' ';//������� �������
					money++;
					eat.setVolume(volume_sound_effect*5.0f);
					eat.play();
					//sleep(seconds(0.2f));
					break;
				}
			}
		}
		if (up)
		{
			int cellY = sy / 32;
			for (int i = sx / 32; i < (sx + 26) / 32; i++)
			{
				if (TileMap[cellY][i] == '0' ||
					TileMap[cellY][i] == '1' ||
					TileMap[cellY][i] == '<' ||
					TileMap[cellY][i] == '>' ||
					TileMap[cellY][i] == '5' ||
					TileMap[cellY][i] == '6' ||
					TileMap[cellY][i] == '.' ||
					TileMap[cellY][i] == ']' ||
					TileMap[cellY][i] == 'q' ||
					TileMap[cellY][i] == 'z' ||
					TileMap[cellY][i] == '0' ||
					TileMap[cellY][i] == 'w' ||
					TileMap[cellY][i] == 'a' ||
					TileMap[cellY][i] == 's' ||
					TileMap[cellY][i] == 'd')
				{
					up = false;
					break;
				}
				if (TileMap[cellY][i] == 'm') { //���� ������� �������:
					TileMap[cellY][i] = ' ';//������� �������
					money++;
					eat.setVolume(volume_sound_effect*5.0f);
					eat.play();
					//sleep(seconds(0.2f));
					break;
				}
			}
		}
		if (down)
		{
			int cellY = (sy + 26)/ 32;
			for (int i = sx / 32; i < (sx + 26) / 32; i++)
			{
				if (TileMap[cellY][i] == '0' ||
					TileMap[cellY][i] == '1' ||
					TileMap[cellY][i] == '<' ||
					TileMap[cellY][i] == '>' ||
					TileMap[cellY][i] == '5' ||
					TileMap[cellY][i] == '6' ||
					TileMap[cellY][i] == '.' ||
					TileMap[cellY][i] == ']' ||
					TileMap[cellY][i] == 'q' ||
					TileMap[cellY][i] == 'z' ||
					TileMap[cellY][i] == '0' ||
					TileMap[cellY][i] == 'w' ||
					TileMap[cellY][i] == 'a' ||
					TileMap[cellY][i] == 's' ||
					TileMap[cellY][i] == 'd')
				{
					down = false;
					break;
				}
				if (TileMap[cellY][i] == 'm') { //���� ������� �������:
					TileMap[cellY][i] = ' ';//������� �������
					money++;
					eat.setVolume(volume_sound_effect*5.0f);
					eat.play();
					//sleep(seconds(0.002f));
					break;
				}
			}
		}

		//������ + ��������
		TileMap[(int)y / 32][ (int)x / 32] = ' ';

		if(left)
		{ 
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(0, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(-0.1*time, 0);//���������� ���� �������� ��������� �����
			x = x + (-0.1*time);

		}

		if (right) 
		{
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(26, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(0.1*time, 0);//���������� ���� �������� ��������� �����
			x = x + (0.1*time);
		}

		if (up) 
		{
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(52, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(0, -0.1*time);//���������� ���� �������� ��������� �����
			y = y + (-0.1*time);
		}

		if (down) 
		{
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(78, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(0, 0.1*time);//���������� ���� �������� ��������� �����
			y = y + (0.1*time);
		}

		TileMap[(int)y / 32][(int)x / 32] = '@';
		
		if (start) 
		{
			Texture ready;
			ready.loadFromFile("images/ready.png");
			Sprite r(ready);
			r.setPosition(278, 275);
			//window.clear();
			window.draw(r);
			window.display();
			musicStart.setVolume(volume_music*5.0f);
			musicStart.play();//������������� ������
			sleep(seconds(4.0f));
			clock.restart();
			start = false;
			m = true;
			continue;
		}

		mobManager.Update(time);

		//���������� �������
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				//�����
				if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//��������������
				if ((TileMap[i][j] == '1')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//������������
				if ((TileMap[i][j] == '<')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//�����
				if ((TileMap[i][j] == '>')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//������
				if ((TileMap[i][j] == '5')) s_map.setTextureRect(IntRect(160, 0, 32, 32));//����
				if ((TileMap[i][j] == '6')) s_map.setTextureRect(IntRect(192, 0, 32, 32));//�����
				if ((TileMap[i][j] == '.')) s_map.setTextureRect(IntRect(224, 0, 32, 32));//������ ������
				if ((TileMap[i][j] == ']')) s_map.setTextureRect(IntRect(256, 0, 32, 32));//������ �������
				if ((TileMap[i][j] == 'q')) s_map.setTextureRect(IntRect(288, 0, 32, 32));//����� �������
				if ((TileMap[i][j] == 'z')) s_map.setTextureRect(IntRect(320, 0, 32, 32));//����� ������
				if (TileMap[i][j] == 'w')  s_map.setTextureRect(IntRect(352, 0, 32, 32)); //����1
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(384, 0, 32, 32)); //���1
				if (TileMap[i][j] == 'd')  s_map.setTextureRect(IntRect(416, 0, 32, 32)); //�����1
				if (TileMap[i][j] == 'a')  s_map.setTextureRect(IntRect(448, 0, 32, 32)); //����1
				//������� �� �����
				if (TileMap[i][j] == 'm')  s_map.setTextureRect(IntRect(480, 0, 32, 32)); //�������	
				if (TileMap[i][j] == 't' || TileMap[i][j] == 'p')  s_map.setTextureRect(IntRect(512, 0, 32, 32)); //��������
				if (TileMap[i][j] == ' ' || TileMap[i][j] == '-' || TileMap[i][j]=='@')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //�������

				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}

		if (Keyboard::isKeyPressed(Keyboard::F10)) 
		{
			for (int i = 0; i < HEIGHT_MAP; i++) 
			{
				for (int j = 0; j < WIDTH_MAP; j++) 
				{
					if (TileMap[i][j] == ' ') 
					{
						TileMap[i][j] = 'm';
					}
				}
			}
			Texture next;
			//win.loadFromFile("images/win.png");
			next.loadFromFile("images/next.png");
			Sprite n(next);
			n.setPosition(200, 355);
			//window.clear();
			window.draw(n);
			window.display();
			bool enter = false;
			siren.pause();
			while (!enter) {
				if ((Keyboard::isKeyPressed(Keyboard::Enter))) enter = true;
			}
			//sleep(seconds(5.0f));
			//start = true;
			back = true;

		}
	
		stringstream ss;
		ss << money;
		string str = ss.str();
		score.setString(str);

		mobManager.Draw(window);
		window.draw(score);
		window.draw(Scoresprite);
		window.draw(herosprite);
		window.display();

		if (gameover) 
		{
			for (int i = 0; i < HEIGHT_MAP; i++) 
			{
				for (int j = 0; j < WIDTH_MAP; j++) 
				{
					if (TileMap[i][j] == ' '|| TileMap[i][j] == '@') 
					{ 
						TileMap[i][j] = 'm';
					}
				
				}
			}
			Texture go, next2;
			go.loadFromFile("images/gameover.png");
			next2.loadFromFile("images/next.png");
			Sprite o(go), n(next2);
			o.setPosition(178, 255);
			n.setPosition(200, 355);
			//window.clear();
			window.draw(o);
			window.draw(n);
			window.display();

			bool enter = false;
			siren.pause();
			while (!enter) {
				if ((Keyboard::isKeyPressed(Keyboard::Enter))) enter = true;
			}
			//sleep(seconds(5.0f));
			start = true;
			back = true;
		}

		//�������� �� �������
		if (money >= 187) 
		{
			for (int i = 0; i < HEIGHT_MAP; i++) 
			{
				for (int j = 0; j < WIDTH_MAP; j++) 
				{
					if (TileMap[i][j] == ' ') 
					{ 
						TileMap[i][j] = 'm';
					}
				}
			}
			Texture win, next;
			win.loadFromFile("images/win.png");
			next.loadFromFile("images/next.png");
			Sprite w(win), n(next);
			w.setPosition(178, 255);
			n.setPosition(200, 355);
			//window.clear();
			window.draw(w);
			window.draw(n);
			window.display();
			bool enter = false;
			siren.pause();
			while (!enter) 
			{
				if ((Keyboard::isKeyPressed(Keyboard::Enter))) enter = true;
			}
			//sleep(seconds(5.0f));
			start = true;
			back=true;
		}
		
	}
	
	return 0;
}