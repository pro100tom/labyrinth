#pragma once

#include "Block.h"
#include "BlockSlot.h"
#include "MathComponent/Models/Dimensions.h"

#include <vector>
#include <tuple>
#include <memory>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class BlockNeighbourSelector;
	enum class RouteGroupSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Route;

	class Labyrinth
	{
	public:
		Labyrinth();
		Labyrinth(const TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions&);

		bool TryAddRoute(
			const Route&,
			const BlockSlot&,
			int routeGroupIndex
		);
		const Block* GetBlock(const BlockSlot&) const;
		const std::vector<std::vector<Block>>& GetBlockGrid() const;
		const Block* GetNeighbourBlock(
			const BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector
		) const;
		std::shared_ptr<BlockSlot> ObtainNeighbourBlockSlot(
			const BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector
		) const;
		const TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions& GetDimensions() const;
		bool IsInBounds(const BlockSlot&) const;
		const std::vector<std::vector<std::tuple<const BlockSlot, int>>>& GetCompleteRouteIndicesList() const;
	protected:
		Block* _GetBlock(const BlockSlot&);

		std::vector<std::vector<Block>> blockGrid;
		std::vector<std::vector<std::tuple<const BlockSlot, int>>> routeIndices;
		TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions dimensions;
	};
}

