#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ImageProcess	{

private:
	int Width;
	int Height;
	float macierz[5][5];
	int ileP;
	Image tempBitmap;

public:

	ImageProcess(int, int);
	~ImageProcess();
	void macierzBlur();
	void macierzBlurGaussian();
	void macierzEdges();
	void macierzSharpnes();
	Image setImage(Image);
	Image doProcess(Image, int);
	Image doGrey(Image);
	Image doLighter(Image, int);
	Image doColor(Image, const char *);
	Image doNegative(Image);
	Image doContrast(Image, float);

};

