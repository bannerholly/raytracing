#pragma once

#include <vector>
#include "Vec.h"
#include "BaseObject.h"

class UniformGrid{
  public:
    UniformGrid()
		: m_cells(nullptr){}

	  ~UniformGrid(){
		  if (m_cells == nullptr) delete [] m_cells;
	  }
	  void clear(){
		  if (m_cells) delete [] m_cells;
		  m_cells = nullptr;
	  }

    bool init( const Vec3 &bboxMin, const Vec3 &bboxMax, int nXCells, int nYCells, int nZCells );

	  void addObject( const BaseObject *o );

    //ゲッター
	  float getXCellSize() const { return m_deltax; }
	  float getYCellSize() const { return m_deltay; }
	  float getZCellSize() const { return m_deltaz; }

	  int getNumXCells() const { return num_xcells; }
	  int getNumYCells() const { return num_ycells; }
	  int getNumZCells() const { return num_zcells; }

	  inline std::vector<BaseObject *> &getCell(int xi, int yi, int zi) const {
		  return m_cells[xi + num_xcells*(yi+num_ycells*zi)];
	  }
    
	  inline std::vector<BaseObject* > &getCell(int xi, int yi, int zi){
		  return m_cells[xi + num_xcells*(yi+num_ycells*zi)];
	  }

	  inline void getIndex(const Vec3 &p, int &xi, int &yi, int &zi){
		  const Vec3 P = p - over_box_min;
		  xi = std::max(0, std::min((int)floorf(P.x/m_deltax), num_xcells-1));
		  yi = std::max(0, std::min((int)floorf(P.y/m_deltay), num_ycells-1));
		  zi = std::max(0, std::min((int)floorf(P.z/m_deltaz), num_zcells-1));
	  }

	  Vec3 getBboxMin() const { return over_box_min; }
	  Vec3 getBboxMax() const { return over_box_max; }

	  bool isInside(const Vec3 &p) const{
		  return (over_box_min.x <= p.x && p.x <= over_box_max.x &&
				      over_box_min.y <= p.y && p.y <= over_box_max.y &&
				      over_box_min.z <= p.z && p.z <= over_box_max.z );
    }


  private:
    int clampInt(int x, int y, int z){
	    return std::max(x, std::min(y,z));
    }
    int num_xcells, num_ycells, num_zcells; //各軸においてのセル数
	  Vec3 over_box_min, over_box_max; //全体のボックスの端っこ？
	  float m_deltax, m_deltay, m_deltaz; //1つあたりのセルの大きさ
	  std::vector<BaseObject *> *m_cells; //グリッド内の各セル(登録するオブジェクトのベクターの配列)
};