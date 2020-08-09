#pragma once

#include "Border.h"

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>

#pragma comment (lib, "Gdiplus.lib") 

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	class Line;

	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(const Gdiplus::PointF&, double, double);
		Rectangle(const Gdiplus::PointF&, double, double, const Border&);

		std::vector<Line> GetBorderLines() const;

		Gdiplus::PointF topLeft;
		double width, height;

		Border border;
	protected:
		//const Gdiplus::PointF& GetTopLeft() const;
		Gdiplus::PointF GetTopRight() const;
		Gdiplus::PointF GetBottomLeft() const;
		Gdiplus::PointF GetBottomRight() const;
	};
}

