#pragma once

#include "LabyrinthComponent/Services/BlockPartManager.h"
#include "LabyrinthComponent/Services/RectangleCreationService.h"
#include "MathComponent/Models/GeometryModels/Rectangle.h"

#include <vector>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles
{
	class BlockStyle;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	class Route
	{
	public:
		Route(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Route&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle&
		);

		const std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle>& GetRectangles() const;

		const static TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::BlockPartManager blockPartManager;
	protected:
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::RectangleCreationService rectangleCreationService;

		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle> rectangles;
	};
}

