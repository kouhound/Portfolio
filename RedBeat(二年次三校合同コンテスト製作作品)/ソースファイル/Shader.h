#ifndef __SHADER_H__
#define __SHADER_H__

#include <d3d11.h>
#include <string>
#include <map>

// �V�F�[�_�[�̊�{�N���X
class Shader
{
protected:
	enum Kind
	{
		VertexShader,
		PixelShader
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader();
public:
	// �V�F�[�_�[�t�@�C��(*.cso)��ǂݍ��ޏ���
	HRESULT Load(ID3D11Device* pDevice, const char *pFileName);
	// �����񂩂�V�F�[�_���R���p�C��
	HRESULT Compile(ID3D11Device* pDevice, const char *pCode);

	// �V�F�[�_�[��`��Ɏg�p
	virtual void Bind(ID3D11DeviceContext* pContext) = 0;

protected:
	// �V�F�[�_�[�t�@�C����ǂݍ��񂾌�A�V�F�[�_�[�̎�ޕʂɏ������s��
	virtual HRESULT MakeShader(ID3D11Device* pDevice, void* pData, UINT size) = 0;

private:
	Kind m_kind;
};

//----------
// ���_�V�F�[�_
class VertexShader : public Shader
{
private:
	using ILKey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::map<std::string, ID3D11InputLayout*>;
public:
	static void ReleaseInputLayout();

	VertexShader();
	~VertexShader() final;
	void Bind(ID3D11DeviceContext* pContext) final;
protected:
	HRESULT MakeShader(ID3D11Device* pDevice, void* pData, UINT size);

private:
	static ILList m_ilList;
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};

//----------
// �s�N�Z���V�F�[�_
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader() final;
	void Bind(ID3D11DeviceContext* pContext) final;
protected:
	HRESULT MakeShader(ID3D11Device* pDevice, void* pData, UINT size);
private:
	ID3D11PixelShader* m_pPS;
};

//--- �e�N�X�`��
void SetTexture(ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTex, UINT slot = 0);

#endif