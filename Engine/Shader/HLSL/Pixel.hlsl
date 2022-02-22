#include "Buffers.hlsli"

namespace Shader {
	const Texture2D Resource : register(T0);

	Buffers::Color Pixel(const Buffers::Pixel Input) : SV_Target{

		Buffers::Color Output = {
			Resource.Load(int3(Input.TexCoord.x, Input.TexCoord.y, 0))
		};

		return Output;
	}
}