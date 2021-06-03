#ifndef APPLICATION_H
#define APPLICATION_H
#include "Window.h"

namespace Saturn {

    class Application {
    private:
        unsigned int a_Width;
        unsigned int a_Height;
        unsigned int a_VirtualWidth;
        unsigned int a_VirtualHeight;
        Window* a_Window;
    public:
        void ApplicationInit();
        void AppRun();
        Application();
        ~Application();
    };

    Application* CreateApplication();

}

#endif APPLICATION_H