#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "editMap.h"
#include "usermap.h"
#include <sstream>
#include <list>

bool gameoverE = false;
bool backE = false;
Music StartE;
Music sirenE;


void game(RenderWindow &window, int value_money ,int volume_sound_effect, int volume_music);

int editMap(RenderWindow &window, int volume_sound_effect, int volume_music) {
	//RenderWindow windowE(VideoMode(200, 300), "Pacman", Style::None | Style::Close);
	//window.setSize(Vector2u(1000, 600));
	int value_money = 0;

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/txr2.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image f1_image; //������ ��� ������ ��������
	f1_image.loadFromFile("images/f1.png");
	Texture f1;
	f1.loadFromImage(f1_image);
	Sprite f;
	f.setTexture(f1);

	Clock clock; //������� ���������� �������, �.�. �������� �� �������(� �� �������������/�������� ����������).
	float CurrentFrame = 0;//������ ������� ����
	Texture herotexture;
	herotexture.loadFromFile("images/pacman.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 26, 26));//������ �������
	
	float x = 385;
	float y = 385;
	herosprite.setPosition(x, y); //������� ������ � ������� x y 

	bool gam = false;
	int k='0';
	int check = '-';
	
	int mx = 0;
	int my = 0;
	while (!gam && window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				//�����
				if (Map[i][j] == '0')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//��������������
				if ((Map[i][j] == '1')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//������������
				if ((Map[i][j] == '<')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//�����
				if ((Map[i][j] == '>')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//������
				if ((Map[i][j] == '5')) s_map.setTextureRect(IntRect(160, 0, 32, 32));//����
				if ((Map[i][j] == '6')) s_map.setTextureRect(IntRect(192, 0, 32, 32));//�����
				if ((Map[i][j] == '.')) s_map.setTextureRect(IntRect(224, 0, 32, 32));//������ ������
				if ((Map[i][j] == ']')) s_map.setTextureRect(IntRect(256, 0, 32, 32));//������ �������
				if ((Map[i][j] == 'q')) s_map.setTextureRect(IntRect(288, 0, 32, 32));//����� �������
				if ((Map[i][j] == 'z')) s_map.setTextureRect(IntRect(320, 0, 32, 32));//����� ������
				if (Map[i][j] == 'w')  s_map.setTextureRect(IntRect(352, 0, 32, 32)); //����1
				if (Map[i][j] == 's')  s_map.setTextureRect(IntRect(384, 0, 32, 32)); //���1
				if (Map[i][j] == 'd')  s_map.setTextureRect(IntRect(416, 0, 32, 32)); //�����1
				if (Map[i][j] == 'a')  s_map.setTextureRect(IntRect(448, 0, 32, 32)); //����1
				//������� �� �����
				if (Map[i][j] == 'm')  s_map.setTextureRect(IntRect(480, 0, 32, 32)); //�������	
				if (Map[i][j] == 't' || Map[i][j] == 'p')  s_map.setTextureRect(IntRect(512, 0, 32, 32)); //��������
				if (Map[i][j] == ' ' || Map[i][j] == '-')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //�������

				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}

		//���������� � ��������� - ��������
		if (Keyboard::isKeyPressed(Keyboard::F1)) {
			f.setTextureRect(IntRect(0, 0, 461, 64));
			f.setPosition(200, 50);
			window.draw(f);
		}

		// ���� ������ ��� ������� �� ������� ��������
		if (Keyboard::isKeyPressed(Keyboard::Num0)) {
			k = '0';
			}
		if (Keyboard::isKeyPressed(Keyboard::Num1)) {
			k = '1';
		}
		if (Keyboard::isKeyPressed(Keyboard::G)) {
			k = '<';
		}
		if (Keyboard::isKeyPressed(Keyboard::H)) {
			k = '>';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5)) {
			k = '5';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6)) {
			k = '6';
		}
		if (Keyboard::isKeyPressed(Keyboard::M)) {
			k = '.';
		}
		if (Keyboard::isKeyPressed(Keyboard::P)) {
			k = ']';
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			k = 'q';
		}
		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			k = 'z';
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			k = 'w';
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			k = 's';
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			k = 'a';
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			k = 'd';
		}
		//���������� ��������
		if (Mouse::isButtonPressed(Mouse::Left)) {
			mx = event.mouseButton.x / 32;
			my = event.mouseButton.y / 32;
			cout <<"x = "<< mx << " y = " << my<<"\n";
			if (my >= 0 && mx >= 0 && mx<=24 && my<=18) { 
				
				Map[my][mx] = k;
			}
		}

		Map[10][9] = '-';
		Map[10][10] = '-';
		Map[10][11] = '-';
		Map[10][12] = '-';
		Map[10][13] = '-';
		Map[10][14] = '-';
		Map[10][15] = '-';
		Map[9][12] = '-';
		for (int i = 8; i <= 16; i++)
		{
			Map[8][i] = 'm';
		}
		for (int i = 8; i <= 16; i++)
		{
			Map[12][i] = 'm';
		}
		for (int i = 8; i <= 12; i++)
		{
			Map[i][7] = 'm';
		}
		for (int i = 8; i <= 12; i++)
		{
			Map[i][17] = 'm';
		}

		for (int i = 1; i <= 23; i++)
		{
			Map[0][i] = '0';
		}

		Map[0][0] = 'q';
		Map[0][24] = ']';

		//������ ����
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			gam = true;
		}
		window.draw(herosprite);
		window.display();
	}
	//�������� ������� �������
	for (int i = 0; i < HEIGHT_MAP; i++) 
	{
		for (int j = 0; j < WIDTH_MAP; j++) 
		{
			if (Map[i][j] == 'm') value_money++;
		}
	}



	game(window, value_money,volume_sound_effect, volume_music);
	//window.setSize(Vector2u(800, 600));

	return 0;

}



struct MobE
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
			Map[msposY][msposX] == '@') //���� ������
		{

			Map[msposY][msposX] = ' ';
			gameoverE = true; //����
		}
		while (msposX < 0 ||  //���� ��� ������
			_mapWidth < msposX ||
			msposY < 0 ||
			_mapHeight < msposY ||
			((_isUp || _isLeft) &&
				!(Map[msposY][msposX] == ' ' ||
					Map[msposY][msposX] == 'm' ||
					Map[msposY][msposX] == '-')) ||
					((_isDown || _isRight) &&
						!(Map[msposY2][msposX2] == ' ' ||
							Map[msposY2][msposX2] == '@' ||
							Map[msposY2][msposX2] == 'm' ||
							Map[msposY2][msposX2] == '-')))
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
	MobE(float x, float y, float speed, float cellSize, sf::Sprite sprite, sf::String *pMap, int mapWidth, int mapHeight)
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

struct MobManagerE
{
	void AddMob(const MobE &mob)
	{
		_mobList.push_back(mob); //�������� ���� � ������
	}

	void Update(float time) //��������� ���� ���������� �����
	{
		for (std::list<MobE>::iterator bItr = _mobList.begin(), end = _mobList.end();
			bItr != end; ++bItr)
		{
			bItr->Update(time);
		}
	}
	void Draw(sf::RenderWindow &window)
	{
		for (std::list<MobE>::iterator bItr = _mobList.begin(), end = _mobList.end();
			bItr != end; ++bItr)
		{
			bItr->Draw(window);
		}
	}
	std::list<MobE> _mobList;
};

void game(RenderWindow &window, int value_money, int volume_sound_effect, int volume_music) {
	window.clear();
	SoundBuffer eatBuffer; //������ ����� ��� �����
	eatBuffer.loadFromFile("eating.wav"); //��������� � ���� ����
	Sound eat(eatBuffer);

	gameoverE = false;
	backE = false;
	bool start = true;
	bool m = false;
	sf::Font font;
	font.loadFromFile("Peace Sans Webfont.ttf");
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(26);
	score.setFillColor(sf::Color::Yellow);
	score.setPosition(70, 253);


	StartE.openFromFile("start.wav");//��������� ����
	sirenE.openFromFile("Siren.wav");
	sirenE.setVolume(volume_music*5.0f);
	sirenE.setLoop(true);
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
	MobE testMob(385.f, 320.f, 0.1f, 32.f, mobSprite, &Map[0], WIDTH_MAP, HEIGHT_MAP);
	MobManagerE mobManagerE;
	mobManagerE.AddMob(testMob);
	mobManagerE.AddMob(testMob);
	mobManagerE.AddMob(testMob);
	mobManagerE.AddMob(testMob);

	//GAMEPLAY
	while (!backE && window.isOpen())
	{

		if (m == true) { sirenE.play(); m = false; }
		//���� ������ ������ ...
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { left = true; right = false; up = false; down = false; }
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) { right = true; left = false; up = false; down = false; }
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { up = true; down = false; left = false; right = false; }
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { down = true; up = false; right = false; left = false; }

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

		if ((Keyboard::isKeyPressed(Keyboard::B))) money = value_money; //��� �� �������
		

																										  //������� ����������
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
				if (Map[i][cellX] == '0' ||
					Map[i][cellX] == '1' ||
					Map[i][cellX] == '<' ||
					Map[i][cellX] == '>' ||
					Map[i][cellX] == '5' ||
					Map[i][cellX] == '6' ||
					Map[i][cellX] == '.' ||
					Map[i][cellX] == ']' ||
					Map[i][cellX] == 'q' ||
					Map[i][cellX] == 'z' ||
					Map[i][cellX] == '0' ||
					Map[i][cellX] == 'w' ||
					Map[i][cellX] == 'a' ||
					Map[i][cellX] == 's' ||
					Map[i][cellX] == 'd')
				{
					left = false;
					break;
				}
				if (Map[i][cellX] == 't') {
					x = 735; y = 325;//��������������� ����
					herosprite.setPosition(x, y);//������������
					break;
				}
				if (Map[i][cellX] == 'm') { //���� ������� �������:
					Map[i][cellX] = ' ';//������� �������
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
				if (Map[i][cellX] == '0' ||
					Map[i][cellX] == '1' ||
					Map[i][cellX] == '<' ||
					Map[i][cellX] == '>' ||
					Map[i][cellX] == '5' ||
					Map[i][cellX] == '6' ||
					Map[i][cellX] == '.' ||
					Map[i][cellX] == ']' ||
					Map[i][cellX] == 'q' ||
					Map[i][cellX] == 'z' ||
					Map[i][cellX] == '0' ||
					Map[i][cellX] == 'w' ||
					Map[i][cellX] == 'a' ||
					Map[i][cellX] == 's' ||
					Map[i][cellX] == 'd')
				{
					right = false;
					break;
				}
				if (Map[i][cellX] == 'p') {
					x = 35; y = 325;//��������������� ����
					herosprite.setPosition(x, y);//������������
					break;
				}
				if (Map[i][cellX] == 'm') { //���� ������� �������:
					Map[i][cellX] = ' ';//������� �������
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
				if (Map[cellY][i] == '0' ||
					Map[cellY][i] == '1' ||
					Map[cellY][i] == '<' ||
					Map[cellY][i] == '>' ||
					Map[cellY][i] == '5' ||
					Map[cellY][i] == '6' ||
					Map[cellY][i] == '.' ||
					Map[cellY][i] == ']' ||
					Map[cellY][i] == 'q' ||
					Map[cellY][i] == 'z' ||
					Map[cellY][i] == '0' ||
					Map[cellY][i] == 'w' ||
					Map[cellY][i] == 'a' ||
					Map[cellY][i] == 's' ||
					Map[cellY][i] == 'd')
				{
					up = false;
					break;
				}
				if (Map[cellY][i] == 'm') { //���� ������� �������:
					Map[cellY][i] = ' ';//������� �������
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
			int cellY = (sy + 26) / 32;
			for (int i = sx / 32; i < (sx + 26) / 32; i++)
			{
				if (Map[cellY][i] == '0' ||
					Map[cellY][i] == '1' ||
					Map[cellY][i] == '<' ||
					Map[cellY][i] == '>' ||
					Map[cellY][i] == '5' ||
					Map[cellY][i] == '6' ||
					Map[cellY][i] == '.' ||
					Map[cellY][i] == ']' ||
					Map[cellY][i] == 'q' ||
					Map[cellY][i] == 'z' ||
					Map[cellY][i] == '0' ||
					Map[cellY][i] == 'w' ||
					Map[cellY][i] == 'a' ||
					Map[cellY][i] == 's' ||
					Map[cellY][i] == 'd')
				{
					down = false;
					break;
				}
				if (Map[cellY][i] == 'm') { //���� ������� �������:
					Map[cellY][i] = ' ';//������� �������
					money++;
					eat.setVolume(volume_sound_effect*5.0f);
					eat.play();
					//sleep(seconds(0.002f));
					break;
				}
			}
		}

		//������ + ��������
		Map[(int)y / 32][(int)x / 32] = ' ';
		cout << "money=" << money << "  value money=" << value_money << "\n";
		if (left)
		{
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(0, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(-0.1*time, 0);//���������� ���� �������� ��������� �����

			x = x + (-0.1*time);
		}

		if (right) {
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(26, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(0.1*time, 0);//���������� ���� �������� ��������� �����
			x = x + (0.1*time);
		}

		if (up) {
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(52, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(0, -0.1*time);//���������� ���� �������� ��������� �����
			y = y + (-0.1*time);
		}

		if (down) {
			CurrentFrame += 0.02*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(78, 26 * int(CurrentFrame), 26, 26)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
			herosprite.move(0, 0.1*time);//���������� ���� �������� ��������� �����
			y = y + (0.1*time);
		}

		Map[(int)y / 32][(int)x / 32] = '@';

		if (start) {
			Texture ready;
			ready.loadFromFile("images/ready.png");
			Sprite r(ready);
			r.setPosition(232, 275);
			//window.clear();
			window.draw(r);
			window.display();
			StartE.setVolume(volume_music*5.0f);
			StartE.play();//������������� ������
			sleep(seconds(4.0f));
			clock.restart();
			start = false;
			m = true;
			continue;
		}

		mobManagerE.Update(time);

		//���������� �������
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				//�����
				if (Map[i][j] == '0')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//��������������
				if ((Map[i][j] == '1')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//������������
				if ((Map[i][j] == '<')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//�����
				if ((Map[i][j] == '>')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//������
				if ((Map[i][j] == '5')) s_map.setTextureRect(IntRect(160, 0, 32, 32));//����
				if ((Map[i][j] == '6')) s_map.setTextureRect(IntRect(192, 0, 32, 32));//�����
				if ((Map[i][j] == '.')) s_map.setTextureRect(IntRect(224, 0, 32, 32));//������ ������
				if ((Map[i][j] == ']')) s_map.setTextureRect(IntRect(256, 0, 32, 32));//������ �������
				if ((Map[i][j] == 'q')) s_map.setTextureRect(IntRect(288, 0, 32, 32));//����� �������
				if ((Map[i][j] == 'z')) s_map.setTextureRect(IntRect(320, 0, 32, 32));//����� ������
				if (Map[i][j] == 'w')  s_map.setTextureRect(IntRect(352, 0, 32, 32)); //����1
				if (Map[i][j] == 's')  s_map.setTextureRect(IntRect(384, 0, 32, 32)); //���1
				if (Map[i][j] == 'd')  s_map.setTextureRect(IntRect(416, 0, 32, 32)); //�����1
				if (Map[i][j] == 'a')  s_map.setTextureRect(IntRect(448, 0, 32, 32)); //����1
																						  //������� �� �����
				if (Map[i][j] == 'm')  s_map.setTextureRect(IntRect(480, 0, 32, 32)); //�������	
				if (Map[i][j] == 't' || Map[i][j] == 'p')  s_map.setTextureRect(IntRect(512, 0, 32, 32)); //��������
				if (Map[i][j] == ' ' || Map[i][j] == '-' || Map[i][j] == '@')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //�������

				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}

		if (Keyboard::isKeyPressed(Keyboard::F10)) {
			for (int i = 0; i < HEIGHT_MAP; i++) {//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (Map[i][j] == ' ') { //���� ������ ����� 's' (������)
						Map[i][j] = 'm';
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
			sirenE.pause();
			while (!enter) {
				if ((Keyboard::isKeyPressed(Keyboard::Enter))) enter = true;
			}
			//sleep(seconds(5.0f));
			//start = true;
			backE = true;

		}


		stringstream ss;
		ss << money;
		string str = ss.str();
		score.setString(str);



		mobManagerE.Draw(window);
		window.draw(score);
		window.draw(Scoresprite);
		window.draw(herosprite);
		window.display();

		if (gameoverE) {
			for (int i = 0; i < HEIGHT_MAP; i++) {//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (Map[i][j] == ' ' || Map[i][j] == '@') { //���� ������ ����� 's' (������)
						Map[i][j] = 'm';
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
			sirenE.pause();
			while (!enter) {
				if ((Keyboard::isKeyPressed(Keyboard::Enter))) enter = true;
			}
			//sleep(seconds(5.0f));
			start = true;
			backE = true;
		}


		//�������� �� �������
		//
		cout << "money=" << money << "  value money=" << value_money << "\n";
		if (money >= (value_money-1)) {
			for (int i = 0; i < HEIGHT_MAP; i++) {//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (Map[i][j] == ' ') { //���� ������ ����� 's' (������)
						Map[i][j] = 'm';
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
			sirenE.pause();
			while (!enter) {
				if ((Keyboard::isKeyPressed(Keyboard::Enter))) enter = true;
			}
			//sleep(seconds(5.0f));
			start = true;
			backE = true;
			
		}
	}
}