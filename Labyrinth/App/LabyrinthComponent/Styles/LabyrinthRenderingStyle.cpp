#include "LabyrinthRenderingStyle.h"

using Gdiplus::Brush;
using Gdiplus::SolidBrush;
using Gdiplus::Pen;
using Gdiplus::Color;
using Gdiplus::GdiplusStartupInput;
using std::shared_ptr;
using std::make_shared;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles
{
	LabyrinthRenderingStyle::LabyrinthRenderingStyle()
	{
		InitGdiplus();

		backgroundBrush = shared_ptr<Brush>(new SolidBrush(Color(112, 120, 146)));
		labyrinthFillBrush = shared_ptr<Brush>(new SolidBrush(Color(231, 235, 248)));
		labyrinthBorderPen = shared_ptr<Pen>(new Pen(Color(30, 0, 0)));
		pathFillBrush = shared_ptr<Brush>(new SolidBrush(Color(164, 172, 200)));
		pathBorderPen = shared_ptr<Pen>(new Pen(Color(30, 0, 0)));
	}

	LabyrinthRenderingStyle::LabyrinthRenderingStyle(const LabyrinthRenderingStyle& labyrinthRenderingStyle)
	{
		InitGdiplus();
		
		backgroundBrush = labyrinthRenderingStyle.backgroundBrush;
		labyrinthFillBrush = labyrinthRenderingStyle.labyrinthFillBrush;
		labyrinthBorderPen = labyrinthRenderingStyle.labyrinthBorderPen;
		pathFillBrush = labyrinthRenderingStyle.pathFillBrush;
		pathBorderPen = labyrinthRenderingStyle.pathBorderPen;
	}

	void LabyrinthRenderingStyle::InitGdiplus()
	{
		ULONG_PTR gdiplusToken;
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
}