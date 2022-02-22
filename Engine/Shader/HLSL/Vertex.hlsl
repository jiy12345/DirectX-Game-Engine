#include "Buffers.hlsli"

namespace Shader {
	Buffers::Pixel Vertex(const Buffers::Vertex Input) {
		Buffers::Pixel Output = {
			Input.Position,
			Input.TexCoord
		};

		return Output;
	}
}