#pragma once

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class LightFactry{
  public:
    //コンストラクタ
    LightFactry(){};
    //デストラクタ
    ~LightFactry(){};
    //生成メソッド
    AmbientLight* createAmbientLight(Vec3& p,Color& c){
      AmbientLight* r = new AmbientLight(p,c);
      return r;
    };
    DirectionalLight* createDirectionalLight(Vec3& p,Color& c){
      p.normalize();
      DirectionalLight* r = new DirectionalLight(p,c);
      return r;
    };
    PointLight* createPointLight(Vec3& p,Color& c){
      PointLight* r = new PointLight(p,c);
      return r;
    };
  private:
};