#pragma once

#include "ObjectFactory.h"
#include "LightFactry.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Material.h"
#include "EmitMaterial.h"
#include "Logger.h"

class SceneMaker{
  public:
    //コンストラクタ
    SceneMaker(){
    };
    //デストラクタ
    ~SceneMaker(){};
    //シーンの作成
    Scene* make();
  private:
    //作成するシーン
    Scene s;
    //オブジェクトファクトリー
    ObjectFactry o_factry;
    //ライトファクトリー
    LightFactry l_factry;
};