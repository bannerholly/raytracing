#pragma once

#include "BaseObject.h"

class Triangle :public BaseObject{
  public:
    //コンストラクタ
    Triangle():BaseObject{Vec3{0.0},new Material()}
    {};
    Triangle(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2)
    :BaseObject((v0+v1+v2)/3,new Material{}),t_pos{v0,v1,v2}{
      //count++;
    };
    Triangle(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2,Material* m)
    :BaseObject((v0+v1+v2)/3,m),t_pos{v0,v1,v2}{
     // count++;
    };
    //コピーコンストラクタ
    Triangle(const Triangle& tri)
    :BaseObject(tri.o_pos,tri.material),
     t_pos{tri.t_pos[0],tri.t_pos[1],tri.t_pos[2]}{
      // count++;
     }
    //デストラクタ
    ~Triangle(){
    //  Logger::logClass(this);
      for (int i=0; i<(int)children.size(); i++)
			  delete children[i];
      children.clear();
    };

    //レイが物体に当たっているかの判定
    bool hit(const Ray &r, float tmin, float tmax, HitRec& record) const;
    //シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
	  bool shadowHit(const Ray &r, float tmin, float tmax) const;
     //ゲッター
    inline Vec3 getPos(int i)const{
      return t_pos[i];
    }
    //座標からテクスチャ座標を別の方法で割り出す(基本はUV)
    Vec3 getTexPos_(float b,float c) const;    
    inline Vec3 getNormal()const{
      Vec3 v10 = t_pos[1] - t_pos[0];
      Vec3 v20 = t_pos[2] - t_pos[0];
      Vec3 cross = v10.cross(v20);
      cross.normalize();
      return cross; 
    }
    Vec3 getTexPos(Vec3& pos) const;

    Vec3 getBoundingBoxMin() const {
		  const float x = std::min( t_pos[0].x, std::min(t_pos[1].x, t_pos[2].x));
		  const float y = std::min( t_pos[0].y, std::min(t_pos[1].y, t_pos[2].y));
		  const float z = std::min( t_pos[0].z, std::min(t_pos[1].z, t_pos[2].z));
		  return Vec3(x,y,z);
	  }
	
	  Vec3 getBoundingBoxMax() const{
		  const float x = std::max( t_pos[0].x, std::max(t_pos[1].x, t_pos[2].x));
		  const float y = std::max( t_pos[0].y, std::max(t_pos[1].y, t_pos[2].y));
		  const float z = std::max( t_pos[0].z, std::max(t_pos[1].z, t_pos[2].z));
		  return Vec3(x,y,z);
	  }
    //セッター
    inline void setPos(Vec3& a,Vec3& b,Vec3& c){
      t_pos[0] = a; t_pos[1] = b; t_pos[2] = c;
      Vec3 tmp = (a+b+c)/3;
      setPosition(tmp);
    }
    inline void setNormal(Vec3& a,Vec3& b,Vec3& c){
      t_normal[0] = a; t_normal[1] = b; t_normal[2] = c;
    }


  //int count = 0;
  private:
    Vec3 t_pos[3]; //三角形の頂点座標
    Vec3 t_normal[3]; //各頂点の法線ベクトル
};