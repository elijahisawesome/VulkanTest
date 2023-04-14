#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>


class GameObject {
	public:
		struct transform {
			glm::vec3 rotation;
			glm::vec3 positon;
			glm::vec3 dimensions;
		};
		GameObject() {
			//mt = MT;
			Transform.dimensions = glm::vec3(1.0,1.0,1.0);
			Transform.positon = glm::vec3(0.0,9.0,8.0);
		}
		transform Transform;
		//ModelsAndTextures *mt;
		// 
		//This is a horrible way to run this but I literally cannot be bothered
		bool rayCastHit(glm::vec3 rayOrigin ,glm::vec3 rayDirection) {
			bool hit = false;

			glm::vec3 sphereCenter = glm::vec3(Transform.positon.x, Transform.positon.y, -Transform.positon.z);
			float sphereRadiusSquered = 5.0f;

			float result = 0.0f;
			//std::cout<< Transform.positon.x << " " << Transform.positon.y << " " << Transform.positon.z << " " << '\n';
			//std::cout << rayOrigin.x << " " << rayOrigin.y << " " << rayOrigin.z << " " << '\n';

			if (glm::intersectRaySphere(rayOrigin, rayDirection, sphereCenter, sphereRadiusSquered, result)) {
				hit = true;
			}

			std::cout<<result;

			return hit;
		}
		void updatePosition(glm::vec3 newPos) {
			Transform.positon = newPos;
		}
};