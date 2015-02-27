
#pragma once

#include <string>
#include <memory>

#include "simplex/application/application.hpp"

namespace simplex {

	class window;

	class single_window_application : public application {
	public:
		single_window_application(std::wstring title, unsigned int width, unsigned int height);

		virtual ~single_window_application();

		void run();

	protected:

		virtual void render() = 0;

	private:
		std::unique_ptr<window> application_window;
	};

}