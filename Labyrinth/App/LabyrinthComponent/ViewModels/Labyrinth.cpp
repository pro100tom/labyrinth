#include "Labyrinth.h"

#include "LabyrinthComponent/Models/Labyrinth.h"
#include "LabyrinthComponent/Models/BlockSlot.h"
#include "LabyrinthComponent/Styles/BlockStyle.h"

using LabyrinthModel = TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot;
using BlockModel = TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Block;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle;
using TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions;

using std::vector;
using std::tuple;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	Labyrinth::Labyrinth(const LabyrinthModel& labyrinthModel, const BlockStyle& blockStyle) :
		dimensions(labyrinthModel.GetDimensions()),
		routeIndices(labyrinthModel.GetCompleteRouteIndicesList()),
		blockStyle(blockStyle)
	{
		for (int columnIndex = 0; columnIndex < dimensions.numberOfColumns; columnIndex++)
		{
			blockGrid.push_back(vector<Block>());
			for (int rowIndex = 0; rowIndex < dimensions.numberOfRows; rowIndex++)
			{
				auto blockModel = labyrinthModel.GetBlock(BlockSlot(columnIndex, rowIndex));
				if (blockModel == nullptr)
					continue;

				blockGrid[columnIndex].push_back(Block(*blockModel, blockStyle));
			}
		}
	}

	Labyrinth::Labyrinth(const Labyrinth& labyrinth) :
		dimensions(labyrinth.dimensions),
		routeIndices(vector<vector<tuple<const BlockSlot, int>>>(labyrinth.routeIndices)),
		blockGrid(vector<vector<Block>>(labyrinth.blockGrid)),
		blockStyle(labyrinth.blockStyle)
	{
		
	}

	const vector<vector<tuple<const BlockSlot, int>>>& Labyrinth::GetCompleteRouteIndicesList() const
	{
		return routeIndices;
	}

	const vector<tuple<const BlockSlot, int>>* Labyrinth::GetRouteIndicesList(int step) const
	{
		if (step < 0 || step >= routeIndices.size())
			return nullptr;

		return &routeIndices[step];
	}
	
	int Labyrinth::GetRouteGroupCount() const
	{
		return routeIndices.size();
	}

	const Dimensions& Labyrinth::GetDimensions() const
	{
		return dimensions;
	}

	const vector<vector<Block>>& Labyrinth::GetBlockGrid() const
	{
		return blockGrid;
	}

	const Block& Labyrinth::GetBlock(const BlockSlot& blockSlot) const
	{
		return blockGrid[blockSlot.columnIndex][blockSlot.rowIndex];
	}

	const BlockStyle& Labyrinth::GetBlockStyle() const
	{
		return blockStyle;
	}
}

