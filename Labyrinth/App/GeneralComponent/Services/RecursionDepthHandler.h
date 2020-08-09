#pragma once

namespace TomasBaranauskas::LabyrinthApp::GeneralComponent::Services
{
	class RecursionDepthHandler
	{
	public:
		RecursionDepthHandler();
		RecursionDepthHandler(int depthIndexLimit);
		RecursionDepthHandler(const RecursionDepthHandler&);

		bool TryIncrementDepthIndex();
		bool CanIncrement() const;
		int GetDepthIndex() const;
		int GetDepthIndexLimit() const;
	protected:
		int depthIndex;
		int depthIndexLimit;
	};
}

