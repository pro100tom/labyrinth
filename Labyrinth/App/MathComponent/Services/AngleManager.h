#pragma once

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Services
{
	class AngleManager
	{
	public:
		double DegreesToRadians(double degrees) const;
		bool IsFullCircle(double angle) const;

		static const double PI;
	};
}

