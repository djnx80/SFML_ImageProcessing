#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ImageProcess.h"

using namespace sf;
using namespace std;

Image obrazek;
Image coWyswietlic;

int Width = 800;
int Height = 600;


int main()
{

	ImageProcess IE(Width, Height);

	RenderWindow okno(VideoMode(900, 700), "Okno");
	okno.setVerticalSyncEnabled(true);	// 60fps


	if (obrazek.loadFromFile("obrazek.jpg") == false) {
		cout << "nie wczytalem obrazka" << endl;
		return -1;
	}

	Texture texture;
	Sprite sprite;
	Time czas;
	Clock zegar;

	Font font;
	if (!font.loadFromFile("BornAddict.ttf"))
	{
		cout << "Nie udalo sie wczytac czcionki" << endl;
		return -1;
	}

	sf::Text text;

	// wybranie czcionki
	text.setFont(font);
	text.setCharacterSize(24); // w pikselach, nie punktach!
	text.setColor(sf::Color::White);

//	text.setStyle(sf::Text::Bold |);

	String napis;

	int wybor =  10;

	coWyswietlic = IE.setImage(obrazek);
	float tempo = -5;

	while (okno.isOpen())
	{
		zegar.restart();

		Event event;
		while (okno.pollEvent(event))
		{
			if (event.type == Event::Closed)
				okno.close();


			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Right)
				{
					cout << "wciœniêto PPM" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
				}
			}


			if (event.type == Event::MouseMoved)
			{
				cout << "x: " << event.mouseMove.x;
				cout << "   y: " << event.mouseMove.y << endl;
			}

			if (event.type == Event::MouseEntered)
				cout << "mysz jest na obszarze okna" << endl;

			if (event.type == Event::MouseLeft)
				cout << "mysz wysz³a poza okno" << endl;

			if (event.type == Event::KeyPressed)
			{
				tempo = -50;
				if (event.key.code == Keyboard::Num1)	wybor = 1;
				if (event.key.code == Keyboard::Num2)	wybor = 2;
				if (event.key.code == Keyboard::Num3)	wybor = 3;
				if (event.key.code == Keyboard::Num4)	wybor = 4;
				if (event.key.code == Keyboard::Num5)	wybor = 5;
				if (event.key.code == Keyboard::Num6)	wybor = 6;
				if (event.key.code == Keyboard::Num7)	wybor = 7;
				if (event.key.code == Keyboard::Num8)	wybor = 8;
				if (event.key.code == Keyboard::Num9)	wybor = 9;
				if (event.key.code == Keyboard::Num0)	wybor = 0;

			}
		}

		if (wybor == 1)	coWyswietlic = IE.doGrey(obrazek);
		if (wybor == 2)	coWyswietlic = IE.doColor(obrazek, "red");
		if (wybor == 3)	coWyswietlic = IE.doColor(obrazek, "green");
		if (wybor == 4)	coWyswietlic = IE.doColor(obrazek, "blue");
		if (wybor == 5)	coWyswietlic = IE.doContrast(obrazek, tempo);
		if (wybor == 6)	coWyswietlic = IE.doLighter(obrazek, tempo);
		if (wybor == 7)	coWyswietlic = IE.doNegative(obrazek);
		if (wybor == 8) {
			IE.macierzBlurGaussian();
			coWyswietlic = IE.doProcess(obrazek, 0);
		}
		if (wybor == 9) {
			IE.macierzEdges();
			coWyswietlic = IE.doProcess(obrazek, 0);
		}
		if (wybor == 0) {
			IE.macierzSharpnes();
			coWyswietlic = IE.doProcess(obrazek, 0);
		}

		napis = "tempo= " + to_string(tempo);
		text.setString(napis);
		tempo += 0.5;
		okno.clear();
		texture.loadFromImage(coWyswietlic);
		sprite.setTexture(texture, true);
		okno.draw(sprite);
		okno.draw(text);

		okno.display();

		czas = zegar.getElapsedTime();
//		cout << "czas [ms]:" << czas.asMilliseconds() << "  [s]: " << czas.asSeconds() << endl;
	}

	return 0;
}

