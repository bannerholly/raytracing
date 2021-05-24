#include "Scene.h"
#include <iostream>
#include "Camera.h"
#include "Logger.h"
#include "cstdio"
extern Camera m_camera; //viewのシーンのはず

//オブジェクトの追加
void Scene::addObject(BaseObject *o){
  objects.push_back(o);
  o->shaprePoint();
}

//発光オブジェクトの追加
void Scene::addEmit(BaseObject* o){
  emittions.push_back(o);
  addObject(o);
  o->shaprePoint();
}

//ライトの追加
void Scene::addLight(BaseLight *l){
  lights.push_back(l);
}

int width;
int height;

void Scene::draw(){
  render();
  //glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(width , height , GL_RGB ,GL_FLOAT,data->getData());
//	glFlush();
}
void Scene::render(){
  Vec3 eye = m_camera.getPosition(); //カメラの始点
  Vec3 u, v, w; //カメラの直行基底ベクトル (u:x,v:y,w:z)
  m_camera.getCameraOrthogonalBasis(u,v,w);
  width = m_camera.getWindowWidth();
  height = m_camera.getWindowHeight();
  data = new Image(width,height);
  float screen_distance = m_camera.getScreenDistance();

  for(int y = 0; y < height;y++){
    for(int x = 0; x < width;x++){
      //中心を原点となるように調整
      Vec3 dir = (x-width/2.0f)*u + (y-height/2.0f)*v - screen_distance*w;
      dir.normalize(); //正規化
      Ray ray{eye,dir};
      Vec3 color = tracer.trace(ray);
      //色を打つ
      float xx,yy;
      xx = (x-width/2.0f)*(2.0f/width);
      yy = (y-height/2.0f)*(2.0f/height);
      data->setPixel(x,y,color); 
    }
  }
}

void Scene::saveImage(const char* filename,bool isPNG){
  if(isPNG){
    if(!im_io.pngImageWrite(filename,data)){
      std::cout << "save failed" << std::endl;
    }
    else{
      std::cout << "save success" << std::endl;
    }
  }
  else{
    if(!im_io.jpegImageWrite(filename,data)){
      std::cout << "save failed" << std::endl;
    }
    else{
      std::cout << "save success" << std::endl;
    }
  }
}