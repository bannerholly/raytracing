#pragma once

#include "HitRec.h"
#include "Vec.h"
#include "Ray.h"
#include "Material.h"
#include <vector>
#include <iostream>
#include <GL/glut.h>

class BaseObject{
  public:
    enum ObjectType
	{
    Normal,
    Emit
	};
    //コンストラクタ
    BaseObject():o_pos(Vec3{0.0}),material(new Material()){};
    BaseObject(const Vec3& v):o_pos(v),material(new Material()){};
    BaseObject(const Vec3& v,Material* m):o_pos(v),material(m){
    };
    
    //デストラクタ
    virtual ~BaseObject(){
      if(material != nullptr){
      //  Logger::logClass(this);
        delete material;
      }
    };
    
    //share関連
    virtual void shaprePoint(){
      ++sharePoint_count;
    }
    bool releaseOK(){
      --sharePoint_count;
      if(sharePoint_count <= 0){
        return true;
      }
      return false;
    }

    //レイが物体に当たっているかの判定
    
    virtual bool hit(const Ray& r, float tmin, float tmax, HitRec& record) const = 0;
    //シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
	  
    virtual bool shadowHit(const Ray& r, float tmin, float tmax) const = 0;
    //座標からテクスチャ座標を割り出す(基本はUV)
    
    virtual Vec3 getTexPos(Vec3& pos) const {};

    //セッター
    inline void setMaterial(Material* m){
      material = m;
    }
    inline void setPosition(Vec3& v){
      o_pos = v;
    }
    inline void setMaterialParam(MaterialParam param,Vec3 p){
      switch(param){
        case MaterialParam::Ambient :
          material->setAmbientReflect(p);
          break;
        case MaterialParam::Diffuse :
          material->setDiffuseReflect(p);
          break;
        case MaterialParam::Specular :
          material->setSpecularReflect(p);
          break;
      };

    }
    inline void setMaterialShiness(int s){
      material->setShiness(s);
    }
    inline void setMaterialPerfectSpecular(Vec3 p){
      material->setPerfectSpecular(p);
    }
    inline void setMaterialReflactSpecular(float t,Vec3 v){
      material->setEta(t);
      material->setPerfectSpecular(v);
    }

    //ゲッター
    inline Material* getMaterial(){
      return material;
    }
    inline Vec3 getPosition(){
      return o_pos;
    }

    virtual Vec3 getBoundingBoxMin() const { return Vec3(0,0,0); }
	  virtual Vec3 getBoundingBoxMax() const { return Vec3(0,0,0); }

    //ON,OFF
    void onPerfectSpecular(){
      material->setIsReflect(true);
      offReflactSpecular();
    }
    void offPerfectSpecular(){
      material->setIsReflect(false);
    }
    void onReflactSpecular(){
      material->setIsReflact(true);
      offPerfectSpecular();
    }
    void offReflactSpecular(){
      material->setIsReflact(false);
    }
 
  protected:
    Vec3 o_pos; //物体の座標(中心)
    std::vector<BaseObject*> children; //子のオブジェクト
    //マテリアル関連
    Material* material;
    int sharePoint_count = 0;
};