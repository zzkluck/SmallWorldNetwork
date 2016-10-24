#pragma once
#include<fstream>
#include"Definitions.h"
#define _Height infoheader.biHeight
#define _Width infoheader.biWidth
using namespace std;
using namespace zzkluck::KBitmap;
class BaseBitmap
{
private:	
	int GetLineByteCnt();
	int GetLineOffsetByteCnt();

protected:
	WORD bfType;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	int LineByteCnt;
	int LineOffsetByteCnt;

	void WriteHeader(std::ostream &os) const;
	void ReadHeader(istream &is);
	void BitmapInitialize(int width, int height, int headerSize = 54);

public:
	BaseBitmap();
	BaseBitmap(unsigned width, unsigned heiget);

	virtual void Write(ostream& os) const = 0;
	virtual void Write(string path)const = 0;
	virtual void Read(istream& is) = 0;
	virtual void Read(string path) = 0;
};


