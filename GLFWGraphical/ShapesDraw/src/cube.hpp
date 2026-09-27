#pragma once
#include <vector>
#include "drawUtils.hpp"
#include <iostream>

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


class Cube3d  {
	public:
		void createCube() {
			//std::cout << "Hello, World\n";

			createPerceptionPespective();
			drawCube();

		}

	private:
		void multiplyVector3Mat4(Vector3 &in , Vector3 &res, Mat4 &mat4){
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
			float aspectRatio {static_cast<float>(HEIGHT)/static_cast<float>(WIDTH)};
			float fieldOfView{90.f};
			float fieldOfViewRad{1.0f/std::tanf(fieldOfView * 0.5 * 3.14159f / 180)};

			matrixProj.mat[0][0] = aspectRatio * fieldOfViewRad;
			matrixProj.mat[1][1] = fieldOfViewRad;
			matrixProj.mat[2][2] =  farPlane / (farPlane - nearPlane);
			matrixProj.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
			matrixProj.mat[2][3] = 1.0f;
			matrixProj.mat[3][3] = 0.0f;


		}
		void drawCube(){
			cubePoints.triangles = {
				// SOUTH
				{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f    },
				{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f    },
				//
				// EAST                                                      
				{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f    },
				{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f    },
				// 																								//
				// NORTH                                                     
				{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f    },
				{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f    },

				// WEST		                                               
				{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f    },
				{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f    },

				// TOP
				{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f    },
				{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f    },
				// 																
				// BOTTOM
				{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f    },
				{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f    },
			};

			
			




			for (auto tri : cubePoints.triangles) {
				TrianglePoints projPoints, translated;
				translated = tri;
				for(auto& p : translated.points) p.z += 3.f;

				for(int i {}; i < 3; i++){
					multiplyVector3Mat4(translated.points[i], projPoints.points[i], matrixProj);
					projPoints.points[i].x = (projPoints.points[i].x + 1.f) * 0.5f * static_cast<float>(WIDTH);
					projPoints.points[i].y = (projPoints.points[i].y + 1.f) * 0.5f * static_cast<float>(HEIGHT);

				}



				Color white{255,255,255};


				drawTriangle(projPoints.points[0].x, projPoints.points[0].y, projPoints.points[1].x,
						projPoints.points[1].y,projPoints.points[2].x, projPoints.points[2].y,white);



			}



		}




	private:
		Vertex cubePoints{};
		Mat4 matrixProj{};
};
