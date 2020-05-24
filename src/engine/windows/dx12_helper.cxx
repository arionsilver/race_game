#include <engine/windows/dx12_helper.h>
#include <windows.h>

namespace Windows
{

struct DX12Helper::Impl
{
    Impl()
    {
    }

    ~Impl();

    void initialize()
    {
    }
};

DX12Helper::DX12Helper() : impl_(std::make_unique<Impl>())
{
}

DX12Helper::~DX12Helper() = default;

void DX12Helper::Initialize()
{
    impl_->initialize();
}

} // namespace Windows
