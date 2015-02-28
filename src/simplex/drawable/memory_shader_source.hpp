
#pragma once

#include "simplex/drawable/shader_source.hpp"

namespace simplex {
	class memory_shader_source : public shader_source {
	public:
		memory_shader_source(std::string program_name, std::string vertex_shader_src, std::string fragment_shader_src) : program_name(program_name), vertex_shader_src(vertex_shader_src), fragment_shader_src(fragment_shader_src) {};
		virtual ~memory_shader_source(){};

		virtual std::string name() { return program_name; }

		virtual std::string vertex_shader() { return vertex_shader_src; }
		virtual std::string fragment_shader() { return fragment_shader_src; }

	private:

		std::string program_name;
		std::string vertex_shader_src;
		std::string fragment_shader_src;
	};
}