#ifndef __SHADER_H__
#define __SHADER_H__

#include <d3d11.h>
#include <string>
#include <map>

// シェーダーの基本クラス
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
	// シェーダーファイル(*.cso)を読み込む処理
	HRESULT Load(ID3D11Device* pDevice, const char *pFileName);
	// 文字列からシェーダをコンパイル
	HRESULT Compile(ID3D11Device* pDevice, const char *pCode);

	// シェーダーを描画に使用
	virtual void Bind(ID3D11DeviceContext* pContext) = 0;

protected:
	// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
	virtual HRESULT MakeShader(ID3D11Device* pDevice, void* pData, UINT size) = 0;

private:
	Kind m_kind;
};

//----------
// 頂点シェーダ
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
// ピクセルシェーダ
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

//--- テクスチャ
void SetTexture(ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTex, UINT slot = 0);

#endif