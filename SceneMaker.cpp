#include "SceneMaker.h"
#include "TextureMaterial.h"
#include "ColorTexture.h"
#include "ObjectInstance.h"

//シーンの作成
    Scene* SceneMaker::make(){
      //物体の追加
      Vec3 color{100.0f, 140.0f, 160.0f};
      Vec3 vv{1.0}; //環境光のパラメータ
      Vec3 orange{1.0f, 0.6f, 0.0f}; //拡散反射光のパラメータ
      Vec3 green{0.2f, 1.0f, 0.2f};
      Vec3 blue{0.6f, 0.6f, 1.0f};
      Vec3 white{1.0f, 1.0f, 1.0f};
      Color red{1.0,0.0,0.0};
      Vec3 spec{1.0,1.0,1.0}; //鏡面反射光のパラメータ
      int shiness = 20;  //輝きの度合い
      Vec3 ps{0.9,0.9,0.9}; //完全反射パラメータ

      //インスタンス座標の実験
      Vec3 center1{20.0,10.0,10.0};
      Vec3 wn{1.0,0.0,0.0};
      Vec3 hn{0.0,1.0,0.0};
      hn.normalize();
      Vec3 v0{-20.0,0.0,0.0};
      Vec3 v1{20.0,0.0,0.0};
      Vec3 v2{30.0,35.0,0.0};

//#if 0
      //反射(屈折)させるやつ
      Vec3 center1_{-40.0,10.0,50.0};
      Sphere* sp = o_factry.createSphere(center1_,20);
      sp->setMaterialParam(MaterialParam::Ambient,vv);
      sp->setMaterialParam(MaterialParam::Diffuse,blue);
      sp->setMaterialParam(MaterialParam::Specular,spec);
      sp->setMaterialShiness(shiness);
      sp->setMaterialPerfectSpecular(ps);
      sp->onPerfectSpecular();
      //sp->setMaterialReflactSpecular(1.5,ps);
      //sp->onReflactSpecular();
      s.addObject(sp);
//#endif
#if 0
      //色ついているやつ(発光させるやつ)
      Vec3 center222{10.0,20.0,50.0};
      //EmitMaterial* em = new EmitMaterial{red};
      
      Sphere* sp_ = o_factry.createSphere(center222,20);
      ColorTexture* ct = new ColorTexture(green);
      TextureMaterial* tm = new TextureMaterial(ct); //カラー版
      sp_->setMaterial(tm); //カラー版
      sp_->setMaterialParam(MaterialParam::Ambient,vv);
    //  sp_->setMaterialParam(MaterialParam::Diffuse,red);
      sp_->setMaterialParam(MaterialParam::Specular,spec);
      sp_->setMaterialShiness(shiness);
      //s.addEmit(sp_);
       s.addObject(sp_);
#endif
//#if 0
      //サンプル球やつ
      Vec3 center2{-10.0,10.0,-100.0};
      Vec3 center22{40.0,40.0,30.0};
      Vec3 a[2] = {center2,center22};
      for(int i = 0; i < 2;i++){
        Sphere* sp1 = o_factry.createSphere(a[i],20);
        sp1->setMaterialParam(MaterialParam::Ambient,vv);
        sp1->setMaterialParam(MaterialParam::Diffuse,orange);
        sp1->setMaterialParam(MaterialParam::Specular,spec);
        sp1->setMaterialShiness(shiness);
        s.addObject(sp1);
      }
//#endif
#if 0
     //テクスチャマッピング
      //Triangle* pn = o_factry.createTriangle(v0,v1,v2);
      //Sphere* pn = o_factry.createSphere(center1,10);
      //Plane* pn = o_factry.createPlane(center1,80,60,wn,hn);
      Plane* pn = o_factry.createPlane(center1,30,30,wn,hn);
      pn->setMaterialParam(MaterialParam::Ambient,vv);
      pn->setMaterialParam(MaterialParam::Diffuse,red);
      pn->setMaterialParam(MaterialParam::Specular,spec);
      pn->setMaterialShiness(shiness);
      s.addObject(pn);
      ObjectInstance * ss = new ObjectInstance(pn);
      ss->translate(-80.0,0.0,0.0);
      ss->scale(1.5,1.5,1.0);
      ss->rotate(M_PI,0.0,1.0,0.0);
      s.addObject(ss);
#endif 
#if 0
      //オブジェクトファイルの使用
      ObjectLoader* loader = new ObjectLoader();
      TriangleMesh* mesh = o_factry.createTriangleMesh();
      bool isLoad = false;
      isLoad = loader->load("XXXXXXXXXX",mesh);
      if(!isLoad){
        Logger::logString("obj_load failed");
      }
      else{
        mesh->setMaterialParam(MaterialParam::Ambient,vv);
        mesh->setMaterialParam(MaterialParam::Diffuse,red);
        mesh->setMaterialParam(MaterialParam::Specular,spec);
        mesh->setMaterialShiness(shiness);
        mesh->computeBoundingBox();
        mesh->buidGrid(8,8,8);
        mesh->onUniformGrid();
        ObjectInstance* mesh_ = new ObjectInstance(mesh);
        mesh_->scale(0.3,0.3,0.3);
        s.addObject(mesh_);
      }
#endif
#if 0
      //箱
      /*
      float p_min = -40.0;
      float p_max = 20.0;
      Vec3 min{p_min};
      Vec3 max{20.0,-20.0,20.0};
      Box* bx = o_factry.createBox(min,max);
      */
      float x = 40,y = 10, z = 60;
      Vec3 c{0.0,-40.0,0.0};
      Box* bx = o_factry.createBox(c,x,y,z);
      bx->setMaterialParam(MaterialParam::Ambient,vv);
      bx->setMaterialParam(MaterialParam::Diffuse,red);
      bx->setMaterialParam(MaterialParam::Specular,spec);
      bx->setMaterialShiness(shiness);
     // s.addObject(bx);
#endif
      //床変わり
      Vec3 center3{0.0,-30.0,0.0};
      Box* sp2 = o_factry.createBox(center3,200,10,200);
      sp2->setMaterialParam(MaterialParam::Ambient,vv);
      sp2->setMaterialParam(MaterialParam::Diffuse,green);
      ObjectInstance* ss1 = new ObjectInstance(sp2);
      s.addObject(ss1);


      //ライト
      Vec3 l_color2{1.0,1.0,1.0};
      Vec3 l_pos2{-0.3,-2.0,-1.0};
      l_pos2.normalize();
      s.addLight(l_factry.createDirectionalLight(l_pos2,l_color2)); //平行光源
      //Vec3 l_pos2{-35.0,20.0,70.0};
      //s.addLight(l_factry.createPointLight(l_pos2,l_color2)); //点光源
      return &s;
    };