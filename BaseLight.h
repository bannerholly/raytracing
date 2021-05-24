#pragma once

#include "Vec.h"
#include "HitRec.h"

class BaseLight{
  public:
  enum LightType
	{
    AmbientLight,
    DirectionalLight,
		PointLight,
	};
  //コンストラクタ
  BaseLight(const Vec3& p,const Color& c,LightType t):l_pos(p),l_color(c),type{t}{};
  
  //デストラクタ
  virtual ~BaseLight(){};

  //ゲッター
  virtual Color getLightColor(Vec3& pos) const = 0;
  virtual float getLightDistance(Vec3& pos){};
  virtual Vec3 getInLight(Vec3& point){}; //入力した座標から単位入射角ベクトルを返す 
  inline LightType getLightType(){
    return type;
  } 
  protected:
    LightType type;
    Vec3 l_pos; //光源の座標
    Color l_color; //光の色
};