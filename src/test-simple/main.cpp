
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

INITIALIZE_EASYLOGGINGPP

class test_application : public simplex::single_window_application {
public:
	test_application() : single_window_application(L"Hello OpenGL", 400, 400)
	{
	}

	virtual void render() override
	{
		// nop
	}

};

int main() {

	test_application app;

	app.run();

	return 0;

}