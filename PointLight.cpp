#include "PointLight.h"
#include "Logger.h"
Color PointLight::getLightColor(Vec3& pos) const{
  Vec3 diff = l_pos - pos;
  float r = diff.norm();
  r *= r;
  Color c = 10000*l_color /r;
  return c;
}

Vec3 PointLight::getInLight(Vec3& pos){
  Vec3 diff = pos - l_pos;
  diff.normalize();
  return diff;
}

float PointLight::getLightDistance(Vec3& pos){
  Vec3 diff = l_pos - pos;
  float r = diff.norm();
  return r;
}