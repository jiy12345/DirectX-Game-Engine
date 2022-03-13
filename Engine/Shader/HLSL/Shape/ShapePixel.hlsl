#include "ShapeLayout.hlsli"

namespace ShapeShader
{
    ShapeLayout::ShapeColor ShapePixel(const ShapeLayout::ShapePixel Input) : SV_TARGET
    {
        ShapeLayout::ShapeColor Output =
        {
            Input.Color
        };

        return Output;
    }
}