#include <engine/windows/main_window.h>
#include <D3d12.h>
#include <windows.h>
#include <assert.h>

namespace Windows
{
    struct MainWindow::Impl
    {
        static constexpr const char *ClassName = "MainWindow";
        HWND handle_;

        WNDCLASS wnd_class_;

        ~Impl()
        {
            DestroyWindow(handle_);
            UnregisterClass(ClassName, nullptr);
        }

        static LRESULT default_event_handler(HWND hwnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
        {
            auto instance = (Impl *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            switch (uMsg)
            {
            case WM_CREATE:
            {
                CREATESTRUCTA *create_param = (CREATESTRUCTA *)lParam;
                SetWindowLongPtr(hwnd, GWLP_USERDATA, LONG_PTR(create_param->lpCreateParams));
                return 0;
            }
            default:
                if (instance && instance->handle_ == hwnd)
                {
                    return instance->EventHandler(uMsg, wParam, lParam);
                }
                else
                {
                    return DefWindowProc(hwnd, uMsg, wParam, lParam);
                }
            }
        }

        void Initialize(const std::string &title_name, uint32_t width, uint32_t height)
        {
            assert(width > 0 && height > 0);

            wnd_class_.style = CS_VREDRAW | CS_HREDRAW;
            wnd_class_.lpfnWndProc = default_event_handler;
            wnd_class_.cbClsExtra = 0;
            wnd_class_.cbWndExtra = 0;
            wnd_class_.hInstance = nullptr;
            wnd_class_.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
            wnd_class_.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wnd_class_.hbrBackground = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
            wnd_class_.lpszMenuName = nullptr;
            wnd_class_.lpszClassName = ClassName;
            RegisterClass(&wnd_class_);

            handle_ = CreateWindowExA(WS_EX_APPWINDOW, ClassName, title_name.c_str(), WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                                      nullptr, nullptr, nullptr, this);
        }

        void Show()
        {
            if (handle_ != nullptr)
            {
                ShowWindow(handle_, SW_SHOW);
            }
        }

        void SetFullscreen(bool is_fullscreen)
        {
        }

        void RunMainLoop()
        {
            MSG msg;
            while (msg.message != WM_QUIT)
            {
                if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }

        LRESULT EventHandler(uint32_t uMsg, WPARAM wParam, LPARAM lParam)
        {
            switch (uMsg)
            {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            case WM_PAINT:
                return 0;
            }
            return DefWindowProc(handle_, uMsg, wParam, lParam);
        }
    };

    MainWindow::MainWindow() : impl_(std::make_unique<Impl>()) {}

    MainWindow::~MainWindow() = default;

    void MainWindow::Initialize(const std::string &title_name, uint32_t width, uint32_t height)
    {
        impl_->Initialize(title_name, width, height);
        impl_->Show();
    }

    void MainWindow::SetFullscreen(bool is_fullscreen)
    {
        impl_->SetFullscreen(is_fullscreen);
    }

    void MainWindow::Run()
    {
        impl_->RunMainLoop();
    }

} // namespace Windows
