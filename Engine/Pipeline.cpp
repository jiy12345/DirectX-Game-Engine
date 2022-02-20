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
            return;
        case WM_APP:
            return;
        case WM_DESTROY:
            return;
        case WM_SIZE:
            return;
        }
    }
};