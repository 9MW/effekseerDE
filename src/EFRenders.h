#pragma once
#include "../EffekseerRendererCommon/EffekseerRenderer.ModelRendererBase.h"
#include"EffekseerRendererDE.h"
namespace EffekseerRendererDE {
	using namespace Diligent;
	typedef ::Effekseer::ModelRenderer::NodeParameter efkModelNodeParam;
	typedef ::Effekseer::ModelRenderer::InstanceParameter efkModelInstanceParam;
	typedef ::Effekseer::Vector3D efkVector3D;

	class ModelRenderer : public EffekseerRenderer::ModelRendererBase
	{
	private:
		RendererImplemented* m_renderer;
		Shader* m_shader_lighting_texture_normal;
		Shader* m_shader_texture;
		Shader* m_shader_distortion_texture;

		ModelRenderer(RendererImplemented* renderer,
			Shader* shader_buf_lighting_texture_normal,
			Shader* shader_buf_texture,
			Shader* shader_buf_distortion_texture);

	public:
		virtual ~ModelRenderer();

		static ModelRenderer* Create(RendererImplemented* renderer, FixedShader* fixedShader);

	public:
		void BeginRendering(const efkModelNodeParam& parameter, int32_t count, void* userData) override;

		virtual void Rendering(const efkModelNodeParam& parameter, const InstanceParameter& instanceParameter, void* userData) override;

		void EndRendering(const efkModelNodeParam& parameter, void* userData) override;
	};

}