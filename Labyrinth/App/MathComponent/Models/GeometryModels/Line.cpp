#include "Line.h"

using Gdiplus::PointF;

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	Line::Line() :
		Line::Line(PointF(), PointF(10.0, 10.0))
	{

	}

	Line::Line(PointF from, PointF to) :
		from(from),
		to(to),
		thickness(1.0)
	{

	}

	Line::Line(PointF from, PointF to, double thickness) :
		from(from),
		to(to),
		thickness(thickness)
	{

	}
}
