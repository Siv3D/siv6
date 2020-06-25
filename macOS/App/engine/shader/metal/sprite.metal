
# include <metal_stdlib>
using namespace metal;

struct VSConstants2D
{
	float4 transform[2];
	float4 colorMul;
};

struct Vertex2D
{
	float2 pos [[attribute(0)]];
	float2 tex [[attribute(1)]];
	float4 color [[attribute(2)]];
};

struct PSInput
{
	float4 clipSpacePosition [[position]];
	float2 tex;
	float4 color;
};

float4 StandardTransform(float2 pos,
						 constant float4(&transform)[2])
{
	float4 result;
	result.xy = transform[0].zw + pos.x * transform[0].xy + pos.y * transform[1].xy;
	result.zw = transform[1].zw;
	return result;
}

vertex
PSInput VS_Sprite(Vertex2D in [[stage_in]],
				  constant VSConstants2D& cb [[buffer(1)]])
{
	PSInput out;
	out.clipSpacePosition = StandardTransform(in.pos, cb.transform);
	out.tex = in.tex;
	out.color = (in.color * cb.colorMul);
	return out;
}

fragment
float4 PS_Shape(PSInput in [[stage_in]])
{
    return in.color;
}
