
#pragma once

#include <string>

namespace simplex {
	class shader_source {
	public:
		shader_source(){};
		virtual ~shader_source(){};

		virtual std::string name() = 0;

		virtual std::string vertex_shader() = 0;
		virtual std::string fragment_shader() = 0;
	};
}