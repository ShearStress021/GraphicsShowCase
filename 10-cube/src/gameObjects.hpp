#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



namespace cube{
	

	struct TransformComponent {
		glm::vec3 translation{};
		glm::vec3 scale{1.f, 1.f, 1.f};

		glm::vec3 rotation{};

		glm::mat4 matCal()
		{
			auto transform = glm::translate(glm::mat4{1.f}, translation);

			transform = glm::rotate(transform,rotation.y, {0.f,1.f,0.f});
			transform = glm::rotate(transform,rotation.x, {1.f,0.f,0.f});
			transform = glm::rotate(transform,rotation.z, {0.f,0.f,1.f});
			transform = glm::scale(transform, scale);
			return transform;
		}

		
	};

	struct BodyMass   
	{
		glm::vec2 velocity{};
		float mass{1.f};
	};


	class GameObject {

		public:
			using id_t = unsigned int;

			static GameObject createGameObjects()
			{
				static id_t currectId = 0;
				return GameObject{currectId++};
			}

			id_t getId(){return id;}

			glm::vec3 color{};

			TransformComponent transformCom{};


			BodyMass rigidBody2dMass{};

			GameObject(const GameObject& ) = delete;
			GameObject &operator=(const GameObject& ) = delete;
			GameObject(GameObject && ) = default;
			GameObject &operator=(GameObject&& ) = default;

		private:
			GameObject(id_t objId): id{objId} {}
			id_t id;
	};
}
