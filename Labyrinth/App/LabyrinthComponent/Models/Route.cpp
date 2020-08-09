#include "Route.h"

#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Enums/ActionSelector.h"
#include "Block.h"

#include <optional>

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::GeneralSelectorConverter;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector;

using std::vector;
using std::optional;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	Route::Route() :
		allowToBeMergedTo(false),
		actions(vector<ActionSelector>())
	{

	}

	Route::Route(BlockPartSelector blockPart, ActionSelector action) :
		Route::Route(blockPart, vector<ActionSelector>{ action })
	{

	}

	Route::Route(BlockPartSelector blockPart, const vector<ActionSelector>& actions) :
		allowToBeMergedTo(false),
		startingBlockPart(blockPart),
		actions(actions)
	{

	}

	optional<BlockPartSelector> Route::GetStartingBlockPart() const
	{
		return startingBlockPart;
	}

	vector<BlockPartSelector> Route::GetDestinationBlockParts() const
	{
		vector<BlockPartSelector> destinationBlockParts;

		for (auto const& action : this->actions)
		{
			auto destinationBlockPart = generalSelectorConverter.ObtainBlockPartSelector(action);
			if (destinationBlockPart != nullptr)
				destinationBlockParts.push_back(*destinationBlockPart);
		}

		return destinationBlockParts;
	}

	bool Route::IsPartInUse(BlockPartSelector blockPartSelector) const
	{
		if (this->startingBlockPart == blockPartSelector)
			return true;

		for (auto const& action : this->actions)
		{
			auto partPositionFromAction = generalSelectorConverter.ObtainBlockPartSelector(action);
			if (partPositionFromAction == nullptr)
				continue;

			if (*partPositionFromAction == blockPartSelector)
				return true;
		}

		return false;
	}

	vector<BlockPartSelector> Route::GetBlockPartsInUse() const
	{
		vector<BlockPartSelector> blockPartsInUse;
		if (!startingBlockPart.has_value())
			return blockPartsInUse;

		blockPartsInUse.push_back(startingBlockPart.value());

		auto destinationBlockparts = GetDestinationBlockParts();
		blockPartsInUse.insert(std::end(blockPartsInUse), std::begin(destinationBlockparts), std::end(destinationBlockparts));
		
		return blockPartsInUse;
	}

	void Route::SetRoute(BlockPartSelector blockPartSelector, ActionSelector action)
	{
		startingBlockPart = blockPartSelector;
		this->actions = vector<ActionSelector>{ action };
	}

	void Route::SetRoute(BlockPartSelector blockPartSelector, const vector<ActionSelector>& actions)
	{
		startingBlockPart = blockPartSelector;
		this->actions = actions;
	}

	const vector<ActionSelector>& Route::GetActions() const
	{
		return actions;
	}

	const GeneralSelectorConverter Route::generalSelectorConverter = GeneralSelectorConverter();
}
