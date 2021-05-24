#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <iostream>

struct Vec3{
  union{
    struct{
      float x,y,z;
    };
    struct{
      float r,g,b;
    };
  };
  //コンストラクタ
  Vec3(){};
  Vec3(const float in_x, const float in_y,const float in_z)
  :x(in_x),y(in_y),z(in_z) {}
  Vec3(const float t)
  :x(t),y(t),z(t) {}
  //コピーコンストラクタ
  Vec3(const Vec3& v):x(v.x),y(v.y),z(v.z) {}
  //デストラクタ
  ~Vec3(){};
  
  //セッター
  inline void set(const float in_x, const float in_y,const float in_z){
    x = in_x; y = in_y; z = in_z;
  }
  //ゲッター
  inline Vec3 get(void){
    return Vec3{x,y,z};
  }

  //代入演算子
  inline Vec3& operator=(const Vec3 & v){
		x = v.x; y = v.y; z = v.z;
        return *this;
  }
  inline bool operator==(const Vec3 & v) const{
        return (v.x == x && v.y == y && v.z == z);
  }

  //四則演算(ベクトルとベクトル)
  inline  Vec3 operator+(const Vec3& v) const {
		return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
	}
  inline  Vec3 operator-(const Vec3& v) const {
		return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
	}
  inline Vec3 operator - () const {
		return Vec3(-x, -y, -z);
	}
  inline Vec3 operator*(const Vec3& v) const {
		return Vec3(this->x * v.x, this->y * v.y, this->z * v.z);
	}

	inline Vec3 operator/(const Vec3& v) const {
	    return Vec3(this->x / v.x, this->y / v.y, this->z / v.z);
	}
  inline Vec3 & operator+=(const Vec3 & u){
        x += u.x;y += u.y;z += u.z;
        return *this;
  }
  inline Vec3 & operator-=(const Vec3 & u){
        x -= u.x;y -= u.y;z -= u.z;
        return *this;
  }
  inline Vec3 & operator*=(const Vec3 & u){
        x *= u.x;y *= u.y;z *= u.z;
        return *this;
  }
  inline Vec3 & operator/=(const Vec3 & u){
        x /= u.x;y /= u.y;z /= u.z;
        return *this;
  }
  //四則演算(ベクトルとスカラー)
  inline Vec3 operator*(const float t) const{
		return Vec3(this->x * t, this->y * t, this->z * t);
	}
  inline Vec3 & operator*=(const float t){
        x *= t;y *= t;z *= t;
        return *this;
  }
  inline Vec3 operator/(const float t) const{
		return Vec3(this->x / t, this->y / t, this->z / t);
	}
  inline Vec3 & operator/=(const float t){
        x /= t;y /= t;z /= t;
        return *this;
  }
  //内積dot
  inline float dot(const Vec3& v) const{
    return this->x * v.x + this->y * v.y + this->z * v.z;
  }
  //外積cross
  inline Vec3 cross(const Vec3& v) const{
    return Vec3(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);;
  }
  //大きさ(長さ)
  //2乗ノルム
  inline float squareNorm() const{
    return x * x + y * y + z * z;
  }
  //ノルム
  inline float norm() const{
    return sqrtf(squareNorm());
  }
  //正規化
  inline void normalize(){
    float l = norm();
    if(l > 0){
      x /= l; y /= l; z /= l;
    }
  }

  //距離
  //2乗距離
  inline float squareDistance(const Vec3 &v) const{
    return (*this - v).squareNorm();
  }
  //距離
  inline float distance(const Vec3 &v)const{
    return sqrtf(squareDistance(v));
  }
  //角度
  float angle(const Vec3& v) const{
    //外積から|a||b|sinを求める
    Vec3 a = this->cross(v);
    float sin = a.norm();
    //内積から|a||b|cosを求める
    float cos = this->dot(v);
    //atan(sin/cos)で角度を求める
    return fabs(atan2(sin,cos)); 
  }

  //friend
  //四則演算(スカラーとベクトル)
  inline friend Vec3 operator*(const float t, const Vec3& u){
		return Vec3(u.x * t, u.y * t, u.z * t);
	}

  inline friend Vec3 operator/(const float t,const Vec3& u){
		return Vec3(u.x / t, u.y / t, u.z / t);
	}
  //出力
  inline friend std::ostream& operator<<(std::ostream &o, const Vec3& u){
		return o << "(" << u.x << "," << u.y << "," << u.z << ")";
	}

  //クラスメソッド(static)
  //反射ベクトル
  static Vec3 reflect(const Vec3 &in_v, const Vec3 &normal){
    //normalは正規化を前提としているので正規化する.
    Vec3 normal_ = normal;
    normal_.normalize();
    const float _dot = normal_.dot(in_v);
		return in_v - (2*_dot)*normal_;
  }
  //屈折ベクトル(スネルの法則を利用)
  static Vec3 refract(const Vec3 &in_v, const Vec3 &normal, float eta){
    //in_vは正規化を前提としているっぽいので辻褄合わせにこうしている.
    Vec3 in_v_ = in_v;
    float in_norm = in_v.norm();
    in_v_.normalize();
    //normalは正規化を前提としているので正規化する.
    Vec3 normal_ = normal;
    normal_.normalize();
    const float _dot = -normal_.dot(in_v_); //内積
		const float D =_dot*_dot + eta*eta - 1; //判別式
		return (D <= 0.0) 
			? Vec3(0,0,0) // total reflection
			: in_norm*((_dot-sqrtf(D))*normal_ + in_v_) / eta;
	}
};
using Color = Vec3;

struct Vec4{
  float x,y,z,w;
  Vec4(){};
  Vec4(const float in_x, const float in_y,const float in_z,const float in_w)
  :x(in_x),y(in_y),z(in_z),w(in_w){}
  Vec4(const float t)
  :x(t),y(t),z(t),w(t){}
  //コピーコンストラクタ
  Vec4(const Vec4& v):x(v.x),y(v.y),z(v.z),w(v.w){}
  //デストラクタ
  ~Vec4(){};

  //大きさ(長さ)
  //2乗ノルム
  inline float squareNorm() const{
    return x * x + y * y + z * z + w * w;
  }
  //ノルム
  inline float norm() const{
    return sqrtf(squareNorm());
  }
  //正規化
  inline void normalize(){
    float l = norm();
    if(l > 0){
      x /= l; y /= l; z /= l; w /= l;
    }
  }
   //出力
  inline friend std::ostream& operator<<(std::ostream &o, const Vec4& u){
		return o << "(" << u.x << "," << u.y << "," << u.z << ")";
	}

};

struct Vec2{
  float x,y;
  Vec2(){};
  Vec2(const float in_x, const float in_y)
  :x(in_x),y(in_y){}
  Vec2(const float t)
  :x(t),y(t){}
  //コピーコンストラクタ
  Vec2(const Vec2& v):x(v.x),y(v.y){}
  //デストラクタ
  ~Vec2(){};

  //大きさ(長さ)
  //2乗ノルム
  inline float squareNorm() const{
    return x * x + y * y;
  }
  //ノルム
  inline float norm() const{
    return sqrtf(squareNorm());
  }
  //正規化
  inline void normalize(){
    float l = norm();
    if(l > 0){
      x /= l; y /= l;
    }
  }
   //出力
  inline friend std::ostream& operator<<(std::ostream &o, const Vec2& u){
		return o << "(" << u.x << "," << u.y << ")";
	}

};