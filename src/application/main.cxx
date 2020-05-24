#include <engine/windows/main_window.h>

int
main(int argc, char **argv)
{
    Windows::MainWindow window;

    window.Initialize("Main Window", 800, 600);
    window.Run();

    return 0;
}
