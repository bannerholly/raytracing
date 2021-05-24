#include "View.h"
#include "Quat.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Scenemaker.h"
#include "Logger.h"

//オレンジ
GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };
//緑
GLfloat green[] = { 0.2f, 1.0f, 0.2f, 1.0f };
//ライトの位置
GLfloat lightpos[] = { 0.0, 0.0,200.0, 1.0 };

//カメラ
Camera m_camera;
Vec3 eye{0.0,0.0,300.0}; //カメラの座標
Vec3 target{0.0,0.0,0.0};   // 注視点の座標
Vec3 up{0.0,1.0,0.0};  //画面の上方向を指すベクトル
float r_;
//回転マトリックス
Matrix4 Rotate;

//シーン
Scene* s;
SceneMaker maker;

//Quat Target;
Quat current={ 0.0, 0.0, 0.0, 1.0 };
int Mouse_X, Mouse_Y;
float WIDTH;
float HEIGHT;

void View::idle(void){
 glutPostRedisplay();
}

void View::crateWindow(char* title){
  glutInitWindowPosition(pos_x,pos_y);
  glutInitWindowSize(v_width,v_height);
  glutCreateWindow(title); //ウィンドウを開く引数はタイトルバーの名前name
  glutDisplayFunc(display);//ウィンドウを再描画する必要があるときに, 引数の関数が実行.
  glutReshapeFunc(resize); //関数の引数にはリサイズ後のウィンドウの幅と高さが渡される.
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);
  glutIdleFunc(idle);
}

//Matrix4 tmp; //デバッグ用
void View::display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* 透視変換行列の設定 */ 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  m_camera.setPerspective(); //投影変換P

  /* モデルビュー変換行列の設定 */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  m_camera.modelView(); //視野変換 V 以後ワールド座標にモデルを置く
  /*gluLookAt(0.0,0.0,200.0, //カメラの座標
             0.0,0.0,0.0, // 注視点の座標
             0.0,1.0,0.0); // 画面の上方向を指すベクトル

  /* 光源の位置設定 */
 // glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  //クォータニオンによる回転
 // glMultMatrixf(Rotate.m_array);
  s->draw();

  //画面を二つに分け, 一方を表示している間に(見えないところで)もう一方に図形を描き,それが完了したらこの二つの画面を入れ換えるダブルバッファリング
   glutSwapBuffers(); 
   glFlush();
}

void View::resize(int w, int h){
  /* ウィンドウ全体をビューポートにする */
  //ビューポートとは, 開いたウィンドウの中で, 実際に描画が行われる領域のこと
  WIDTH = w;
  HEIGHT = h;
  glViewport(0, 0, w, h); //ビューポート変換U
  m_camera.setWindowSize(w,h);

}

//マウスを押したときの挙動
void View::mouse(int button, int state, int x, int y){
  switch (button) {
  case GLUT_LEFT_BUTTON:
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;
  default:
    break;
  }
  switch (state) {
  case GLUT_UP:
    break;
  case GLUT_DOWN:
    break;
  default:
    break;
  }
}
void View::motion(int x, int y){
}

//キーボードを押したときの挙動
void View::keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':  /* '\033' は ESC の ASCII コード */
    exit(0);
  case 'a':
  case 'A':
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
      m_camera.setAction(Camera::MOVE_ACTION);
    }
   // m_camera.action(0.0,-1.0,0.0,0.0);
    m_camera.action(0.0,-cos(r_),0.0,sin(r_));
    glutIdleFunc(idle);
    break;
  case 'd':
  case 'D':
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
      m_camera.setAction(Camera::MOVE_ACTION);
    }
   // m_camera.action(0.0,1.0,0.0,0.0);
    m_camera.action(0.0,cos(r_),0.0,-sin(r_));
    glutIdleFunc(idle);
    break;
  case 'w':
  case 'W':
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
      m_camera.setAction(Camera::MOVE_ACTION);
    }
    //m_camera.action(0.0,0.0,0.0,1.0);
    m_camera.action(0.0,sin(r_),0.0,cos(r_));
    glutIdleFunc(idle);
    break;
  case 's':
  case 'S':
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
      m_camera.setAction(Camera::MOVE_ACTION);
    }
    //m_camera.action(0.0,0.0,0.0,-1.0);
    m_camera.action(0.0,-sin(r_),0.0,-cos(r_));
    glutIdleFunc(idle);
    break;
  case 'z':
  case 'Z':
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
       m_camera.setAction(Camera::ZOOM_ACTION);
    }
    else{
      m_camera.setAction(Camera::NO_ACTION);
    }
    break;
  default:
   // m_camera.setAction(Camera::NO_ACTION);
    glutIdleFunc(0);
    break;
  }
}

//特別なキーを押したときの挙動
void View::specialKeyboard(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_LEFT:
    m_camera.setAction(Camera::ROTATE_ACTION);
    m_camera.action(-M_PI/180,0.0,1.0,0.0);
    r_ -= M_PI/180;
    if(r_ < 0){
      r_ = 359* M_PI/180;
    }
    glutIdleFunc(idle);
    break;
  case GLUT_KEY_RIGHT:
    m_camera.setAction(Camera::ROTATE_ACTION);
    m_camera.action(M_PI/180,0.0,1.0,0.0);
    r_ += M_PI/180;
    if(r_ >= 2*M_PI){
      r_ = 0;
    }
    glutIdleFunc(idle);
    break;
  case GLUT_KEY_UP:
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
      m_camera.setAction(Camera::MOVE_ACTION);
    }
    m_camera.action(0.0,0.0,1.0,0.0);
    glutIdleFunc(idle);
    break;
  case GLUT_KEY_DOWN:
    if(m_camera.getAction() != Camera::ZOOM_ACTION){
      m_camera.setAction(Camera::MOVE_ACTION);
    }
    m_camera.action(0.0,0.0,-1.0,0.0);
    glutIdleFunc(idle);
    break;
  case GLUT_KEY_F5:
    s->saveImage("XXXXXXXXxX",false);
  default:
    glutIdleFunc(0);
    break;
  }
}

void View::init(int argc, char *argv[]){
  glutInit(&argc, argv); //GLUT および OpenGL 環境を初期化
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);//ディスプレイの表示モードを設定
  crateWindow(argv[0]);
  m_camera.setWindowSize(v_width,v_height);
}

void View::init_(void){
  s =  maker.make();
  Vec3 backcolor{0.8f, 1.0f, 1.0f};
  s->setBackgroundColor(backcolor);
  //glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST); // 描画のときにデプスバッファを使うようになります
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  current.toMatrix(Rotate);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  m_camera.setLookAt(eye,target,up);
}