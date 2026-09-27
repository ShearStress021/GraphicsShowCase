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
		Vector3 camera{0.f,0.f,0.f};
		float cubeSize{2.f};
		float cubeDistance{4.f};
		bool ready{false};
		std::uint32_t startTick{};
	private:
		bool userConstruct(){
			createPerceptionPespective();
			buildCube();
			drawCube();
			//drawTriangle(30,10,20,40,40,10);
			return true;
		}

		static Vector3 rotateX(const Vector3& v, float a){
			float c = std::cos(a), s = std::sin(c);
			return {v.x, v.y * c - v.z * s, v.y * s + v.z * c};
		}

		static Vector3 rotateY(const Vector3& v, float a){
			float c = std::cos(a), s = std::sin(c);
			return {v.x * c + v.y * s, v.y, -v.x * s + v.z * c};
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
			float cellAspect{2.f};
			float aspectRatio {static_cast<float>(getScreenHeight())/(getScreenWidth()) * cellAspect};
			float fieldOfView{90.f};
			float fieldOfViewRad{1.0f/std::tanf(fieldOfView * 0.5 * 3.14159f / 180)};

			matrixProj.mat[0][0] = aspectRatio * fieldOfViewRad;
			matrixProj.mat[1][1] = fieldOfViewRad;
			matrixProj.mat[2][2] =  farPlane / (farPlane - nearPlane);
			matrixProj.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
			matrixProj.mat[2][3] = 1.0f;
			matrixProj.mat[3][3] = 0.0f;
		}
		void buildCube(){
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

			for(auto& tri: cubePoints.triangles){
				for(auto& p: tri.points){
					p.x -= 0.5f;
					p.y -= 0.5f;
					p.z -= 0.5f;
				}
			}


		}
		void drawCube(){
			for (auto tri : cubePoints.triangles) {
				TrianglePoints  translated , projPoints, moved;
				translated = tri;

				for(size_t i{}; i < 3; i++){
					Vector3 p = tri.points[i];
					p.x *= 2.f;
					p.y *= 2.f;
					p.z *= 2.f;
					p = rotateX(rotateY(p, 35.f), 35.f * 0.5f);
					p.z += 4.f;
					moved.points[i] = p;
				}
				//for(auto& p : translated.points) p.z += 3.f;


				//translated.points[0].z = tri.points[0].z + 3.f;
				//translated.points[1].z = tri.points[1].z + 3.f;
				//translated.points[2].z = tri.points[2].z + 3.f;

				const Vector3& a = moved.points[0];
				Vector3 e1{moved.points[1].x - a.x, moved.points[1].y - a.y, moved.points[1].z - a.z};
				Vector3 e2{moved.points[2].x - a.x, moved.points[2].y - a.y, moved.points[2].z - a.z};


				Vector3 normal {
					e1.y * e2.z  - e1.z * e2.y,
					e1.z * e2.x  - e1.z * e2.y,
					e1.x * e2.y  - e1.y * e2.x,
				};

				Vector3 toTri {a.x - camera.x, a.y - camera.y, a.z - camera.z};

				if(normal.x * toTri.x + normal.y * toTri.y + normal.z * toTri.z >= 0.0f) continue;

				
				



				for(int i = 0; i < 3; i++){
					multiplyVector3Mat4(moved.points[i], projPoints.points[i], matrixProj);
					//projPoints.points[i].x += 1.f;
					//projPoints.points[i].y += 1.f;
					projPoints.points[i].x *= 0.5f * static_cast<float>(getScreenWidth());
					projPoints.points[i].y *= 0.5f * static_cast<float>(getScreenHeight());

				}

				
				//multiplyVector3Mat4(translated.points[0], projPoints.points[0], matrixProj);
				//multiplyVector3Mat4(translated.points[1], projPoints.points[1], matrixProj);
				//multiplyVector3Mat4(translated.points[2], projPoints.points[2], matrixProj);




				//projPoints.points[0].x += 1.f; projPoints.points[0].y += 1.f;
				//projPoints.points[1].x += 1.f; projPoints.points[1].y += 1.f;
				//projPoints.points[2].x += 1.f; projPoints.points[2].y += 1.f;

				//projPoints.points[0].x *= 0.5f * static_cast<float>(getScreenWidth());
				//projPoints.points[0].y *= 0.5f * static_cast<float>(getScreenHeight());
				//projPoints.points[1].x *= 0.5f * static_cast<float>(getScreenWidth());
				//projPoints.points[1].y *= 0.5f * static_cast<float>(getScreenHeight());
				//projPoints.points[2].x *= 0.5f * static_cast<float>(getScreenWidth());
				//projPoints.points[2].y *= 0.5f * static_cast<float>(getScreenHeight());

				drawTriangle(projPoints.points[0].x, projPoints.points[0].y, projPoints.points[1].x, 
						projPoints.points[1].y,	projPoints.points[2].x, projPoints.points[2].y);


			}


		}







};


int main(){
	Cube3d res{};
	if(res.createWindow(130,35,"3d Cube") != 0) return 1;
	res.init();
}

