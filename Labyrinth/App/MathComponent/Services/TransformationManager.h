#pragma once

#include "MathComponent/Services/AngleManager.h"

#include <vector>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Enums
{
	enum class RightAngleSelector;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	class Rectangle;
	class Border;
	class Line;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Services
{
	class TransformationManager
	{
	public:
		const static TomasBaranauskas::LabyrinthApp::MathComponent::Services::AngleManager angleManager;

		Gdiplus::PointF TranslatePoint(
			Gdiplus::PointF,
			double horizontalOffset,
			double verticalOffset
		) const;
		std::vector<Gdiplus::PointF> TranslatePoints(
			std::vector<Gdiplus::PointF>,
			double horizontalOffset,
			double verticalOffset
		) const;

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line TranslateLine(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line line,
			double horizontalOffset,
			double verticalOffset
		) const;
		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line> TranslateLines(
			std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line> lines,
			double horizontalOffset,
			double verticalOffset
		) const;

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle TranslateRectangle(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle,
			double horizontalOffset,
			double verticalOffset
		) const;
		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle> TranslateRectangles(
			std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle>,
			double horizontalOffset,
			double verticalOffset
		) const;

		Gdiplus::PointF RotatePoint(
			Gdiplus::PointF point,
			double angle,
			Gdiplus::PointF center = Gdiplus::PointF(0, 0)
		) const;
		std::vector<Gdiplus::PointF> RotatePoints(
			std::vector<Gdiplus::PointF> points,
			double angle,
			Gdiplus::PointF center = Gdiplus::PointF(0, 0)
		) const;

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line RotateLine(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line line,
			double angle,
			Gdiplus::PointF center = Gdiplus::PointF(0, 0)
		) const;
		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line> RotateLines(
			std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line> lines,
			double angle,
			Gdiplus::PointF center = Gdiplus::PointF(0, 0)
		) const;

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border RotateBorder(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border,
			TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector
		) const;
		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border> RotateBorders(
			std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border>,
			TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector
		) const;

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle RotateRectangle(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle,
			TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector,
			Gdiplus::PointF
		) const;
		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle> RotateRectangles(
			std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle>,
			TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector,
			Gdiplus::PointF center
		) const;
	};
}

