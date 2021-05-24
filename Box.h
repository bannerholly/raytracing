#pragma once

#include "BaseObject.h"
#include "Logger.h"

class Box : public BaseObject{
  public:
    enum MaxOrMin{
    max,
    min
  };
    //コンストラクタ
    Box()
    :BaseObject{Vec3{0.0},new Material()}{};
    Box(const Vec3 &v1, const Vec3 &v2)
    :BaseObject((v1 + v2)/2,new Material{}),p_min{v1},p_max{v2}{};
    Box(const Vec3 &v1, const Vec3 &v2, Material *m)
    :BaseObject((v1 + v2)/2,m),p_min{v1},p_max{v2}{};
    Box(const Vec3& p,float x,float y,float z)
    :BaseObject(p,new Material{}),
     p_min{p.x-x/2,p.y-y/2,p.z-z/2},p_max{p.x+x/2,p.y+y/2,p.z+z/2}{};
    Box(const Vec3& p,float x,float y,float z,Material *m)
    :BaseObject(p,m),
     p_min{p.x-x/2,p.y-y/2,p.z-z/2},p_max{p.x+x/2,p.y+y/2,p.z+z/2}{};
    //コピーコンストラクタ
    Box(const Box& bx)
    :BaseObject(bx.o_pos,bx.material),p_min{bx.p_min},p_max{bx.p_max}{}
    //デストラクタ
    ~Box(){
     // Logger::logClass(this);
      for (int i=0; i<(int)children.size(); i++)
			  delete children[i];
      children.clear();
    };
    //レイが物体に当たっているかの判定
    bool hit(const Ray &r, float tmin, float tmax, HitRec& record) const;
    //シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
	  bool shadowHit(const Ray &r, float tmin, float tmax) const;

    //ゲッター
    inline Vec3 getMin() const { return p_min; };
	  inline Vec3 getMax() const { return p_min; };

    //セッター
	  inline void setMin(const Vec3 &p) { p_min = p; };
	  inline void setMax(const Vec3 &p) { p_max = p; };
   
  private:
    Vec3 p_min;
    Vec3 p_max;
};