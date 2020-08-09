#pragma once

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class BlockPartSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	class BlockPartManager
	{
	public:
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector ObtainBlockPartOnTheLeft(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector ObtainBlockPartOnTheRight(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector ObtainBlockPartAcross(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
	};
}

