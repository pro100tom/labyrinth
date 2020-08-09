#pragma once

#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Enums/ActionSelector.h"
#include "LabyrinthComponent/Services/GeneralSelectorConverter.h"

#include <vector>
#include <optional>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Block;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Route
	{
	public:
		Route();
		Route(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector
		);
		Route(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			const std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector>&
		);

		std::optional<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector> GetStartingBlockPart() const;
		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector> GetDestinationBlockParts() const;
		bool IsPartInUse(TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector) const;
		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector> GetBlockPartsInUse() const;
		void SetRoute(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector
		);
		void SetRoute(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			const std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector>&
		);

		const std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector>& GetActions() const;

		bool allowToBeMergedTo;

		const static TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::GeneralSelectorConverter generalSelectorConverter;
	protected:
		std::optional<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector> startingBlockPart;
		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector> actions;
	};
}

