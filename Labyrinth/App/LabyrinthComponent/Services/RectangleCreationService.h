#pragma once

#include "LabyrinthComponent/Services/BlockPartManager.h"
#include "LabyrinthComponent/Styles/BlockStyle.h"
#include "LabyrinthComponent/Services/TransformationManager.h"
#include "MathComponent/Models/GeometryModels/Border.h"

#include <vector>
#include <optional>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class BlockPartSelector;
	enum class ActionSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Route;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	class Rectangle;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Enums
{
	enum class RightAngleSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	class RectangleCreationService
	{
	public:
		RectangleCreationService();
		RectangleCreationService(const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle&);

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle CreateLeftRectangle(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border(0, 1, 0, 1)
		) const;
		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle CreateLeftDeadendRectangle(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border(0, 1, 1, 1)
		) const;
		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle CreateRectangle(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border(0, 1, 0, 1),
			bool = false
		) const;
		std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle> CreateRectangles(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Route&
		) const;
		TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle CreateCenterRectangle(
			TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border()
		) const;
		TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector ObtainRectangleRotationAngle(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;

		const static TransformationManager transformationManager;
		const static BlockPartManager blockPartManager;

		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle blockStyle;
	};
}

