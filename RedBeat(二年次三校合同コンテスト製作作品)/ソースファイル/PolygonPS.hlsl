//頂点シェーダーから渡されるデータ
//SV_POSITIONはラスタライズで利用されるので
//記述はするが利用できない
struct PS_IN {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};
//テクスチャの受け取りさき
Texture2D tex : register(t0);
SamplerState samp : register(s0);
//画面に出力する色
float4 main(PS_IN pin) : SV_TARGET			//戻り値は画面に出力する色
{
		return  tex.Sample(samp,pin.uv);

}
