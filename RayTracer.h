#pragma once

#include "vec.h"
#include "Ray.h"

class RayTracer{
  public:
    static int max_depth;
    //コンストラクタ
    RayTracer(){};
    //デストラクタ
    ~RayTracer(){};
    Vec3 trace(const Ray &ray);
    Vec3 traceRec(const Ray& ray, int depth);
  private:
};