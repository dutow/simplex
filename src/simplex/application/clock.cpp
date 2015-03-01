
#include "clock.hpp"

namespace simplex {


	clock::clock() : last_call(internal_clock::now())
	{
	}

	clock::~clock()
	{

	}

	uint64_t clock::elapsed_microseconds()
	{

		typedef std::chrono::microseconds us;
		typedef std::chrono::duration<int64_t> usec;
		auto old_time = last_call;
		last_call = internal_clock::now();

		return	std::chrono::duration_cast<us>(last_call - old_time).count();
	}

}