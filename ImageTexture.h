#pragma once

#include "Texture.h"
#include "Image.h"
#include "ImageIO.h"
#include "Logger.h"

static ImageIO io;
class ImageTexture : public Texture{
  public:
    //コンストラクタ
    ImageTexture(){};
    //デストラクタ
    ~ImageTexture(){
     // Logger::logClass(this);
    };

    //画像読み込み
    bool loadPNGImage(const std::string &filename){
		  return io.pngImageRead(filename.c_str(), image);
    }
    bool loadJPEGImage(const std::string &filename){
		  return io.jpegImageRead(filename.c_str(), image);
    }
    //セッター
    void setColor(Color& c){
      t_color = c;
    }

    //ゲッター
    Color getColor() const{
      return t_color;
    }
    Color getColor(const Vec3 &uvw) const{
      int w = image.getWidth();
      int h = image.getHeight();
      const float _x = std::max(0.f, std::min(uvw.x * w, (float)(w-1)));
		  const float _y = std::max(0.f, std::min(uvw.y * h, (float)(h-1)));
      int x = (int)floorf(_x);
      int y = (int)floorf(_y);
      Color c = image.getPixel(x,y);
    //  Logger::logPut(&c);
		  return c;
	  }
  private:
    Image image;
    Color t_color; //色
};