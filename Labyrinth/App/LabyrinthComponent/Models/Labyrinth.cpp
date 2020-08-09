#include "Labyrinth.h"

#include "BlockSlot.h"
#include "Route.h"
#include "LabyrinthComponent/Enums/BlockNeighbourSelector.h"
#include "LabyrinthComponent/Enums/RouteGroupSelector.h"

using TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::RouteGroupSelector;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector;

using std::vector;
using std::tuple;
using std::shared_ptr;
using std::make_shared;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	Labyrinth::Labyrinth() :
		Labyrinth::Labyrinth(Dimensions())
	{

	}

	Labyrinth::Labyrinth(const Dimensions& dimensions) :
		dimensions(dimensions)
	{
		blockGrid = vector<vector<Block>>(this->dimensions.numberOfColumns, vector<Block>(this->dimensions.numberOfRows));

		//Debugging
		/*
		for (int row = 0; row < dimensions.numberOfRows; row++)
			for (int column = 0; column < dimensions.numberOfColumns; column++)
				blockGrid[column][row] = Block();
		*/
		for (int rowIndex = 0; rowIndex < dimensions.numberOfRows; rowIndex++)
		{
			for (int columnIndex = 0; columnIndex < dimensions.numberOfColumns; columnIndex++)
			{
				auto block = Block();
				block.blockSlot = BlockSlot(columnIndex, rowIndex);
				blockGrid[columnIndex][rowIndex] = block;
			}
		}
	}

	const Block* Labyrinth::GetBlock(const BlockSlot& blockSlot) const
	{
		if (!IsInBounds(blockSlot))
			return nullptr;

		return &blockGrid[blockSlot.columnIndex][blockSlot.rowIndex];
	}

	Block* Labyrinth::_GetBlock(const BlockSlot& blockSlot)
	{
		if (!IsInBounds(blockSlot))
			return nullptr;

		return &blockGrid[blockSlot.columnIndex][blockSlot.rowIndex];
	}

	bool Labyrinth::TryAddRoute(
		const Route& route,
		const BlockSlot& blockSlot,
		int routeGroupIndex
	) {
		auto block = _GetBlock(blockSlot);
		if (block == nullptr)
			return false;

		block->AddRoute(route);
		int routeIndex = block->GetRoutes().size() - 1;

		while (routeIndices.size() <= routeGroupIndex)
			routeIndices.push_back(vector<tuple<const BlockSlot, int>>());

		routeIndices[routeGroupIndex].push_back({ blockSlot, routeIndex });

		return true;
	}

	const vector<vector<Block>>& Labyrinth::GetBlockGrid() const
	{
		return blockGrid;
	}

	const Block* Labyrinth::GetNeighbourBlock(
		const BlockSlot& blockSlot,
		BlockNeighbourSelector blockNeighbourSelector
	) const {
		auto neighbourBlockSlot = ObtainNeighbourBlockSlot(blockSlot, blockNeighbourSelector);
		if (neighbourBlockSlot == nullptr)
			return nullptr;

		return GetBlock(*neighbourBlockSlot);
	}

	shared_ptr<BlockSlot> Labyrinth::ObtainNeighbourBlockSlot(
		const BlockSlot& blockSlot,
		BlockNeighbourSelector blockNeighbourSelector
	) const {
		int horizontalOffset = 0;
		int verticalOffset = 0;

		switch (blockNeighbourSelector)
		{
			case BlockNeighbourSelector::Above:
				verticalOffset = -1;
				break;
			case BlockNeighbourSelector::Below:
				verticalOffset = 1;
				break;
			case BlockNeighbourSelector::OnTheLeft:
				horizontalOffset = -1;
				break;
			case BlockNeighbourSelector::OnTheRight:
				horizontalOffset = 1;
				break;
			default:
				break;
		}

		auto neighbourBlockSlot = BlockSlot(blockSlot.columnIndex + horizontalOffset, blockSlot.rowIndex + verticalOffset);
		if (!IsInBounds(neighbourBlockSlot))
			return nullptr;

		return make_shared<BlockSlot>(neighbourBlockSlot);
	}

	const Dimensions& Labyrinth::GetDimensions() const
	{
		return dimensions;
	}

	bool Labyrinth::IsInBounds(const BlockSlot& blockSlot) const
	{
		if (blockSlot.columnIndex < 0 || blockSlot.columnIndex >= dimensions.numberOfColumns)
			return false;

		if (blockSlot.rowIndex < 0 || blockSlot.rowIndex >= dimensions.numberOfRows)
			return false;

		return true;
	}

	const vector<vector<tuple<const BlockSlot, int>>>& Labyrinth::GetCompleteRouteIndicesList() const
	{
		return routeIndices;
	}
}
