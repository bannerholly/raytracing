#include "AmbientLight.h"
#include "Logger.h"

Color AmbientLight::getLightColor(Vec3& pos) const{
  return l_color;
}