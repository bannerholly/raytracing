#pragma once

#include "Texture.h"

class ColorTexture : public Texture{
  public:
    //コンストラクタ
    ColorTexture(Color c):t_color(c){};
    //デストラクタ
    ~ColorTexture(){};

    //セッター
    void setColor(Color& c){
      t_color = c;
    }

    //ゲッター
    Color getColor() const{
      return t_color;
    }
    Color getColor(const Vec3 &uvw) const{
		  return t_color;
	  }
  private:
    Color t_color; //色
};