#pragma once

#include "BaseObject.h"
#include "BaseLight.h"
//#include "Sphere.h"
#include "Plane.h"
#include "RayTracer.h"
#include "Image.h"
#include "ImageIO.h"
#include <iostream>
#include <GL/glut.h>
#include <vector> //オブジェクトとか光源をベクターでまとめて管理する方式(Compositeパターンにする?)
class Scene{
  public:
    //コンストラクタ
    Scene():data(new Image(320,240))
    {};
    //デストラクタ
    ~Scene(){
      for (BaseObject* o :objects){
        if(o != nullptr){
          if(o->releaseOK()){
            delete o;
          }
        }
      }
      objects.clear();
      for (BaseLight* l :lights){
        if(l != nullptr){
         // free(l);
          delete l;
        }
      }
      lights.clear();
      for(BaseObject* e: emittions){
        if(e != nullptr){
          if(e->releaseOK()){
            //free(e);
            delete e;
          }
        }
      } 
      emittions.clear();

      if(data != nullptr){
        delete data;
      }
    };
    //オブジェクトの追加
    void addObject(BaseObject *o);
    //オブジェクトのゲッター
    std::vector<BaseObject*>* getObject() { return &objects;}

    //発光オブジェクトの追加
    void addEmit(BaseObject* o);
    //発光オブジェクトのゲッター
    std::vector<BaseObject*>* getEmit() { return &emittions;}

    //ライトの追加
    void addLight(BaseLight *l);
    //ライトのゲッター
    std::vector<BaseLight*>* getLight() { return &lights;}

    //シーンの描画
    void draw();
    //レイトレのレンダリング
    void render();
    //背景色のセッターとゲッター
    inline void setBackgroundColor(Vec3& c){
      glClearColor(c.r, c.g, c.b, 1.0f); //背景色のセット
      background_color = c;

    }
    inline Vec3 getBackgroundColor(){
      return background_color;
    } 
    void saveImage(const char* filename,bool isPNG);
  private:
	  std::vector<BaseLight *> lights; //光源のベクター
	  std::vector<BaseObject *> objects; //物体のベクター
    std::vector<BaseObject *> emittions; //発光オブジェクトのベクター

    Vec3 background_color; //背景色<--多分初期時のやつかな
    RayTracer tracer; //レイトレ―スするやつ
    ImageIO im_io;
    Image* data;
};