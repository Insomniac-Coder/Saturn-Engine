#include "GameObject.h"

Saturn::GameObject::GameObject()
{
}

Saturn::GameObject::~GameObject()
{
}

void Saturn::GameObject::SetPosition(Position position)
{
	transform.Position = position;
}

void Saturn::GameObject::SetRotation(Rotation rotation)
{
	transform.Rotation = rotation;
}
