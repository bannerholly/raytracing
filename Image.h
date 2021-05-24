#pragma once

#include "Vec.h"
#include <cstring>
#include <cassert>

class Image{
  protected:
	int width; //幅
	int height; //高さ
	Vec3* data; //出力データ

  public:
    //コンストラクタ
    Image();
    Image(int w,int h);
    Image(int w,int h,Vec3* d);
    //コピーコンストラクタ
    Image(const Image& im);
    //デストラクタ
    ~Image();
  
  //セッター
  inline void setPixel(int x,int y,Vec3 v){
    assert(data != nullptr); //データの実態があってほしい
    //参照範囲が正しくありたい
		assert(0 <= x && x < width);
		assert(0 <= y && y < height);
    data[x + width*y] = v;
  }
  
  inline void allocate(int w, int h){
    if(data != nullptr) delete[] data;
    width = w;
		height = h;
		data = new Vec3[width*height]; //データの再確保
  }
   
  //ゲッター
  inline Vec3 getPixel(int x,int y) const {
    assert(data != nullptr); //データの実態があってほしい
    //参照範囲が正しくありたい
		assert(0 <= x && x < width);
		assert(0 <= y && y < height);
    return data[x + width*y];
  }
  inline int getWidth() const { return width;}
	inline int getHeight() const { return height;}
  inline Vec3 * getData() { return data; }

  //演算子
  //参照
  inline const Vec3& operator()(int x, int y) const
	{
		assert(data != nullptr);
		assert(0 <= x && x < width);
		assert(0 <= y && y < height);

		return data[x + width*y];
	}
  //代入 <- コピー代入だけどdeleteしちゃうの？　== 
  inline Image& operator=(const Image& im)
	{
		if(data != nullptr) delete [] data;
		width = im.width;
		height = im.height;
		data = new Vec3[width*height]; //データの再確保
		memcpy(data, im.data, width*height*sizeof(Vec3));
		return *this;
  }
  //全部同じ色にしちゃう
  void fill(Vec3 v);

  //画像の再確保
};