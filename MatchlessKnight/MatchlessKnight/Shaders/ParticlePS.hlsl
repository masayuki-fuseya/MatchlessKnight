#include "Particle.hlsli"

float4 main(PSInput In) : SV_TARGET
{
	float4 color = In.color * g_texture.Sample(g_sampler, In.uv);

	// やってみよう② //////////////

	// 白黒反転
	//color.rgb = 1.0f - color.rgb;

	////////////////////////////////

	return color;
}