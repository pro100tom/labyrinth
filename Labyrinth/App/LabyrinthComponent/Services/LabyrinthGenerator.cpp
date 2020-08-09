#include "LabyrinthGenerator.h"

#include "LabyrinthComponent/Models/Block.h"
#include "LabyrinthComponent/Models/BlockSlot.h"
#include "LabyrinthComponent/Models/Route.h"
#include "LabyrinthComponent/Models/Labyrinth.h"
#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Enums/ActionSelector.h"
#include "LabyrinthComponent/Enums/RouteGroupSelector.h"
#include "LabyrinthComponent/Enums/BlockNeighbourSelector.h"
#include "MathComponent/Models/Dimensions.h"
#include "GeneralComponent/Services/RecursionDepthHandler.h"

#include <vector>
#include <tuple>
#include <optional>
#include <algorithm>

using namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models;
using namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums;

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Settings::LabyrinthGeneratorSettings;
using TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions;
using TomasBaranauskas::LabyrinthApp::MathComponent::Services::AngleManager;
using TomasBaranauskas::LabyrinthApp::MathComponent::Services::RandomManager;
using TomasBaranauskas::LabyrinthApp::GeneralComponent::Services::RecursionDepthHandler;

using std::vector;
using std::deque;
using std::tuple;
using std::get;
using std::optional;
using std::shared_ptr;
using std::map;

using PathPart = tuple<BlockSlot, ActionSelector>;
using Path = deque<PathPart>;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	LabyrinthGenerator::LabyrinthGenerator(LabyrinthGeneratorSettings labyrinthGeneratorSettings) :
		labyrinthGeneratorSettings(labyrinthGeneratorSettings)
	{

	}

	// Add another field where to start (with validation)
	Labyrinth LabyrinthGenerator::GenerateLabyrinth(const Dimensions& dimensions)
	{
		auto labyrinth = Labyrinth(dimensions);

		int idealPathSize = 10;
		int routeGroupIndex = 0;
		vector<tuple<BlockSlot, BlockPartSelector>> blockSlotTupleList = { { BlockSlot(1, 1), BlockPartSelector::Left } };

		while (blockSlotTupleList.size() > 0)
		{
			vector<tuple<BlockSlot, BlockPartSelector>> nextBlockSlotTupleList;

			for (auto const& blockSlotTuple : blockSlotTupleList)
			{
				auto path = Path();

				auto blockSlot = std::get<0>(blockSlotTuple);
				auto blockPartStart = std::get<1>(blockSlotTuple);

				for (int i = 0; i < 10; i++)
				{
					auto potentialPath = GenerateRandomPath(labyrinth, blockSlot, blockPartStart, idealPathSize);
					if (potentialPath.size() == idealPathSize)
					{
						path = potentialPath;
						break;
					}
					
					if (path.size() < potentialPath.size())
						path = potentialPath;
				}
				
				bool continueSpreading = path.size() > 1;
				vector<ActionSelector> actions = { continueSpreading ? std::get<1>(path[0]) : ActionSelector::StopNear };
				auto actionLimit = GenerateActionLimit();
				if (continueSpreading && actionLimit > 1)
				{
					auto availableActions = ObtainAvailableActions2(labyrinth, blockSlot, blockPartStart, false);
					while (actions.size() < actionLimit)
					{
						if (availableActions.size() == 0)
							break;

						auto randomAction = randomManager.GetRandomItem(availableActions, true);
						if (std::find(actions.begin(), actions.end(), randomAction) != actions.end())
							continue;

						actions.push_back(randomAction);
					}
				}

				auto route = Route(blockPartStart, actions);
				labyrinth.TryAddRoute(route, blockSlot, routeGroupIndex);
				if (!continueSpreading)
					continue;
	
				for (auto const& action : actions)
				{
					auto blockPartSelector = generalSelectorConverter.ObtainBlockPartSelector(action);
					auto blockNeighbourSelector = generalSelectorConverter.ObtainNeighbourSelector(*blockPartSelector);
					auto neighbourBlockSlot = labyrinth.ObtainNeighbourBlockSlot(blockSlot, blockNeighbourSelector);
					auto neighbourBlockPartStart = blockPartManager.ObtainBlockPartAcross(*blockPartSelector);

					nextBlockSlotTupleList.push_back({ *neighbourBlockSlot, neighbourBlockPartStart });
				}
			}

			routeGroupIndex++;
			blockSlotTupleList = nextBlockSlotTupleList;
		}

		return labyrinth;
	}

	Path LabyrinthGenerator::GenerateRandomPath(Labyrinth labyrinth, BlockSlot blockSlot, BlockPartSelector blockPartStart, int pathLength)
	{
		auto path = Path();
		if (pathLength-- <= 0)
			return path;

		auto availableActions = ObtainAvailableActions2(labyrinth, blockSlot, blockPartStart, false);
		if (availableActions.size() <= 0)
			return path;

		auto randomAvailableAction = randomManager.GetRandomItem(availableActions);
		auto route = Route(blockPartStart, randomAvailableAction);
		labyrinth.TryAddRoute(route, blockSlot, 0);
		path.push_back({ blockSlot, randomAvailableAction });

		auto blockPartSelector = generalSelectorConverter.ObtainBlockPartSelector(randomAvailableAction);
		auto blockNeighbourSelector = generalSelectorConverter.ObtainNeighbourSelector(*blockPartSelector);
		auto neighbourBlockSlot = labyrinth.ObtainNeighbourBlockSlot(blockSlot, blockNeighbourSelector);
		auto neighbourBlockPartStart = blockPartManager.ObtainBlockPartAcross(*blockPartSelector);

		for (auto const& pathPart : GenerateRandomPath(labyrinth, *neighbourBlockSlot, neighbourBlockPartStart, pathLength))
			path.push_back(pathPart);

		return path;
	}

	vector<ActionSelector> LabyrinthGenerator::PickRandomPath(
		Labyrinth labyrinth,
		BlockSlot blockSlot,
		BlockPartSelector blockPartStart,
		int routeLength
	) {
		auto blockParts = vector<BlockPartSelector>
		{
			BlockPartSelector::Left,
			BlockPartSelector::Top,
			BlockPartSelector::Right,
			BlockPartSelector::Bottom
		};

		bool canGo = false;
		while (blockParts.size() > 0)
		{
			auto potentialDestinationBlockParts = randomManager.GetRandomItems(blockParts, 1, true);
			for (auto const& potentialDestinationBlockPart : potentialDestinationBlockParts)
			{
				auto neighbourSelector = generalSelectorConverter.ObtainNeighbourSelector(potentialDestinationBlockPart);
				if (!CanAccessNeighbour(labyrinth, blockSlot, blockPartStart, neighbourSelector))
					continue;

				canGo = true;
			}

			if (canGo)
				break;
		}

		return vector<ActionSelector>();
	}

	bool LabyrinthGenerator::CanAccessNeighbour(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector blockPartStart,
		BlockNeighbourSelector blockNeighbourSelector
	) {
		// * We check if starting block part (for this block) is available
		auto block = labyrinth.GetBlock(blockSlot);
		if (block == nullptr)
			return false;

		if (block->IsPartInUse(blockPartStart))
			return false;

		// * We check if starting block part is not the same as the destination block part (for this block)
		auto blockPartDestination = generalSelectorConverter.ObtainBlockPartSelector(blockNeighbourSelector);
		if (blockPartStart == blockPartDestination)
			return false;

		// * We check if destination block part (for this block) is available
		if (block->IsPartInUse(blockPartDestination))
			return false;

		// * We check if center (for this block) is available. If not, then check if we can go overlap
		auto oppositeOfBlockPartDestination = blockPartManager.ObtainBlockPartAcross(blockPartDestination);
		if (block->IsCentreIsUse())
			if (oppositeOfBlockPartDestination != blockPartStart)
				return false;

		// * We check if destination block exists
		auto neighbourBlock = labyrinth.GetNeighbourBlock(blockSlot, blockNeighbourSelector);
		if (neighbourBlock == nullptr)
			return false;

		if (neighbourBlock->IsPartInUse(oppositeOfBlockPartDestination))
			return false;

		/*
		auto route = Route(blockPartStart, generalSelectorConverter.ObtainActionSelector(blockPartDestination));
		if (!labyrinth.TryAddRoute(route, blockSlot, RouteGroupSelector::AddToCurrentRouteGroup))
			return false;
		*/

		return true;
	}



	vector<ActionSelector> LabyrinthGenerator::ObtainAvailableActions(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector blockPartStart,
		int depthIndexLimit
	) {
		auto block = labyrinth.GetBlock(blockSlot);
		if (block == nullptr)
			return vector<ActionSelector>();

		if (block->IsPartInUse(blockPartStart))
			return vector<ActionSelector>();

		if (depthIndexLimit < 2)
			depthIndexLimit = 2;

		if (depthIndexLimit > 30)
			depthIndexLimit = 30;

		canGoCache.clear();
		for (int depthIndex = depthIndexLimit; depthIndex >= 2; depthIndex--)
		{
			auto recursionDepthSettings = RecursionDepthHandler(depthIndex);
			auto availableActions = vector<ActionSelector>();

			if (CanGo(labyrinth, blockSlot, blockPartStart, BlockPartSelector::Left, recursionDepthSettings))
				availableActions.push_back(ActionSelector::GoLeft);

			if (CanGo(labyrinth, blockSlot, blockPartStart, BlockPartSelector::Right, recursionDepthSettings))
				availableActions.push_back(ActionSelector::GoRight);

			if (CanGo(labyrinth, blockSlot, blockPartStart, BlockPartSelector::Top, recursionDepthSettings))
				availableActions.push_back(ActionSelector::GoUp);

			if (CanGo(labyrinth, blockSlot, blockPartStart, BlockPartSelector::Bottom, recursionDepthSettings))
				availableActions.push_back(ActionSelector::GoDown);

			if (availableActions.size() == 0)
				continue;

			return availableActions;
		}

		// Todo: deal with merge logic
		auto availableActions = vector<ActionSelector>();
		availableActions.push_back(ActionSelector::StopNear);

		return availableActions;
	}

	vector<ActionSelector> LabyrinthGenerator::ObtainAvailableActions2(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector blockPartStart,
		bool includeStop
	) {
		auto block = labyrinth.GetBlock(blockSlot);
		auto availableActions = vector<ActionSelector>();
		if (block == nullptr)
			return availableActions;

		if (block->IsPartInUse(blockPartStart))
			return availableActions;

		if (CanAccessNeighbour(labyrinth, blockSlot, blockPartStart, BlockNeighbourSelector::OnTheLeft))
			availableActions.push_back(ActionSelector::GoLeft);

		if (blockSlot.columnIndex == 0 && blockSlot.rowIndex == 1 && blockPartStart != BlockPartSelector::Right)
			int gg = 5;

		if (CanAccessNeighbour(labyrinth, blockSlot, blockPartStart, BlockNeighbourSelector::OnTheRight))
			availableActions.push_back(ActionSelector::GoRight);

		if (CanAccessNeighbour(labyrinth, blockSlot, blockPartStart, BlockNeighbourSelector::Above))
			availableActions.push_back(ActionSelector::GoUp);

		if (CanAccessNeighbour(labyrinth, blockSlot, blockPartStart, BlockNeighbourSelector::Below))
			availableActions.push_back(ActionSelector::GoDown);

		return availableActions;
	}

	bool LabyrinthGenerator::CanGo(
		Labyrinth labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector blockPartStart,
		BlockPartSelector blockPartDestination,
		RecursionDepthHandler recursionDepthHandler
	) const {	
		// * We check if starting block part (for this block) is available
		auto block = labyrinth.GetBlock(blockSlot);
		if (block == nullptr)
			return false;

		if (block->IsPartInUse(blockPartStart))
			return false;

		// * We check if starting block part is not the same as the destination block part (for this block)
		if (blockPartStart == blockPartDestination)
			return false;

		// * We check if destination block part (for this block) is available
		if (block->IsPartInUse(blockPartDestination))
			return false;

		// * We check if center (for this block) is available. If not, then check if we can go overlap
		auto oppositeOfBlockPartDestination = blockPartManager.ObtainBlockPartAcross(blockPartDestination);
		if (block->IsCentreIsUse())
			if (oppositeOfBlockPartDestination != blockPartStart)
				return false;

		// Todo: add TryAddRoute here too
		auto route = Route(blockPartStart, generalSelectorConverter.ObtainActionSelector(blockPartDestination));
		if (!labyrinth.TryAddRoute(route, blockSlot, 0))
			return false;

		// * We check if destination block exists
		auto neighbourBlockSlot = labyrinth.ObtainNeighbourBlockSlot(blockSlot, generalSelectorConverter.ObtainNeighbourSelector(blockPartDestination));
		if (neighbourBlockSlot == nullptr)
			return false;

		if (!recursionDepthHandler.TryIncrementDepthIndex())
			return true;

		auto blockParts = vector<BlockPartSelector>
		{
			BlockPartSelector::Left,
			BlockPartSelector::Top,
			BlockPartSelector::Right,
			BlockPartSelector::Bottom
		};
		
		while (blockParts.size() > 0)
		{
			auto potentialDestinationBlockPart = randomManager.GetRandomItem(blockParts, true);
			bool canGo = CanGo(labyrinth, *neighbourBlockSlot, oppositeOfBlockPartDestination, potentialDestinationBlockPart, recursionDepthHandler);
			if (canGo)
				return true;
		}

		return false;
	}

	bool LabyrinthGenerator::CanMerge(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector startingBlockPart
	) const {
		return false;
	}

	bool LabyrinthGenerator::CanStopNear(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector startingBlockPart
	) const {
		return false;
	}

	bool LabyrinthGenerator::CanStopCenter(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector startingBlockPart) const
	{
		return false;
	}

	bool LabyrinthGenerator::CanStopFar(
		const Labyrinth& labyrinth,
		const BlockSlot& blockSlot,
		BlockPartSelector startingBlockPart
	) const {
		return false;
	}

	int LabyrinthGenerator::GenerateActionLimit()
	{
		int randomCount = randomManager.GenerateRandomInt(
			labyrinthGeneratorSettings.MIN_PERCENTAGE,
			labyrinthGeneratorSettings.MAX_PERCENTAGE,
			false
		);

		if (randomCount >= labyrinthGeneratorSettings.MIN_PERCENTAGE && randomCount < labyrinthGeneratorSettings.GetThreeWaySplitChance())
			return 3;

		if (randomCount >= labyrinthGeneratorSettings.MAX_PERCENTAGE - labyrinthGeneratorSettings.GetTwoWaySplitChance() && randomCount < labyrinthGeneratorSettings.MAX_PERCENTAGE)
			return 2;

		return 1;
	}

	const BlockPartManager LabyrinthGenerator::blockPartManager = BlockPartManager();
	const GeneralSelectorConverter LabyrinthGenerator::generalSelectorConverter = GeneralSelectorConverter();
	const AngleManager LabyrinthGenerator::angleManager = AngleManager();
	const RandomManager LabyrinthGenerator::randomManager = RandomManager();
}
