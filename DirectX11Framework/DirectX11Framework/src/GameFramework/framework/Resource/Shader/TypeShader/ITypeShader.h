// 個々の種類のシェーダのインターフェース
// 2017.05.14	: プログラム作成
// author		: SyunMizuno


#pragma once

#include	<Windows.h>
#include	<string>


namespace ShaderCollection {

	interface ITypeShader {
	public:
		ITypeShader() {}
		virtual ~ITypeShader() {}
		virtual void Begin() {}
		virtual void End() {}

		const std::string& GetFileName() const { return m_FileName; }
		const std::string& GetFunction() const { return m_Function; }
		const std::string& GetVersion() const { return m_Version; }

		__declspec(property(get = GetFileName)) std::string filename;

	protected:
		std::string m_FileName;
		std::string m_Function;
		std::string m_Version;
	};

}