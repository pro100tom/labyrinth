#pragma once

#include <memory>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class ActionSelector;
	enum class BlockPartSelector;
	enum class BlockNeighbourSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	class GeneralSelectorConverter
	{
	public:
		std::shared_ptr<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector> ObtainBlockPartSelector(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector
		) const;
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector ObtainBlockPartSelector(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector
		) const;

		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector ObtainActionSelector(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;

		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector ObtainNeighbourSelector(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
	};
}

