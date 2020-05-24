#include <string>
#include <cstdint>
#include <memory>

namespace Windows
{

class MainWindow
{
    struct Impl;
    std::unique_ptr<Impl> impl_;

public:
    MainWindow();
    ~MainWindow();

    void Initialize(std::string title_name, uint32_t width, uint32_t height);
    void SetFullscreen(bool is_fullscreen);
};

} // namespace Windows