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
        ID3D11RenderTargetView* RenderTargetView;

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
#include "Shader/Bytecode/Image/Vertex.h"
                D3D11_INPUT_ELEMENT_DESC const Descriptor[2]{
                    {
                        "POSITION",
                        0,
                        DXGI_FORMAT_R32G32_FLOAT,
                        0
                    },
                    {
                        "TEXCOORD",
                        0,
                        DXGI_FORMAT_R32G32_FLOAT,
                        1
                    }
                };

                ID3D11InputLayout* InputLayout = nullptr;

                MUST(Device->CreateInputLayout(Descriptor, 2, Bytecode, sizeof(Bytecode), &InputLayout));

                DeviceContext->IASetInputLayout(InputLayout);

                InputLayout->Release();
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

                DeviceContext->IASetVertexBuffers(
                    1,
                    1,
                    &Buffer::Vertex,
                    &Stride,
                    &Offset
                );
            }

            { DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); }

            {
#include "Shader/Bytecode/Image/Pixel.h"
                ID3D11PixelShader* PixelShader = nullptr;
                
                MUST(Device->CreatePixelShader(Bytecode,sizeof(Bytecode),
                    nullptr,
                    &PixelShader
                ));
                
                DeviceContext->PSSetShader(PixelShader, nullptr, 0);
                
                PixelShader->Release();
            }

            return;
        }
        case WM_SIZE:
        {
            {
                D3D11_VIEWPORT Viewport = D3D11_VIEWPORT();

                Viewport.Width = LOWORD(lParameter);
                Viewport.Height = HIWORD(lParameter);

                DeviceContext->RSSetViewports(1, &Viewport);
            }
            {
                if (RenderTargetView != nullptr) {
                    RenderTargetView->Release();
                    MUST(SwapChain->ResizeBuffers(1, LOWORD(lParameter), HIWORD(lParameter), DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE));
                }

                ID3D11Texture2D* Texture2D = nullptr;

                MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Texture2D)));
                {
                    MUST(Device->CreateRenderTargetView(Texture2D, nullptr, &RenderTargetView));
                }
                Texture2D->Release();

                DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);

                Texture2D->Release();
            }
            return;
        }
        case WM_APP:
        {
            MUST(SwapChain->Present(0, 0));

            float const Color[4]{ 0.0f, 0.0f, 0.0f, 1.0f };

            DeviceContext->ClearRenderTargetView(RenderTargetView, Color);

            return;
        }
        case WM_DESTROY:
            RenderTargetView->Release();
            Buffer::Vertex->Release();
            DeviceContext->Release();
            Device->Release();
            SwapChain->Release();
            return;

        }
    }
};