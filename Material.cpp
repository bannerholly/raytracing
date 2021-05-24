#include "Material.h"

Color Material::calcLight(BaseLight* l,HitRec rec,Vec3 out){
  Color c = l->getLightColor(rec.p);
  if(l->getLightType() == BaseLight::LightType::AmbientLight){
    return calcAmbient(c);
  }
  else{
    Vec3 in = l->getInLight(rec.p); //入射光
    Vec3 n = rec.n; //法線ベクトル
    return calcDiffuse(c,in,n) + calcSpecular(c,in,n,out);
  }
}

//環境光
   //(c:環境光(入射光)の強さ)
Color Material::calcAmbient(Color& c){
  return Color(ka.r * c.r,ka.g * c.g,ka.b * c.b);
}
//拡散反射光
  //(c:入射光の強さ, indir:光線から物体への方向を示す単位ベクトル,n:物体の(単位)法線ベクトル)
Color Material::calcDiffuse(Color& c,Vec3& indir,Vec3& n){
  float d = n.dot(-indir); //内積(単位ベクトルなのでcosになるはず)
  //内積が0以下は反射しないとする
  if(d < 0){
    return Color(0.0,0.0,0.0);
  }
  else{
    float r = kd.r * c.r * d;
    float g = kd.g * c.g * d;
    float b = kd.b * c.b * d;
    return Color(r,g,b);
  }
}
//鏡面反射光
  //(c:入射光の強さ, indir:物体から光線方向を示す単位ベクトル,
     //n:物体の(単位)法線ベクトル,out:物体から視点への単位ベクトル)
Color Material::calcSpecular(Color&c,Vec3& indir,Vec3& n,Vec3& out){
  Vec3 r = Vec3::reflect(indir,n); //反射ベクトル
  float d = r.dot(out); //内積
  //内積が0以下は反射しないとする
  if(d < 0){
    return Color(0.0,0.0,0.0);
  }
  else{
    d = pow(d,shiness);
    float r = ks.r * c.r * d;
    float g = ks.g * c.g * d;
    float b = ks.b * c.b * d;
    return Color(r,g,b);
  }
}