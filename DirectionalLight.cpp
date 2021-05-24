#include "DirectionalLight.h"

#include "Vec.h"
#include <limits>

Color DirectionalLight::getLightColor(Vec3& pos) const{
  return l_color;
}

Vec3 DirectionalLight::getInLight(Vec3& point){
  Vec3 c = dir;
  c.normalize();
  return c;
}

float DirectionalLight::getLightDistance(Vec3& pos){
  return std::numeric_limits<float>::max();
}