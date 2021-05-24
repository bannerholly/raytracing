#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include "Logger.h"
class View{
  private:
    int pos_x,pos_y;
    int v_width,v_height;
  public:
    //コンストラクタ
    View(): pos_x(100),pos_y(100),v_width(320),v_height(240)
    {};
    View(int width,int height): pos_x(100),pos_y(100),v_width(width),v_height(height)
    {};
    //デストラクタ
    ~View(){};

    static void idle(void);
    static void display(void);
    static void resize(int w, int h);
    static void mouse(int button, int state, int x, int y);
    static void keyboard(unsigned char key, int x, int y);
    static void specialKeyboard(int key, int x, int y);
    static void motion(int x, int y);
    void crateWindow(char* title);
    void init(int argc, char *argv[]);
    void init_(void);
};