#pragma once

#include "Route.h"

#include <vector>

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class Block;
	class BlockStyle;
}

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels
{
	class Block
	{
	public:
		Block(
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Block&,
			const TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle&
		);

		const std::vector<Route>& GetRoutes() const;
	protected:
		std::vector<Route> routes;
	};
}

