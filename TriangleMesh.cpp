#include "TriangleMesh.h"

//レイが物体に当たっているかの判定
bool TriangleMesh::hit(const Ray& r, float tmin, float tmax, HitRec& record) const{
  if(!isUniformGrid) return hit_(r,tmin,tmax,record);
  else return uniformHit(r,tmin,tmax,record);
}
bool TriangleMesh::hit_(const Ray& r, float tmin, float tmax, HitRec& record) const{
  record.t = std::numeric_limits<float>::max(); //最大値に設定
  bool isObj = false;
  for(Triangle* tri : triangles){
    HitRec tmpRec;
    bool isHit = tri->hit(r,tmin,tmax,tmpRec);
    if(isHit && record.t > tmpRec.t){
      isObj = true;
      record = tmpRec;
      record.material = material;
    }
  }
  return isObj;
};
bool TriangleMesh::uniformHit(const Ray& r, float tmin, float tmax, HitRec& record) const{
  UniformGridTracer traverser(r, m_Grid);
	bool hitTriangle = false;
  record.t = tmax;
	while ( traverser.isInsideGrid() ){
		const std::vector<BaseObject *>& triangles = traverser.getCurrentCell();

		const float tCellMin = traverser.getCurrentCellTMin();
		const float tCellMax = traverser.getCurrentCellTMax();
    
		for (int ti=0; ti<(int)triangles.size(); ti++){
      HitRec tmpRec;
      bool isHit = triangles[ti]->hit(r,tmin,tmax,tmpRec);  
      if(isHit && record.t > tmpRec.t && tCellMin <= tmpRec.t && tmpRec.t <= tCellMax){
        hitTriangle = true;
        record = tmpRec;
        record.material = material;
      }  
		}

		if (hitTriangle) break;

		traverser.advanceToNext();
	}

	return hitTriangle;
}
//シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
bool TriangleMesh::shadowHit(const Ray& r, float tmin, float tmax) const{
  if(!isUniformGrid) return shadowHit_(r,tmin,tmax);
  else return uniformShadowHit(r,tmin,tmax);
}
bool TriangleMesh::shadowHit_(const Ray& r, float tmin, float tmax) const{
  bool isObj = false;
  for(Triangle* tri : triangles){
    bool isHit = tri->shadowHit(r,tmin,tmax);
    if(isHit){
      isObj = true;
      break;
    }
  }
  return isObj;
};

bool TriangleMesh::uniformShadowHit(const Ray& r, float tmin, float tmax) const{
  UniformGridTracer traverser(r, m_Grid);
	bool hitTriangle = false;
	while ( traverser.isInsideGrid() ){
		const std::vector<BaseObject *>& triangles = traverser.getCurrentCell();
		for (int ti=0; ti<(int)triangles.size(); ti++){
      bool isHit = triangles[ti]->shadowHit(r,tmin,tmax);  
      if(isHit){
        hitTriangle = true;
      }  
		}

		if (hitTriangle) break;

		traverser.advanceToNext();
	}

	return hitTriangle;
}

void TriangleMesh::computeBoundingBox()
{
  boundingBox_min = Vec3{100000.f};
  boundingBox_max = Vec3{-100000.f};
	for (int i=0; i<(int)triangles.size(); i++)
	{

		const Vec3 v0 = triangles[i]->getPos(0);
		const Vec3 v1 = triangles[i]->getPos(1);
		const Vec3 v2 = triangles[i]->getPos(2);

		boundingBox_min.x = std::min(boundingBox_min.x, std::min(v0.x, std::min(v1.x, v2.x)));
		boundingBox_min.y = std::min(boundingBox_min.y, std::min(v0.y, std::min(v1.y, v2.y)));
		boundingBox_min.z = std::min(boundingBox_min.z, std::min(v0.z, std::min(v1.z, v2.z)));

		boundingBox_max.x = std::max(boundingBox_max.x, std::max(v0.x, std::max(v1.x, v2.x)));
		boundingBox_max.y = std::max(boundingBox_max.y, std::max(v0.y, std::max(v1.y, v2.y)));
		boundingBox_max.z = std::max(boundingBox_max.z, std::max(v0.z, std::max(v1.z, v2.z)));
	}	
}

void TriangleMesh::buidGrid(int nXCells, int nYCells, int nZCells)
{
	if ( ! m_Grid.init(boundingBox_min,boundingBox_max, nXCells, nYCells, nZCells) ){
		std::cout << ": grid cannot build" << std::endl;
		return;
	}
	for (int ti=0; ti<(int)triangles.size(); ti++){
		m_Grid.addObject( triangles[ti] );
  }  
}