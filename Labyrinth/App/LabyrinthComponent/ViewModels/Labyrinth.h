#pragma once

#include "Block.h"
#include "MathComponent/Models/Dimensions.h"

#include <tuple>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Labyrinth;
	class BlockSlot;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles
{
	class BlockStyle;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	class Labyrinth
	{
	public:
		Labyrinth(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle&
		);
		Labyrinth(const Labyrinth&);
		const std::vector<std::vector<std::tuple<const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot, int>>>& GetCompleteRouteIndicesList() const;
		const std::vector<std::tuple<const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot, int>>* GetRouteIndicesList(int) const;
		int GetRouteGroupCount() const;
		const TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions& GetDimensions() const;
		const std::vector<std::vector<Block>>& GetBlockGrid() const;
		const Block& GetBlock(const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&) const;
		const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle& GetBlockStyle() const;
	protected:
		std::vector<std::vector<Block>> blockGrid; // make contiguous? Create a class?
		std::vector<std::vector<std::tuple<const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot, int>>> routeIndices;

		TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions dimensions;
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle blockStyle;
	};
}

