#pragma once

#include "vec.h"
#include "iostream"

class Ray{
  public:
    //コンストラクタ
    Ray(){};
    Ray(const Vec3& o,const Vec3& d):start(o),direction(d){};
    //コピーコンストラクタ
    Ray(const Ray& r):start(r.start),direction(r.direction){};
    //デストラクタ
    ~Ray(){};
    //ゲッター
    inline Vec3 getStart() const { return start; }
	  inline Vec3 getDirection() const { return direction; }
    //セッター
    inline void setStart(Vec3& s){start = s;}
	  inline void setDirection(Vec3& d){direction = d; }
    //ポジション
    inline Vec3 getPosition(float t) const{return start + t*direction;}
    //出力
    friend std::ostream &operator<<(std::ostream &os, const Ray &r)
	{
		os << r.getStart() << " + t" << r.getDirection();
		return os;
	}
  private:
    //始点と方向
    Vec3 start;
    Vec3 direction;
};