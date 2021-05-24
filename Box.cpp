#include "Box.h"

//レイが物体に当たっているかの判定
bool Box::hit(const Ray &r, float tmin, float tmax, HitRec& record) const{
  float tnear = tmin;
  float tfar = tmax;
  float t;
  MaxOrMin x_point; //交点におけるx軸のパラメータ
  MaxOrMin y_point; //交点におけるy軸のパラメータ
  MaxOrMin z_point; //交点におけるz軸のパラメータ
  Vec3 origin = r.getStart();
  Vec3 dir = r.getDirection();
  Vec3 normal{0.0}; //法線ベクトル
  //xについて判定
  if(dir.x == 0){
    if(!(p_min.x <= origin.x && origin.x <= p_max.x)){
      return false;
    }
  }
  else{
    float txnear,txfar;
    if(dir.x > 0){
      txnear = (p_min.x - origin.x) /dir.x;
      txfar = (p_max.x - origin.x) /dir.x;
      x_point = (txnear < 0)? max : min;
    }
    else if(dir.x < 0){
      txnear = (p_max.x - origin.x) /dir.x;
      txfar = (p_min.x - origin.x) /dir.x;
      x_point = (txnear < 0)? min : max;
    }
    if(tnear < txnear){
      normal = (x_point == min)?Vec3{-1.0,0.0,0.0}:Vec3{1.0,0.0,0.0};
      tnear = txnear;
      t = txnear;
    }
    if(tfar > txfar){
      //内部に視点があった場合
      if(txnear < 0){
        normal = (x_point == min)?Vec3{-1.0,0.0,0.0}:Vec3{1.0,0.0,0.0};
        t = txfar;
      }
      tfar = txfar;
    }
    if(tnear > tfar) return false;
  }
  //yについて判定
  if(dir.y == 0){
    if(!(p_min.y <= origin.y && origin.y <= p_max.y)){
      return false;
    }
  }
  else{
    float tynear,tyfar;
    if(dir.y > 0){
      tynear = (p_min.y - origin.y) /dir.y;
      tyfar = (p_max.y - origin.y) /dir.y;
      y_point = (tynear < 0)? max : min;
    }
    else if(dir.y < 0){
      tynear = (p_max.y - origin.y) /dir.y;
      tyfar = (p_min.y - origin.y) /dir.y;
      y_point = (tynear < 0)? min : max;
    }
    if(tnear < tynear){
      normal = (y_point == min)?Vec3{0.0,-1.0,0.0}:Vec3{0.0,1.0,0.0};
      tnear = tynear;
      t = tynear;
    }
    if(tfar > tyfar){
      //内部に視点があった場合
      if(tynear < 0){
        normal = (y_point == min)?Vec3{0.0,-1.0,0.0}:Vec3{0.0,1.0,0.0};
        t = tyfar;
      }
      tfar = tyfar;
    }
    if(tnear > tfar) return false;
  }
  //zについて判定
  if(dir.z == 0){
    if(!(p_min.z <= origin.z && origin.z <= p_max.z)){
      return false;
    }
  }
  else{
    float tznear,tzfar;
    if(dir.z > 0){
      tznear = (p_min.z - origin.z) /dir.z;
      tzfar = (p_max.z - origin.z) /dir.z;
      z_point = (tznear < 0)? max : min;
    }
    else if(dir.z < 0){
      tznear = (p_max.z - origin.z) /dir.z;
      tzfar = (p_min.z - origin.z) /dir.z;
      z_point = (tznear < 0)? min : max;
    }
    if(tnear < tznear){
      normal = (z_point == min)?Vec3{0.0,0.0,-1.0}:Vec3{0.0,0.0,1.0};
      tnear = tznear;
      t = tznear;
    }
    if(tfar > tzfar){
      //内部に視点があった場合
      if(tznear < 0){
        normal = (z_point == min)?Vec3{0.0,0.0,-1.0}:Vec3{0.0,0.0,1.0};
        t = tzfar;
      }
      tfar = tzfar;
    }
    if(tnear > tfar) return false;
  }

  record.p = r.getPosition(t);
  record.t = t;
  record.n = normal;
  record.material = material;
  return true;
};
//シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
bool Box::shadowHit(const Ray &r, float tmin, float tmax) const{
  float tnear = tmin;
  float tfar = tmax;
  Vec3 origin = r.getStart();
  Vec3 dir = r.getDirection();
  //xについて判定
  if(dir.x == 0){
    if(!(p_min.x <= origin.x && origin.x <= p_max.x)){
      return false;
    }
  }
  else{
    float txnear,txfar;
    if(dir.x > 0){
      txnear = (p_min.x - origin.x) /dir.x;
      txfar = (p_max.x - origin.x) /dir.x;
    }
    else if(dir.x < 0){
      txnear = (p_max.x - origin.x) /dir.x;
      txfar = (p_min.x - origin.x) /dir.x;
    }
    if(tnear < txnear){
      tnear = txnear;
    }
    if(tfar > txfar){
      tfar = txfar;
    }
    if(tnear > tfar) return false;
  }
  //yについて判定
  if(dir.y == 0){
    if(!(p_min.y <= origin.y && origin.y <= p_max.y)){
      return false;
    }
  }
  else{
    float tynear,tyfar;
    if(dir.y > 0){
      tynear = (p_min.y - origin.y) /dir.y;
      tyfar = (p_max.y - origin.y) /dir.y;
    }
    else if(dir.y < 0){
      tynear = (p_max.y - origin.y) /dir.y;
      tyfar = (p_min.y - origin.y) /dir.y;
    }
    if(tnear < tynear){
      tnear = tynear;
    }
    if(tfar > tyfar){
      tfar = tyfar;
    }
    if(tnear > tfar) return false;
  }
  //zについて判定
  if(dir.z == 0){
    if(!(p_min.z <= origin.z && origin.z <= p_max.z)){
      return false;
    }
  }
  else{
    float tznear,tzfar;
    if(dir.z > 0){
      tznear = (p_min.z - origin.z) /dir.z;
      tzfar = (p_max.z - origin.z) /dir.z;
    }
    else if(dir.z < 0){
      tznear = (p_max.z - origin.z) /dir.z;
      tzfar = (p_min.z - origin.z) /dir.z;
    }
    if(tnear < tznear){
      tnear = tznear;
    }
    if(tfar > tzfar){
      tfar = tzfar;
    }
    if(tnear > tfar) return false;
  }
  return true;
};