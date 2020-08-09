#pragma once

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	class Border
	{
	public:
		Border();
		Border(double left, double top, double right, double bottom);

		double left, top, right, bottom;
	};
}

