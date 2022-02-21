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

        namespace Buffer {
            ID3D11Buffer* Vertex;
        }
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
            {
                float const Coordinates[4][2]{
                    {-0.5f, +0.5f},
                    {+0.5f, +0.5f},
                    {-0.5f, -0.5f},
                    {+0.5f, -0.5f}
                };

                D3D11_SUBRESOURCE_DATA const Subresource{ Coordinates };

                D3D11_BUFFER_DESC const Descriptor{
                    sizeof(Coordinates),
                    D3D11_USAGE_IMMUTABLE,
                    D3D11_BIND_VERTEX_BUFFER,
                    0
                };

                ID3D11Buffer* Buffer = nullptr;

                MUST(Device->CreateBuffer(&Descriptor, &Subresource, &Buffer));

                UINT const Stride = sizeof(*Coordinates);
                UINT const Offset = 0;

                DeviceContext->IASetVertexBuffers(
                    0,
                    1,
                    &Buffer,
                    &Stride,
                    &Offset
                );

                Buffer->Release();
            }
            {
                D3D11_BUFFER_DESC const Descriptor{
                    sizeof(float[4][2]),
                    D3D11_USAGE_DYNAMIC,
                    D3D11_BIND_VERTEX_BUFFER,
                    D3D11_CPU_ACCESS_WRITE
                };

                MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Vertex));

                UINT const Stride = sizeof(float[2]);
                UINT const Offset = 0;

                // 이미지 로컬 좌표를 위해 0번 슬롯이 이미 사용되었으므로!
                DeviceContext->IASetVertexBuffers(
                    1,
                    1,
                    &Buffer::Vertex,
                    &Stride,
                    &Offset
                );
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