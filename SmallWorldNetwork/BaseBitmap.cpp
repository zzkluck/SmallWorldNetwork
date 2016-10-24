#include "BaseBitmap.h"
using namespace zzkluck::KBitmap;
BaseBitmap::BaseBitmap()
{
}


BaseBitmap::BaseBitmap(unsigned width, unsigned heiget)
{
	BitmapInitialize(width, heiget);
}

void BaseBitmap::WriteHeader(std::ostream &os)const{
	os.write((char*)&bfType, sizeof(bfType));
	os.write((char*)&fileheader, sizeof(fileheader));
	os.write((char*)&infoheader, sizeof(infoheader));
}

void BaseBitmap::ReadHeader(istream & is)
{
	is.read((char*)&bfType, sizeof(bfType));
	is.read((char*)&fileheader, sizeof(fileheader));
	is.read((char*)&infoheader, sizeof(infoheader));
}

void BaseBitmap::BitmapInitialize(int width, int height,int headerSize)
{
	//提供一个通用的Bitmap初始化
	this->bfType = 19778;
	this->infoheader.biSize = 40;
	this->infoheader.biPlane = 1;
	this->_Height = height;
	this->_Width = width;
	LineByteCnt = GetLineByteCnt();
	LineOffsetByteCnt = GetLineOffsetByteCnt();
	this->fileheader.bfSize = headerSize + LineByteCnt*_Height;
}



int BaseBitmap::GetLineByteCnt() {
	//计算数据对齐后每行的字节数 
	int a = 1<< 5 >> 4;
	return ((infoheader.biWidth)*(infoheader.biBitCount) + 31) >> 5 << 2;
}


int BaseBitmap::GetLineOffsetByteCnt() {
	//计算每行补齐字节的数量
	return 4 - ((infoheader.biWidth)*(infoheader.biBitCount) >> 3) & 3;
}