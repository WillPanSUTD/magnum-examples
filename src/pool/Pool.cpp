#include <Scene.h>
#include <Camera.h>
#include <Light.h>

#include "AbstractExample.h"
#include "Quad.h"

namespace Magnum { namespace Examples {

class Pool: public AbstractExample {
    public:
        inline Pool(int& argc, char** argv): AbstractExample(argc, argv, "Pool") {
            /* Every scene needs a camera */
            camera = new Camera(&scene);
            camera->setPerspective(deg(35.0f), 0.1f, 100.0f);
            camera->setClearColor(Vector3(0.6f));
            camera->translate({0.0f, 0.0f, 3.5f})->rotate(deg(-15.0f), Vector3::xAxis())->rotate(deg(25.0f), Vector3::yAxis());

            /* Light */
            light = new Light(&scene);
            light->translate({0.0f, -3.0f, 0.0f});

            /* Add triangle to the scene */
            new Quad(light, &scene);
        }

    protected:
        inline void viewportEvent(const Math::Vector2<GLsizei>& size) {
            camera->setViewport(size);
        }

        inline void drawEvent() {
            camera->draw();
            swapBuffers();
        }

        virtual void keyEvent(Key key, const Magnum::Math::Vector2<int>& position) {
            if(key == Key::Left)
                camera->rotate(deg(5.0f), Vector3::yAxis());
            else if(key == Key::Right)
                camera->rotate(deg(-5.0f), Vector3::yAxis());
            else if(key == Key::Up)
                camera->rotate(deg(-5.0f), camera->transformation()[0].xyz());
            else if(key == Key::Down)
                camera->rotate(deg(5.0f), camera->transformation()[0].xyz());

            redraw();
        }

    private:
        Scene scene;
        Camera* camera;
        Light* light;
};

}}

MAGNUM_EXAMPLE_MAIN(Magnum::Examples::Pool)