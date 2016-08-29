#include "stdafx.h"
#include "ImageProcess.h"

ImageProcess::ImageProcess(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;
	tempBitmap.create(Width, Height, Color::Yellow);
}
ImageProcess::~ImageProcess() { }
Image ImageProcess::setImage(Image obraz) {
	return obraz;
}
void ImageProcess::macierzBlur() {
	macierz[0][0] = 1;	macierz[0][1] = 1;	macierz[0][2] = 1;	macierz[0][3] = 1;	macierz[0][4] = 1;
	macierz[1][0] = 1;	macierz[1][1] = 1;	macierz[1][2] = 1;	macierz[1][3] = 1;	macierz[1][4] = 1;
	macierz[2][0] = 1;	macierz[2][1] = 1;	macierz[2][2] = 1;	macierz[2][3] = 1;	macierz[2][4] = 1;
	macierz[3][0] = 1;	macierz[3][1] = 1;	macierz[3][2] = 1;	macierz[3][3] = 1;	macierz[3][4] = 1;
	macierz[4][0] = 1;	macierz[4][1] = 1;	macierz[4][2] = 1;	macierz[4][3] = 1;	macierz[4][4] = 1;
	ileP = 25;
}
void ImageProcess::macierzBlurGaussian() {
	macierz[0][0] = 0;	macierz[0][1] = 0;	macierz[0][2] = 0;	macierz[0][3] = 0;	macierz[0][4] = 0;
	macierz[1][0] = 0;	macierz[1][1] = 1;	macierz[1][2] = 2;	macierz[1][3] = 1;	macierz[1][4] = 0;
	macierz[2][0] = 0;	macierz[2][1] = 2;	macierz[2][2] = 4;	macierz[2][3] = 2;	macierz[2][4] = 0;
	macierz[3][0] = 0;	macierz[3][1] = 1;	macierz[3][2] = 2;	macierz[3][3] = 1;	macierz[3][4] = 0;
	macierz[4][0] = 0;	macierz[4][1] = 0;	macierz[4][2] = 0;	macierz[4][3] = 0;	macierz[4][4] = 0;
	ileP = 8;
}
void ImageProcess::macierzEdges() {
	macierz[0][0] = -1;	macierz[0][1] = -1;	macierz[0][2] = -1;	macierz[0][3] = -1;	macierz[0][4] = -1;
	macierz[1][0] = -1;	macierz[1][1] = -1;	macierz[1][2] = -1;	macierz[1][3] = -1;	macierz[1][4] = -1;
	macierz[2][0] = -1;	macierz[2][1] = -1;	macierz[2][2] = 24;	macierz[2][3] = -1;	macierz[2][4] = -1;
	macierz[3][0] = -1;	macierz[3][1] = -1;	macierz[3][2] = -1;	macierz[3][3] = -1;	macierz[3][4] = -1;
	macierz[4][0] = -1;	macierz[4][1] = -1;	macierz[4][2] = -1;	macierz[4][3] = -1;	macierz[4][4] = -1;
	ileP = 25;
}
void ImageProcess::macierzSharpnes() {
	macierz[0][0] = 0;	macierz[0][1] = 0;	macierz[0][2] = 0;	macierz[0][3] = 0;	macierz[0][4] = 0;
	macierz[1][0] = 0;	macierz[1][1] = 0;	macierz[1][2] = -2;	macierz[1][3] = 0;	macierz[1][4] = 0;
	macierz[2][0] = 0;	macierz[2][1] = -2;	macierz[2][2] = 11;	macierz[2][3] = -2;	macierz[2][4] = 0;
	macierz[3][0] = 0;	macierz[3][1] = 0;	macierz[3][2] = -2;	macierz[3][3] = 0;	macierz[3][4] = 0;
	macierz[4][0] = 0;	macierz[4][1] = 0;	macierz[4][2] = 0;	macierz[4][3] = 0;	macierz[4][4] = 0;
	ileP = 3;
}

Image ImageProcess::doColor(Image bitplane_1, const char * tryb = "red") {
	cout << "Zmien Kolor na " << tryb << endl;
	Color kolor;
	int grey;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			kolor = bitplane_1.getPixel(x, y);
			if (tryb == "blue") {
				kolor.r = 0;
				kolor.g = 0;
				kolor.b = kolor.b;
			}
			else if (tryb == "green") {
				kolor.r = 0;
				kolor.g = kolor.g;
				kolor.b = 0;
			}
			else
			{
				kolor.r = kolor.r;
				kolor.g = 0;
				kolor.b = 0;
			}

			tempBitmap.setPixel(x, y, kolor);
		}
	}
	return tempBitmap;
}
Image ImageProcess::doLighter(Image bitplane_1, int swiatlo) {
	cout << "Rozjasnij / Sciemnij   swiatlo:"<< swiatlo << endl;
	Color kolor;
	int r, g, b;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			kolor = bitplane_1.getPixel(x, y);
			r = kolor.r + swiatlo;
			g = kolor.g + swiatlo;
			b = kolor.b + swiatlo;

			if (r < 0) r = 0;
			if (r > 255) r = 255;
			if (g < 0) g = 0;
			if (g > 255) g = 255;
			if (b < 0) b = 0;
			if (b > 255) b = 255;

			kolor.r = r;
			kolor.g = g;
			kolor.b = b;
			tempBitmap.setPixel(x, y, kolor);
		}
	}
	return tempBitmap;
//	bitplane_1.copy(tempBitmap, 0, 0);
}
Image ImageProcess::doNegative(Image bitplane_1) {
	cout << "Negative" << endl;
	Color kolor;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			kolor = bitplane_1.getPixel(x, y);
			kolor.r = 255 - kolor.r;
			kolor.g = 255 - kolor.g;
			kolor.b = 255 - kolor.b;
			tempBitmap.setPixel(x, y, kolor);
		}
	}
	return tempBitmap;
}
Image ImageProcess::doContrast(Image bitplane_1, float wartosc_kontrastu) {
	cout << "Kontrast  wartosc: "<< wartosc_kontrastu << endl;
	Color kolor;
	float r, g, b;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			kolor = bitplane_1.getPixel(x, y);
			r = kolor.r - 128;
			g = kolor.g - 128;
			b = kolor.b - 128;
			r = r * wartosc_kontrastu;
			g = g * wartosc_kontrastu;
			b = b * wartosc_kontrastu;
			r = r + 128;
			g = g + 128;
			b = b + 128;

			if (r < 0) r = 0;
			if (r > 255) r = 255;
			if (g < 0) g = 0;
			if (g > 255) g = 255;
			if (b < 0) b = 0;
			if (b > 255) b = 255;

			kolor.r = (Uint8)r;
			kolor.g = (Uint8)g;
			kolor.b = (Uint8)b;
			tempBitmap.setPixel(x, y, kolor);
		}
	}
	return tempBitmap;
}
Image ImageProcess::doGrey(Image bitplane_1) {
	cout << "Grey" << endl;
	Color kolor;
	int grey;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			kolor = bitplane_1.getPixel(x, y);
			grey = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;
			if (grey < 0) grey = 0;
			if (grey > 255) grey = 255;
			kolor.r = (Uint8)grey;
			kolor.g = (Uint8)grey;
			kolor.b = (Uint8)grey;
			tempBitmap.setPixel(x, y, kolor);
		}
	}
	return tempBitmap;
}
Image ImageProcess::doProcess(Image bitplane_1, int wspolczynnik=0) {

	if (wspolczynnik != 0)	ileP = wspolczynnik;

	cout << "another 5x5 matrix process" << endl;
	int mW = 5, mH = 5;

	Color kolor;
	int tr, tg, tb;

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {

			tr = 0;
			tg = 0;
			tb = 0;

			for (int mY = 0; mY < mH; mY++) {
				for (int mX = 0; mX < mW; mX++) {
					if (x + mX < Width && y + mY < Height) {
						kolor = bitplane_1.getPixel(x + mX, y + mY);
						tr = tr + (kolor.r * macierz[mX][mY]);
						tg = tg + (kolor.g * macierz[mX][mY]);
						tb = tb + (kolor.b * macierz[mX][mY]);
					}
				}
			}
			tr = tr / ileP;
			tg = tg / ileP;
			tb = tb / ileP;
			if (tr < 0) tr = 0;
			if (tr > 255) tr = 255;
			if (tg < 0) tg = 0;
			if (tg > 255) tg = 255;
			if (tb < 0) tb = 0;
			if (tb > 255) tb = 255;

			kolor.r = (Uint8)tr;
			kolor.g = (Uint8)tg;
			kolor.b = (Uint8)tb;
			tempBitmap.setPixel(x, y, kolor);
		}
	}
	
	bitplane_1.copy(tempBitmap, mW / 2, mH / 2);	// trzeba przesun¹æ bo inaczej bêdzie obrazek siê przesuwa³
	return bitplane_1;

}

