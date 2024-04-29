//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}

//CPUから受け取った頂点データ
struct VS_IN 
{ 
	float3 pos:POSITION0;
	float2 uv:TEXCOORD0;
};
//ピクセルシェーダに渡すデータ
//SV_POSITIONはラスタライザに渡される
struct VS_OUT 
{ 
	float4 pos: SV_POSITION; 
	float2 uv:TEXCOORD0;
};

//定数バッファ定義
//cbuffer AnimeUV : register(b0) {
//	float uvW;
//	float uvH;
//	float uvTX;
//	float uvTY;
//}
//画面に表示する位置を計算
//実際の画面は-1~1の座標となっているので
//その範囲に収まるよう計算する
VS_OUT main(VS_IN vin) {  //戻り値はピクセルシェーダに渡すデータ


	VS_OUT vout;
	vout.uv = vin.uv;

	//分割したサイズにスケーリング
	//vout.uv.x *= uvW;
	//vout.uv.y *= uvH;
	//vout.uv.x += uvTX;
	//vout.uv.x += uvTY;
	vout.pos = float4(vin.pos, 1.0f);

	//1.画面の上下をひっくり返す
	vout.pos.y *= -1.0f;
	//2.画面のスケールを小さくする
	vout.pos.x /= 480.0f;
	vout.pos.y /= 270;

	//3.0.0の座標の位置を左上美移動
	vout.pos.x -= 1.0f;
	vout.pos.y += 1.0f;

		return vout;
}