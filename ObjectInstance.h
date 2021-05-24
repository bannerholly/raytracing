#pragma once

#include "BaseObject.h"
#include "Matrix.h"
#include "Quat.h"
//オブジェクトに対して幾何学変換を施して座標変換するためのクラス
//(同じ実体(BaseObject)に対して別々の変換が施せるようにこのようにした)

class ObjectInstance : public BaseObject{
  public:
    //コンストラクタ
    ObjectInstance()
		: m_object(nullptr), inverse_matrix(Matrix4::identity()),trans_pos(Vec3{0.0}){};
    ObjectInstance(BaseObject* o)
		: m_object(o), inverse_matrix(Matrix4::identity()),trans_pos(Vec3{0.0}){};
    //デストラクタ
    ~ObjectInstance(){
      if(m_object != nullptr){
        //Logger::logClass(this);
        if(m_object->releaseOK()){
          delete m_object;
        }
      }
    }

    //share関連
    void shaprePoint(){
      m_object->shaprePoint();
      BaseObject::shaprePoint();
    }
    //レイが物体に当たっているかの判定
    bool hit(const Ray& r, float tmin, float tmax, HitRec& record) const;
    //シャドウレイ(レイの交点から光源にレイを飛ばしたもの)が他の物体に当たるかどうかの判定
	  bool shadowHit(const Ray& r, float tmin, float tmax) const;

    BaseObject* getObject();
	  void setObject(BaseObject *o);
    ObjectInstance& transform(const Matrix4& M);
	  ObjectInstance& translate(float x, float y, float z);
	  ObjectInstance& translate(const Vec3& t);
	  ObjectInstance& scale(float sx, float sy, float sz);
	  ObjectInstance& rotate(float angle, float x, float y, float z);


  private:
    BaseObject* m_object; //オブジェクトの実体のアドレス
    Matrix4 inverse_matrix; //変換行列の逆行列
    Vec3 trans_pos; //移動した座標
};