#pragma once

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Image.h"
#include "Logger.h"
#include "Vec.h"
#include "png.h"
#include "jpeglib.h"

class ImageIO{
  public:
    //コンストラクタ
    ImageIO(){};
    //デストラクタ
    ~ImageIO(){};

    bool pngImageRead(const char* filename,Image& img);
    bool jpegImageRead(const char* filename,Image& img);
    bool pngImageWrite(const char* filename,Image* img);
    bool jpegImageWrite(const char* filename,Image* img);
  private:
  const int PNG_HEADER_NUM = 8; //pngのヘッダー部分
};
