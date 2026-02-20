#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>


namespace rectangle{


	struct TransformComponent{
		glm::vec2 translation{};
		glm::vec2 scale{1.f, 1.f};
		float rotation{};

		glm::mat2 mat2() {

			const float s{glm::sin(rotation)};
			const float c{glm::cos(rotation)};

			glm::mat2 rotMatrix{{c, s}, {-s, c}};

			glm::mat2 scaleMat{{scale.x, 0.f}, {0.f, scale.y}};
//			return scaleMat * rotMatrix;
			return rotMatrix * scaleMat;
		}

	};
	class GameObject {

		public:
			using id_t = unsigned int;

			static GameObject createGameObjects()
			{
				static id_t currentId = 0;
				return GameObject{currentId++};
			}

			id_t getId(){return id;};


			
			glm::vec3 color{};

			TransformComponent transform2D{};


			GameObject(const GameObject& ) = delete;
			GameObject &operator=(const GameObject& ) = delete;
			GameObject(GameObject && ) = default;
			GameObject &operator=(GameObject&& ) = default;

		private:
			GameObject(id_t objId) : id{objId} {}
			id_t id;


	};


}
