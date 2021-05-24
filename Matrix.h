#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <iostream>
#include <cstring>
#include "Vec.h"

float det33(float a00,float a01,float a02,float a10,float a11,float a12,float a20,float a21,float a22);

struct Matrix4{

  float m_array[16];
  //コンストラクタ
  Matrix4(){};
  explicit Matrix4(const float* array){
    std::memcpy(m_array, array, sizeof(float) * 16);
	}
  //コピーコンストラクタ
  Matrix4(const Matrix4& M){
    std::memcpy(m_array, M.m_array, sizeof(float) * 16);
  }
  //デストラクタ
  ~Matrix4(){};

  //転置
  void transpose();
  //行列式
	float det() const;
  //逆行列(余因子で解く)
  void invert();
  //配列のように参照するために(const用とそうでないので)
  inline float& operator() (const int i, const int j){
        return m_array[ j * 4 + i ];
  }
  inline const float operator()(const int i, const int j) const {
        return  m_array[ j * 4 + i ];
  }
  //四則演算系統
  inline Matrix4 operator + (const Matrix4 & M)const {
    Matrix4 A;
    for(int i = 0; i < 16;i++){
      A.m_array[i] = this->m_array[i] + M.m_array[i];
    }
    return A; 
  }
  inline Matrix4 operator - (const Matrix4 & M)const {
    Matrix4 A;
    for(int i = 0; i < 16;i++){
      A.m_array[i] = this->m_array[i] - M.m_array[i];
    }
    return A; 
  }
  inline Matrix4 operator +=(const Matrix4 & M){
    for(int i = 0; i < 16;i++){
      this->m_array[i] +=  M.m_array[i];
    }
    return *this; 
  }
  inline Matrix4 operator -= (const Matrix4 & M){
    for(int i = 0; i < 16;i++){
      this->m_array[i] -= M.m_array[i];
    }
    return *this; 
  }
  //積と商(スカラーと行列)
  inline Matrix4 operator* (const float t) const{
    Matrix4 M;
    for(int i = 0; i < 16;++i) M.m_array[i] = this->m_array[i] * t;
    return M;
  }
  inline Matrix4 operator/ (const float t)const {
    Matrix4 M;
    for(int i = 0; i < 16;++i) M.m_array[i] = this->m_array[i] / t;
    return M;
  }
  //積(行列同士)
  Matrix4 operator* (const Matrix4& u) const;

  //積(行列とベクトル)
  Vec4 operator* (Vec4& v) const;

  //積と商(スカラーと行列)
  inline Matrix4 & operator*=(const float t){
        for(int i = 0; i < 16;++i) m_array[i] *= t;
        return *this;
  }
  inline Matrix4 & operator/=(const float t){
        for(int i = 0; i < 16;++i) m_array[i] /= t;
        return *this;
  }
  //積(行列同士)
  Matrix4 & operator *= (const Matrix4 & u);

  //friend
  //四則演算(スカラーと行列)
  inline friend Matrix4 operator*(const float t, const Matrix4& u){
    Matrix4 M;
    for(int i = 0; i < 16;++i) M.m_array[i] = u.m_array[i] / t;
    return M;
	}

  inline friend Matrix4 operator/(const float t,const Matrix4& u){
    Matrix4 M;
    for(int i = 0; i < 16;++i) M.m_array[i] = u.m_array[i] / t;
    return M;
	}

  //出力
  inline friend std::ostream& operator<<(std::ostream &o, const Matrix4& M){
		return o<<"["<< M.m_array[0] << "," << M.m_array[4] << "," << M.m_array[8] << "," << M.m_array[12]<<"\n " 
    << M.m_array[1] << "," << M.m_array[5] << "," << M.m_array[9] << "," << M.m_array[13]<<"\n " 
    << M.m_array[2] << "," << M.m_array[6] << "," << M.m_array[10] << "," << M.m_array[14]<<"\n " 
    << M.m_array[3] << "," << M.m_array[7] << "," << M.m_array[11] << "," << M.m_array[15]<<"] " ;
	}

  //初期化用
  static Matrix4 identity(void){
    Matrix4 m;
    m.m_array[0] = 1.0f; m.m_array[1] = 0.0; m.m_array[2] = 0.0; m.m_array[3] = 0.0;
    m.m_array[4] = 0.0f; m.m_array[5] = 1.0; m.m_array[6] = 0.0; m.m_array[7] = 0.0;
    m.m_array[8] = 0.0f; m.m_array[9] = 0.0; m.m_array[10] = 1.0; m.m_array[11] = 0.0;
    m.m_array[12] = 0.0f; m.m_array[13] = 0.0; m.m_array[14] = 0.0; m.m_array[15] = 1.0;
    return m;            
  }
};