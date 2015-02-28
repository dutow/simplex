
#pragma once

#include <easylogging++.h>

#include "simplex/drawable/shader_source.hpp"
#include "simplex/assets/asset_loader.hpp"
#include "simplex/error/asset_not_found_error.hpp"

namespace simplex {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	asset based shader source. </summary>
	///
	/// <remarks>
	/// The path parameter it expects is a directory, containing files named vertex.glsl and
	/// fragment.glsl.
	/// </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class asset_shader_source : public shader_source {
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a new shader source based on the given strings. </summary>
		///
		/// <exception cref="exc">	Thrown when an exc error condition occurs. </exception>
		///
		/// <param name="assets">	  	An asset factory. </param>
		/// <param name="parent_path">	Path of a directory containing the shader files (vertex.glsl and fragment.glsl). </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		asset_shader_source(asset_loader const& assets, asset_loader::path parent_path) : assets(assets), parent_path(parent_path) {
			if (!assets.asset_exists(parent_path / "vertex.glsl")) {
				auto exc = new asset_not_found_error((parent_path / "vertex.glsl").string());
				LOG(FATAL) << *exc;
				throw exc;
			}
			if (!assets.asset_exists(parent_path / "fragment.glsl")) {
				auto exc = new asset_not_found_error((parent_path / "vertex.glsl").string());
				LOG(FATAL) << *exc;
				throw exc;
			}
		}
		/// <summary>	Destructor. </summary>
		virtual ~asset_shader_source(){};

		virtual std::string name() { return parent_path.string(); }

		virtual std::string vertex_shader() { return assets.load_asset(parent_path / "vertex.glsl"); }
		virtual std::string fragment_shader() { return assets.load_asset(parent_path / "fragment.glsl"); }

	private:
		asset_loader const& assets;
		asset_loader::path parent_path;
	};
}