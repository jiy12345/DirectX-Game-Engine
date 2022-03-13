namespace ShapeLayout
{
    struct ShapeVertex
    {
        float4 Position : POSITION;
        float4 Color    : COLOR;
    };
    
    struct ShapePixel
    {
        float4 Position : SV_POSITION;
        float4 Color    : COLOR;
    };
    
    typedef float4 ShapeColor;
}