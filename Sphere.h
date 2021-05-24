#pragma once

#include "BaseObject.h"

class Sphere : public BaseObject{
  public:
    //コンストラクタ
    Sphere():BaseObject{Vec3{0.0},new Material()}
    {};
	  Sphere(Vec3 &_center, float r)
		:BaseObject(_center,new Material{}), radius(r){};
    Sphere(Vec3 &_center, float r,Material* m)
		:BaseObject(_center,m), radius(r){};
    //コピーコンストラクタ
    Sphere(const Sphere &s)
		: BaseObject(s.o_pos,s.material), radius(s.radius){};
    //デストラクタ
    ~Sphere(){
      for (int i=0; i<(int)children.size(); i++)
			  delete children[i];
      children.clear();
    };

    //レイが物体に当たっているかの判定
    bool hit(const Ray &r, float tmin, float tmax, HitRec& record) const;
    //シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
	  bool shadowHit(const Ray &r, float tmin, float tmax) const;
   //座標からテクスチャ座標を割り出す(基本はUV)
    Vec3 getTexPos(Vec3& pos) const;

  private:
   // Vec3 center;
	  float radius;
};