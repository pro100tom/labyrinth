#include "LabyrinthGeneratorSettings.h"

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Settings
{
	LabyrinthGeneratorSettings::LabyrinthGeneratorSettings() :
		twoWaySplitChance(15),
		threeWaySplitChance(5)
	{

	}

	int LabyrinthGeneratorSettings::GetTwoWaySplitChance() const
	{
		return twoWaySplitChance;
	}

	int LabyrinthGeneratorSettings::GetThreeWaySplitChance() const
	{
		return threeWaySplitChance;
	}

	void LabyrinthGeneratorSettings::SetSplitChances(int twoWaySplitChance, int threeWaySplitChance)
	{
		if (twoWaySplitChance < MIN_PERCENTAGE)
			twoWaySplitChance = MIN_PERCENTAGE;
		else if (twoWaySplitChance > MAX_PERCENTAGE)
			twoWaySplitChance = MAX_PERCENTAGE;

		this->twoWaySplitChance = twoWaySplitChance;


		if (threeWaySplitChance < MIN_PERCENTAGE)
			threeWaySplitChance = MIN_PERCENTAGE;
		else if (threeWaySplitChance > MAX_PERCENTAGE)
			threeWaySplitChance = MAX_PERCENTAGE;

		this->threeWaySplitChance = twoWaySplitChance + threeWaySplitChance > MAX_PERCENTAGE 
			? MAX_PERCENTAGE - twoWaySplitChance
			: threeWaySplitChance;
	}

	const int LabyrinthGeneratorSettings::MIN_PERCENTAGE = 0;
	const int LabyrinthGeneratorSettings::MAX_PERCENTAGE = 100;
}
