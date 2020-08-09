#include "Block.h"

#include "Route.h"
#include "BlockSlot.h"
#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Services/BlockPartManager.h"

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector;

using std::vector;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	Block::Block() : 
		routes(vector<Route>())
	{

	}

	Block::Block(const Block& block) :
		blockSlot(block.blockSlot), // Debugging
		routes(vector<Route>(block.routes))
	{

	}

	bool Block::HasRoutes() const
	{
		return routes.size() == 0;
	}

	bool Block::IsPartInUse(BlockPartSelector blockPartPosition) const
	{
		for (auto const& route : routes)
			if (route.IsPartInUse(blockPartPosition))
				return true;

		return false;
	}

	bool Block::IsCentreIsUse() const
	{
		for (auto const& route : routes)
			if (route.GetBlockPartsInUse().size() > 1)
				return true;

		return false;
	}

	const vector<Route>& Block::GetRoutes() const
	{
		return routes;
	}

	void Block::AddRoute(const Route& route)
	{
		// Todo: need to test whether there is enough room to add the route
		this->routes.push_back(route);
	}
}
