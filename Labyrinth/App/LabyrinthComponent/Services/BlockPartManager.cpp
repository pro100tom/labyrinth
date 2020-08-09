#include "BlockPartManager.h"

#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Enums/BlockNeighbourSelector.h"

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	BlockPartSelector BlockPartManager::ObtainBlockPartOnTheLeft(BlockPartSelector blockPart) const
	{
		if (blockPart == BlockPartSelector::Left)
			return BlockPartSelector::Top;

		if (blockPart == BlockPartSelector::Top)
			return BlockPartSelector::Right;

		if (blockPart == BlockPartSelector::Right)
			return BlockPartSelector::Bottom;

		return BlockPartSelector::Left;
	}

	BlockPartSelector BlockPartManager::ObtainBlockPartOnTheRight(BlockPartSelector blockPart) const
	{
		if (blockPart == BlockPartSelector::Left)
			return BlockPartSelector::Bottom;

		if (blockPart == BlockPartSelector::Top)
			return BlockPartSelector::Left;

		if (blockPart == BlockPartSelector::Right)
			return BlockPartSelector::Top;

		return BlockPartSelector::Right;
	}

	BlockPartSelector BlockPartManager::ObtainBlockPartAcross(BlockPartSelector blockPart) const
	{
		if (blockPart == BlockPartSelector::Left)
			return BlockPartSelector::Right;

		if (blockPart == BlockPartSelector::Top)
			return BlockPartSelector::Bottom;

		if (blockPart == BlockPartSelector::Right)
			return BlockPartSelector::Left;

		return BlockPartSelector::Top;
	}
}
