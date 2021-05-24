#include "Sphere.h"
#include "Logger.h"

//レイが物体に当たっているかの判定
bool Sphere::hit(const Ray &r, float tmin, float tmax, HitRec& record) const{
  const Vec3 v = r.getStart() - o_pos;
  const Vec3 d = r.getDirection();
  float b = d.dot(v);
  float c = v.squareNorm() - radius*radius;
  float D = b*b -c; //判別式D
  //D:正は2交点, 0は接している, 負は交差していない
  if(D > 0.0){
    float t1 = -b - sqrtf(D),t2 = -b + sqrtf(D);
    if(tmin < t1 && t1 < tmax){
      record.t = t1;
      record.p = r.getPosition(t1);
      record.n = (record.p - o_pos)/radius;
      record.n.normalize(); //単位ベクトルだから
      record.material = material;
      record.tex_pos = getTexPos(record.n);
      return true;
    }
    if(tmin < t2 && t2 < tmax){
      record.t = t2;
      record.p = r.getPosition(t2);
      record.n = (record.p - o_pos)/radius;
      record.n.normalize(); //単位ベクトルだから
      record.material = material;
      record.tex_pos = getTexPos(record.n);
     // Logger::logPut(&record.tex_pos);
      return true;
    }
  }
  return false;
};

//シャドウレイが他の物体に当たるかどうかの判定
bool Sphere::shadowHit(const Ray &r, float tmin, float tmax) const{
  const Vec3 v = r.getStart() - o_pos;
  const Vec3 d = r.getDirection();
  float b = d.dot(v);
  float c = v.squareNorm() - radius*radius;
  float D = b*b -c; //判別式D
  //D:正は2交点, 0は接している, 負は交差していない
  if(D > 0.0){
    float t1 = -b - sqrtf(D),t2 = -b + sqrtf(D);
    if(tmin < t1 && t1 < tmax){
      return true;
    }
    if(tmin < t2 && t2 < tmax){
      return true;
    }
  }
  return false;
};

//座標からテクスチャ座標を割り出す(基本はUV)
Vec3 Sphere::getTexPos(Vec3& pos) const{
 // Vec3 tmp = pos;
 // tmp.normalize();
  float phi = atan2f(pos.z,pos.x);
  float theta = asinf(pos.y);
  Vec3 uvw;
  uvw.x = (phi + M_PI) / (2.0f * M_PI); //u
  uvw.y = (theta + M_PI/2) / M_PI; //v
  uvw.z = 1.0f;
  return uvw;
}