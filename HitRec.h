#pragma once
#include "vec.h"

//HitRecにマテリアル情報を入れる場合(相互インクルードになったがな)
//入れなかったらコメントアウト
class Material;

class HitRec {
public:
    float t; //光線のパラメータ
    Vec3 p; //衝突の位置
    Vec3 n; //衝突位置における物体の法線ベクトル
    //HitRecにマテリアル情報を入れる場合(相互インクルードになったがな)
    //入れなかったらコメントアウト
    Material* material;
    Vec3 tex_pos; //テクスチャのUVW座標(主に使うのはUV座標系)
};