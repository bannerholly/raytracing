#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <iostream>
#include "vec.h"
#include "matrix.h"

struct Quat{
  float x,y,z,w;

  //コンストラクタ
  Quat(){};
  Quat(const float in_x, const float in_y,const float in_z, const float in_w)
  :x(in_x),y(in_y),z(in_z),w(in_w) {};
  Quat(Vec3 & v,float angle);
  Quat(Matrix4& m);
  //コピーコンストラクタ
  Quat(const Quat& q)
  :x(q.x),y(q.y),z(q.z),w(q.w) {}
  //デストラクタ
  ~Quat(){};

  //代入演算子
  inline Quat& operator=(const Quat& q){
		x = q.x; y = q.y; z = q.z; w = q.w;
		return *this;
	}
  inline bool operator ==(const Quat& q) const{
		return (q.x == x && q.y == y && q.z == z && q.w == w);
	}
   
  //四則演算
  inline Quat operator-(){
		return Quat(-x, -y, -z, -w);
	}
  Quat operator*(const Quat& q);
  Quat& operator*=(const Quat& q);

  //大きさ
  //2乗ノルム
  inline float squareNorm() const {
		return x*x + y*y + z*z + w*w;
	}
  //ノルム
  inline float norm() const {
		return sqrtf(x*x + y*y + z*z + w*w);
	}
  //正規化
  inline void normalize(){
    const float l = norm();
    if(l > 0){
      x /= l; y /= l; z /= l; w /= l;
    }
  }
  
  //共役
  inline Quat inverse(void){
    return Quat(-x, -y, -z, w);
  }
  //クォータリオンから回転行列
  void toMatrix(Matrix4& m);

  //回転行列からクォータリオン
  void fromMatrix(Matrix4& m);

  //出力
  inline friend std::ostream& operator<<(std::ostream &o, const Quat& q){
		return o << "(" << q.x << "," << q.y << "," << q.z << "," << q.w << ")";
	}
  //void from4x4Matrix(const float M[16]);
}; 