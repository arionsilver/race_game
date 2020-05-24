#include <cstdint>
#include <memory>
#include <string>

namespace Windows
{

class MainWindow
{
    struct Impl;
    std::unique_ptr<Impl> impl_;

  public:
    MainWindow();
    ~MainWindow();

    void Initialize(const std::string &title_name, uint32_t width, uint32_t height);
    void SetFullscreen(bool is_fullscreen);

    void Run();
};

} // namespace Windows
