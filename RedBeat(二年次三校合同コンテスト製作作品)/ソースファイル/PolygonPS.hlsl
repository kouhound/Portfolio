//���_�V�F�[�_�[����n�����f�[�^
//SV_POSITION�̓��X�^���C�Y�ŗ��p�����̂�
//�L�q�͂��邪���p�ł��Ȃ�
struct PS_IN {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};
//�e�N�X�`���̎󂯎�肳��
Texture2D tex : register(t0);
SamplerState samp : register(s0);
//��ʂɏo�͂���F
float4 main(PS_IN pin) : SV_TARGET			//�߂�l�͉�ʂɏo�͂���F
{
		return  tex.Sample(samp,pin.uv);

}
