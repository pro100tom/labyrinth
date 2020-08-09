#pragma once

#include "MathComponent/Services/TransformationManager.h"

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class BlockPartSelector;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Enums
{
	enum class RightAngleSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	class TransformationManager : public TomasBaranauskas::LabyrinthApp::MathComponent::Services::TransformationManager
	{
	public:
		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector> RotateBlockParts(
			std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector>,
			TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector
		) const;
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector RotateBlockPart(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector
		) const;
	};
}

