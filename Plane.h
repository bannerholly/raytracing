#pragma once

#include "BaseObject.h"

class Plane : public BaseObject{
  public:
    //コンストラクタ
    Plane():BaseObject{Vec3{0.0},new Material()}{};
    Plane(Vec3 &_center,float w,float h,Vec3 wn,Vec3 hn)
    :BaseObject(_center,new Material{}),width(w),height(h),w_unit(wn),h_unit(hn){};
    Plane(Vec3 &_center,float w,float h,Vec3 wn,Vec3 hn,Material* m)
    :BaseObject(_center,m),width(w),height(h),w_unit(wn),h_unit(hn){};
    //コピーコンストラクタ
    Plane(const Plane &s)
		: BaseObject(s.o_pos,s.material),width(s.width),height(s.height),
      w_unit(s.w_unit),h_unit(s.h_unit){};
    //デストラクタ
    ~Plane(){
     // Logger::logClass(this);
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
    float width; //幅
    float height; //高さ
    Vec3 w_unit; //幅の単位ベクトル
    Vec3 h_unit; //高さの単位ベクトル
};