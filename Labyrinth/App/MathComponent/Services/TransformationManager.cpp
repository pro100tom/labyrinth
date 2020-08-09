#include "TransformationManager.h"

#include "MathComponent/Enums/RightAngleSelector.h"
#include "MathComponent/Models/GeometryModels/Line.h"
#include "MathComponent/Models/GeometryModels/Rectangle.h"
#include "MathComponent/Models/GeometryModels/Border.h"

#include <cmath>

using TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector;
using TomasBaranauskas::LabyrinthApp::MathComponent::Services::TransformationManager;
using TomasBaranauskas::LabyrinthApp::MathComponent::Services::AngleManager;
using TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line;
using LocalRectangle = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle;
using TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border;

using Gdiplus::PointF;

using std::vector;

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Services
{
	PointF TransformationManager::TranslatePoint(PointF point, double horizontalOffset, double verticalOffset) const
	{
		point.X += horizontalOffset;
		point.Y += verticalOffset;

		return point;
	}

	vector<PointF> TransformationManager::TranslatePoints(vector<PointF> points, double horizontalOffset, double verticalOffset) const
	{
		auto translatedPoints = vector<PointF>();
		for (auto point : points)
			translatedPoints.push_back(TranslatePoint(point, horizontalOffset, verticalOffset));

		return translatedPoints;
	}

	Line TransformationManager::TranslateLine(Line line, double horizontalOffset, double verticalOffset) const
	{
		line.from = TranslatePoint(line.from, horizontalOffset, verticalOffset);
		line.to = TranslatePoint(line.to, horizontalOffset, verticalOffset);

		return line;
	}

	vector<Line> TransformationManager::TranslateLines(vector<Line> lines, double horizontalOffset, double verticalOffset) const
	{
		vector<Line> newLines;

		for (auto line : lines)
			newLines.push_back(TranslateLine(line, horizontalOffset, verticalOffset));

		return newLines;
	}

	LocalRectangle TransformationManager::TranslateRectangle(
		LocalRectangle rectangle,
		double horizontalOffset,
		double verticalOffset
	) const {
		rectangle.topLeft.X += horizontalOffset;
		rectangle.topLeft.Y += verticalOffset;

		return rectangle;
	}

	vector<LocalRectangle> TransformationManager::TranslateRectangles(
		vector<LocalRectangle> rectangles,
		double horizontalOffset,
		double verticalOffset
	) const {
		vector<LocalRectangle> translatedRectangles;

		for (auto const& rectangle : rectangles)
			translatedRectangles.push_back(TranslateRectangle(rectangle, horizontalOffset, verticalOffset));

		return translatedRectangles;
	}

	PointF TransformationManager::RotatePoint(Gdiplus::PointF point, double angle, Gdiplus::PointF center) const
	{
		if (!angleManager.IsFullCircle(angle))
			return point;

		auto transformedPoint = Gdiplus::PointF();
		double angleRad = angleManager.DegreesToRadians(angle);
		double cosAngle = std::cos(angleRad);
		double sinAngle = std::sin(angleRad);

		transformedPoint.X = round(cosAngle * (point.X - center.X) - sinAngle * (point.Y - center.Y) + center.X);
		transformedPoint.Y = round(sinAngle * (point.X - center.X) + cosAngle * (point.Y - center.Y) + center.Y);

		return transformedPoint;
	}

	vector<PointF> TransformationManager::RotatePoints(vector<PointF> points, double angle, PointF center) const
	{
		auto rotatedPoints = vector<PointF>();
		for (auto point : points)
			rotatedPoints.push_back(RotatePoint(point, angle, center));

		return rotatedPoints;
	}

	Line TransformationManager::RotateLine(Line line, double angle, PointF center) const
	{
		if (!angleManager.IsFullCircle(angle))
			return line;

		Line rotatedLine = Line();

		rotatedLine.from = RotatePoint(line.from, angle, center);
		rotatedLine.to = RotatePoint(line.to, angle, center);

		return rotatedLine;
	}

	vector<Line> TransformationManager::RotateLines(vector<Line> lines, double angle, PointF center) const
	{
		if (!angleManager.IsFullCircle(angle))
			return lines;

		auto rotatedLines = vector<Line>();

		for (auto const& line : lines)
			rotatedLines.push_back(RotateLine(line, angle, center));

		return rotatedLines;
	}

	Border TransformationManager::RotateBorder(Border border, RightAngleSelector angle) const
	{
		vector<double*> borderValues =
		{
			&border.left,
			&border.top,
			&border.right,
			&border.bottom
		};

		auto rotatedBorder = Border();
		vector<double*> rotatedBorderValues =
		{
			&rotatedBorder.left,
			&rotatedBorder.top,
			&rotatedBorder.right,
			&rotatedBorder.bottom
		};

		int shiftIndex = 0;
		switch (angle)
		{
			case RightAngleSelector::Rotate90:
				shiftIndex = 1;
				break;
			case RightAngleSelector::Rotate180:
				shiftIndex = 2;
				break;
			case RightAngleSelector::Rotate270:
				shiftIndex = 3;
			default:
				break;
		}

		int size = borderValues.size();
		for (int i = 0; i < size; i++)
			*rotatedBorderValues[(i + shiftIndex) % size] = *borderValues[i];

		return rotatedBorder;
	}

	vector<Border> TransformationManager::RotateBorders(vector<Border> borders, RightAngleSelector angle) const
	{
		auto rotatedBorders = vector<Border>();
		for (auto const& border : borders)
			rotatedBorders.push_back(RotateBorder(border, angle));

		return rotatedBorders;
	}

	LocalRectangle TransformationManager::RotateRectangle(
		LocalRectangle rectangle,
		RightAngleSelector angle,
		PointF center
	) const {
		if (!angleManager.IsFullCircle((int)angle))
			return rectangle;

		vector<PointF> points =
		{
			PointF(rectangle.topLeft.X, rectangle.topLeft.Y),
			PointF(rectangle.topLeft.X + rectangle.width, rectangle.topLeft.Y),
			PointF(rectangle.topLeft.X, rectangle.topLeft.Y + rectangle.height),
			PointF(rectangle.topLeft.X + rectangle.width, rectangle.topLeft.Y + rectangle.height)
		};

		auto rotatedPoints = RotatePoints(points, (double)angle, center);

		double leftMost = rotatedPoints[0].X;
		double topMost = rotatedPoints[0].Y;
		double rightMost = rotatedPoints[0].X;
		double bottomMost = rotatedPoints[0].Y;

		for (auto const& point : rotatedPoints)
		{
			if (point.X < leftMost)
				leftMost = point.X;

			if (point.X > rightMost)
				rightMost = point.X;

			if (point.Y < topMost)
				topMost = point.Y;

			if (point.Y > bottomMost)
				bottomMost = point.Y;
		}

		auto rotatedRectangle = LocalRectangle(PointF(leftMost, topMost), rightMost - leftMost, bottomMost - topMost);
		rotatedRectangle.border = RotateBorder(rectangle.border, angle);

		return rotatedRectangle;
	}

	vector<LocalRectangle> TransformationManager::RotateRectangles(
		vector<LocalRectangle> rectangles,
		RightAngleSelector angle,
		PointF center
	) const {
		vector<LocalRectangle> rotatedRectangles;

		for (auto const& rectangle : rectangles)
			rotatedRectangles.push_back(RotateRectangle(rectangle, angle, center));

		return rotatedRectangles;
	}

	const AngleManager TransformationManager::angleManager = AngleManager();
}
