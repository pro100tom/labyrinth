#include "Border.h"

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	Border::Border() :
		Border::Border(0.0, 0.0, 0.0, 0.0)
	{

	}

	Border::Border(double left, double top, double right, double bottom) :
		left(left),
		top(top),
		right(right),
		bottom(bottom)
	{

	}
}
