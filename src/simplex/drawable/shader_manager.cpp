
#include "shader_manager.hpp"

#include <easylogging++.h>

#include "simplex/drawable/asset_shader_source.hpp"
#include "simplex/error/asset_not_found_error.hpp"
namespace simplex {



	shader_manager::shader_manager(asset_loader const& assets) : assets(assets)
	{

	}

	shader_manager::~shader_manager()
	{

	}

	void shader_manager::add_shader(asset_loader::path const location)
	{
		shaders[location] = std::make_unique<shader>(std::make_unique<asset_shader_source>(assets, location));
	}

	bool shader_manager::has_shader(asset_loader::path const location) const
	{
		return shaders.find(location) != shaders.end();
	}

	void shader_manager::remove_shader(asset_loader::path const location)
	{
		shaders.erase(location);
	}

	void shader_manager::clear()
	{
		shaders.clear();
	}

	shader& shader_manager::operator[](asset_loader::path const location) const
	{
		auto rec = shaders.find(location);

		if (rec == shaders.end()) {
			auto exc = new asset_not_found_error("ShaderManager." + location.string());  // TODO: better error
			LOG(FATAL) << exc;
			throw exc;
		}

		return *(rec->second);
	}

}