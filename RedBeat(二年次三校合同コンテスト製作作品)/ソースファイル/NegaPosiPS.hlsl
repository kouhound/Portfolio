//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}





//頂点シェーダーから渡されるデータ
//SV_POSITIONはラスタライズで利用されるので
//記述はするが利用できない
struct PS_IN {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};
//テクスチャの受け取りさき
Texture2D tex : register(t0);
//色の拾い方の設定
SamplerState samp : register(s0);
//画面に出力する色
float4 main(PS_IN pin) : SV_TARGET			//戻り値は画面に出力する色
{
	//テクスチャの色を取得
	float4 color = tex.Sample(samp,pin.uv);
	//ネガポジ反転　　　1から入力値を抜く

	//color.r = 1 - color.r;
	//color.g = 1 - color.g;
	//color.b = 1 - color.b;
	color.r = 1- color.r;
	color.g = 1- color.g;
	color.b = 1-color.b;
	return  color;

}
