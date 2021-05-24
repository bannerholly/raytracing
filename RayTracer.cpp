#include "RayTracer.h"
#include "scene.h"
#include "HitRec.h"
#include "Material.h"
#include <limits>
#include "Logger.h"

int RayTracer::max_depth = 5;
extern Scene* s; //viewのシーンのはず

Vec3 RayTracer::trace(const Ray &ray){
  return traceRec(ray,0);
}

Vec3 RayTracer::traceRec(const Ray& ray, int depth){
  if(depth > max_depth){
    return  s->getBackgroundColor(); //背景色を返す
  }
  bool isObject = false;
  HitRec record;
	record.t = std::numeric_limits<float>::max(); //最大値に設定
  std::vector<BaseObject*>* objects = s->getObject();
  std::vector<BaseLight*>* lights = s->getLight();
  BaseObject* hitObject;
  Material* material;
  for (BaseObject* o: *objects){
    HitRec tmpRec;
    bool isHit = o->hit(ray,0.0,std::numeric_limits<float>::max(), tmpRec);
    if(isHit && record.t > tmpRec.t){
      isObject = true;
      record = tmpRec;
      hitObject = o;

    }
  } 
  /* if レイが度の物体ともぶつからない
    ---->背景色を返す 
  */
  if(!isObject){
     return s->getBackgroundColor(); //背景色を返す
  }
//HitRecにマテリアル情報を入れない場合(相互インクルードは回避できた)
  //material = hitObject->getMaterial(); 

//HitRecにマテリアル情報を入れる場合(相互インクルードになったがな)
  material = record.material;
  Material::MaterialType param = material->getMaterialType();

  if(param == Material::MaterialType::EmissionType){
    BaseLight* ll = nullptr;
    return material->calcLight(ll,record,Vec3{1.0});
  } 
  Color sp{0.0}; //完全鏡面反射成分
  Color rep{0.0}; //屈折光成分
     if(material->getIsReflect() == true){
       Vec3 R = Vec3::reflect(ray.getDirection(),record.n); //反射ベクトル
       Color ir = traceRec( Ray{record.p+0.01f*record.n,R},depth+1);
       Vec3 kr = material->getPerfectSpecular();
       float r = kr.r * ir.r;
       float g = kr.g * ir.g;
       float b = kr.b * ir.b;
       sp += Vec3{r,g,b};
       return sp;
     }

     if(material->getIsReflact() == true){
       float n = material->getEta();
       Vec3 L = ray.getDirection();
       Vec3 N = record.n;
       float c = -L.dot(N); //内積計算
       bool isOut; //物体から外に出るかどうか true: 出る, false:　入る
       if(c < 0){
         isOut = true; //入るということ
       }
       else{
         isOut = false; //出るということ
       }
       //例が内部から外に出る場合
       if(isOut == true){
         n = 1/n;
         N = -N;
       }
       Vec3 T = Vec3::refract(L,N,n);
       T.normalize();
       //全反射の場合
       if(T == Vec3{0.0,0.0,0.0}){
         Vec3 R = Vec3::reflect(ray.getDirection(),record.n); //反射ベクトル
         Color ir = traceRec( Ray{record.p+0.01f*record.n,R},depth+1);
         Vec3 kr = material->getPerfectSpecular();
         float r = kr.r * ir.r; float g = kr.g * ir.g; float b = kr.b * ir.b;
         rep += Vec3{r,g,b};
         return rep;
       }
       else{
         float c_ = -L.dot(N); //内積計算
         float g_ = sqrtf(n*n +c_*c_ -1);

         //フレネルの公式
         float rs = ((c_-g_)*(c_-g_))/((c_+g_)*(c_+g_));
         float rp = ((n*n*c_-g_)*(n*n*c_-g_))/((n*n*c_+g_)*(n*n*c_+g_));
         float kr = 0.5*(rs + rp);
         Vec3 R = Vec3::reflect(L,N); //反射ベクトル
         //光が完全鏡面反射した先でレイが交差する点の色 Ir を再帰的に計算;
         Color ir = traceRec( Ray{record.p+0.01f*record.n,R},depth+1); 
         //光が屈折した先でレイが交差する点の色 It を再帰的に計算;
         Color it = traceRec( Ray{record.p-0.01f*N,T},depth+1);
         Vec3 kf = material->getPerfectSpecular();
         float r = kr * ir.r + (1-kr)*it.r;
         float g = kr * ir.g + (1-kr)*it.g;
         float b = kr * ir.b + (1-kr)*it.b;
         rep += Vec3{r,g,b};
         return rep;
       }
     }
  Vec3 c{0.0,0.0,0.0};
  Vec3 out = -ray.getDirection(); //物体から視点への単位べクトル
  float shadow = 0.8;
  //光源から色を計算する
  for (BaseLight* l: *lights){
    bool isShadow = false; 
    //環境光以外で影の判定
    if(l->getLightType() != BaseLight::LightType::AmbientLight){
      //光源との距離を計算する
      Vec3 pos = record.p+0.01f*record.n;
      float distance = l->getLightDistance(pos);
      Ray shadow_ray{pos,-(l->getInLight(pos))};
      //影の計算
      for (BaseObject* o: *objects){
        bool isShadowHit = o->shadowHit(shadow_ray,0.001,distance);
        if(isShadowHit == true){
          isShadow = true;
          break;
        }
      }
    }
    if (!isShadow){
      c += material->calcLight(l,record,out);
    }
    else{
      Color buf = material->calcLight(l,record,out);
      c += shadow*buf*buf;
    }
  }
  //発光オブジェクトから色を計算する
  std::vector<BaseObject*>* emits = s->getEmit();
  HitRec new_rec;
  new_rec.t = std::numeric_limits<float>::max(); //最大値に設定
  bool is_newObject = false;
  BaseObject* new_hitObject;
  for (BaseObject* e: *emits){
    //当たったところから光源までのベクトル
    Vec3 diff = e->getPosition() - (record.p+0.01f*record.n); 
    float distance = diff.norm();
    for(BaseObject* o : *objects){
      HitRec new_tmpRec;
      Ray emit_ray{record.p+0.01f*record.n,diff};
      bool isHit = o->hit(emit_ray,0.0,distance,new_tmpRec);
      if(isHit && new_rec.t > new_tmpRec.t){
        is_newObject = true;
        new_rec = new_tmpRec;
        new_hitObject = o;
      }
    }
    if(is_newObject){
      Material* new_material = new_hitObject->getMaterial();
      Material::MaterialType new_param = new_material->getMaterialType();
      if(new_param == Material::MaterialType::EmissionType){
        BaseLight* lll;
        Vec3 diff2 = new_rec.p - record.p;
        Color cc = new_material->calcLight(lll,new_rec,diff2);
        c += cc;
      } 
    }
  } 
  return c + sp + rep;
}