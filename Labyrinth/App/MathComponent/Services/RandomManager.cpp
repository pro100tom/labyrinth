#include "RandomManager.h"

#include <random>

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Services
{
	int RandomManager::GenerateRandomInt(int min, int max, bool inclusive) const
	{
		random_device randomDevice;
		mt19937 generator(randomDevice());

		if (!inclusive)
			max--;

		uniform_int_distribution<int> distribution(min, max);

		return distribution(generator);
	}
}
