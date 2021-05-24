#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "all.h"


View v{640,480};
RayTracer rt;
int main(int argc, char *argv[]){
  v.init(argc,argv);
  v.init_();
  glutMainLoop(); //無限ループ
  return 0;
}