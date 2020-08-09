#pragma once

#include "LabyrinthComponent/Models/BlockSlot.h"
#include "LabyrinthComponent/Services/BlockPartManager.h"
#include "LabyrinthComponent/Services/GeneralSelectorConverter.h"
#include "LabyrinthComponent/Settings/LabyrinthGeneratorSettings.h"
#include "MathComponent/Services/AngleManager.h"
#include "MathComponent/Services/RandomManager.h"

#include <vector>
#include <deque>
#include <map>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	//class BlockSlot;
	class Labyrinth;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class BlockPartSelector;
	enum class ActionSelector;
	enum class BlockNeighbourSelector;
}

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models
{
	class Dimensions;
}

namespace TomasBaranauskas::LabyrinthApp::GeneralComponent::Services
{
	class RecursionDepthHandler;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	class LabyrinthGenerator
	{
	public:
		LabyrinthGenerator(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Settings::LabyrinthGeneratorSettings = TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Settings::LabyrinthGeneratorSettings()
		);

		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth GenerateLabyrinth(
			const TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions&
		);

		const static TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::BlockPartManager blockPartManager;
		const static TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services::GeneralSelectorConverter generalSelectorConverter;
		const static TomasBaranauskas::LabyrinthApp::MathComponent::Services::AngleManager angleManager;
		const static TomasBaranauskas::LabyrinthApp::MathComponent::Services::RandomManager randomManager;
	protected:
		TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Settings::LabyrinthGeneratorSettings labyrinthGeneratorSettings;
		using Test = std::tuple<
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			int
		>;
		mutable std::vector<std::tuple<Test, bool>> canGoCache;

		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector> ObtainAvailableActions(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			int
		);
		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector> ObtainAvailableActions2(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			bool
		);


		std::vector<TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector> PickRandomPath(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			int routeLength
		);

		std::deque<
			std::tuple<
				TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot,
				TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::ActionSelector
			>
		> GenerateRandomPath(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector,
			int pathLength

		);

		

		bool CanGo(
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector blockPartStart,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector blockPartDestination,
			TomasBaranauskas::LabyrinthApp::GeneralComponent::Services::RecursionDepthHandler
		) const;

		bool CanAccessNeighbour(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector blockPartStart,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockNeighbourSelector
		);







		bool CanMerge(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
		bool CanStopNear(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
		bool CanStopCenter(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;
		bool CanStopFar(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Labyrinth&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot&,
			TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector
		) const;

		int GenerateActionLimit();
	};
}

