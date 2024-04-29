//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}





//���_�V�F�[�_�[����n�����f�[�^
//SV_POSITION�̓��X�^���C�Y�ŗ��p�����̂�
//�L�q�͂��邪���p�ł��Ȃ�
struct PS_IN {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};
//�e�N�X�`���̎󂯎�肳��
Texture2D tex : register(t0);
//�F�̏E�����̐ݒ�
SamplerState samp : register(s0);
//��ʂɏo�͂���F
float4 main(PS_IN pin) : SV_TARGET			//�߂�l�͉�ʂɏo�͂���F
{
	//�e�N�X�`���̐F���擾
	float4 color = tex.Sample(samp,pin.uv);
	//�l�K�|�W���]�@�@�@1������͒l�𔲂�

	//color.r = 1 - color.r;
	//color.g = 1 - color.g;
	//color.b = 1 - color.b;
	color.r = 1- color.r;
	color.g = 1- color.g;
	color.b = 1-color.b;
	return  color;

}
