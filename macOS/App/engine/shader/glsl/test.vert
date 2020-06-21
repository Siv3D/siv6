#version 410

//
// VSInput
//
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec4 VertexColor;

//
// VSOutput
//
layout(location = 0) out vec4 Color;
layout(location = 1) out vec2 UV;
out gl_PerVertex
{
	vec4 gl_Position;
};

void main()
{
	gl_Position = vec4(VertexPosition, 0.0, 1.0);

	Color = VertexColor;
	
	UV = VertexUV;
}
