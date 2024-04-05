#pragma once
#include "../Camera.hpp"
#include "stdafx.h"


namespace models {
	class FirstPersonCamera : public Camera
	{
		public:
		FirstPersonCamera(std::string name, float fieldOfView);
	};
}


