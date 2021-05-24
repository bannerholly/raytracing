#include "matrix.h"

float det33(float a00,float a01,float a02,float a10,float a11,float a12,float a20,float a21,float a22){
  //サラスの公式
  float plus = (a00*a11*a22)+(a01*a12*a20)+(a02*a10*a21);
  float minus = (a02*a11*a20)+(a01*a10*a22)+(a00*a12*a21);
  return plus-minus;
}

void Matrix4::transpose(){
  float tmp;
  tmp = m_array[1]; m_array[1] = m_array[4];m_array[4] = tmp;
  tmp = m_array[2]; m_array[2] = m_array[8];m_array[8] = tmp;
  tmp = m_array[3]; m_array[3] = m_array[12];m_array[12] = tmp;
  tmp = m_array[6]; m_array[6] = m_array[9];m_array[9] = tmp;
  tmp = m_array[7]; m_array[7] = m_array[13];m_array[13] = tmp;
  tmp = m_array[11]; m_array[11] = m_array[14];m_array[14] = tmp;
}

float Matrix4::det() const{
  float a00 = m_array[0]*det33(m_array[5],m_array[9],m_array[13],
                               m_array[6],m_array[10],m_array[14],
                               m_array[7],m_array[11],m_array[15]
                              );
  float a01 = m_array[4]*det33(m_array[1],m_array[9],m_array[13],
                               m_array[2],m_array[10],m_array[14],
                               m_array[3],m_array[11],m_array[15]
                              );
  float a02 = m_array[8]*det33(m_array[1],m_array[5],m_array[13],
                               m_array[2],m_array[6],m_array[14],
                               m_array[3],m_array[7],m_array[15]
                              );
  float a03 = m_array[12]*det33(m_array[1],m_array[5],m_array[9],
                               m_array[2],m_array[6],m_array[10],
                               m_array[3],m_array[7],m_array[11]
                              );                 
  return a00-a01+a02-a03;
}

void Matrix4::invert(){
  Matrix4 tmp;
  tmp.m_array[0] = det33(m_array[5],m_array[9],m_array[13],m_array[6],m_array[10],m_array[14],
                               m_array[7],m_array[11],m_array[15]);
  tmp.m_array[1] = -det33(m_array[4],m_array[8],m_array[12],m_array[6],m_array[10],m_array[14],
                               m_array[7],m_array[11],m_array[15]);
  tmp.m_array[2] = det33(m_array[4],m_array[8],m_array[12],m_array[5],m_array[9],m_array[13],
                               m_array[7],m_array[11],m_array[15]);                                           
  tmp.m_array[3] = -det33(m_array[4],m_array[8],m_array[12],m_array[5],m_array[9],m_array[13],
                               m_array[6],m_array[10],m_array[14]);                           
  tmp.m_array[4] = -det33(m_array[1],m_array[9],m_array[13],m_array[2],m_array[10],m_array[14],
                               m_array[3],m_array[11],m_array[15]);
  tmp.m_array[5] = det33(m_array[0],m_array[8],m_array[12],m_array[2],m_array[10],m_array[14],
                               m_array[3],m_array[11],m_array[15]);
  tmp.m_array[6] = -det33(m_array[0],m_array[8],m_array[12],m_array[1],m_array[9],m_array[13],
                               m_array[3],m_array[11],m_array[15]);                                           
  tmp.m_array[7] = det33(m_array[0],m_array[8],m_array[12],m_array[1],m_array[9],m_array[13],
                               m_array[2],m_array[10],m_array[14]);                                     
  tmp.m_array[8] = det33(m_array[1],m_array[5],m_array[13],m_array[2],m_array[6],m_array[14],
                               m_array[3],m_array[7],m_array[15]);
  tmp.m_array[9] = -det33(m_array[0],m_array[4],m_array[12],m_array[2],m_array[6],m_array[14],
                               m_array[3],m_array[7],m_array[15]);
  tmp.m_array[10] = det33(m_array[0],m_array[4],m_array[12],m_array[1],m_array[5],m_array[13],
                               m_array[3],m_array[7],m_array[15]);                                           
  tmp.m_array[11] = -det33(m_array[0],m_array[4],m_array[12],m_array[1],m_array[5],m_array[13],
                               m_array[2],m_array[6],m_array[14]);          
  tmp.m_array[12] = -det33(m_array[1],m_array[5],m_array[9],m_array[2],m_array[6],m_array[10],
                               m_array[3],m_array[7],m_array[11]);
  tmp.m_array[13] = det33(m_array[0],m_array[4],m_array[8],m_array[2],m_array[6],m_array[10],
                               m_array[3],m_array[7],m_array[11]);
  tmp.m_array[14] = -det33(m_array[0],m_array[4],m_array[8],m_array[1],m_array[5],m_array[9],
                               m_array[3],m_array[7],m_array[11]);                                           
  tmp.m_array[15] = det33(m_array[0],m_array[4],m_array[8],m_array[1],m_array[5],m_array[9],
                               m_array[2],m_array[6],m_array[10]); 

  const float det_tmp = m_array[0]*tmp.m_array[0] + m_array[4]*tmp.m_array[4]
                        + m_array[8]*tmp.m_array[8] +m_array[12]*tmp.m_array[12];
  //行列式が0だと逆行列は存在しないため
  if(det_tmp != 0){
    tmp /= det_tmp;
    tmp.transpose();
    *this = tmp;
  }                    
}

Matrix4  Matrix4::operator * (const Matrix4& u)const{
  Matrix4 M;
  for(int i = 0; i < 4;++i){
    for(int j = 0;j < 4;++j){
      M(i,j) = 0;
      for(int k = 0; k < 4;++k){
        M(i,j) += (*this)(i,k)*u(k,j);
      }
    }
  }
  return M;
}

//積(行列とベクトル)
Vec4 Matrix4::operator* (Vec4& v) const{
  Vec4 tmp;
  tmp.x = m_array[0]*v.x + m_array[4]*v.y+ m_array[8]*v.z+ m_array[12]*v.w;
  tmp.y = m_array[1]*v.x + m_array[5]*v.y+ m_array[9]*v.z+ m_array[13]*v.w;
  tmp.z = m_array[2]*v.x + m_array[6]*v.y+ m_array[10]*v.z+ m_array[14]*v.w;
  tmp.w = m_array[3]*v.x + m_array[7]*v.y+ m_array[11]*v.z+ m_array[15]*v.w;
  return tmp;
}

Matrix4 & Matrix4::operator *= (const Matrix4& u){
  Matrix4 tmp;
  tmp = *this;
  *this = tmp * u;
  return *this;
}