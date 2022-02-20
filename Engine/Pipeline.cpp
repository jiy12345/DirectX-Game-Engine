#include "Pipeline.h"

#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

namespace Pipeline {
	namespace {
        ID3D11Device* Device;
        ID3D11DeviceContext* DeviceContext;
        IDXGISwapChain* SwapChain;
	}

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter) {
        switch (uMessage) {
        case WM_CREATE:
        {
            {
                DXGI_SWAP_CHAIN_DESC Descriptor = DXGI_SWAP_CHAIN_DESC();
                
                Descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                Descriptor.BufferCount = 1;
                Descriptor.SampleDesc.Count = 1;
                Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                Descriptor.OutputWindow = hWindow;
                Descriptor.Windowed = true;

                MUST(D3D11CreateDeviceAndSwapChain(
                    nullptr,
                    D3D_DRIVER_TYPE_HARDWARE,
                    nullptr,
                    0,
                    nullptr,
                    0,
                    D3D11_SDK_VERSION,
                    &Descriptor,
                    &SwapChain,
                    &Device,
                    nullptr,
                    &DeviceContext
                ));

            }

            return;
        }

        case WM_APP:
            return;
        case WM_DESTROY:
            return;
        case WM_SIZE:
            return;
        }
    }
};