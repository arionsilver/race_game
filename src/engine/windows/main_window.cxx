#include <engine/windows/main_window.h>
#include <D3d12.h>
#include <windows.h>

namespace Windows
{

struct MainWindow::Impl
{
    HWND handle_;

    static LRESULT default_event_handler(HWND hwnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void create_window()
    {
        WNDCLASSW wnd_class;
        wnd_class.style = CS_VREDRAW | CS_HREDRAW;
        wnd_class.lpfnWndProc = default_event_handler;
        wnd_class.cbClsExtra = 0;
        wnd_class.cbWndExtra = 0;
        wnd_class.hInstance = nullptr;

        CreateWindowA("MainWindow", "WindowName", 0, 100, 100, 800, 600, nullptr, nullptr, nullptr, nullptr);
    }
};

MainWindow::MainWindow() : impl_(std::make_unique<Impl>()) {}

MainWindow::~MainWindow() = default;

void MainWindow::Initialize(std::string title_name, uint32_t width, uint32_t height) {}

void MainWindow::SetFullscreen(bool is_fullscreen) {}

} // namespace Windows
