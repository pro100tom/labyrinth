#include "GeneralSelectorConverter.h"

#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Enums/ActionSelector.h"

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector;

using std::shared_ptr;
using std::make_shared;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	shared_ptr<BlockPartSelector> GeneralSelectorConverter::ObtainBlockPartSelector(ActionSelector action) const
	{
		switch (action)
		{
			case ActionSelector::GoLeft:
				return make_shared<BlockPartSelector>(BlockPartSelector::Left);
			case ActionSelector::GoRight:
				return make_shared<BlockPartSelector>(BlockPartSelector::Right);
			case ActionSelector::GoUp:
				return make_shared<BlockPartSelector>(BlockPartSelector::Top);
			case ActionSelector::GoDown:
				return make_shared<BlockPartSelector>(BlockPartSelector::Bottom);
		}

		return nullptr;
	}

	BlockPartSelector GeneralSelectorConverter::ObtainBlockPartSelector(BlockNeighbourSelector blockNeighbour) const
	{
		return (BlockPartSelector)blockNeighbour;
	}

	ActionSelector GeneralSelectorConverter::ObtainActionSelector(BlockPartSelector blockPartSelector) const
	{
		switch (blockPartSelector)
		{
			case BlockPartSelector::Left:
				return ActionSelector::GoLeft;
			case BlockPartSelector::Right:
				return ActionSelector::GoRight;
			case BlockPartSelector::Top:
				return ActionSelector::GoUp;
		}

		return ActionSelector::GoDown;
	}

	BlockNeighbourSelector GeneralSelectorConverter::ObtainNeighbourSelector(BlockPartSelector blockPartSelector) const
	{
		return (BlockNeighbourSelector)blockPartSelector;
	}
}
