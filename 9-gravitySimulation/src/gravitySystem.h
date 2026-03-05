#pragma once

#include "gameObjects.hpp"
#include <vector>




namespace gravity {


	class GravitySystem 
	{
		public:
			GravitySystem(float gravityPull) : gravityStrength(gravityPull) {}

			const float gravityStrength{};

			void update(std::vector<GameObject>& objs, float deltaTime, unsigned int numSteps = 1)
			{
				const float stepDelta = deltaTime / numSteps;

				for (int i = 0 ; i < numSteps ; i++)
				{
					stepSimulation(objs, stepDelta);
				}

			}

			glm::vec2 computeForce(GameObject& fromObj, GameObject& toObj) const
			{
				auto offset =  fromObj.transform2D.translation - toObj.transform2D.translation;

				float distanceSquared = glm::dot(offset, offset);

				if (glm::abs(distanceSquared) < 1e-10f)
				{
					return {.0f, .0f};
				}

				float force = gravityStrength * toObj.rigidBody2dMass.mass * fromObj.rigidBody2dMass.mass / distanceSquared;

				return force * offset / glm::sqrt(distanceSquared);

			}

		private:
			void stepSimulation(std::vector<GameObject>& physicsObjs, float deltaTime)
			{
					  // Loops through all pairs of objects and applies attractive force between them
				for (auto iterA = physicsObjs.begin(); iterA != physicsObjs.end(); ++iterA) {
				  auto& objA = *iterA;
				  for (auto iterB = iterA; iterB != physicsObjs.end(); ++iterB) {
					if (iterA == iterB) continue;
					auto& objB = *iterB;

					auto force = computeForce(objA, objB);
					objA.rigidBody2dMass.velocity += deltaTime * -force / objA.rigidBody2dMass.mass;
					objB.rigidBody2dMass.velocity += deltaTime * force / objB.rigidBody2dMass.mass;
				  }
				}
				    // update each objects position based on its final velocity
			for (auto& obj : physicsObjs) {
			  obj.transform2D.translation += deltaTime * obj.rigidBody2dMass.velocity;

			  if (obj.transform2D.translation.x > 1 || obj.transform2D.translation.y > 1)
			  {
				  obj.transform2D.translation -= 0.005f;

			  }

			  if (obj.transform2D.translation.x < -1 || obj.transform2D.translation.y < -1)
			  {
				  obj.transform2D.translation += 0.005f;
			  }

		
		}
	}
	};



	class Vec2FieldSystem {
	 	public:
		  void update(
			  const GravitySystem& physicsSystem,
			  std::vector<GameObject>& physicsObjs,
			  std::vector<GameObject>& vectorField) 
		  {
			// For each field line we caluclate the net graviation force for that point in space
			for (auto& vf : vectorField) {
			  glm::vec2 direction{};
			  for (auto& obj : physicsObjs) {
				direction += physicsSystem.computeForce(obj, vf);
			  }

			  // This scales the length of the field line based on the log of the length
			  // values were chosen just through trial and error based on what i liked the look
			  // of and then the field line is rotated to point in the direction of the field
			  vf.transform2D.scale.x =
				  0.005f + 0.045f * glm::clamp(glm::log(glm::length(direction) + 1) / 3.f, 0.f, 1.f);
			  vf.transform2D.rotation = atan2(direction.y, direction.x);
			}
		  }
	};
}
