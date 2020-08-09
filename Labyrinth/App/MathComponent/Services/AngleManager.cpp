#include "AngleManager.h"

#include <cmath>

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Services
{
	double AngleManager::DegreesToRadians(double degrees) const
	{
		return degrees * PI / 180.0;
	}

	bool AngleManager::IsFullCircle(double angle) const
	{
		return (bool)((int)(angle + 360) % 360);
	}

	const double AngleManager::PI = std::acos(-1);
}