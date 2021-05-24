#include "Camera.h"
#include "Logger.h"

//初期の視野変換するための位置と姿勢を求める
void Camera::setLookAt(Vec3& e,Vec3& t,Vec3& u){
  c_position = e;
  //e:視点(eye),t:目標点(target),u:上方向(up)
  Vec3 et = e-t; //視点から目標点までのベクトル(z)
  et.normalize(); //正規化
  Vec3 side = u.cross(et); //カメラの横ベクトル(x)
  side.normalize(); //正規化
  Vec3 newup = et.cross(side); //新しい上ベクトル(y)
  //このx,y,zは視点座標系における新たな基底となる

  Matrix4 R;
  //x
  R.m_array[0] = side.x;
  R.m_array[4] = side.y;
  R.m_array[8] = side.z;
  //y
  R.m_array[1] = newup.x;
  R.m_array[5] = newup.y;
  R.m_array[9] = newup.z;
  //z
  R.m_array[2] = et.x;
  R.m_array[6] =  et.y;
  R.m_array[10] = et.z;
  R.m_array[3] = R.m_array[7] = R.m_array[11] = 0.0;
  R.m_array[12] = R.m_array[13] = R.m_array[14] = 0.0;
  R.m_array[15] = 1.0;
  //回転行列からクォータリオンc_rotにパラメータを設定<-ワールド座標におけるカメラの回転の姿勢となる

  c_rot.fromMatrix(R);
  c_rot_p = c_rot;
  c_trans.x =  -(side.dot(e));
  c_trans.y =  -(newup.dot(e));
  c_trans.z =  -(et.dot(e));

}

//カメラの姿勢
void Camera::getCameraOrthogonalBasis(Vec3& u,Vec3& v,Vec3& w){
  Matrix4 m;
  c_rot.toMatrix(m);
  u.set(m(0,0),m(0,1),m(0,2));
  v.set(m(1,0),m(1,1),m(1,2));
  w.set(m(2,0),m(2,1),m(2,2));
}

//カメラのアクション
void Camera::action(float angle,float x,float y,float z){
  switch(c_action){
    case(MOVE_ACTION):
      move(x,-y,z);
      break;
    case(ROTATE_ACTION):
      rotate(angle,x,y,z);
      break;
    case(ZOOM_ACTION):
      zoom(z);
      break;
  }
}

//opengl上で透視変換をさせる
void Camera::modelView(void){
  Matrix4 M;
  //Matrix4 M_p;
  //座標を移動
  glTranslatef(c_trans.x, c_trans.y, c_trans.z);  
  //回転情報から回転行列を設定
  c_rot.toMatrix(M);
  //回転処理
  glMultMatrixf(M.m_array);

  //移動後の座標を取り出して保存するための処理
    // LookAtの行列 "RT"から"T"のみを取り出す
  c_rot_p.toMatrix(M);
  Matrix4 M_inv = M;
  M_inv.invert();
  M.m_array[12] = c_trans.x;M.m_array[13] = c_trans.y; M.m_array[14] = c_trans.z;
  M_inv *= M;
  Vec3 e{-M_inv(0,3),-M_inv(1,3),-M_inv(2,3)};
  c_position = e;
}

//カメラの回転
void Camera::rotate(float angle,float x,float y,float z){
      Vec3 v{x,y,z};
      Quat q_{v,angle};
      c_rot = c_rot*q_;
}
