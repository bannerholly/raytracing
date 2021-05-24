#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include "TriangleMesh.h"
#include "Logger.h"
#include "Vec.h"

class ObjectLoader{
  public:
    //コンストラクタ
    ObjectLoader(){};
    //デストラクタ
    ~ObjectLoader(){};
    bool load(const char* filename, TriangleMesh* t_mesh);

    std::string getExtension(const std::string& filename);
    bool getInt( int *pIdx, std::istringstream &is);
};