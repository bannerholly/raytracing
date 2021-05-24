#pragma once

#include "BaseLight.h"

//平行光限
class DirectionalLight: public BaseLight{
  public:
    //コンストラクタ
	  DirectionalLight(Vec3& p,Color& c)
		: BaseLight(p,c,LightType::DirectionalLight),dir(p){};
    //コピーコンストラクタ
    DirectionalLight(const DirectionalLight &l)
		: BaseLight(l.l_pos,l.l_color,l.type),dir(l.dir){};
    //デストラクタ
    ~DirectionalLight(){};

    Color getLightColor(Vec3& pos) const;
    float getLightDistance(Vec3& pos);
    Vec3 getInLight(Vec3& point);
  private:
    Vec3 dir; //平行ベクトル
};