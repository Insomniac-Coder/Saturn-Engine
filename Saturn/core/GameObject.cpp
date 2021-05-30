#include "GameObject.h"

void Saturn::GameObject::SetModelMatrix()
{
	model = glm::translate(model, g_Position);
	model = glm::rotate(model, g_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, g_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, g_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}
