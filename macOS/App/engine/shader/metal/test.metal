
# include <metal_stdlib>

struct VSConstants2D
{
	float4 transform[2];
	float4 colorMul;
};

struct Vertex2D
{
	float2 pos;
	float2 tex;
	float4 color;
};

struct RasterizerData
{
	float4 clipSpacePosition [[position]];
	float2 textureCoordinate;
	float4 color;
};

using namespace metal;

float4 StandardTransform(float2 pos, constant float4(&transform)[2])
{
	float4 result;
	result.xy = transform[0].zw + pos.x * transform[0].xy + pos.y * transform[1].xy;
	result.zw = transform[1].zw;
	return result;
}

vertex RasterizerData v_simple(
    constant Vertex2D* in [[buffer(0)]],
    constant VSConstants2D& cb [[buffer(1)]],
    uint vid [[vertex_id]])
{
	RasterizerData out;
	out.clipSpacePosition = StandardTransform(in[vid].pos, cb.transform);
	out.textureCoordinate = in[vid].tex;
	out.color = (in[vid].color * cb.colorMul);
	return out;
}

fragment float4 f_simple(
    RasterizerData in [[stage_in]])
{
    return in.color;
}
