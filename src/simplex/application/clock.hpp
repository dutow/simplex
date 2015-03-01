
#pragma once

#include <cstdint>
#include <chrono>

namespace simplex {
	// TODO: check if every platform supports c++11 chrono

	/// <summary>	A high precision clock measuring time since the previous get operation. </summary>
	class clock {
	public:
		/// <summary>	Default constructor. </summary>
		clock();
		/// <summary>	Destructor. </summary>
		virtual ~clock();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Elapsed microseconds. </summary>
		///
		/// <returns>	Microseconds since the previous call. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		uint64_t elapsed_microseconds();

		typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_type;
		typedef std::chrono::high_resolution_clock internal_clock;
	private:
		time_type last_call;
	};
}