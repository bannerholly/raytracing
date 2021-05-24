#include "Image.h"
#include <png.h>
#include <jpeglib.h>
#include "Logger.h"
//コンストラクタ
Image::Image():data(nullptr){}

Image::Image(int w,int h)
:width(w),height(h),data(new Vec3[w*h]){
}

Image::Image(int w,int h,Vec3* d):width(w),height(h){
  assert(d != nullptr); //入れるデータの実体があってほしい
  data = new Vec3[width*height]; //データの確保
  memcpy(data, d, width*height*sizeof(Vec3)); //データのコピー
}
//デストラクタ
Image::~Image(){
 // Logger::logClass(this);
  if(data != nullptr){
    delete [] data;
  }
}
//コピーコンストラクタ
Image::Image(const Image& im)
:width(im.width), height(im.height),data(new Vec3[im.width*im.height])
{
  if(im.data != nullptr){
    memcpy(data,im.data, width*height*sizeof(Vec3)); //データのコピー
  }
}

void Image::fill(const Vec3 v){
  assert(data != nullptr); //データがあってほしい
  for (int y=0; y<height; y++)
			for (int x=0; x<width; x++)
				data[x + width*y] = v;
}
