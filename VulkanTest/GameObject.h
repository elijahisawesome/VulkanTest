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
			Transform.dimensions = glm::vec3(1.0,1.0,1.0);
			Transform.positon = glm::vec3(0.0,9.0,-8.0);
		}
		transform Transform;

		//This is a horrible way to run this but I literally cannot be bothered
		bool rayCastHit(glm::vec3 rayOrigin ,std::vector<float> Orientation) {
			bool hit = false;

			glm::vec3 sphereCenter = glm::vec3(Transform.positon.x, Transform.positon.y, -Transform.positon.z);
			float sphereRadiusSquered = 5.0f;
			glm::vec3 rayDirection (-Orientation[0], -Orientation[1], -Orientation[2]);
			
			glm::vec3 idealRayDirection = glm::normalize(sphereCenter - rayOrigin);
			
			float result = 0.0f;
			//std::cout<< Transform.positon.x << " " << Transform.positon.y << " " << Transform.positon.z << " " << '\n';
			//std::cout << rayDirection.x << " " << rayDirection.y << " " << rayDirection.z << " RD" << '\n';
			//std::cout << idealRayDirection.x << " " << idealRayDirection.y << " " << idealRayDirection.z << " " << '\n';

			if (glm::intersectRaySphere(rayOrigin, rayDirection, sphereCenter, sphereRadiusSquered, result)) {
				hit = true;
			}

			return hit;
		}
		void updatePosition(glm::vec3 newPos) {
			Transform.positon = newPos;
		}
};