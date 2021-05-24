#pragma once

#include "Vec.h"

class Texture{
  public:
    //コンストラクタ
    Texture(){};
    //デストラクタ
    virtual ~Texture(){};

    virtual void setColor(Color& c){};
    virtual Color getColor() const{
      return Color(0.f, 0.f, 0.f);
    };
    virtual Color getColor(const Vec3 &uvw) const{
		  return Color(0.f, 0.f, 0.f);
	  };
	  inline Color getColor(float u, float v, float w) const{
      Vec3 a = Vec3(u,v,w);
		  return getColor(a);
  	};
};