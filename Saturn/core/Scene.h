#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <vector>
#include <unordered_map>

namespace Saturn {

	class Scene
	{

	public:
		std::unordered_map<int, Saturn::GameObject> s_GameObjects;
		void AddGameObject();

	private:
		Scene* nextScene;

	};

}

#endif SCENE_H

