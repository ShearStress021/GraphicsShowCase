#include "myConsoleEngine.hpp"
#include <vector>
#include <cmath>

struct Vector3 {
	float x, y, z;
};

struct TrianglePoints {
	Vector3 points[3];
};

struct Vertex {
	std::vector<TrianglePoints> triangles{};
};

struct Mat4 {
	float mat[4][4]{};
};


class Cube3d : public ConsoleEngine {
	private:
		Vertex cubePoints{};
		Mat4 matrixProj{};
	private:
		bool userConstruct(){
			createPerceptionPespective();
			drawCube();
			//drawTriangle(30,10,20,40,40,10);


			return true;

		}

		void multiplyVector3Mat4(Vector3 &in, Vector3 &res, Mat4 &mat4) {
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

		void createPerceptionPespective(){
			float nearPlane{0.1f};
			float farPlane{100.f};
			float aspectRatio {static_cast<float>(getScreenHeight())/static_cast<float>(getScreenWidth())};
			float fieldOfView{90.f};
			float fieldOfViewRad{1.0f/std::tanf(fieldOfView * 0.5 * 3.14159f / 180)};

			matrixProj.mat[0][0] = aspectRatio * fieldOfView;
			matrixProj.mat[1][1] = fieldOfViewRad;
			matrixProj.mat[2][2] =  farPlane / (farPlane - nearPlane);
			matrixProj.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
			matrixProj.mat[2][3] = 1.0f;
			matrixProj.mat[3][3] = 0.0f;
		}
		void drawCube(){
			cubePoints.triangles = {
				// SOUTH
				{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f   },
				{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f   },

				// EAST                                                      
				{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f   },
				{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f   },
				//
				// NORTH                                                     
				{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f   },
				{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f   },
				//
				// WEST                                                      
				{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f   },
				{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f   },
				
				// TOP                                                       
				{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f   },
				{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f   },
				
				//Bottom
				{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f   },
				{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f   },
			};

			for (auto tri : cubePoints.triangles) {
				TrianglePoints projPoints, translated;
				translated.points[0].z = tri.points[0].z + 3.f;
				translated.points[1].z = tri.points[1].z + 3.f;
				translated.points[2].z = tri.points[2].z + 3.f;


				
				multiplyVector3Mat4(translated.points[0], projPoints.points[0], matrixProj);
				multiplyVector3Mat4(translated.points[1], projPoints.points[1], matrixProj);
				multiplyVector3Mat4(translated.points[2], projPoints.points[2], matrixProj);




				projPoints.points[0].x += 1.f; projPoints.points[0].y += 1.f;
				projPoints.points[1].x += 1.f; projPoints.points[1].y += 1.f;
				projPoints.points[2].x += 1.f; projPoints.points[2].y += 1.f;

				projPoints.points[0].x *= 0.5f * static_cast<float>(getScreenWidth());
				projPoints.points[0].y *= 0.5f * static_cast<float>(getScreenHeight());
				projPoints.points[1].x *= 0.5f * static_cast<float>(getScreenWidth());
				projPoints.points[1].y *= 0.5f * static_cast<float>(getScreenHeight());
				projPoints.points[2].x *= 0.5f * static_cast<float>(getScreenWidth());
				projPoints.points[2].y *= 0.5f * static_cast<float>(getScreenHeight());

				drawTriangle(projPoints.points[0].x, projPoints.points[0].y, projPoints.points[1].x, projPoints.points[1].y,
						projPoints.points[2].x, projPoints.points[2].y,'o', 0x0009);


			}


		}







};


int main(){
	Cube3d res{};
	res.createWindow(130,35,"3d Cube");
	res.init();
}

