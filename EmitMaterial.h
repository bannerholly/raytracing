#pragma once
#include "Material.h"
#include "ColorTexture.h"
#include "Logger.h"
class EmitMaterial : public Material{
  public:
  //コンストラクタ
  EmitMaterial()
  :Material(Material::MaterialType::EmissionType),color{Vec3(1.0)}{
    Vec3 a = color.getColor();
    setDiffuseReflect(a);
  };
  EmitMaterial(Color c)
  :Material(Material::MaterialType::EmissionType),color(c){
    Vec3 a = color.getColor();
    setDiffuseReflect(a);
  };
  //コピーコンストラクタ
  EmitMaterial(const EmitMaterial& m)
  :Material(Material::MaterialType::EmissionType),color(m.color){
    Vec3 a = color.getColor();
    setDiffuseReflect(a);
  }
  //デストラクタ
  ~EmitMaterial(){};
  
  //ゲッター
  Color calcLight(BaseLight* l,HitRec rec,Vec3 diff){
    //lとrecは今のところ使わない?
    Color c = color.getColor();
    float r = diff.norm();
    return 10*c/r;
  }
  private:
    ColorTexture color;
};