#include "ObjectInstance.h"
#include "Logger.h"

BaseObject* ObjectInstance::getObject(){ return m_object;};

void ObjectInstance::setObject(BaseObject *o){
  m_object = o;
};

ObjectInstance& ObjectInstance::transform(const Matrix4& M){
  Matrix4 tmp = M;
 // tmp.m_array[12] *= -1;
  trans_pos.x += tmp.m_array[12];
  trans_pos.y += tmp.m_array[13];
  trans_pos.z += tmp.m_array[14];
  tmp.invert();
  inverse_matrix *= tmp;
  return *this;
};
ObjectInstance& ObjectInstance::translate(float x, float y, float z){
  Matrix4 tmp = Matrix4::identity();
  tmp.m_array[12] = x; tmp.m_array[13] = y; tmp.m_array[14] = z;
  trans_pos.x += x;
  trans_pos.y += y;
  trans_pos.z += z;
  tmp.invert();
  inverse_matrix *= tmp;
  return *this;
};
ObjectInstance& ObjectInstance::translate(const Vec3& t){
  Matrix4 tmp = Matrix4::identity();
  tmp.m_array[12] = t.x; tmp.m_array[13] = t.y; tmp.m_array[14] = t.z;
  trans_pos.x += t.x;
  trans_pos.y += t.y;
  trans_pos.z += t.z;
  tmp.invert();
  inverse_matrix *= tmp;
  return *this;
};
ObjectInstance& ObjectInstance::scale(float sx, float sy, float sz){
  Matrix4 tmp = Matrix4::identity();
  Matrix4 tmp1,tmp3;
  Vec3 tmp2 = m_object->getPosition();
  Vec3 t = tmp2 + trans_pos;
  if(sx == 0.0 || sy == 0.0 || sz == 0.0){
    std::cout << "Invalid Size" << std::endl;
    return *this;
  }
  tmp1 = Matrix4::identity();
  tmp1.m_array[12] = -t.x;
  tmp1.m_array[13] = -t.y;
  tmp1.m_array[14] = -t.z;
  tmp1.invert();
  tmp.m_array[0] = sx; tmp.m_array[5] = sy; tmp.m_array[10] = sz;
  tmp.invert();
  tmp3 = Matrix4::identity();
  tmp3.m_array[12] = t.x;
  tmp3.m_array[13] = t.y;
  tmp3.m_array[14] = t.z;
  tmp3.invert();
  inverse_matrix *= tmp1;
  inverse_matrix *= tmp;
  inverse_matrix *= tmp3;

  return *this;
};
ObjectInstance& ObjectInstance::rotate(float angle, float x, float y, float z){
  Vec3 v{x,y,z};
  Quat q{v,angle};
  Matrix4 tmp1,tmp2,tmp3;
  Vec3 tmp = m_object->getPosition();
  Vec3 t = tmp + trans_pos;
  tmp1 = Matrix4::identity();
  tmp1.m_array[12] = -t.x;
  tmp1.m_array[13] = -t.y;
  tmp1.m_array[14] = -t.z;
  tmp1.invert();
  q.toMatrix(tmp2);
  tmp2.invert();
  tmp3 = Matrix4::identity();
  tmp3.m_array[12] = t.x;
  tmp3.m_array[13] = t.y;
  tmp3.m_array[14] = t.z;
  tmp3.invert();

  inverse_matrix *= tmp1;
  inverse_matrix *= tmp2;
  inverse_matrix *= tmp3;
  return *this;
};

bool ObjectInstance::hit(const Ray& r, float tmin, float tmax, HitRec& record) const{
  Vec3 start = r.getStart(); Vec4 o{start.x,start.y,start.z,1.0};
  Vec3 dire = r.getDirection(); Vec4 d{dire.x,dire.y,dire.z,0.0};
  Vec4 o_ = inverse_matrix * o;
  Vec4 d_ = inverse_matrix * d;
  const float norm_d = d_.norm();
  d_.normalize();
  Vec3 start_{o_.x,o_.y,o_.z};
  Vec3 dire_{d_.x,d_.y,d_.z};
  Ray r_{start_,dire_};
  if(m_object->hit(r_,tmin,tmax,record) == true){
    Matrix4 tmp = inverse_matrix; 
    tmp.transpose();
    Vec4 nn{record.n.x,record.n.y,record.n.z,1.0};
    Vec4 n_ = tmp * nn;
    Vec3 new_n{n_.x,n_.y,n_.z};
    new_n.normalize();
    record.t = record.t / norm_d;
    record.n = new_n;
    record.p = r.getPosition(record.t);
    return true;
  }
  return false;
};

bool ObjectInstance::shadowHit(const Ray& r, float tmin, float tmax) const{
  Vec3 start = r.getStart(); Vec4 o{start.x,start.y,start.z,1.0};
  Vec3 dire = r.getDirection(); Vec4 d{dire.x,dire.y,dire.z,0.0};
  Vec4 o_ = inverse_matrix * o;
  Vec4 d_ = inverse_matrix * d;
  const float norm_d = d_.norm();
  d_.normalize();
  Vec3 start_{o_.x,o_.y,o_.z};
  Vec3 dire_{d_.x,d_.y,d_.z};
  Ray r_{start_,dire_};
  if(m_object->shadowHit(r_,tmin,tmax) == true){
    return true;
  }
  return false;
};