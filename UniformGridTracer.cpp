#include <iostream>
#include <limits>
#include <cmath>
#include "UniformGridTracer.h"


UniformGridTracer::UniformGridTracer(const Ray &ray, const UniformGrid &grid)
: m_pGrid(const_cast<UniformGrid *>(&grid))
{
	const Vec3 &p = ray.getStart();
	const Vec3 &d = ray.getDirection();
  xCellSize = m_pGrid->getXCellSize();
	yCellSize = m_pGrid->getYCellSize();
	zCellSize = m_pGrid->getZCellSize();
  m_IncrementX = (d.x > 0.0) ? 1 :-1;
  m_IncrementY = (d.y > 0.0) ? 1 :-1;
  m_IncrementZ = (d.z > 0.0) ? 1 :-1;
  m_DeltaTX = xCellSize / fabs(d.x);
  m_DeltaTY = yCellSize / fabs(d.y);
  m_DeltaTZ = zCellSize / fabs(d.z);
  
	if ( m_pGrid->isInside(p) )	//視点がグリッドの中の場合
	{
		m_CurrentTMin = 0.f;
		m_pGrid->getIndex(p, m_CurrentX, m_CurrentY, m_CurrentZ);
		calculateNextIntersectionParameters(p, d, m_CurrentTMin, m_NextTX, m_NextTY, m_NextTZ);
	}
	else	//視点がグリッドの外の場合
	{
		float tIntersect; //t_inのことグリッドの最初のパラメータ

		//バウンディングと交差があったかどうか
		if ( calculateRayBoxIntersection(tIntersect, ray) )
		{
			m_CurrentTMin = tIntersect;
			const Vec3 pIntersect = ray.getPosition( tIntersect );

			m_pGrid->getIndex(pIntersect, m_CurrentX, m_CurrentY, m_CurrentZ);
			calculateNextIntersectionParameters(pIntersect, d, m_CurrentTMin, m_NextTX, m_NextTY, m_NextTZ);
		}
		else	//バウンディングと交差がなかったら何もしない
		{
			m_CurrentTMin = 0.f;
			m_CurrentX = m_CurrentY = m_CurrentZ = -1;
			return;
		}
	}
}

void UniformGridTracer::advanceToNext()
{
	if (m_NextTX < m_NextTY && m_NextTX < m_NextTZ)	// m_NextTX is the smallest
	{
		m_CurrentTMin = m_NextTX;
		m_NextTX += m_DeltaTX;
		m_CurrentX += m_IncrementX;
	}
	else if (m_NextTY < m_NextTZ)	// m_NextTY is the smallest
	{
		m_CurrentTMin = m_NextTY;
		m_NextTY += m_DeltaTY;
		m_CurrentY += m_IncrementY;
	}
	else		// m_NextTZ is the smallest
	{
		m_CurrentTMin = m_NextTZ;
		m_NextTZ += m_DeltaTZ;
		m_CurrentZ += m_IncrementZ;
	}
}

void UniformGridTracer::calculateNextIntersectionParameters(const Vec3 &pIntersect, const Vec3 &dir, float tStart, float &nextTX, float &nextTY, float &nextTZ) const
{
	const Vec3 bboxMin = m_pGrid->getBboxMin();
	const Vec3 bboxMax = m_pGrid->getBboxMax();
  //x
  if(dir.x == 0) nextTX = std::numeric_limits<float>::max();
  else{
    float deltaX;
    if(dir.x > 0){
      float l = pIntersect.x - bboxMin.x;
      l =  fmodf(l,xCellSize);
      deltaX = xCellSize - l;
    }
    else if(dir.x < 0){
      float r =  bboxMax.x - pIntersect.x;
      r =  fmodf(r,xCellSize);
      deltaX = xCellSize - r;
    }
    nextTX = tStart + deltaX/fabs(dir.x);
  }
  //y
  if(dir.y == 0) nextTY = std::numeric_limits<float>::max();
  else{
    float deltaY;
    if(dir.y > 0){
      float l = pIntersect.y - bboxMin.y;
      l =  fmodf(l,yCellSize);
      deltaY = yCellSize - l;
    }
    else if(dir.y < 0){
      float r =  bboxMax.y - pIntersect.y;
      r =  fmodf(r,yCellSize);
      deltaY = yCellSize - r;
    }
    nextTY = tStart + deltaY/fabs(dir.y);
  }
  //z
  if(dir.z == 0) nextTZ = std::numeric_limits<float>::max();
  else{
    float deltaZ;
    if(dir.z > 0){
      float l = pIntersect.z - bboxMin.z;
      l =  fmodf(l,zCellSize);
      deltaZ = zCellSize - l;
    }
    else if(dir.z < 0){
      float r =  bboxMax.z - pIntersect.z;
      r =  fmodf(r,zCellSize);
      deltaZ = zCellSize - r;
    }
    nextTZ = tStart + deltaZ/fabs(dir.z);
  }
}

bool UniformGridTracer::calculateRayBoxIntersection(float &tIntersect, const Ray &r) const{

  Vec3 p_min = m_pGrid->getBboxMin();
  Vec3 p_max = m_pGrid->getBboxMax();
  float tnear = 0.0;
  float tfar = std::numeric_limits<float>::max();
  float t;
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
      t = txnear;
    }
    if(tfar > txfar){
      //内部に視点があった場合
      if(txnear < 0){
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
    }
    else if(dir.y < 0){
      tynear = (p_max.y - origin.y) /dir.y;
      tyfar = (p_min.y - origin.y) /dir.y;
    }
    if(tnear < tynear){
      tnear = tynear;
      t = tynear;
    }
    if(tfar > tyfar){
      //内部に視点があった場合
      if(tynear < 0){
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
    }
    else if(dir.z < 0){
      tznear = (p_max.z - origin.z) /dir.z;
      tzfar = (p_min.z - origin.z) /dir.z;
    }
    if(tnear < tznear){
      tnear = tznear;
      t = tznear;
    }
    if(tfar > tzfar){
      //内部に視点があった場合
      if(tznear < 0){
        t = tzfar;
      }
      tfar = tzfar;
    }
    if(tnear > tfar) return false;
  }
  tIntersect = t;
  return true;
}