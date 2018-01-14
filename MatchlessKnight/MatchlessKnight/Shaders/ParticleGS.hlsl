#include "Particle.hlsli"

// 四角形の頂点数
static const uint vnum = 4;

// 中心点からのオフセット
static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),		// 左下
	float4( 0.5f, -0.5f, 0, 0),		// 右下
	float4(-0.5f,  0.5f, 0, 0),		// 左上
	float4( 0.5f,  0.5f, 0, 0)		// 右上
};

// テクスチャUV
static const float2 uv_array[vnum] =
{
	float2(0, 1),	// 左下
	float2(1, 1),	// 右下
	float2(0, 0),	// 左上
	float2(1, 0)	// 右上
};

[maxvertexcount(vnum)]
void main(
	point GSInput input[1], 
	inout TriangleStream< PSInput > output
)
{
	//for (uint j = 0; j < vnum; j++)
	{
		PSInput element;
		float4 offset;
		float scale = input[0].other.x;
		float rotation = input[0].other.y;

		//for (uint i = 0; i < 3; i++)
		//{
		//	element.pos = input[i].pos + float4(j, 0, 0, 0);
		//	element.pos = mul(element.pos, g_WVP);
		//	element.color = input[i].color;
		//	element.uv = input[i].uv;
		//	output.Append(element);
		//}

		// やってみよう⑤ ///////////////////////////////

		// ×字
		//if (j < 50)
		//{
		//	element.pos = input[0].pos + float4(-0.05f + j * 0.004f, -0.05f + j * 0.004f, 0, 0);
		//}
		//else
		//{
		//	element.pos = input[0].pos + float4(-0.05f + (j - 50) * 0.004f, 0.05f - ((j - 50) * 0.004f), 0, 0);
		//}

		// 円
		//float angle;
		//angle = radians(j / 100.0f * 360);
		//element.pos = input[0].pos + float4(cos(angle) * 0.1f, sin(angle) * 0.1f, 0, 0);

		// 8の字
		//float angle;
		//angle = radians(j / 100.0f * 360);
		//element.pos = input[0].pos + float4(sin(angle * 2) * 0.1f, cos(angle) * 0.2f, 0, 0);

		/////////////////////////////////////////////////

		// 4点分
		for (uint i = 0; i < vnum; i++)
		{
			offset.x = offset_array[i].x * cos(rotation) - offset_array[i].y * sin(rotation);
			offset.y = offset_array[i].x * sin(rotation) + offset_array[i].y * cos(rotation);
			offset.z = 0;
			offset.w = 0;
			// ビルボード行列による回転
			offset = mul(offset, g_Billboard);
			element.pos = input[0].pos + offset * scale;
			// 座標変換(3D座標→2D座標)
			element.pos = mul(element.pos, g_WVP);
			element.color = input[0].color;
			element.uv = uv_array[i];
			output.Append(element);
		}

		output.RestartStrip();
	}
}