#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <iostream>
#include "vec.h"
#include "matrix.h"
#include "Quat.h"
#include <GL/glut.h>

class Camera{
  public:
    enum CameraAction{
		  NO_ACTION = 0,
		  ROTATE_ACTION, //回転
		  MOVE_ACTION, //並進移動
		  ZOOM_ACTION //カメラズーム
	  };
    //コンストラクタ
    Camera()
    :c_fov(30.0f),c_zNear(1.0f),c_zFar(1000.0f),c_action(NO_ACTION),c_speed(2.0f),window_width(320), window_height(240){}
    Camera(int width,int height)
    :c_fov(30.0f),c_zNear(1.0f),c_zFar(1000.0f),c_action(NO_ACTION),c_speed(2.0f),window_width(width), window_height(height){};
    //デストラクタ
    ~Camera(){};
    
    //セッター
    //視野変換するための位置と姿勢を求める
    void setLookAt(Vec3& e,Vec3& t,Vec3& u);
    
    //画面サイズの再設定
    inline void setWindowSize(unsigned _width, unsigned _height){
		  window_width = _width;
		  window_height = _height;
    }
    //アクションの設定
    inline void setAction(CameraAction act){
      c_action = act;
    }   
    //oengl上での視野角の設定
    inline void setPerspective(void){
      gluPerspective(c_fov, (float)window_width / (float)window_height, c_zNear,c_zFar);
    }

    //ゲッター

    //画面サイズの幅
    inline int getWindowWidth(void){
		 return window_width;
    }
    //画面サイズの高さ
    inline int getWindowHeight(void){
		 return window_height;
    }
    //アクション
    inline CameraAction getAction(void){
      return c_action;
    }
    //カメラの座標
    inline Vec3 getPosition(void){
      return c_position;
    }
    //カメラの姿勢
    void getCameraOrthogonalBasis(Vec3& u,Vec3& v,Vec3& w);
    //カメラからスクリーンまでの距離w
    inline float getScreenDistance(void) const{
		  return 0.5f * window_height / tanf(c_fov * (float)M_PI / 360.0f);
	  }
    //カメラのアクション
    void action(float angle,float x,float y,float z);

    //opengl上で透視変換をさせる(openglで使うモデルビュー行列を設定)
    void modelView(void);
  private:
    //メンバ変数
    //カメラが写す画面のサイズ
    int window_width,window_height;
    //カメラの座標
    Vec3 c_position;
    Vec3 c_trans; //変換時における変換の位置?
    //カメラの回転角を表すクォータリオン(回転だけの情報だけほしい)
    Quat c_rot;
    Quat c_rot_p; //座標を取り出す用
    //視野角,描画する範囲(最も近い距離,最も遠い距離)
    float c_fov,c_zNear,c_zFar;
    CameraAction c_action;
    float c_speed; //カメラのスピード
    //メンバメソッド
    inline void move(float move_x, float move_y,float move_z){
		  c_trans.x -= move_x*c_speed;
      c_trans.y += move_y*c_speed;
		  c_trans.z += move_z*c_speed;
	  }
    inline void zoom(float z){
		  c_fov -=  c_speed*z;
	  }

    void rotate(float angle,float x,float y,float z);
};