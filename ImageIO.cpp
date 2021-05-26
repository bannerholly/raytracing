#include "ImageIO.h"


bool ImageIO::pngImageRead(const char* filename,Image& img){
  FILE* fp;
  unsigned int width, height;
  unsigned int readSize;

  png_colorp palette;
  png_structp png;
  png_infop info;
  png_bytep row;
  png_bytepp rows;
  png_byte type;
  png_byte header[PNG_HEADER_NUM];
  int num;

  //ファイルの読み込み
  if( (fp = fopen(filename,"rb")) == NULL){
    std::cout << "Can't Open" << std::endl;
    return false;
  }

  readSize = fread(header, 1, PNG_HEADER_NUM, fp);

  //ファイルがpngかのチェック
  if(png_sig_cmp(header,0,PNG_HEADER_NUM)){
    std::cout << "Not PNG File " << std::endl;
    return false;
  }

  //read構造体とinfo構造体の生成
  png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(png == NULL){
    std::cout << "png_create_read_struct error" << std::endl;
    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);
    return false;
  }
  info = png_create_info_struct(png);
  if(info == NULL){
    std::cout << "PNG_create_info struct error" << std::endl;
    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);
    return false;
  }

  //読み込み先ファイルポインタの設定
  png_init_io(png, fp);
  //読み込んだバイト数の設定
  png_set_sig_bytes(png, readSize);
  //画像の読み込み
  png_read_png(png, info, PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16, NULL);

  //画像情報取得
  width = png_get_image_width(png, info); //画像のwidth
  height = png_get_image_height(png, info);  //画像のheight
  rows = png_get_rows(png, info);  //でコードされたBITMAPデータのポインタ
  type = png_get_color_type(png, info);  //pngの画像形式
  rows = png_get_rows(png, info);

  //デコード結果のメモリ領域へのコピー

  switch(type){
    case PNG_COLOR_TYPE_PALETTE:
      std::cout << "color type is PALETTE" <<  std::endl;
      png_get_PLTE(png, info, &palette, &num);
      img.allocate(width,height);
      for (int y = 0; y < height; y++) {
        row = rows[y];
        for (int x = 0; x < width; x++) {
          float r = static_cast<float>(palette[*row].red)/255;
          float g = static_cast<float>(palette[*row].green)/255;
          float b = static_cast<float>(palette[*row].blue)/255;
          Color v{r,g,b};
          img.setPixel(x,height-1-y,v);
          row++;
        }
      }
      break;
    case PNG_COLOR_TYPE_GRAY:
      std::cout << "color type is GRAY" << std::endl;
      png_destroy_read_struct(&png, &info, NULL);
      fclose(fp);
      return false;
      break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
      std::cout << "color type is GRAY_ALPHA" <<  std::endl;
      png_destroy_read_struct(&png, &info, NULL);
      fclose(fp);
      return false;
      break;
    case PNG_COLOR_TYPE_RGB:
      std::cout << "color type is RGB" <<  std::endl;
      img.allocate(width,height);
      for (int y = 0; y < height; y++) {
        row = rows[y];
        for (int x = 0; x < width; x++) {
          float r = static_cast<float>(*row)/255;
          row++;
          float g = static_cast<float>(*row)/255;
          row++;
          float b = static_cast<float>(*row)/255;
          row++;
          Color v{r,g,b};
          img.setPixel(x,height-1-y,v);
        }
      }
      break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
      std::cout << "color type is RGB_ALPHA" <<  std::endl;
      img.allocate(width,height);
      for (int y = 0; y < height; y++) {
        row = rows[y];
        for (int x = 0; x < width; x++) {
          float r = static_cast<float>(*row)/255;
          row++;
          float g = static_cast<float>(*row)/255;
          row++;
          float b = static_cast<float>(*row)/255;
          row++;
          Color v{r,g,b};
          img.setPixel(x,height-1-y,v);
          row++; //α値のため
        }
      }
      break;
  };

  png_destroy_read_struct(&png, &info, NULL);
  fclose(fp);
  return true;
}

bool ImageIO::jpegImageRead(const char* filename,Image& img){
  FILE* fp;
  unsigned int width, height;
  struct jpeg_decompress_struct jpegd;
  struct jpeg_error_mgr err;
  JSAMPROW buffer = NULL;
  JSAMPROW row;
  int stride;

  jpegd.err = jpeg_std_error(&err);
  //ファイルの読み込み
  if( (fp = fopen(filename,"rb")) == NULL){
    std::cout << "Can't Open" << std::endl;
    return false;
  }
  //画像の読み込み
  jpeg_create_decompress(&jpegd);
  jpeg_stdio_src(&jpegd, fp);
  //ヘッダの読み込み
  if (jpeg_read_header(&jpegd, 1) != JPEG_HEADER_OK) {
    std::cout << "Not JPEG_HEADER" << std::endl;
    jpeg_destroy_decompress(&jpegd);
    fclose(fp);
    return false;
  }
  //復号の開始
  jpeg_start_decompress(&jpegd);
  //色空間の確認
  if (jpegd.out_color_space != JCS_RGB) {
    std::cout << "Not RGB" << std::endl;
    jpeg_destroy_decompress(&jpegd);
    fclose(fp);
    return false;
  }
  width = jpegd.output_width;
  height = jpegd.output_height;

  //1行分の作業バッファの確保
  stride = sizeof(JSAMPLE) * jpegd.output_width * jpegd.output_components;
  if ((buffer = (JSAMPROW)calloc(stride, 1)) == NULL) {
    jpeg_destroy_decompress(&jpegd);
    fclose(fp);
    return false;
  }
  //デコード結果のメモリ領域へのコピー
  img.allocate(width,height);
  for (int y = 0; y < height; y++) {
    jpeg_read_scanlines(&jpegd, &buffer, 1);
    row = buffer;
    for (int x = 0; x < width; x++) {
      float r = static_cast<float>(*row)/255;
      row++;
      float g = static_cast<float>(*row)/255;
      row++;
      float b = static_cast<float>(*row)/255;
      row++;
      Color v{r,g,b};
      img.setPixel(x,height-1-y,v);
    }
  } 
  //複合の終了と破壊
  jpeg_finish_decompress(&jpegd);
  jpeg_destroy_decompress(&jpegd);
  free(buffer);
  fclose(fp);
  return true;
}

bool ImageIO::pngImageWrite(const char* filename,Image* img){
  //今回はRGBAの書き込みとする
  FILE* fp;
  int row_size;
  int color_type = PNG_COLOR_TYPE_RGB;
  int width,height;
  png_structp png = NULL;
  png_infop info = NULL;
  png_bytep row;
  png_bytepp rows = NULL;
  png_colorp palette = NULL;
  //画像データがあるかを確認
  if (img == nullptr) {
    std::cout << "Image is null" << std::endl;
    return false;
  }
  //ファイルの読み込み
  if( (fp = fopen(filename,"wb")) == NULL){
    std::cout << "Can't Open" << std::endl;
    return false;
  }
  width = img->getWidth();
  height = img->getHeight();
  row_size = sizeof(png_byte) * width * 3;
  png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png == NULL) {
    if (rows != NULL) {
      for (int y = 0; y < height; y++) {
        png_free(png, rows[y]);
      }
      png_free(png, rows);
    }
    png_destroy_write_struct(&png, &info);
    return false;
  }

  info = png_create_info_struct(png);

  if (info == NULL) {
    if (rows != NULL) {
      for (int y = 0; y < height; y++) {
        png_free(png, rows[y]);
      }
      png_free(png, rows);
    }
    png_destroy_write_struct(&png, &info);
    return false;
  }
  if (setjmp(png_jmpbuf(png))) {
    if (rows != NULL) {
      for (int y = 0; y < height; y++) {
        png_free(png, rows[y]);
      }
      png_free(png, rows);
    }
    png_destroy_write_struct(&png, &info);
    return false;
  }
  png_init_io(png, fp);
  png_set_IHDR(png, info, width, height ,PNG_HEADER_NUM,
      color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);
  rows = (png_bytepp)png_malloc(png, sizeof(png_bytep) * height);
  if (rows == NULL) {
    png_destroy_write_struct(&png, &info);
    return false;
  }
  png_set_rows(png, info, rows);
  memset(rows, 0, sizeof(png_bytep) * height);
  for (int y = 0; y < height; y++) {
    if ((rows[y] = (png_bytep)png_malloc(png, row_size)) == NULL) {
      if (rows != NULL) {
        for (int y = 0; y < height; y++) {
          png_free(png, rows[y]);
        }
        png_free(png, rows);
      }
      png_destroy_write_struct(&png, &info);
      return false;
    }
  }
  
  for (int y = 0; y < height; y++) {
    row = rows[y];
    for (int x = 0; x < width; x++) {
      Color co = img->getPixel(x,height-1-y);
      co *= 255;
      if(co.r > 255) co.r = 255;
      if(co.g > 255) co.g = 255;
      if(co.b > 255) co.b = 255;
      *row++ = static_cast<char>(co.r);
      *row++ = static_cast<char>(co.g);
      *row++ = static_cast<char>(co.b);
    }
  }
  png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);
  if (rows != NULL) {
    for (int y = 0; y < height; y++) {
      png_free(png, rows[y]);
    }
    png_free(png, rows);
  }
  png_destroy_write_struct(&png, &info);
  return true;
}
bool ImageIO::jpegImageWrite(const char* filename,Image* img){
  FILE* fp;
  int width,height;
  struct jpeg_compress_struct jpegc;
  struct jpeg_error_mgr err;
  JSAMPROW buffer = NULL;
  JSAMPROW row;
  
  width = img->getWidth();
  height = img->getHeight();
  jpegc.err = jpeg_std_error(&err);
  //画像データがあるかを確認
  if (img == nullptr) {
    std::cout << "Image is null" << std::endl;
    return false;
  }
  //ファイルの読み込み
  if( (fp = fopen(filename,"wb")) == NULL){
    std::cout << "Can't Open" << std::endl;
    return false;
  }
  if ((buffer = (JSAMPROW)malloc(sizeof(JSAMPLE) * 3 * width)) == NULL) {
    return false;
  }
  jpeg_create_compress(&jpegc);
  jpeg_stdio_dest(&jpegc, fp);
  jpegc.image_width = width;
  jpegc.image_height = height;
  jpegc.input_components = 3;
  jpegc.in_color_space = JCS_RGB;
  jpeg_set_defaults(&jpegc);
  jpeg_set_quality(&jpegc, 75, 1);
  jpeg_start_compress(&jpegc, 1);
  for (int y = 0; y < height; y++) {
    row = buffer;
    for (int x = 0; x < width; x++) {
      Color co = img->getPixel(x,height-1-y);
      co *= 255;
      if(co.r > 255) co.r = 255;
      if(co.g > 255) co.g = 255;
      if(co.b > 255) co.b = 255;
      *row++ = static_cast<char>(co.r);
      *row++ = static_cast<char>(co.g);
      *row++ = static_cast<char>(co.b);
    }
    jpeg_write_scanlines(&jpegc, &buffer, 1);
  }
  jpeg_finish_compress(&jpegc);
  jpeg_destroy_compress(&jpegc);
  free(buffer);
  return true;
}