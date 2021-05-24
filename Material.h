#pragma once

#include "Vec.h"
#include "Logger.h"
#include "BaseLight.h"
#include "HitRec.h"
enum MaterialParam
	{
    Ambient,
    Diffuse,
    Specular
	};
  
class Material{
  public:
  enum MaterialType
	{
    NormalType,
    EmissionType,
    TextureType
	};
  //コンストラクタ
  Material()
  :type(NormalType),
  ka(Vec3{0.0}),kd(Vec3{0.0}),ks(Vec3{0.0}),kr(Vec3{0.0}),shiness(1),eta(1.0),
   isReflect(false),isReflact(false){};
  Material(MaterialType t)
  :type(t),ka{Vec3{0.0}},kd{Vec3{0.0}},ks{Vec3{0.0}},
   kr(Vec3{0.0}),shiness(1),eta(1.0),isReflect(false),isReflact(false){};
  //コピーコンストラクタ
  Material(const Material& m)
  :type(m.type),ka(m.ka),kd(m.kd),ks(m.ks),
   kr(m.kr),shiness(m.shiness),eta(m.eta),isReflect(m.isReflect),isReflact(m.isReflact){};
  //デストラクタ
  virtual ~Material(){
    //Logger::logClass(this);
  };
  
  //セッター
  inline void setMaterialType(MaterialType t){ type = t;}
  inline void setAmbientReflect(Vec3& v){ ka = v;}
  inline void setDiffuseReflect(Vec3& v){ kd = v;}
  inline void setSpecularReflect(Vec3& v){ ks = v;}
  inline void setPerfectSpecular(Vec3& v){ kr = v;}
  inline void setShiness(int s){ shiness = s;}
  inline void setEta(float e){ eta = e;}
  inline void setIsReflect(bool b){ isReflect = b;}
  inline void setIsReflact(bool b){ isReflact = b;}
  //ゲッター
  inline MaterialType getMaterialType(){ return type;}
  inline Vec3 getAmbientReflect(){ return ka;}
  inline Vec3 getDiffuseReflect(){ return kd;}
  inline Vec3 getSpecularReflect(){ return ks;}
  inline Vec3 getPerfectSpecular(){ return kr;}
  inline int getShiness(){ return shiness;}
  inline float getEta(){ return eta;}
  inline bool getIsReflect(){ return isReflect;}
  inline bool getIsReflact(){ return isReflact;}
  //光源から物体の色を計算する
  virtual Color calcLight(BaseLight* l,HitRec rec,Vec3 out);
  
  //環境光の反射
  Color calcAmbient(Color& c);
  //拡散反射光の反射
  Color calcDiffuse(Color& c,Vec3& indir,Vec3& n);
  //鏡面反射光の反射
  Color calcSpecular(Color&c,Vec3& indir,Vec3& n,Vec3& out);
  protected:
    MaterialType type; //材質のタイプ
    Vec3 ka; //環境光の反射率
    Vec3 kd; //拡散反射光の反射率
    Vec3 ks; //鏡面反射光の反射率
    int shiness; //鏡面反射の輝きの度合い
    Vec3 kr;  //完全鏡面反射係数
    float eta; //物体の相対屈折率
    bool isReflect; //完全鏡面反射係数
    bool isReflact; //屈折させるかどうか
};