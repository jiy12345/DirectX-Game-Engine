#include "ShapeLayout.hlsli"

namespace ShapeShader
{
    ShapeLayout::ShapePixel ShapeVertex(const ShapeLayout::ShapeVertex Input)
    {
        ShapeLayout::ShapePixel Output =
        {
            Input.Position,
            Input.Color
        };

        return Output;
    }
}
