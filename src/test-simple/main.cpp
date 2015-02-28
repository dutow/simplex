
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

INITIALIZE_EASYLOGGINGPP

class test_application : public simplex::single_window_application {
   public:
    test_application() : single_window_application(
                             L"Hello OpenGL", 400, 400),
                         q(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)) {
    }

    virtual void render() override {
        // nop
        q.render();
    }

   private:
    simplex::primitive2d::quad q;
};

int main() {
    test_application app;

    app.run();

    return 0;
}