#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef glm::vec3 position;
typedef glm::vec3 rotation;

namespace Saturn {

	class Scene;

	class GameObject
	{
	public:
		inline position GetPosition() const { return g_Position; }
		inline rotation GetRotation() const { return g_Rotation; }
		inline void SetPosition(position pos) { g_Position =  pos; }
		inline void SetRotation(rotation rot) { g_Rotation = rot; }

	protected:
		void SetModelMatrix();

	private:
		position g_Position = position(0.0f);
		rotation g_Rotation = rotation(0.0f);
		glm::mat4 model = glm::mat4(1.0f);
	};

}

#endif GAMEOBJECT_H