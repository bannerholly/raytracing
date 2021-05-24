#pragma once

#include "BaseLight.h"
#include "Logger.h"
#include <GL/glut.h>

//平行光
class PointLight: public BaseLight{
  public:
    //コンストラクタ
	  PointLight(Vec3& p,Color& c)
		: BaseLight(p,c,LightType::PointLight){
    };
    //コピーコンストラクタ
    PointLight(const PointLight &l)
		: BaseLight(l.l_pos,l.l_color,l.type){};
    //デストラクタ
    ~PointLight(){};
    
    Color getLightColor(Vec3& pos) const;
    float getLightDistance(Vec3& pos);
    Vec3 getInLight(Vec3& point);
  private:
};
