#include "Quat.h"
#include "Logger.h"
float sgn(float x){
if(x >= 0) return 1.0;
return -1.0;
}

Quat::Quat(Vec3 & v,float angle){
  const float l = v.norm();
  float scale;
  //長さが0だと正規化できんので
  if(l > 0){
    scale = sinf(angle/2)/l;
    x = scale * v.x;
    y = scale * v.y;
    z = scale * v.z;
    w = cosf(angle/2);
  }
}

Quat::Quat(Matrix4& m){
  fromMatrix(m);  
}

Quat Quat::operator *(const Quat& q){
		const float _x = w * q.x + x * q.w + y * q.z - z * q.y;
		const float _y = w * q.y + y * q.w + z * q.x - x * q.z;
		const float _z = w * q.z + z * q.w + x * q.y - y * q.x;
		const float _w = w * q.w - x * q.x - y * q.y - z * q.z;
		return Quat(_x,_y,_z,_w);
	}

Quat& Quat::operator*=(const Quat& q){
		const float _x = w * q.x + x * q.w + y * q.z - z * q.y;
		const float _y = w * q.y + y * q.w + z * q.x - x * q.z;
		const float _z = w * q.z + z * q.w + x * q.y - y * q.x;
		const float _w = w * q.w - x * q.x - y * q.y - z * q.z;
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		return *this;
}

void Quat::toMatrix(Matrix4& M){
  const float s = 2.0f/norm();
  M.m_array[0] = 1 - s*(y*y+z*z);
  M.m_array[1] = s*(x*y+w*z);
  M.m_array[2] = s*(z*x-y*w);
  M.m_array[3] = 0.0;
  M.m_array[4] = s*(x*y-z*w);
  M.m_array[5] = 1 - s*(z*z + x*x);
  M.m_array[6] = s*(y*z+x*w);
  M.m_array[7] = 0.0;
  M.m_array[8] = s*(z*x+y*w);
  M.m_array[9] = s*(y*z-x*w);
  M.m_array[10] = 1 - s*(x*x + y*y);
  M.m_array[11] = 0.0;
  M.m_array[12] = 0.0;
  M.m_array[13] = 0.0;
  M.m_array[14] = 0.0;
  M.m_array[15] = 1.0;
}

void Quat::fromMatrix(Matrix4& M){
  Quat q;
  float m11 = M.m_array[0],m22 = M.m_array[5],m33 = M.m_array[10];
  //0:w^2, 1:x^2, 2:y^2, 3:z^2
  float tmp[4] = {(m11 + m22 + m33 + (float)1.0)/(float)4.0,( m11 - m22 - m33 + (float)1.0)/(float)4.0,
         (-m11 + m22 - m33 + (float)1.0)/(float)4.0,(-m11 - m22 + m33 + (float)1.0)/(float)4.0};
  //√とってる
  for(int i = 0; i < 4;++i){
    if(tmp[i] < 0) tmp[i] = 0;
    tmp[i] = sqrtf(tmp[i]);
  }
  //最大値を求める
  float r = tmp[0];
  int index = 0;
  for(int i = 1; i < 4;++i){
    if(r < tmp[i]){
      r = tmp[i]; index = i; 
    }
  }
  float scale = 1/(4*r);
  //最大値のインデックスを元に求める
  if(index == 0){
    //w
    tmp[1] = scale*(M.m_array[6] -M.m_array[9]);
    tmp[2] = scale*(M.m_array[8] -M.m_array[2]);
    tmp[3] = scale*(M.m_array[1] -M.m_array[4]);
  }
  else if(index == 1){
    //x
    tmp[0] = scale*(M.m_array[6] -M.m_array[9]);
    tmp[2] = scale*(M.m_array[1] + M.m_array[4]);
    tmp[3] = scale*(M.m_array[8] + M.m_array[2]);
  }
  else if(index == 2){
    //y
    tmp[0] = scale*(M.m_array[8] -M.m_array[2]);;
    tmp[1] = scale*(M.m_array[1] + M.m_array[4]);
    tmp[3] = scale*(M.m_array[6] + M.m_array[9]);
  }
  else{
    //z
    tmp[0] = scale*(M.m_array[1] - M.m_array[4]);
    tmp[1] = scale*(M.m_array[8] + M.m_array[2]);
    tmp[2] = scale*(M.m_array[6] + M.m_array[9]);
  }
  x = tmp[1]; y = tmp[2]; z = tmp[3]; w = tmp[0];
}
