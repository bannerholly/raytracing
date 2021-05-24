#include "Triangle.h"
#include "Logger.h"
#include "cmath"

//レイが物体に当たっているかの判定
bool Triangle::hit(const Ray &r, float tmin, float tmax, HitRec& record) const{
  Vec3 r_ = r.getStart() - t_pos[0];
  Vec3 d = r.getDirection();
  Vec3 v10 =  t_pos[1] -t_pos[0];
  Vec3 v20 =  t_pos[2] -t_pos[0];
  Vec3 u =  d.cross(v20);
  Vec3 v = r_.cross(v10);
  float a = u.dot(v10);
  //分母が小さかったらアウト
  if (fabs(a) < 1.0e-10) return false;

  Vec3 param{0.0};
  param.x = v.dot(v20) / a; //t
  param.y = u.dot(r_) / a; //β
  param.z = v.dot(d) / a; //γ

  //tが範囲外ならアウト
  if (param.x < tmin || param.x > tmax){
    return false;
  }

  //β,γが範囲内ならばOK
  if(param.y > 0 && param.z > 0 && (param.y + param.z) <= 1){
    record.t = param.x;
    record.p = r.getPosition(param.x);
    record.n = getNormal();
    if((record.n.dot(d)) > 0.0) record.n = -record.n;
    
    record.material = material;
    record.tex_pos = getTexPos_(param.y,param.z);
    return true;
  }
  return false;
}

//シャドウレイが他の物体に当たるかどうかの判定
bool Triangle::shadowHit(const Ray &r, float tmin, float tmax) const{
  Vec3 r_ = r.getStart() - t_pos[0];
  Vec3 d = r.getDirection();
  Vec3 v10 =  t_pos[1] -t_pos[0];
  Vec3 v20 =  t_pos[2] -t_pos[0];
  Vec3 u =  d.cross(v20);
  Vec3 v = r_.cross(v10);
  float a = u.dot(v10);
  //分母が小さかったらアウト
  if (fabs(a) < 1.0e-10) return false;

  Vec3 param{0.0};
  param.x = v.dot(v20) / a; //t
  param.y = u.dot(r_) / a; //β
  param.z = r_.dot(d) / a; //γ
  //tが範囲外ならアウト
  if (param.x < tmin || param.x > tmax) return false;
  //β,γが範囲内ならばOK
  if(param.y > 0 && param.z > 0 && (param.y + param.z) < 1){
    return true;
  }
  return false;
};

//座標からテクスチャ座標を割り出す(基本はUV)
Vec3 Triangle::getTexPos(Vec3& pos) const{
  return Vec3{0.0f};
}

Vec3 Triangle::getTexPos_(float b,float c) const{
  return Vec3{b + c/2,c,1.0};
}