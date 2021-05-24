#pragma once
#include "Material.h"
#include "Texture.h"
#include "Logger.h"

class TextureMaterial : public Material{
  public:
  //コンストラクタ
  TextureMaterial()
  :Material(Material::MaterialType::TextureType),texture(nullptr){
  };
  //コンストラクタ
  TextureMaterial(Texture* tex)
  :Material(Material::MaterialType::TextureType),texture(tex){
  };
  //コピーコンストラクタ
  TextureMaterial(const TextureMaterial& m)
  :Material(Material::MaterialType::TextureType),texture(m.texture){
  }
  //デストラクタ
  ~TextureMaterial(){
   // Logger::logClass(this);
    if(texture != nullptr){
      delete texture;
    }
  };
  void setTexture(Texture* tex){
    texture = tex;
  };

  Texture* getTexture(void){
    return texture;
  };

  //光源から物体の色を計算する
  Color calcLight(BaseLight* l,HitRec rec,Vec3 out);

  private:
    Texture* texture;
};