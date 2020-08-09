#pragma once

#include "LabyrinthComponent/ViewModels/Labyrinth.h"
#include "LabyrinthComponent/Styles/LabyrinthRenderingStyle.h"

#include <vector>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class BlockSlot;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	class Route;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels
{
	class Line;
	class Rectangle;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	class LabyrinthRenderer
	{
	public:
		LabyrinthRenderer(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels::Labyrinth,
			const HWND&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::LabyrinthRenderingStyle
		);
		bool TryRenderNextLabyrinthRouteGroup(bool = false);
		bool TryRenderLabyrinthRouteGroup(int);
	protected:
		HWND hWnd;
		mutable int routeGroupIndex;
		const int routeGroupCount;
		bool visualInitRequired;
		std::vector<std::vector<HDC>> hdcGrid;
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::LabyrinthRenderingStyle labyrinthRenderingStyle;

		RECT clientRectangle;
		PAINTSTRUCT paintStruct;

		void PrepareRenderingTools();

		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels::Labyrinth labyrinth;

		Gdiplus::RectF ConvertRectangle(
			const TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle&
		) const;
		std::vector<Gdiplus::RectF> ConvertRectangles(
			const std::vector<TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle>&
		) const;
	};
}

