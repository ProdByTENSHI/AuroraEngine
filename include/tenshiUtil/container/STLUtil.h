#pragma once

#include <algorithm>
#include <concepts>
#include <iostream>
#include <map>
#include <vector>

#include "debug/Logger.hpp"
#include "globals/AuroraTypes.hpp"

namespace Aurora {
	template <typename T>
	concept IsComparable = std::equality_comparable<T>;

	struct STLUtil {
		// Const-Version
		// Either returns the Iterator Position to the Element in the Vector or -1 if
		// it couldnt be found
		template <IsComparable T>
		static std::vector<T>::const_iterator
			GetItOfElementInVec(const std::vector<T>& vec, const T& element) {
			if (vec.empty()) {
				return vec.begin();
			}

			typename std::vector<T>::const_iterator _it =
				std::find(vec.begin(), vec.end(), element);
			if (_it == vec.end())
				Logger::Instance().Log("Could not find given Element. Element Type: " + typeid(T).name()
					, LogType::Warning);

			return _it;
		}

		// Non-Const-Version
		// Either returns the Iterator Position to the Element in the Vector or -1 if
		// it couldnt be found
		template <IsComparable T>
		static std::vector<T>::iterator GetItOfElementInVec(std::vector<T>& vec,
			const T& element) {
			if (vec.empty()) {
				return vec.begin();
			}

			typename std::vector<T>::iterator _it =
				std::find(vec.begin(), vec.end(), element);
			if (_it == vec.end()) {
				Logger::Instance().Log("Could not find Element of Type "
					+ typeid(T).name()
					, LogType::Warning);
			}

			return _it;
		}

		template <IsComparable T>
		static bool IsElementInVector(const std::vector<T>& vec, const T& element) {
			for (auto& elem : vec) {
				if (elem == element)
					return true;
			}

			Logger::Instance().Log("Element of Type " + typeid(T).name(),
				LogType::Warning);
			return false;
		}
	};
} // namespace Aurora
