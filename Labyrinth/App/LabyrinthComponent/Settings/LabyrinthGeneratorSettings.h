#pragma once

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Settings
{
	class LabyrinthGeneratorSettings
	{
	public:
		LabyrinthGeneratorSettings();
		int GetTwoWaySplitChance() const;
		int GetThreeWaySplitChance() const;

		void SetSplitChances(int, int);

		static const int MIN_PERCENTAGE;
		static const int MAX_PERCENTAGE;
	protected:
		int twoWaySplitChance;
		int threeWaySplitChance;
	};
}

