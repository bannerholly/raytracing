#include "Plane.h"
#include "Logger.h"
#include "cmath"

//レイが物体に当たっているかの判定
bool Plane::hit(const Ray &r, float tmin, float tmax, HitRec& record) const{
  Vec3 normal = w_unit.cross(h_unit); //外積から法線ベクトル
  normal.normalize();
  Vec3 diff = o_pos - r.getStart();
  Vec3 d = r.getDirection();
  float a = d.dot(normal);
  float b = diff.dot(normal);
  //分母が小さかったらアウト
  if (fabs(a) < 1.0e-10) return false;
  float t = b/a;
  //tが範囲外ならアウト
  if (t < tmin || t > tmax) return false;
  //o + tdが範囲外ならアウト
  Vec3 diff2 = r.getPosition(t) - o_pos;
  float w2 = diff2.dot(w_unit);
  float h2 = diff2.dot(h_unit);

  if((w2 < -width/2 || w2 > width/2) || (h2 < -height/2 || h2 > height/2)){
    return false;
  }
  
  if(a > 0.0) normal = -normal;
  
  record.t = t;
  record.p = r.getPosition(t);
  record.n = normal;
  record.material = material;
  record.tex_pos = getTexPos(record.p);
  return true;
}

//シャドウレイが他の物体に当たるかどうかの判定
bool Plane::shadowHit(const Ray &r, float tmin, float tmax) const{
  Vec3 normal = w_unit.cross(h_unit); //外積から法線ベクトル
  normal.normalize();
  Vec3 diff = o_pos - r.getStart();
  Vec3 d = r.getDirection();
  float a = d.dot(normal);
  float b = diff.dot(normal);
  //分母が小さかったらアウト
  if (fabs(a) < 1.0e-10) return false;
  float t = b/a;
  //tが範囲外ならアウト
  if (t < tmin || t > tmax) return false;
  //o + tdが範囲外ならアウト
  Vec3 diff2 = r.getPosition(t) - o_pos;
  float w2 = diff2.dot(w_unit);
  float h2 = diff2.dot(h_unit);

  if((w2 < -width/2 || w2 > width/2) || (h2 < -height/2 || h2 > height/2)){
    return false;
  }
  return true;
};

//座標からテクスチャ座標を割り出す(基本はUV)
Vec3 Plane::getTexPos(Vec3& pos) const{
  Vec3 diff = pos - o_pos;
  float up = diff.dot(w_unit);
  float vp = diff.dot(h_unit);
  float ups = up/ width + 0.5;
  float vps = vp/ height + 0.5;
  return Vec3{ups,vps,1.0f};
}