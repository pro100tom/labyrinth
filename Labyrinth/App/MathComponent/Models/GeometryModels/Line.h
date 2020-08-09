#pragma once

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	class Line
	{
	public:
		Line();
		Line(Gdiplus::PointF, Gdiplus::PointF);
		Line(Gdiplus::PointF, Gdiplus::PointF, double);

		Gdiplus::PointF from, to;
		double thickness;
	};
}

