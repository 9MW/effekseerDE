#pragma once
#define PLATFORM_WIN32 1
//#define _MSC_VER 1
#include <Effekseer.h>
//#include "Effekseer.h"
#include "EffekseerRendererCommon/EffekseerRenderer.Renderer.h"

#include <Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>

#include<filesystem>

#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "Common/interface/RefCntAutoPtr.hpp"
#include "EffekseerRendererCommon/EffekseerRenderer.RenderStateBase.h"
#include "EffekseerRendererCommon/EffekseerRenderer.StandardRenderer.h"
#include "EffekseerRendererCommon/EffekseerRenderer.CommonUtils.h"
#include "EffekseerRendererCommon/EffekseerRenderer.IndexBufferBase.h"
#include "EffekseerRendererCommon/EffekseerRenderer.PngTextureLoader.h"
#include "EffekseerRendererCommon/EffekseerRenderer.ModelRendererBase.h"
#include "span.hpp""
//#include"MaterialLoader.cpp"
namespace LLGI
{

	struct CompilerResult
	{
		std::string Message;
		std::vector<std::vector<uint8_t>> Binary;
	};
}
namespace std {
	using namespace std;
	template<class T>
	using span = nonstd::span<T>;
}
namespace EffekseerRendererDE
{
	using BYTE = unsigned char;
	typedef ::Effekseer::ModelRenderer::NodeParameter efkModelNodeParam;
	typedef ::Effekseer::ModelRenderer::InstanceParameter efkModelInstanceParam;
	typedef ::Effekseer::Vector3D efkVector3D;
	using namespace Diligent;
	//using Uint32 = Diligent::Uint32;

	template <class T> void SafeAddRef(T& t)
	{
		if (t != NULL)
		{
			t->AddRef();
		}
	}
	template <class T> void SafeRelease(T& t)
	{
		if (t != NULL)
		{
			t->Release();
			t = NULL;
		}
	}
	struct DataStructure {
		//using BYTE = void*;
		void* Data = nullptr;
		std::vector<ShaderResourceVariableDesc> _srvd;
		size_t Size = 0;
		DataStructure(void* d, size_t sz,const std::vector<ShaderResourceVariableDesc> sd)
			:Data((d)), Size(sz),_srvd(sd) {}
		DataStructure(void* d, size_t sz)
			:Data((d)), Size(sz) {}
		DataStructure() {}
		size_t size_bytes()const { return Size; }
		void* data() { return Data; }
	};
	class ReferenceObject
	{
	private:
		mutable std::atomic<int32_t> reference;

	public:
		ReferenceObject() : reference(1) {}

		virtual ~ReferenceObject() {}

		int AddRef()
		{
			std::atomic_fetch_add_explicit(&reference, 1, std::memory_order_consume);
			return reference;
		}

		int GetRef() { return reference; }

		int Release()
		{
			assert(reference > 0);

			bool destroy = std::atomic_fetch_sub_explicit(&reference, 1, std::memory_order_consume) == 1;
			if (destroy)
			{
				delete this;
				return 0;
			}

			return reference;
		}
	};
	class Vbuf
	{
	private:
		Diligent::IBuffer* buf = nullptr;
		size_t Size_ = 0;

	public:
		Vbuf(Diligent::IBuffer* buffer, int size) :buf(buffer)
			, Size_(size) {
		}
		Vbuf() {}
		Vbuf(const Vbuf& v) :buf(v.buf), Size_(v.Size_) { v.buf->AddRef(); }
		~Vbuf() {
			SafeRelease(buf);
		}
		void Release() { buf->Release(); }
		void WriteTo(IDeviceContext* pContext, const void* p, const size_t sz) {
			void* mapped_ = nullptr;
			pContext->MapBuffer
			(buf, MAP_WRITE, MAP_FLAG_DO_NOT_WAIT, (PVoid&)mapped_);
			std::memcpy(mapped_, p, sz);
		}
		void* Lock() {
			return nullptr;
		};
		void reset(IBuffer* vertexBuffer) {
			buf = vertexBuffer;
		}
		int GetSize() const { return Size_; };
		Diligent::IBuffer* Get() { return buf; }
	};
	using VertexDistortion = EffekseerRenderer::VertexDistortion;
	using RenderPassPipelineState = Diligent::IPipelineState;
	class RendererImplemented;
	using Vertex = EffekseerRenderer::SimpleVertex;
	using GraphicsDevice = Diligent::IRenderDevice;
	struct GraphicsDE {
		GraphicsDevice* graphicsDevice = nullptr;
		Diligent::IDeviceContext* ImmediateContext = nullptr;
		IEngineFactory* m_pEngineFactory;
		ISwapChain* m_pSwapChain;
		GraphicsDevice* GetDevice() { return graphicsDevice; }
		Diligent::IDeviceContext*& GetContext() { return ImmediateContext; }

		void Release() {
			graphicsDevice->Release(); ImmediateContext->Release();
		}
	};

	class MaterialLoader : public ::Effekseer::MaterialLoader
	{
	private:
		GraphicsDE* GraphicsDE_ = nullptr;
		::Effekseer::FileInterface* fileInterface_ = nullptr;
		/*::Effekseer::CompiledMaterialPlatformType platformType_;
		::Effekseer::MaterialCompiler* materialCompiler_ = nullptr;*/
		::Effekseer::DefaultFileInterface defaultFileInterface_;

		::Effekseer::MaterialData* LoadAcutually(::Effekseer::Material& material, void* binary);



	public:
		MaterialLoader(GraphicsDE* GraphicsDE,
			::Effekseer::FileInterface* fileInterface
			/*::Effekseer::CompiledMaterialPlatformType platformType,
			::Effekseer::MaterialCompiler* materialCompiler*/
		)
			: fileInterface_(fileInterface), GraphicsDE_(GraphicsDE)
		{
			if (fileInterface == nullptr)
			{
				fileInterface_ = &defaultFileInterface_;
			}

			/*ES_SAFE_ADDREF(GraphicsDE_);
			ES_SAFE_ADDREF(materialCompiler_);*/
		}
		//virtual ~MaterialLoader();

		::Effekseer::MaterialData* Load(const EFK_CHAR* path) override;

		::Effekseer::MaterialData* Load(const void* data, int32_t size, Effekseer::MaterialFileType fileType) override;

		void Unload(::Effekseer::MaterialData* data) override;
	};
	class InternalSingleFrameMemoryPool
	{
	private:
		IBuffer* constantBuffer_ = nullptr;
		int32_t constantBufferSize_ = 0;
		int32_t constantBufferOffset_ = 0;
		Diligent::BufferViewDesc bvdesc;
	public:
		InternalSingleFrameMemoryPool(GraphicsDE* graphics, int32_t constantBufferPoolSize, int32_t drawingCount);
		~InternalSingleFrameMemoryPool();
		//template<class T>
		bool GetConstantBuffer(int32_t size, IBuffer*& resource, Diligent::Uint32& offset);
		void Reset();
	};
	class ConstantBuffer;
	class SingleFrameMemoryPool : public ReferenceObject
	{
	protected:
		int32_t currentSwapBuffer_ = -1;
		int32_t swapBufferCount_ = 2;
		std::vector<int32_t> offsets_;
		std::vector<std::vector<ConstantBuffer*>> constantBuffers_;

		GraphicsDE* graphics_ = nullptr;
		bool isStrongRef_ = false;
		std::vector<std::shared_ptr<InternalSingleFrameMemoryPool>> memoryPools;
		int32_t currentSwap_ = 0;
		int32_t drawingCount_ = 0;

		/**
			@brief	create constant buffer
		*/
		ConstantBuffer* CreateConstantBufferInternal(int32_t size);
		/**
			@brief	reinitialize buffer with a size
		*/
		ConstantBuffer* ReinitializeConstantBuffer(ConstantBuffer* cb, int32_t size);

	public:
		SingleFrameMemoryPool(
			GraphicsDE* graphics, bool isStrongRef, int32_t swapBufferCount, int32_t constantBufferPoolSize, int32_t drawingCount);

		~SingleFrameMemoryPool();
		static SingleFrameMemoryPool* CreateSingleFrameMemoryPool
		(GraphicsDE* gd, size_t sz = 1024 * 1024 * 8, int32_t swapBufferCount = 2);
		static SingleFrameMemoryPool* CreateSingleFrameMemoryPool
		(::EffekseerRenderer::Renderer* renderer);

		/**
		@brief	Start new frame
		*/
		bool GetConstantBuffer(int32_t size, IBuffer*& resource, Uint32& offset);
		GraphicsDE* GetDE() { return graphics_; }
		InternalSingleFrameMemoryPool* GetInternal();

		int32_t GetDrawingCount() const;

		void NewFrame();

		ConstantBuffer* CreateConstantBuffer(int32_t size);
	};
	class IndexBuffer : public ReferenceObject, public EffekseerRenderer::IndexBufferBase
	{
	private:
		IBuffer* indexBuffer_ = nullptr;
		//uint8_t* mapped_ = nullptr;
		int32_t  count_ = 0;
		GraphicsDE* graphicsDevice_;
	public:
		bool Initialize(GraphicsDevice* graphics, int32_t stride, int32_t count) {
			Diligent::BufferDesc BuffDesc;
			BuffDesc.Name = "Effekseer index buffer";
			BuffDesc.Usage = USAGE_DEFAULT;
			BuffDesc.BindFlags = BIND_INDEX_BUFFER;
			BuffDesc.ElementByteStride = stride;
			BuffDesc.uiSizeInBytes = BuffDesc.ElementByteStride * count;
			graphics->CreateBuffer(BuffDesc, nullptr, &indexBuffer_);
			return (indexBuffer_ != nullptr);
		}
		static IBuffer* CreateIndexBuffer(GraphicsDevice* graphicsDevice, int32_t stride, int32_t count)
		{
			IBuffer* indexBuffer_ = nullptr;
			Diligent::BufferDesc BuffDesc;
			BuffDesc.Name = "Effekseer index buffer";
			BuffDesc.Usage = USAGE_DEFAULT;
			BuffDesc.BindFlags = BIND_INDEX_BUFFER;
			BuffDesc.ElementByteStride = stride;
			BuffDesc.uiSizeInBytes = BuffDesc.ElementByteStride * count;
			graphicsDevice->CreateBuffer(BuffDesc, nullptr, &indexBuffer_);
			return indexBuffer_;
		}
		IndexBuffer(GraphicsDE* graphicsDevice, IBuffer* buffer, int maxCount, bool isDynamic, bool hasRefCount)
			: IndexBufferBase(maxCount, isDynamic), indexBuffer_(buffer), graphicsDevice_(graphicsDevice)
		{
			/*auto pContext = graphicsDevice->GetContext();
			pContext->MapBuffer(indexBuffer_, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, (PVoid&)m_resource);*/
		}
		//IndexBuffer() {}
		~IndexBuffer();
		static IndexBuffer* Create(GraphicsDE* graphicsDevice, int maxCount, bool isDynamic, bool hasRefCount);
		void reset(IBuffer* indexBuffer) {
			indexBuffer_ = indexBuffer;
			m_resource = nullptr;
			stride_ = 0;
			count_ = 0;
		}
		constexpr void* Map(IDeviceContext* pContext) {
			return m_resource == nullptr ? m_resource : nullptr;
		}
		void Lock()override;
		//void* Lock(int32_t offset, int32_t size);
		void Unlock()override;
		virtual int32_t GetStride() { return stride_; }
		virtual int32_t GetCount() { return count_; }
		IBuffer* Get() { return indexBuffer_; }
	};
	/*4. Unmap the buffer and issue draw command.Note that in Direct3D12 and Vulkan backends, unmapping the buffer is not required
		and can be safely skipped to improve performance*/
	class Model : public Effekseer::Model
	{
	private:
		GraphicsDE* graphicsDevice_ = nullptr;

	public:
		struct InternalModel
		{
			IBuffer* VertexBuffer;
			IBuffer* IndexBuffer;
			int32_t VertexCount;
			int32_t IndexCount;
			int32_t FaceCount;

			InternalModel()
			{
				VertexBuffer = nullptr;
				IndexBuffer = nullptr;
				VertexCount = 0;
				IndexCount = 0;
				FaceCount = 0;
			}

			virtual ~InternalModel()
			{
				ES_SAFE_RELEASE(VertexBuffer);
				ES_SAFE_RELEASE(IndexBuffer);
			}
		};

		InternalModel* InternalModels = nullptr;
		int32_t ModelCount;
		bool IsLoadedOnGPU = false;

		Model(uint8_t* data, int32_t size, GraphicsDE* graphicsDevice)
			: Effekseer::Model(data, size), InternalModels(nullptr), graphicsDevice_(graphicsDevice), ModelCount(0)
		{
			this->m_vertexSize = sizeof(VertexWithIndex);
			//ES_SAFE_ADDREF(graphicsDevice_);
		}

		virtual ~Model()
		{
			ES_SAFE_DELETE_ARRAY(InternalModels);
			//ES_SAFE_RELEASE(graphicsDevice_);
		}

		bool LoadToGPU();
	};
	class ModelLoader : public ::Effekseer::ModelLoader
	{
		using GraphicsDevice = GraphicsDE;
	private:
		GraphicsDevice* graphicsDevice_ = nullptr;
		::Effekseer::FileInterface* m_fileInterface;
		::Effekseer::DefaultFileInterface m_defaultFileInterface;

	public:
		ModelLoader(GraphicsDevice* graphicsDevice, ::Effekseer::FileInterface* fileInterface);
		virtual ~ModelLoader();

	public:
		void* Load(const EFK_CHAR* path);

		void* Load(const void* data, int32_t size) override;

		void Unload(void* data);
	};

	//using namespace Diligent;
	using VertexLayout = Diligent::LayoutElement;
	template<class T>
	constexpr void DeleteArray(T& ay)
	{
		if (ay)
			delete[] ay;
	}
	constexpr int CbSize = 512;
	class Shader //: public DeviceObject, public EffekseerRenderer::ShaderBase
	{
	private:
		using GraphicsDevice = Diligent::IRenderDevice;
		Diligent::IShader* vertexShader_ = nullptr;
		Diligent::IShader* pixelShader_ = nullptr;
		std::vector<VertexLayout> layouts_;
		std::vector<ShaderResourceVariableDesc> vsv_;
		std::vector<ShaderResourceVariableDesc> psv_;
		IShaderResourceVariable* VCbuf;
		void* m_vertexConstantBuffer = nullptr;;
		void* m_pixelConstantBuffer = nullptr;;
		int32_t vertexConstantBufferSize = 0;
		int32_t pixelConstantBufferSize = 0;
		bool write = false;
		int32_t m_vertexRegisterCount;
		int32_t m_pixelRegisterCount;
		GraphicsDE* gd;
		/*Shader(GraphicsDevice* m_pDevice,
			DataStructure* vertexShader,
			DataStructure* pixelShader,
			const char* name,
			const std::span<VertexLayout> layouts,
			bool hasRefCount) :
			m_vertexRegisterCount(0)
			, m_pixelRegisterCount(0)
			, layouts_(layouts.begin(), layouts.end()), name(name) {

			ShaderCreateInfo                               ShaderCI;
			ShaderCI.ByteCode = vertexShader->data();
			ShaderCI.ByteCodeSize = vertexShader->size_bytes();
			ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
			ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
			m_pDevice->CreateShader(ShaderCI, &vertexShader_);

			ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
			ShaderCI.ByteCode = pixelShader->data();
			ShaderCI.ByteCodeSize = pixelShader->size_bytes();
			m_pDevice->CreateShader(ShaderCI, &vertexShader_);
		}
		Shader(GraphicsDevice* m_pDevice,
			char* vertexShader,
			char* pixelShader,
			const char* name,
			const std::span<VertexLayout> layouts,
			bool hasRefCount) :
			m_vertexRegisterCount(0)
			, m_pixelRegisterCount(0)
			, layouts_(layouts.begin(), layouts.end()), name(name) {

			ShaderCreateInfo                               ShaderCI;
			ShaderCI.Source = vertexShader;
			ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
			ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
			m_pDevice->CreateShader(ShaderCI, &vertexShader_);

			ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
			ShaderCI.Source = pixelShader;
			m_pDevice->CreateShader(ShaderCI, &vertexShader_);
		}*/
		Shader(GraphicsDE* gd,
			IShader* vertexShader,
			IShader* pixelShader,
			const char* name,
			const std::span<VertexLayout> layouts,
			bool hasRefCount) :
			vertexShader_(vertexShader),
			pixelShader_(pixelShader),
			m_vertexRegisterCount(0)
			, m_pixelRegisterCount(0),gd(gd)
			, layouts_(layouts.begin(), layouts.end()), name(name) {
			vertexShader->AddRef();
			pixelShader->AddRef();
			Diligent::BufferDesc VertBuffDesc;
			VertBuffDesc.Name = "EF pixel constant buffer";
			VertBuffDesc.Usage = USAGE_DEFAULT;
			VertBuffDesc.BindFlags = BIND_UNIFORM_BUFFER;
			VertBuffDesc.uiSizeInBytes = CbSize;
			//VertBuffDesc.Mode = BUFFER_MODE_RAW;
			VertBuffDesc.ElementByteStride = CbSize;
			gd->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &m_P);
			CreateUniformBuffer(gd->GetDevice(), CbSize, "EF vertex constant buffer", &m_V, USAGE_DEFAULT, BIND_UNIFORM_BUFFER,CPU_ACCESS_NONE);
			//gd->GetContext()->MapBuffer(m_V, MAP_TYPE::MAP_WRITE, MAP_FLAG_DISCARD,m_vertexConstantBuffer);
		}

		//Shader(GraphicsDE* gd,
		//	IShader* vertexShader,
		//	IShader* pixelShader,
		//	const char* name,
		//	const std::span<VertexLayout> layouts,
		//	const std::span<ShaderResourceVariableDesc> sv,
		//	bool hasRefCount) :
		//	vertexShader_(vertexShader),
		//	pixelShader_(pixelShader),
		//	m_vertexRegisterCount(0)
		//	, m_pixelRegisterCount(0), gd(gd)
		//	, layouts_(layouts.begin(), layouts.end()),
		//	sv_(sv.begin(),sv.end()),name(name) {
		//	vertexShader->AddRef();
		//	pixelShader->AddRef();
		//	Diligent::BufferDesc VertBuffDesc;
		//	VertBuffDesc.Name = "EF pixel constant buffer";
		//	VertBuffDesc.Usage = USAGE_DEFAULT;
		//	VertBuffDesc.BindFlags = BIND_UNIFORM_BUFFER;
		//	VertBuffDesc.uiSizeInBytes = CbSize;
		//	VertBuffDesc.Mode = BUFFER_MODE_RAW;
		//	VertBuffDesc.ElementByteStride = CbSize;
		//	gd->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &m_P);
		//	CreateUniformBuffer(gd->GetDevice(), CbSize, "EF vertex constant buffer", &m_V, USAGE_DEFAULT, BIND_UNIFORM_BUFFER, CPU_ACCESS_NONE);
		//	//gd->GetContext()->MapBuffer(m_V, MAP_TYPE::MAP_WRITE, MAP_FLAG_DISCARD,m_vertexConstantBuffer);
		//}
	public:
		~Shader() {
			for (size_t i = 0; i < TexSrv_.size(); i++)
			{
				TexSrv_[i]->Release();
			}
			VCbuf->Release();
			vertexShader_->Release();
			pixelShader_->Release();
		}

		static Shader* Create(GraphicsDevice* graphicsDevice,
			DataStructure* vertexData,
			int32_t vertexDataCount,
			DataStructure* pixelData,
			int32_t pixelDataCount,
			const char* name,
			const std::span<VertexLayout> layout,
			bool hasRefCount) {

			return nullptr;
		}
		/*static Shader* Create(GraphicsDevice* graphicsDevice,
			void* vertexData,
			int32_t vertexDataCount,
			void* pixelData,
			int32_t pixelDataCount,
			const char* name,
			const std::span<VertexLayout> layout,
			bool hasRefCount) {
			return  new Shader(graphicsDevice,&DataStructure(vertexData, vertexDataCount),
				&DataStructure(pixelData, pixelDataCount), name, layout, hasRefCount);
		}*/
		/*static Shader* Create(GraphicsDE* m_pDevice,
			const DataStructure* vertexShader,
			const DataStructure* pixelShader,
			const char* name,
			const std::span<VertexLayout> layouts,
			const std::span<ShaderResourceVariableDesc> sv,
			bool hasRefCount) {
			return  new Shader(m_pDevice, (IShader*)(vertexShader->Data), (IShader*)pixelShader->Data, name, layouts,sv,hasRefCount);
		}*/
		static Shader* Create(GraphicsDE* m_pDevice,
			const DataStructure* vertexShader,
			const DataStructure* pixelShader,
			const char* name,
			const std::span<VertexLayout> layouts,
			bool hasRefCount) {
			Shader* sd=  new Shader(m_pDevice, (IShader*)(vertexShader->Data), (IShader*)pixelShader->Data, name, layouts, hasRefCount);
			const auto svdv= vertexShader->_srvd;
			sd->vsv_.insert(sd->vsv_.end(),svdv.begin(),svdv.end());
			const auto svdp = pixelShader->_srvd;
			sd->psv_.insert(sd->psv_.end(), svdp.begin(), svdp.end());
			return sd;
		}
	public:
		std::vector<Diligent::RefCntAutoPtr<IPipelineState>> ps_;
		std::vector<ShaderResourceVariableDesc> Vars;
		std::vector<IShaderResourceVariable*> TexSrv_;

		RefCntAutoPtr<IShaderResourceBinding> m_SRB;
		RefCntAutoPtr<IBuffer> m_V;
		RefCntAutoPtr<IBuffer> m_P;
		RefCntAutoPtr<IShaderResourceVariable> VCB;
		RefCntAutoPtr<IShaderResourceVariable> VPB;
		const char* name;
		Diligent::IShader* GetVertexShader() const { return vertexShader_; }
		Diligent::IShader* GetPixelShader() const { return pixelShader_; }
		std::vector<VertexLayout>& GetVertexLayouts() { return layouts_; }
		void SetVertexConstantBufferSize(int32_t size) {
			//assert(size < CbSize);
			DeleteArray(m_vertexConstantBuffer);
			m_vertexConstantBuffer = new uint8_t[size];
			vertexConstantBufferSize = size;
		}
		void SetPixelConstantBufferSize(int32_t size) {
			DeleteArray(m_pixelConstantBuffer);
			m_pixelConstantBuffer = new uint8_t[size];
			pixelConstantBufferSize = size;
		}
		void SetVCB(IShaderResourceVariable* vcb,bool uniform=false) {
			VCB = vcb;
			if (uniform) {
				vcb->Set(m_V);
			}
			write = false;
		}
		void SetVPCB(IShaderResourceVariable* vcb, IShaderResourceVariable* vpb,bool uniform = true) {
			VCB = vcb;
			VPB = vpb;
			vcb->Set(m_V);
			if(VPB)
			vpb->Set(m_P);
			//write = false;
		}
		void Writecb(Diligent::IDeviceContext* ctx) {
			/*if (write)return;
			write = true;*/
		   ctx->UpdateBuffer(m_V, 0, vertexConstantBufferSize, m_vertexConstantBuffer, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		   if (m_pixelConstantBuffer)
		   ctx->UpdateBuffer(m_P, 0, pixelConstantBufferSize, m_pixelConstantBuffer, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		}
		int32_t GetVertexConstantBufferSize() { return vertexConstantBufferSize; }
		int32_t GetPixelConstantBufferSize() { return pixelConstantBufferSize; }

		std::vector<ShaderResourceVariableDesc>& GetVerteVariableDesc() { return vsv_; }
		std::vector<ShaderResourceVariableDesc>& GetPixelVariableDesc() { return psv_; }


		void* GetVertexConstantBuffer() { return m_vertexConstantBuffer; }
		void* GetPixelConstantBuffer() { return m_pixelConstantBuffer; }

		void SetVertexRegisterCount(int32_t count) { m_vertexRegisterCount = count; }
		void SetPixelRegisterCount(int32_t count) { m_pixelRegisterCount = count; }

		void SetConstantBuffer() {}
	};
	struct FixedShader
	{
		std::vector<DataStructure> StandardTexture_VS;
		std::vector<DataStructure> StandardLightingTexture_VS;
		std::vector<DataStructure> StandardDistortedTexture_VS;

		std::vector<DataStructure> ModelShaderLightingTextureNormal_VS;
		std::vector<DataStructure> ModelShaderTexture_VS;
		std::vector<DataStructure> ModelShaderDistortionTexture_VS;

		std::vector<DataStructure> StandardTexture_PS;
		std::vector<DataStructure> StandardLightingTexture_PS;
		std::vector<DataStructure> StandardDistortedTexture_PS;

		std::vector<DataStructure> ModelShaderLightingTextureNormal_PS;
		std::vector<DataStructure> ModelShaderTexture_PS;
		std::vector<DataStructure> ModelShaderDistortionTexture_PS;
	};
	class Tex : public ReferenceObject
	{
	public:

		Tex(Diligent::ITexture* t = nullptr, Diligent::RESOURCE_STATE state = RESOURCE_STATE_UNKNOWN) :texture(t), state_(state) {
			tvs.fill(nullptr);
			
		}
		//Tex() {}
		~Tex() { Release(); }
		Diligent::ITexture* texture = nullptr;
		SamplerDesc CurrsamplerDesc;
		static Tex* CreateTexture(GraphicsDE* gd, const TextureDesc TexDesc,
			const TextureData InitData)
		{
			Diligent::IRenderDevice* graphicsDevice_ = gd->GetDevice();
			Diligent::ITexture* tex = nullptr;
			/*TextureViewDesc desc;
			desc.TextureDim = RESOURCE_DIMENSION::RESOURCE_DIM_TEX_2D;*/
			graphicsDevice_->CreateTexture(TexDesc, &InitData, &tex);
			auto tx= new Tex(tex);
			auto& state_ = tx->state_;
			state_ = RESOURCE_STATE_SHADER_RESOURCE;
			StateTransitionDesc Barriers = { tex,RESOURCE_STATE_UNKNOWN, state_, true };
			gd->GetContext()->TransitionResourceStates(1, &Barriers);
			return tx;
		}
		void reset(const Tex& other) {
			if (texture != other.texture) {
				//other.texture->AddRef(); 
				for (size_t i = 0; i < tvs.size(); i++)
				{
					SafeRelease(tvs[i]);
				}
				texture = other.texture;
			}
			/*if (sampler != other.sampler) {
				SafeRelease(sampler);
				sampler = other.sampler;
			}*/
			state_ = other.state_;
		}
		void Release() {
			SafeRelease(texture);
			for (size_t i = 0; i < tvs.size(); i++)
			{
				SafeRelease(tvs[i]);
			}
		}
		ITextureView* GetView(const SamplerDesc samplerDesc, GraphicsDE* graphicsDevice);
	private:
		std::array<ITextureView*,8> tvs;
		Diligent::RESOURCE_STATE state_;
	};

	enum class ShaderStageType
	{
		Vertex,
		Pixel,
		Max,
	};
	class CommandList //: public ::Effekseer::IReference
	{
		static constexpr int NumTexture = 8;
		using PipelineState = Diligent::IPipelineState;
		struct BindingVertexBuffer
		{
			Diligent::IBuffer* vertexBuffer = nullptr;
			int32_t stride = 0;
			int32_t offset = 0;
		};
		struct BindingConstBuffer
		{
			Diligent::IBuffer* Pbf = nullptr;
			Diligent::BufferViewDesc desc;
		};
		struct BindingIndexBuffer
		{
			IndexBuffer* indexBuffer = nullptr;
			int32_t offset = 0;
		};

		Diligent::IDeviceContext* pCtx;
		GraphicsDE* gd;
		SingleFrameMemoryPool* memoryPool_ = nullptr;
		RefCntAutoPtr<IShaderResourceBinding> m_pSRB;
		bool isVertexBufferDirtied = true;
		bool isCurrentIndexBufferDirtied = true;
		bool isPipelineDirtied = true;
		bool doesBeginWithPlatform_ = false;

		BindingVertexBuffer bindingVertexBuffer;
		BindingIndexBuffer bindingIndexBuffer;
		std::array<BindingConstBuffer*, static_cast<int>(ShaderStageType::Max)> constantBuffers = {};
		PipelineState* currentPipelineState = nullptr;
	public:
		RefCntAutoPtr<ICommandList> currentCommandList_;
		std::array<std::array<Tex, NumTexture>, static_cast<int>(ShaderStageType::Max)> currentTextures;

		CommandList(SingleFrameMemoryPool* memoryPool)
			:gd(memoryPool->GetDE()), pCtx(memoryPool->GetDE()->ImmediateContext),
			//currentCommandList_(currentCommandList),
			memoryPool_(memoryPool) {

			for (auto& t : currentTextures)
			{
				for (auto& bt : t)
				{
					bt.texture = nullptr;
				}
			}
		}
		inline void End();
		void SetVertexBuffer(Vbuf* vertexBuffer, int32_t stride, int32_t offset);
		void SetIndexBuffer(IndexBuffer* indexBuffer, int32_t offset = 0);
		void GetCurrentConstantBuffer(ShaderStageType type, BindingConstBuffer*& buffer)
		{
			buffer = constantBuffers[static_cast<int>(type)];
		}
		void SetPipelineState(PipelineState* pipelineState)
		{
			currentPipelineState = pipelineState;
			isPipelineDirtied = true;
		}
		void Release() {}
		SingleFrameMemoryPool* GetMemoryPooll() { return memoryPool_; }
		void Draw(int32_t primitiveCount, Shader* target, int32_t instanceCount = 1);

		//virtual ~CommandList() = default;
	};

	class TextureLoader : public ::Effekseer::TextureLoader
	{
	private:
		GraphicsDevice* graphicsDevice_ = nullptr;
		GraphicsDE* gd;
		::Effekseer::FileInterface* m_fileInterface;
		::Effekseer::DefaultFileInterface m_defaultFileInterface;
		::EffekseerRenderer::PngTextureLoader pngTextureLoader_;

	public:
		TextureLoader(GraphicsDE* gd, ::Effekseer::FileInterface* fileInterface)
			: m_fileInterface(fileInterface), gd(gd)
		{
			//ES_SAFE_ADDREF(graphicsDevice);
			graphicsDevice_ = gd->GetDevice();
			if (fileInterface == nullptr)
			{
				m_fileInterface = &m_defaultFileInterface;
			}
			pngTextureLoader_.Initialize();
		}
		~TextureLoader()override {
			pngTextureLoader_.Finalize();
		}

	public:
		Effekseer::TextureData* Load(const EFK_CHAR* path, ::Effekseer::TextureType textureType) {

			std::unique_ptr<::Effekseer::FileReader> reader(m_fileInterface->OpenRead(path));

			if (reader.get() != NULL)
			{
				Effekseer::TextureData* textureData = nullptr;

				size_t size_texture = reader->GetLength();
				char* data_texture = new char[size_texture];
				reader->Read(data_texture, size_texture);

				if (pngTextureLoader_.Load(data_texture, size_texture, false))
				{
					/*auto ImgFileFormat = IMAGE_FILE_FORMAT_UNKNOWN;
					ImgFileFormat = Image::GetFileFormat(reinterpret_cast<Uint8*>(data_texture), size_texture);*/
					//if (ImgFileFormat == IMAGE_FILE_FORMAT_UNKNOWN)
					{
						//	const auto FilePath = path;
						//	LOG_WARNING_MESSAGE("Unable to derive image format from the header for file \"", FilePath, "\". Trying to analyze extension.");
						//	
						//	// Try to use extension to derive format
						//	auto* pDotPos = std::strrchr(FilePath, '.');
						//	if (pDotPos == nullptr)
						//		LOG_ERROR_AND_THROW("Unable to recognize file format: file name \"", FilePath, "\" does not contain extension");

						//	auto* pExtension = pDotPos + 1;
						//	if (*pExtension == 0)
						//		LOG_ERROR_AND_THROW("Unable to recognize file format: file name \"", FilePath, "\" contain empty extension");

						//	String Extension = StrToLower(pExtension);
						//	if (Extension == "png")
						//		ImgFileFormat = IMAGE_FILE_FORMAT_PNG;
						//	else if (Extension == "jpeg" || Extension == "jpg")
						//		ImgFileFormat = IMAGE_FILE_FORMAT_JPEG;
						//	else if (Extension == "tiff" || Extension == "tif")
						//		ImgFileFormat = IMAGE_FILE_FORMAT_TIFF;
						//	else if (Extension == "dds")
						//		ImgFileFormat = IMAGE_FILE_FORMAT_DDS;
						//	else if (Extension == "ktx")
						//		ImgFileFormat = IMAGE_FILE_FORMAT_KTX;
						//	else
						//		LOG_ERROR_AND_THROW("Unsupported file format ", Extension);
						//}

						//if (ImgFileFormat == IMAGE_FILE_FORMAT_PNG ||
						//	ImgFileFormat == IMAGE_FILE_FORMAT_JPEG ||
						//	ImgFileFormat == IMAGE_FILE_FORMAT_TIFF)
						//{
						//	ImageLoadInfo ImgLoadInfo;
						//	ImgLoadInfo.Format = ImgFileFormat;
						//	Image::CreateFromDataBlob(pFileData, ImgLoadInfo, ppImage);
						//}
						//else if (ppRawData != nullptr)
						//{
						//	*ppRawData = pFileData.Detach();
						//}
						Diligent::TextureDesc TexDesc;
						TexDesc.Name = "png texture for ef renderer";
						TexDesc.Type = RESOURCE_DIM_TEX_2D;
						TexDesc.Usage = USAGE_STATIC;
						TexDesc.BindFlags = BIND_SHADER_RESOURCE;
						TexDesc.Width = pngTextureLoader_.GetWidth();
						TexDesc.Height = pngTextureLoader_.GetHeight();
						TexDesc.Format = TEX_FORMAT_RGBA8_UNORM;
						TexDesc.MipLevels = 1;
						TextureSubResData       Level0Data{
							pngTextureLoader_.GetData().data(),
							(Uint32)(pngTextureLoader_.GetWidth() * 4)
						};
						TextureData             InitData{ &Level0Data, 1 };
						auto* graphicsDevice = graphicsDevice_;
						auto texture = Tex::CreateTexture(gd, TexDesc, InitData);

						textureData = new Effekseer::TextureData();
						textureData->UserPtr = texture;
						textureData->UserID = 0;
						textureData->TextureFormat = Effekseer::TextureFormatType::ABGR8;
						textureData->Width = pngTextureLoader_.GetWidth();
						textureData->Height = pngTextureLoader_.GetHeight();
					}

					delete[] data_texture;
					return textureData;
				}
			}
			return nullptr;
		}

		void Unload(Effekseer::TextureData* data) {

			if (data != nullptr && data->UserPtr != nullptr)
			{
				auto texture = (Tex*)data->UserPtr;
				texture->Release();
			}

			if (data != nullptr)
			{
				delete data;
			}
		}
	};

	class VertexBuffer : public ReferenceObject, public EffekseerRenderer::VertexBufferBase
	{

	private:
		// TODO make ring buffer
		int32_t currentIndex = 0;
		//Diligent::IBuffer* vertexBuffer_ = nullptr;
		uint8_t* mapped_ = nullptr;
		int32_t size_ = 0;
		//IDeviceContext* pContext;
		void* lockedResource_;

		std::vector<Vbuf> vertexBuffers;
		uint32_t m_vertexRingOffset;
		bool m_ringBufferLock;
		GraphicsDE graphics_;
		int32_t m_ringLockedOffset;
		int32_t m_ringLockedSize;
	public:
		bool Initialize(GraphicsDE* graphics, int32_t size);
		VertexBuffer(GraphicsDE* graphicsDevice, Diligent::IBuffer* buffer, int size, bool isDynamic, bool hasRefCount);
		GraphicsDE& GetGraphicsDevice() {
			return graphics_;
		}
		VertexBuffer();
		~VertexBuffer();
		static VertexBuffer* Create(GraphicsDE* graphicsDevice, int size, bool isDynamic, bool hasRefCount);
		void Lock() override;
		Vbuf* GetVertexBuffer() { return &vertexBuffers[currentIndex]; }
		bool RingBufferLock(int32_t size, int32_t& offset, void*& data, int32_t alignment) override;
		bool TryRingBufferLock(int32_t size, int32_t& offset, void*& data, int32_t alignment) override;
		void Unlock() override;
		int32_t GetSize();
		//Diligent::IBuffer* Get() { return vertexBuffer_; }
	};

	class ConstantBuffer : public ReferenceObject
	{
	private:
		Diligent::IBuffer* constantBuffer_ = nullptr;
		int memSize_ = 0;
		Diligent::BufferViewDesc bvdesc;

		Uint8* mapped_ = nullptr;
	public:
		bool Initialize(Diligent::IRenderDevice* graphics, int32_t size);
		bool InitializeAsShortTime(SingleFrameMemoryPool* memoryPool, int32_t size);

		ConstantBuffer();
		~ConstantBuffer() {
			SafeRelease(constantBuffer_);
		}
		void WriteTo(IDeviceContext* pContext, const void* p, const size_t sz);
		void* Lock() {
			return nullptr;
		};
		RefCntAutoPtr<IBufferView> lbv;
		void* Lock(int32_t offset, int32_t size) {
			bvdesc.ByteOffset = offset;
			bvdesc.ByteWidth = size;
			//Diligent::IBufferView* lbv;
			constantBuffer_->CreateView(bvdesc, &lbv);
		};
		void Unlock() {};
		int32_t GetSize() const { return memSize_; };
		BufferViewDesc& GetVDS() { return bvdesc; }
		/**
			@brief	memory size must be multiple of 256 in DirectX12. So specified size and actual size are different.
		*/
		int32_t GetActualSize() const { return bvdesc.ByteWidth; };
		int32_t GetOffset() const { return bvdesc.ByteOffset; };

		Diligent::IBuffer* Get() { return constantBuffer_; }
	};
	//
	//	class GraphicsDE 
	//	{
	//		using CommandList = Diligent::ICommandList;
	//	private:
	//		int32_t swapBufferCount_ = 0;
	//		int32_t currentSwapBufferIndex = -1;
	//		
	//
	//		Diligent::RefCntAutoPtr<Diligent::IRenderDevice>  device_;
	//		std::function<std::tuple<D3D12_CPU_DESCRIPTOR_HANDLE, Texture*>()> getScreenFunc_;
	//		std::function<void()> waitFunc_;
	//
	//		const D3D12_COMMAND_LIST_TYPE commandListType_ = D3D12_COMMAND_LIST_TYPE_DIRECT;
	//		Diligent::IDeviceContext* commandQueue_ = nullptr;
	//		ID3D12CommandAllocator* commandAllocator_ = nullptr;
	//		ReferenceObject* owner_ = nullptr;
	//
	//		std::unordered_map<RenderPassPipelineStateKey, std::shared_ptr<RenderPassPipelineStateDX12>, RenderPassPipelineStateKey::Hash>
	//			renderPassPipelineStates_;
	//
	//	public:
	//		GraphicsDE(Diligent::IRenderDevice* device,
	//			std::function<std::tuple<D3D12_CPU_DESCRIPTOR_HANDLE, Texture*>()> getScreenFunc,
	//			std::function<void()> waitFunc,
	//			ID3D12CommandQueue* commandQueue,
	//			int32_t swapBufferCount,
	//			ReferenceObject* owner = nullptr);
	//		~GraphicsDE() override;
	//
	//		void Execute(CommandList* commandList) override;
	//		void WaitFinish() override;
	//
	//		VertexBuffer* CreateVertexBuffer(int32_t size) override;
	//		IndexBuffer* CreateIndexBuffer(int32_t stride, int32_t count) override;
	//		ConstantBuffer* CreateConstantBuffer(int32_t size) override;
	//		Shader* CreateShader(DataStructure* data, int32_t count) override;
	//		PipelineState* CreatePiplineState() override;
	//		SingleFrameMemoryPool* CreateSingleFrameMemoryPool(int32_t constantBufferPoolSize, int32_t drawingCount) override;
	//		CommandList* CreateCommandList(SingleFrameMemoryPool* memoryPool) override;
	//		RenderPass* CreateRenderPass(Texture** textures, int32_t textureCount, Texture* depthTexture) override;
	//		RenderPass* CreateRenderPass(Texture* texture, Texture* resolvedTexture, Texture* depthTexture, Texture* resolvedDepthTexture) override;
	//		Texture* CreateTexture(uint64_t id) override;
	//		Texture* CreateTexture(const TextureInitializationParameter& parameter) override;
	//		Texture* CreateRenderTexture(const RenderTextureInitializationParameter& parameter) override;
	//		Texture* CreateDepthTexture(const DepthTextureInitializationParameter& parameter) override;
	//
	//		RenderPassPipelineState* CreateRenderPassPipelineState(RenderPass* renderpass) override;
	//
	//		RenderPassPipelineState* CreateRenderPassPipelineState(const RenderPassPipelineStateKey& key) override;
	//
	//		Diligent::IRenderDevice* GetDevice();
	//
	//		// int32_t GetCurrentSwapBufferIndex() const;
	//		int32_t GetSwapBufferCount() const;
	//		ID3D12CommandQueue* GetCommandQueue() { return commandQueue_; }
	//
	//		ID3D12Resource* CreateResource(D3D12_HEAP_TYPE heapType,
	//			DXGI_FORMAT format,
	//			D3D12_RESOURCE_DIMENSION resourceDimention,
	//			D3D12_RESOURCE_STATES resourceState,
	//			Vec2I size)
	//		{
	//			return CreateResource(heapType, format, resourceDimention, resourceState, D3D12_RESOURCE_FLAG_NONE, size);
	//		}
	//
	//		ID3D12Resource* CreateResource(D3D12_HEAP_TYPE heapType,
	//			DXGI_FORMAT format,
	//			D3D12_RESOURCE_DIMENSION resourceDimention,
	//			D3D12_RESOURCE_STATES resourceState,
	//			D3D12_RESOURCE_FLAGS flags,
	//			Vec2I size);
	//
	//		std::vector<uint8_t> CaptureRenderTarget(Texture* renderTarget);
	//
	//		//! ResolvingDepth is only supported on the latestet Nvidia video card and driver
	//		bool IsResolvedDepthSupported() const override { return false; }
	//	};
	//
	//	class DeviceObject;
	//
	//	class GraphicsDevice : public ::EffekseerRenderer::GraphicsDevice, public ::Effekseer::ReferenceObject
	//	{
	//		friend class DeviceObject;
	//
	//	private:
	//		std::set<DeviceObject*> deviceObjects_;
	//
	//		LLGI::Graphics* graphics_ = nullptr;
	//
	//		/**
	//			@brief	register an object
	//		*/
	//		void Register(DeviceObject* device);
	//
	//		/**
	//			@brief	unregister an object
	//		*/
	//		void Unregister(DeviceObject* device);
	//
	//	public:
	//		GraphicsDevice(LLGI::Graphics* graphics)
	//			: graphics_(graphics)
	//		{
	//			ES_SAFE_ADDREF(graphics_);
	//		}
	//
	//		virtual ~GraphicsDevice()
	//		{
	//			ES_SAFE_RELEASE(graphics_);
	//		}
	//
	//		/**
	//			@brief
	//			\~english Call when device lost causes
	//			\~japanese デバイスロストが発生した時に実行する。
	//		*/
	//		void OnLostDevice();
	//
	//		/**
	//			@brief
	//			\~english Call when device reset causes
	//			\~japanese デバイスがリセットされた時に実行する。
	//		*/
	//		void OnResetDevice();
	//
	//		LLGI::Graphics* GetGraphics() const { return graphics_; }
	//
	//		virtual int GetRef() override { return ::Effekseer::ReferenceObject::GetRef(); }
	//		virtual int AddRef() override { return ::Effekseer::ReferenceObject::AddRef(); }
	//		virtual int Release() override { return ::Effekseer::ReferenceObject::Release(); }
	//	};
	//	class DeviceObject
	//	{
	//	private:
	//		GraphicsDevice* graphicsDevice_ = nullptr;
	//
	//		//! whether does this instance inc and dec the reference count of renderer
	//		bool hasRefCount_ = false;
	//
	//	public:
	//		DeviceObject(GraphicsDevice* graphicsDevice, bool hasRefCount);
	//		virtual ~DeviceObject();
	//
	//	public:
	//		GraphicsDevice* GetGraphicsDevice() const;
	//
	//		virtual void OnLostDevice() {}
	//		virtual void OnResetDevice() {}
	//	};
	//
	//}
	//	/*class VertexLayout
	//	{
	//	public:
	//		LLGI::VertexLayoutFormat Format;
	//		std::string Name;
	//		int32_t Semantic;
	//	};*/
	//
	class PiplineStateKey
	{
	public:
		Shader* shader = nullptr;
		EffekseerRenderer::RenderStateBase::State state;
		/*LLGI::TopologyType topologyType;
		Diligent::IPipelineState* renderPassPipelineState = nullptr;*/
		Diligent::PRIMITIVE_TOPOLOGY topologyType;
		Diligent::IPipelineState* renderPassPipelineState = nullptr;
		bool operator<(const PiplineStateKey& v) const;
	};

	class RenderState : public ::EffekseerRenderer::RenderStateBase
	{
	private:
		static const int32_t DepthTestCount = 2;
		static const int32_t DepthWriteCount = 2;
		static const int32_t CulTypeCount = 3;
		static const int32_t AlphaTypeCount = 5;
		static const int32_t TextureFilterCount = 2;
		static const int32_t TextureWrapCount = 2;

		RendererImplemented* m_renderer;

	public:
		RenderState(RendererImplemented* renderer) : m_renderer(renderer) {}
		virtual ~RenderState();

		void Update(bool forced);
	};
	using Texture = Diligent::ITexture;

	/**
		@brief	描画クラス
		@note
		ツール向けの描画機能。
	*/
	class RendererImplemented : public ::EffekseerRenderer::Renderer, public ::Effekseer::ReferenceObject
	{
		friend class DeviceObject;

	protected:
		std::vector<Diligent::IPipelineState*> piplineStates_;
		std::vector<PiplineStateKey>pipKeys_;
		IBuffer* currentVertexBuffer_ = nullptr;
		IBuffer* currentIndexBuffer_ = nullptr;
		int32_t currentVertexBufferStride_ = 0;
		Diligent::PRIMITIVE_TOPOLOGY currentTopologyType_ = Diligent::PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		// TODO
		/**
			Create constants and copy
			Shader
		*/
		GraphicsDE GDlocal;
		GraphicsDE* graphicsDevice_ = nullptr;
		Diligent::IPipelineState* renderPassPipelineState_ = nullptr;

		std::vector<StateTransitionDesc> Barriers;
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		IndexBuffer* m_indexBufferForWireframe = nullptr;
		int32_t m_squareMaxCount;

		Shader* m_shader = nullptr;
		Shader* m_shader_lighting = nullptr;
		Shader* m_shader_distortion = nullptr;
		Shader* currentShader = nullptr;

		std::function<void()> waitFunc_;
		bool isReversedDepth_ = false;

		EffekseerRenderer::StandardRenderer<RendererImplemented, Shader, Vertex, VertexDistortion>* m_standardRenderer;

		::Effekseer::CoordinateSystem m_coordinateSystem;

		::EffekseerRenderer::RenderStateBase* m_renderState;

		Effekseer::TextureData m_background;

		//std::set<DeviceObject*> m_deviceObjects;

		EffekseerRenderer::DistortingCallback* m_distortingCallback;

		Effekseer::RenderMode m_renderMode = Effekseer::RenderMode::Normal;

		CommandList* commandList_ = nullptr;

		CommandList* GetCurrentCommandList() { return commandList_; }

		Diligent::IPipelineState* GetOrCreatePiplineState();

		void GenerateVertexBuffer();

		void GenerateIndexBuffer();
		/*void CreateConsBuf(Diligent::IBuffer*& data, const size_t size) {

			Diligent::BufferDesc VertBuffDesc;
			VertBuffDesc.Name = "Effekseer vertex buffer";
			VertBuffDesc.Usage = USAGE_DYNAMIC;
			VertBuffDesc.BindFlags = BIND_C;
			VertBuffDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
			VertBuffDesc.uiSizeInBytes = size;

			graphics->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &vertexBuffer_);
		}*/
	public:
		//! shaders (todo implemented)
		FixedShader fixedShader_;

		::Effekseer::CompiledMaterialPlatformType platformType_;

		::Effekseer::MaterialCompiler* materialCompiler_ = nullptr;

		RendererImplemented(int32_t squareMaxCount);

		~RendererImplemented();

		void OnLostDevice()override {}
		void OnResetDevice() override {}

		bool Initialize(GraphicsDE* graphicsDevice, Diligent::IPipelineState* renderPassPipelineState, bool isReversedDepth);

		//bool Initialize(LLGI::Graphics* graphics, Diligent::IPipelineState* renderPassPipelineState, bool isReversedDepth);

		void Destroy() override;

		void SetRestorationOfStatesFlag(bool flag) override;

		void SetRenderPassPipelineState(Diligent::IPipelineState* renderPassPipelineState);

		bool BeginRendering() override;

		bool EndRendering() override;

		void SetCommandList(CommandList* commandList);

		auto* GetGraphicsDevice() const { return graphicsDevice_; }

		auto GetGraphics() const { return graphicsDevice_->graphicsDevice; }

		/**
			@brief	頂点バッファ取得
		*/
		VertexBuffer* GetVertexBuffer() { return m_vertexBuffer; }

		///**
		//	@brief	インデックスバッファ取得
		//*/
		IndexBuffer* GetIndexBuffer() {
			if (m_renderMode == ::Effekseer::RenderMode::Wireframe)
			{
				return m_indexBufferForWireframe;
			}
			else
			{
				return m_indexBuffer;
			}
		}


		/**
			@brief	最大描画スプライト数
		*/
		int32_t GetSquareMaxCount() const override;

		::EffekseerRenderer::RenderStateBase* GetRenderState();

		/**
			@brief	スプライトレンダラーを生成する。
		*/
		::Effekseer::SpriteRenderer* CreateSpriteRenderer() override;

		/**
			@brief	リボンレンダラーを生成する。
		*/
		::Effekseer::RibbonRenderer* CreateRibbonRenderer() override;

		/**
			@brief	リングレンダラーを生成する。
		*/
		::Effekseer::RingRenderer* CreateRingRenderer() override;

		/**
			@brief	モデルレンダラーを生成する。
		*/
		::Effekseer::ModelRenderer* CreateModelRenderer() override;

		/**
			@brief	軌跡レンダラーを生成する。
		*/
		::Effekseer::TrackRenderer* CreateTrackRenderer() override;

		/**
			@brief	テクスチャ読込クラスを生成する。
		*/
		::Effekseer::TextureLoader* CreateTextureLoader(::Effekseer::FileInterface* fileInterface = NULL) override;

		/**
			@brief	モデル読込クラスを生成する。
		*/
		::Effekseer::ModelLoader* CreateModelLoader(::Effekseer::FileInterface* fileInterface = NULL) override;

		::Effekseer::MaterialLoader* CreateMaterialLoader(::Effekseer::FileInterface* fileInterface = nullptr) override;

		/**
		@brief	背景を取得する。
		*/
		Effekseer::TextureData* GetBackground();

		void SetBackground(Tex* background);

		void SetBackgroundTexture(Effekseer::TextureData* textuerData) override;
		EffekseerRenderer::DistortingCallback* GetDistortingCallback() override { return m_distortingCallback; }

		void SetDistortingCallback(EffekseerRenderer::DistortingCallback* callback) override;

		EffekseerRenderer::StandardRenderer<RendererImplemented, Shader, Vertex, VertexDistortion>* GetStandardRenderer()
		{
			return m_standardRenderer;
		}

		void SetVertexBuffer(VertexBuffer* vertexBuffer, int32_t stride);
		void SetVertexBuffer(IBuffer* vertexBuffer, int32_t stride);
		void SetIndexBuffer(IndexBuffer* indexBuffer);
		void SetIndexBuffer(IBuffer* indexBuffer);

		void SetLayout(Shader* shader);
		void DrawSprites(int32_t spriteCount, int32_t vertexOffset);
		void DrawPolygon(int32_t vertexCount, int32_t indexCount);

		Shader* GetShader(bool useTexture, ::Effekseer::RendererMaterialType materialType) const;
		void BeginShader(Shader* shader);
		void EndShader(Shader* shader);

		void SetVertexBufferToShader(const void* data, int32_t size, int32_t dstOffset);

		void SetPixelBufferToShader(const void* data, int32_t size, int32_t dstOffset);

		void SetTextures(Shader* shader, Effekseer::TextureData** textures, int32_t count);

		void ResetRenderState() override;

		Effekseer::TextureData* CreateProxyTexture(EffekseerRenderer::ProxyTextureType type) override;

		void DeleteProxyTexture(Effekseer::TextureData* data) override {
			if (data != nullptr && data->UserPtr != nullptr)
			{
				auto texture = (Tex*)data->UserPtr;
				texture->Release();
			}

			if (data != nullptr)
			{
				delete data;
			}
		}
		GraphicsDE& GetgraphicsDevice() { return GDlocal; }
		virtual int GetRef() override { return ::Effekseer::ReferenceObject::GetRef(); }
		virtual int AddRef() override { return ::Effekseer::ReferenceObject::AddRef(); }
		virtual int Release() override { return ::Effekseer::ReferenceObject::Release(); }
	};
	EffekseerRenderer::Renderer* Create(GraphicsDE* graphicsDevice,
		const TEXTURE_FORMAT* renderTargetFormats,
		int32_t renderTargetCount,
		const TEXTURE_FORMAT depthFormat,
		bool isReversedDepth,
		int32_t squareMaxCount, std::filesystem::path ShaderPath);
}