#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <chrono>

using Position = glm::vec3;
using Rotation = glm::vec3;

namespace Saturn {

	struct Transform
	{
		Position Position;
		Rotation Rotation;
	};

	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		inline Transform GetTransform() const { return transform; }
		void SetPosition(Position position);
		void SetRotation(Rotation rotation);

	private:
		Transform transform = {
								Position(0.0f),
								Rotation(0.0f)
								};


	};
}

#endif GAMEOBJECT_H