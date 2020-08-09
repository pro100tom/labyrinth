#include "Block.h"

#include "Route.h"
#include "LabyrinthComponent/Models/Block.h"
#include "LabyrinthComponent/Styles/BlockStyle.h"

using BlockModel = TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Block;
using BlockView = TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels::Block;

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle;

using std::vector;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	BlockView::Block(const BlockModel& blockModel, const BlockStyle& blockStyle)
	{
		for (auto const& route : blockModel.GetRoutes())
			routes.push_back(Route(route, blockStyle));
	}

	const vector<Route>& BlockView::GetRoutes() const
	{
		return routes;
	}
}
