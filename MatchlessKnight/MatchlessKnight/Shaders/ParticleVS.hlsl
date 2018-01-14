#include "Particle.hlsli"

GSInput main( float4 pos : POSITION, float4 color : COLOR, float2 other : TEXCOORD )
{
	GSInput Out;

	Out.pos = pos;
	Out.color = color;
	Out.other = other;

	// やってみよう② ////////////////

	// 左右上下反転
	//Out.pos.x *= -1.0f;
	//Out.pos.y *= -1.0f;

	// スケーリング
	//Out.pos.x *= 1.5f;
	//Out.pos.y *= 1.5f;
	
	//////////////////////////////////

	return Out;
}