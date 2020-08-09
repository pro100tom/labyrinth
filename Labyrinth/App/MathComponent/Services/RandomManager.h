#pragma once

#include <vector>

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Services
{
	class RandomManager
	{
	public:
		template <typename T>
		std::vector<T> GetRandomItems(std::vector<T>& items, size_t n, bool destructive = false) const
		{
			std::vector<T>* itemsToUse = &items;
			if (!destructive)
				itemsToUse = new std::vector<T>(items);

			int size = itemsToUse->size();
			if (size == 0)
				return std::vector<T>();

			if (n > size || n <= 0)
				n = size;

			std::vector<T> resultItems;
			while (n-- > 0)
			{
				int index = GenerateRandomInt(0, itemsToUse->size(), false);
				resultItems.push_back(itemsToUse->at(index));
				itemsToUse->erase(itemsToUse->begin() + index);
			}

			if (!destructive)
			{
				delete itemsToUse;
				itemsToUse = nullptr;
			}

			return resultItems;
		};

		template <typename T>
		T GetRandomItem(std::vector<T>& items, bool destructive = false) const
		{
			return GetRandomItems(items, 1, destructive)[0];
		};

		int GenerateRandomInt(int min, int max, bool inclusive) const;
	};
}

