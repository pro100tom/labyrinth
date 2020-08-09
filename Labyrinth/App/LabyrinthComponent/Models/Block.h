#pragma once

#include "Route.h"
//Debugging
#include "BlockSlot.h"

#include <vector>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums
{
	enum class BlockPartSelector;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Block
	{
	public:
		Block();
		Block(const Block&);

		bool HasRoutes() const;
		bool IsPartInUse(TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector) const;
		bool IsCentreIsUse() const;

		void AddRoute(const Route&);
		const std::vector<Route>& GetRoutes() const;

		// Debugging...
		BlockSlot blockSlot;
	protected:
		std::vector<Route> routes;
	};
}

