#pragma once

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include "Vec.h"
class Logger{
  public:
    //コンストラクタ
    Logger(){};
    //デストラクタ
    ~Logger(){};
    
    //クラスメソッド
    template<typename T>
    static void logClass(T* s){
      std::cout << abi::__cxa_demangle(typeid(s).name(),0,0,status) <<std::endl;
    };
    template<typename T>
    static void logPut(T* s){
      std::cout << *s << std::endl;
    }
    template<typename T>
    static void logPointColor(T x, T y,Vec3& v){
      std::cout << "(x,y) = " << "("<< x <<","<< y<<") " << "color: " << v << std::endl;
    }
    static void logTest(){
      std::cout << "test" << std::endl;
    }
    
    static void logString(std::string s){
      std::cout << s << std::endl;
    }
  private:
    //クラス変数
    static int* status;
};