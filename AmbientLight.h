#pragma once

#include "BaseLight.h"

//環境光
class AmbientLight: public BaseLight{
  public:
    //コンストラクタ
	  AmbientLight(Vec3& p,Color& c)
		: BaseLight(p,c,LightType::AmbientLight){};
    //コピーコンストラクタ
    AmbientLight(const AmbientLight &l)
		: BaseLight(l.l_pos,l.l_color,l.type){};
    //デストラクタ
    ~AmbientLight(){};
    Color getLightColor(Vec3& pos) const;
  private:
};