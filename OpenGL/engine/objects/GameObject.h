#pragma once
#include <iostream>
#include <map>
#include "engine/Utils/Utility.h"

namespace Extonic {
	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(const GameObject& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{

		}
	private:
		Extonic::Array<class, 10> components;
	};
}