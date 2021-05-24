#pragma once

#include "Ray.h"
#include "UniformGrid.h"

class UniformGridTracer 
{
public:
	UniformGridTracer(const Ray &ray, const UniformGrid &grid);

	~UniformGridTracer(){}

	std::vector<BaseObject *> &getCurrentCell() { return m_pGrid->getCell(m_CurrentX, m_CurrentY, m_CurrentZ); }

	bool isInsideGrid() const
	{
		return ( 0 <= m_CurrentX && m_CurrentX < m_pGrid->getNumXCells() &&
			     0 <= m_CurrentY && m_CurrentY < m_pGrid->getNumYCells() &&
				 0 <= m_CurrentZ && m_CurrentZ < m_pGrid->getNumZCells() );
	}

	inline float getNextRayParameter() const { return std::min(m_NextTX, std::min(m_NextTY, m_NextTZ)); }

	void advanceToNext();

	inline int getCurrentCellIndex() const
	{
		return m_CurrentX + m_pGrid->getNumXCells() * (m_CurrentY + m_pGrid->getNumYCells() * m_CurrentZ);
	}

	inline int getCurrentX() const { return m_CurrentX; }
	inline int getCurrentY() const { return m_CurrentY; }
	inline int getCurrentZ() const { return m_CurrentZ; }

	float getCurrentCellTMin() const { return m_CurrentTMin; }
	float getCurrentCellTMax() const { return std::min(m_NextTX, std::min(m_NextTY, m_NextTZ)); }

private:
	UniformGrid *m_pGrid; //バウンディングボックスを表すもの

	int m_CurrentX, m_CurrentY, m_CurrentZ; //トラバーサルを開始するセルのインデックス
	int m_IncrementX, m_IncrementY, m_IncrementZ; 
	//隣接するセルのうち上下左右前後のどの方向に進むかの増分（+1 あるいは-1）
	float m_CurrentTMin;  
	float m_NextTX, m_NextTY, m_NextTZ;  //レイが次に x, y, z の壁とぶつかるときのパラメータ

	float m_DeltaTX, m_DeltaTY, m_DeltaTZ;  //x, y, z 方向のレイが壁とぶつかる間隔

  float xCellSize;
	float yCellSize;
	float zCellSize;

	void calculateNextIntersectionParameters(const Vec3 &pIntersect, const Vec3 &dir, float tStart, float &nextTX, float &nextTY, float &nextTZ) const;

	bool calculateRayBoxIntersection(float &tIntersect, const Ray &ray) const;

};

