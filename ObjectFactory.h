#pragma once

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Triangle.h"
#include "ObjectInstance.h"

class ObjectFactry{
  public:
    //コンストラクタ
    ObjectFactry(){};
    //デストラクタ
    ~ObjectFactry(){};
    //生成メソッド
    Sphere* createSphere(Vec3& _center, float r){
		  Sphere *obj = new Sphere(_center, r);
		  return obj;
	  }
    Plane* createPlane(Vec3& _center,float w,float h,Vec3 wn,Vec3 hn){
		  Plane *obj = new Plane(_center, w,h,wn,hn);
		  return obj;
	  }
    Box* createBox(const Vec3 &v1, const Vec3 &v2){
      Box* obj = new Box(v1,v2);
      return obj;
    }
    Box* createBox(const Vec3 &v1,float x,float y,float z){
      Box* obj = new Box(v1,x,y,z);
      return obj;
    }
    Triangle* createTriangle(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2){
		  Triangle *obj = new Triangle(v0,v1,v2);
		  return obj;
	  }
    ObjectInstance* createObjectInstance(BaseObject* b){
      ObjectInstance *obj = new ObjectInstance(b);
      return obj;
    }

};