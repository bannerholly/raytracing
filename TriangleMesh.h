#pragma once

#include "Triangle.h"
#include "UniformGrid.h"
#include "UniformGridTracer.h"
#include <vector>
#include <limits>

class TriangleMesh : public BaseObject{
  public:
    //コンストラクタ
    TriangleMesh()
    :BaseObject(Vec3{0.0},new Material{}),isUniformGrid(false){};
    //デストラクタ
    ~TriangleMesh(){
     // for (Triangle o :triangles){
     //   if(o != nullptr){
      //    delete o;
      //  }
      //}
    };
    //レイが物体に当たっているかの判定
    bool hit(const Ray& r, float tmin, float tmax, HitRec& record) const;
    bool hit_(const Ray& r, float tmin, float tmax, HitRec& record) const;
    bool uniformHit(const Ray& r, float tmin, float tmax, HitRec& record) const;
    //シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
	  bool shadowHit(const Ray& r, float tmin, float tmax) const;
    bool shadowHit_(const Ray& r, float tmin, float tmax) const;
    bool uniformShadowHit(const Ray& r, float tmin, float tmax) const;

    inline void addTriangle(Triangle* t) {
      triangles.push_back(t);
    }
    inline void setTriangles(int i,Triangle* t){ triangles[i] = t;}

    void setBoundingBoxMin(const Vec3 &p) { boundingBox_min =  p; }
	  void setBoundingBoxMax(const Vec3 &p) { boundingBox_max =  p; }

	  Vec3 getBoundingBoxMin() const { return boundingBox_min; }
	  Vec3 getBoundingBoxMax() const { return boundingBox_max; }

    const std::vector<Triangle*>& getTriangles() const { return triangles; }
	  std::vector<Triangle*>& getTriangles() { return triangles; }

    //on/off
    void onUniformGrid(){ isUniformGrid = true;}
    void offUniformGrid() { isUniformGrid = false;}

    void computeBoundingBox();
    
    void buidGrid(int nXCells, int nYCells, int nZCells);
  private:
    std::vector<Triangle*> triangles; //三角形のポリゴンの集合

    Vec3 boundingBox_min;
    Vec3 boundingBox_max;

    UniformGrid m_Grid;
    bool isUniformGrid; //ユニフォームグリッドでレイトレするかどうか
};