//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}

//CPU����󂯎�������_�f�[�^
struct VS_IN 
{ 
	float3 pos:POSITION0;
	float2 uv:TEXCOORD0;
};
//�s�N�Z���V�F�[�_�ɓn���f�[�^
//SV_POSITION�̓��X�^���C�U�ɓn�����
struct VS_OUT 
{ 
	float4 pos: SV_POSITION; 
	float2 uv:TEXCOORD0;
};

//�萔�o�b�t�@��`
//cbuffer AnimeUV : register(b0) {
//	float uvW;
//	float uvH;
//	float uvTX;
//	float uvTY;
//}
//��ʂɕ\������ʒu���v�Z
//���ۂ̉�ʂ�-1~1�̍��W�ƂȂ��Ă���̂�
//���͈̔͂Ɏ��܂�悤�v�Z����
VS_OUT main(VS_IN vin) {  //�߂�l�̓s�N�Z���V�F�[�_�ɓn���f�[�^


	VS_OUT vout;
	vout.uv = vin.uv;

	//���������T�C�Y�ɃX�P�[�����O
	//vout.uv.x *= uvW;
	//vout.uv.y *= uvH;
	//vout.uv.x += uvTX;
	//vout.uv.x += uvTY;
	vout.pos = float4(vin.pos, 1.0f);

	//1.��ʂ̏㉺���Ђ�����Ԃ�
	vout.pos.y *= -1.0f;
	//2.��ʂ̃X�P�[��������������
	vout.pos.x /= 480.0f;
	vout.pos.y /= 270;

	//3.0.0�̍��W�̈ʒu��������ړ�
	vout.pos.x -= 1.0f;
	vout.pos.y += 1.0f;

		return vout;
}