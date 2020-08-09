#include "Route.h"

#include "MathComponent/Models/GeometryModels/Line.h"
#include "LabyrinthComponent/Styles/BlockStyle.h"
#include "LabyrinthComponent/Models/Route.h"
#include "Block.h"

#include <math.h>

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::BlockPartManager;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::RectangleCreationService;
using RouteModel = TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Route;
using LocalRectangle = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle;

using std::vector;
using Gdiplus::PointF;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	Route::Route(const RouteModel& routeModel, const BlockStyle& blockStyle) :	
		rectangleCreationService(blockStyle),
		rectangles(rectangleCreationService.CreateRectangles(routeModel))
	{	

	}

	const vector<LocalRectangle>& Route::GetRectangles() const
	{
		return rectangles;
	}

	const BlockPartManager Route::blockPartManager = BlockPartManager();
}
