engineobj = main.o View.o Camera.o RayTracer.o Scene.o Logger.o Image.o SceneMaker.o 
engine = $(engineobj:%.o=%.cpp)
objectobj = Sphere.o AmbientLight.o DirectionalLight.o PointLight.o Material.o TextureMaterial.o Plane.o Triangle.o ObjectInstance.o  Box.o UniformGrid.o UniformGridTracer.o
object = $(objectobj:%.o=%.cpp)
mathobj = Matrix.o Quat.o
math = $(mathobj:%.o=%.cpp)

obj = main.o Matrix.o Quat.o View.o Camera.o RayTracer.o Sphere.o Scene.o Logger.o Image.o
source = $(obj:%.o=%.cpp)

test = Image.cpp
testobj = $(test:%.cpp=%.o)

main.o: main.cpp
	g++ -c -o main.o main.cpp
Matrix.o: Matrix.cpp
	g++ -c -o Matrix.o Matrix.cpp
Quat.o: Quat.cpp
	g++ -c -o Quat.o Quat.cpp
View.o: View.cpp
	g++ -c -o View.o View.cpp
Camera.o: Camera.cpp
	g++ -c -o Camera.o Camera.cpp
Scene.o: Scene.cpp
	g++ -c -o Scene.o Scene.cpp
SceneMaker.o: SceneMaker.cpp
	g++ -c -o SceneMaker.o SceneMaker.cpp
Sphere.o: Sphere.cpp
	g++ -c -o Sphere.o Sphere.cpp
Plane.o: Plane.cpp
	g++ -c -o Plane.o Plane.cpp
Box.o: Box.cpp
	g++ -c -o Box.o Box.cpp	
Triangle.o: Triangle.cpp
	g++ -c -o Triangle.o Triangle.cpp	
TriangleMesh.o: TriangleMesh.cpp
	g++ -c -o TriangleMesh.o TriangleMesh.cpp	
UniformGrid.o : UniformGrid.cpp
	g++ -c -o UniformGrid.o UniformGrid.cpp
UniformGridTracer.o : UniformGridTracer.cpp
	g++ -c -o UniformGridTracer.o UniformGridTracer.cpp
ObjectInstance.o: ObjectInstance.cpp
	g++ -c -o ObjectInstance.o ObjectInstance.cpp
RayTracer.o: RayTracer.cpp
	g++ -c -o RayTracer.o RayTracer.cpp
Logger.o: Logger.cpp
	g++ -c -o Logger.o Logger.cpp
Image.o: Image.cpp
	g++ -c -o Image.o Image.cpp
AmbientLight.o: AmbientLight.cpp
	g++ -c -o AmbientLight.o AmbientLight.cpp
DirectionalLight.o: DirectionalLight.cpp
	g++ -c -o DirectionalLight.o DirectionalLight.cpp
PointLight.o: PointLight.cpp
	g++ -c -o PointLight.o PointLight.cpp
Material.o: Material.cpp
	g++ -c -o Material.o Material.cpp
TextureMaterial.o: TextureMaterial.cpp
	g++ -c -o TextureMaterial.o TextureMaterial.cpp

program: $(engineobj) $(objectobj) $(mathobj)
	g++  -o program $(engineobj) $(objectobj) $(mathobj) -lglut -lGLU -lGL -lm -lpng -ljpeg
#デバックコンパイル用
debug: main.cpp $(test)
	touch main.cpp
	g++ -c -o main.o main.cpp
	g++ -c -o $(testobj) $(test)
#オブジェクト関連のデバッグコンパイル用
object: main.cpp $(object)
	touch main.cpp
	g++ -c -o main.o main.cpp
	g++ -c -o $(objectobj) $(object)

run: program
	./program
clear:
	rm -f ./program $(engineobj) $(objectobj) $(mathobj)
all: $(engine) $(object) $(math)
	g++ -o program $(engine) $(object) $(math) -lglut -lGLU -lGL -lm -lpng
	./program
.PHONY : run clean all