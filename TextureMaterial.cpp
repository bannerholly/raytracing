#include "TextureMaterial.h"

Color TextureMaterial::calcLight(BaseLight* l,HitRec rec,Vec3 out){
  Color c = l->getLightColor(rec.p);
  if(l->getLightType() == BaseLight::LightType::AmbientLight){
    return calcAmbient(c);
  }
  else{
    Vec3 in = l->getInLight(rec.p); //入射光
    Vec3 n = rec.n; //法線ベクトル
    Color tmp = texture->getColor(rec.tex_pos);
    setDiffuseReflect(tmp);
    return calcDiffuse(c,in,n) + calcSpecular(c,in,n,out);
  }
}