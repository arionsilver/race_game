#include <memory>

namespace Windows
{

class DX12Helper
{
    struct Impl;
    std::unique_ptr<Impl> impl_;
    void Finalize();

public:
    DX12Helper();
    ~DX12Helper();

    void Initialize();
};

} // namespace Windows
