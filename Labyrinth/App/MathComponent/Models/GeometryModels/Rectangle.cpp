#include "Rectangle.h"

#include "Line.h"

using TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line;

using Gdiplus::PointF;
using std::vector;

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	Rectangle::Rectangle() :
		Rectangle::Rectangle(PointF(), 10.0, 10.0)
	{

	}

	Rectangle::Rectangle(const PointF& point, double width, double height) :
		Rectangle::Rectangle(point, width, height, Border())
	{

	}

	Rectangle::Rectangle(const PointF& point, double width, double height, const Border& border) :
		topLeft(point),
		width(width),
		height(height),
		border(border)
	{

	}

	vector<Line> Rectangle::GetBorderLines() const
	{
		auto borderLines = vector<Line>();

		auto topRight = GetTopRight();
		auto bottomLeft = GetBottomLeft();
		auto bottomRight = GetBottomRight();

		if (border.left > 0)
			borderLines.push_back(Line(topLeft, bottomLeft, border.left));

		if (border.top > 0)
			borderLines.push_back(Line(topLeft, topRight, border.top));

		if (border.right > 0)
			borderLines.push_back(Line(topRight, bottomRight, border.right));

		if (border.bottom > 0)
			borderLines.push_back(Line(bottomLeft, bottomRight, border.bottom));

		return borderLines;
	}

	PointF Rectangle::GetTopRight() const
	{
		return PointF(topLeft.X + width, topLeft.Y);
	}

	PointF Rectangle::GetBottomLeft() const
	{
		return PointF(topLeft.X, topLeft.Y + height);
	}

	PointF Rectangle::GetBottomRight() const
	{
		return PointF(topLeft.X + width, topLeft.Y + height);
	}
}
