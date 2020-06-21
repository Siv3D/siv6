#version 410

//
// PSInput
//
layout(location = 0) in vec4 Color;

//
// PSOutput
//
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
}
