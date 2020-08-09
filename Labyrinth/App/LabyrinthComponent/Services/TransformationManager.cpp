#include "TransformationManager.h"

#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "MathComponent/Enums/RightAngleSelector.h"

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector;
using TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector;

using std::vector;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	vector<BlockPartSelector> TransformationManager::RotateBlockParts(
		vector<BlockPartSelector> blockPartSelectors,
		RightAngleSelector rightAngleSelector
	) const {
		vector<BlockPartSelector> rotatedBlockPartSelectors;
		for (auto const& blockPartSelector : blockPartSelectors)
			rotatedBlockPartSelectors.push_back(RotateBlockPart(blockPartSelector, rightAngleSelector));

		return rotatedBlockPartSelectors;
	}

	BlockPartSelector TransformationManager::RotateBlockPart(
		BlockPartSelector blockPartSelector,
		RightAngleSelector angle
	) const {
		vector<BlockPartSelector> clockwiseBlockPartSelectors =
		{
			BlockPartSelector::Left,
			BlockPartSelector::Top,
			BlockPartSelector::Right,
			BlockPartSelector::Bottom
		};

		int shiftIndex = 0;
		switch (angle)
		{
			case RightAngleSelector::Rotate90:
				shiftIndex = 1;
				break;
			case RightAngleSelector::Rotate180:
				shiftIndex = 2;
				break;
			case RightAngleSelector::Rotate270:
				shiftIndex = 3;
			default:
				break;
		}

		int index = 0;
		int size = clockwiseBlockPartSelectors.size();
		for (; index < size; index++)
			if (blockPartSelector == clockwiseBlockPartSelectors[index])
				break;

		return clockwiseBlockPartSelectors[index];
	}
}
