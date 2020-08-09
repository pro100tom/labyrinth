#pragma once

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <memory>

#pragma comment (lib, "Gdiplus.lib")

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles
{
	class LabyrinthRenderingStyle
	{
	public:
		LabyrinthRenderingStyle();
		LabyrinthRenderingStyle(const LabyrinthRenderingStyle&);

		std::shared_ptr<Gdiplus::Brush> backgroundBrush;

		std::shared_ptr<Gdiplus::Brush> labyrinthFillBrush;
		std::shared_ptr<Gdiplus::Pen> labyrinthBorderPen;

		std::shared_ptr<Gdiplus::Brush> pathFillBrush;
		std::shared_ptr<Gdiplus::Pen> pathBorderPen;
	protected:
		void InitGdiplus();
	};
}

