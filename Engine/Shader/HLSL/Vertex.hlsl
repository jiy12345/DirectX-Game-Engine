#include "Layout.hlsli"

namespace Shader {
	Layout::Pixel Vertex(const Layout::Vertex Input) {
		Layout::Pixel Output = {
			Input.Position,
			Input.TexCoord
		};

		return Output;
	}
}