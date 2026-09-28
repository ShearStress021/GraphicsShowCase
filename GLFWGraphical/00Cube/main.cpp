#include "../myGLFWEngine.h"

struct Vector3 {
	float x, y, z;
};

struct Mat4 {
	float mat[4][4]{};

};

class Cube : public GLFWEngine {
	protected:
		bool userConstruct(){
			CreatePersepectiveProjection();
			drawCubeIndexed();
//			drawLine(100,200,550,450, {0,0,255});
			return true;
		}
	private:

		Mat4 matProj{};
		Vector3 vertices[8] {
			{0,0,0}, {1,0,0}, {1,1,0},{0,1,0},
			{0,0,1}, {1,0,1}, {1,1,1},{0,1,1}
		};

		int cubeTris [12][3]{
			{0,3,2}, {0,2,1},
			{1,2,6}, {1,6,5},
			{5,6,7}, {5,7,4},
			{4,7,3}, {4,3,0},
			{3,7,6}, {3,6,2},
			{5,4,0}, {5,0,1}
		};

		void MultiplyVector3ByMat(Vector3 &in, Vector3 &res, Mat4 &mat4){
			res.x = in.x * mat4.mat[0][0] + in.y * mat4.mat[1][0] + in.z * mat4.mat[2][0] + mat4.mat[3][0];
			res.y = in.x * mat4.mat[0][1] + in.y * mat4.mat[1][1] + in.z * mat4.mat[2][1] + mat4.mat[3][1];
			res.z = in.x * mat4.mat[0][2] + in.y * mat4.mat[1][2] + in.z * mat4.mat[2][2] + mat4.mat[3][2];
			float w = in.x * mat4.mat[0][3] + in.y * mat4.mat[1][3] + in.z * mat4.mat[2][3] + mat4.mat[3][3];

			if (w != 0.f){
				res.x /= w;
				res.z /= w;
				res.y /= w;
			}
		}

		void CreatePersepectiveProjection(){
			float nearPlane{0.1f};
			float farPlane{100.f};
			float cellAspect{2.f};
			float aspectRatio {static_cast<float>(getScreenHeight())/(getScreenWidth()) * cellAspect};
			float fieldOfView{90.f};
			float fieldOfViewRad{1.0f/std::tanf(fieldOfView * 0.5 * 3.14159f / 180)};

			matProj.mat[0][0] = aspectRatio * fieldOfViewRad;
			matProj.mat[1][1] = fieldOfViewRad;
			matProj.mat[2][2] =  farPlane / (farPlane - nearPlane);
			matProj.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
			matProj.mat[2][3] = 1.0f;
			matProj.mat[3][3] = 0.0f;

		}

		Vector3 projectPoint(Vector3 point){
			point.x -= 1.5f;
			point.y += 1.f;
			point.z += 3.f;
			Vector3 res{};

			MultiplyVector3ByMat(point,res,matProj);
			res.x = (res.x + 1.f) * 0.5f * static_cast<float>(getScreenWidth());
			res.y = (res.y + 1.f) * 0.5f * static_cast<float>(getScreenHeight());
			return res;
		}

		void drawCubeIndexed(){
			Vector3 s[8];
			for(size_t i{}; i < 8; i++) s[i] = projectPoint(vertices[i]);

			for(auto& t: cubeTris) 
				drawTriangle(s[t[0]].x, s[t[0]].y, s[t[1]].x, s[t[1]].y, s[t[2]].x, s[t[2]].y,{255,100,50});
		}


	
};

int main(){
	Cube cube{};
	if(cube.createWindow(800,600, "3d Cube") != 0) return 1;
	cube.initWindow();
	
}
