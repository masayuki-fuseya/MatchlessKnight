// 定数バッファ(コンスタントバッファ)
cbuffer global
{
	// ワールドから射影までの変換行列(列優先)
	row_major matrix g_WVP;
	// ビルボード行列(列優先)
	row_major matrix g_Billboard;
};

// テクスチャスロット0番に受け取る
Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

// ジオメトリシェーダへの入力
struct GSInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 other : TEXCOORD;	// x:スケール
};

// ピクセルシェーダへの入力
struct PSInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};