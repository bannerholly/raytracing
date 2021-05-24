#include "ObjectLoader.h"
#include "ObjectFactory.h"
bool ObjectLoader::load(const char* filename, TriangleMesh* t_mesh){
  std::vector<Vec3*> vertex;
  std::vector<Vec3*> normal;
  std::vector<Vec2*> tex;
  std::vector< std::vector<int> > face_vertices;
	std::vector< std::vector<int> > face_normals;
	std::vector< std::vector<int> > face_texcoords;
  //拡張子のチェック
  const std::string ext = getExtension(filename);
  if(ext != "obj"){
    Logger::logString("Not Object File");
    return false;
  };
  //ファイルストリームの読み込み
	std::ifstream fp(filename);
  while(! fp.eof()){
    std::string s;
    std::getline(fp,s);
    std::istringstream s1(s);
    //コメントとかだったら次に行く
    if (s[0] == '#') continue;	
		if (s == "") continue;
    //最初の文字を見る
    std::string token;
    s1 >> token;
    if(token == "v"){
      Vec3* p = new Vec3;
      s1 >> p->x >> p->y >> p->z;
      vertex.push_back(p);
    }
    else if(token == "vt"){
      Vec2* t = new Vec2;
      s1 >> t->x >> t->y;
      tex.push_back(t);
    }
    else if(token == "vn"){
      Vec3* n = new Vec3;
      s1 >> n->x >> n->y >> n->z;
      normal.push_back(n);
    }
    else if(token == "f"){
      //面の頂点データをそれぞれ格納
      std::vector<int> face_v;
      std::vector<int> face_n;
      std::vector<int> face_t;
      int i = 0;
      while (! s1.eof() && i < 3){
        int f_v;
        int f_t;
        int f_n;
        std::string s_vertex;
        s1 >> s_vertex;
        // 文字列 v/t/n にデータを入れる
        std::sscanf(s_vertex.c_str(),"%d/%d/%d",&f_v,&f_t,&f_n);
        f_v -= 1; f_t -= 1; f_n -=1;
        face_v.push_back(f_v);
        face_t.push_back(f_t);
        face_n.push_back(f_n);
        ++i;
      }
      //三角じゃなかったらアウト(ととりあえずしとく)
      if(i != 3){
        Logger::logString("Polygon Miss!");
        return false;
      }
      face_vertices.push_back(face_v);
      face_texcoords.push_back(face_t);
      face_normals.push_back(face_n);
    }
  }
  const size_t num = face_vertices.size();
  std::vector<Triangle*>& triangles = t_mesh->getTriangles();
  triangles.resize(num);
  for (int tri=0; tri<num; tri++)
	{
    const std::vector<int>& tmp = face_vertices[tri];
    triangles[tri] = new Triangle(*(vertex[tmp[0]]),*(vertex[tmp[1]]),*(vertex[tmp[2]]));
	}
  return true;
};

std::string ObjectLoader::getExtension(const std::string& filename){
  std::string::size_type n = filename.rfind(".");
  return (n == std::string::npos) ? "" : filename.substr(n+1);
};