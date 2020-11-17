#pragma once

#include <random>
#include"EffekseerRendererDE.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.RibbonRendererBase.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.RingRendererBase.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.SpriteRendererBase.h"
#include "../EffekseerRendererCommon/EffekseerRenderer.TrackRendererBase.h"
#include"EFRenders.h"
using BYTE = unsigned char;
namespace Standard_VS
{

#include "Shader/EffekseerRenderer.Standard_VS.h"
} // namespace Standard_VS

namespace Standard_PS
{

#include "Shader/EffekseerRenderer.Standard_PS.h"
} // namespace Standard_PS

namespace Standard_Distortion_VS
{

#include "Shader/EffekseerRenderer.Standard_Distortion_VS.h"
} // namespace Standard_Distortion_VS

namespace Standard_Distortion_PS
{

#include "Shader/EffekseerRenderer.Standard_Distortion_PS.h"
} // namespace Standard_Distortion_PS

namespace ShaderLightingTextureNormal_
{

#include "Shader/EffekseerRenderer.ModelRenderer.ShaderLightingTextureNormal_VS.h"


#include "Shader/EffekseerRenderer.ModelRenderer.ShaderLightingTextureNormal_PS.h"

} // namespace ShaderLightingTextureNormal_

namespace ShaderTexture_
{

#include "Shader/EffekseerRenderer.ModelRenderer.ShaderTexture_VS.h"


#include "Shader/EffekseerRenderer.ModelRenderer.ShaderTexture_PS.h"
} // namespace ShaderTexture_

namespace ShaderDistortionTexture_
{

#include "Shader/EffekseerRenderer.ModelRenderer.ShaderDistortion_VS.h"


#include "Shader/EffekseerRenderer.ModelRenderer.ShaderDistortion_PS.h"
} // namespace ShaderDistortionTexture_

namespace ShaderStandardLighting_
{

#include "Shader/EffekseerRenderer.Standard_Lighting_VS.h"


#include "Shader/EffekseerRenderer.Standard_Lighting_PS.h"
} // namespace ShaderStandardLighting_

namespace EffekseerRendererDE
{


	//MaterialLoader:: MaterialLoader(GraphicsDE* GraphicsDE,
	//	::Effekseer::FileInterface* fileInterface,
	//	::Effekseer::CompiledMaterialPlatformType platformType,
	//	::Effekseer::MaterialCompiler* materialCompiler) : fileInterface_(fileInterface), platformType_(platformType), materialCompiler_(materialCompiler),
	//	GraphicsDE_(GraphicsDE)
	//{
	//	if (fileInterface == nullptr)
	//	{
	//		fileInterface_ = &defaultFileInterface_;
	//	}

	//	/*ES_SAFE_ADDREF(GraphicsDE_);
	//	ES_SAFE_ADDREF(materialCompiler_);*/
	//}
	//void MaterialLoader::Deserialize(uint8_t* data, uint32_t datasize, LLGI::CompilerResult& result)
	//{
	//	if (datasize < 4)
	//		return;

	//	uint32_t count = 0;
	//	uint32_t offset = 0;

	//	memcpy(&count, data + offset, sizeof(int32_t));
	//	offset += sizeof(uint32_t);

	//	result.Binary.resize(count);

	//	for (uint32_t i = 0; i < count; i++)
	//	{
	//		uint32_t size = 0;
	//		memcpy(&size, data + offset, sizeof(int32_t));
	//		offset += sizeof(uint32_t);

	//		result.Binary[i].resize(size);

	//		memcpy(result.Binary[i].data(), data + offset, size);
	//		offset += size;
	//	}
	//}

	//MaterialLoader ::~MaterialLoader() {
	//	/*ES_SAFE_RELEASE(materialCompiler_);
	//	ES_SAFE_RELEASE(GraphicsDE_);*/
	//}

	//::Effekseer::MaterialData* MaterialLoader::Load(const EFK_CHAR* path)
	//{
	//	// code file
	//	{
	//		auto binaryPath = std::u16string(path) + u"d";
	//		std::unique_ptr<Effekseer::FileReader> reader(fileInterface_->OpenRead(binaryPath.c_str()));

	//		if (reader.get() != nullptr)
	//		{
	//			size_t size = reader->GetLength();
	//			std::vector<char> data;
	//			data.resize(size);
	//			reader->Read(data.data(), size);

	//			auto material = Load(data.data(), (int32_t)size, ::Effekseer::MaterialFileType::Compiled);

	//			if (material != nullptr)
	//			{
	//				return material;
	//			}
	//		}
	//	}

	//	// code file
	//	if (materialCompiler_ != nullptr)
	//	{
	//		std::unique_ptr<Effekseer::FileReader> reader(fileInterface_->OpenRead(path));

	//		if (reader.get() != nullptr)
	//		{
	//			size_t size = reader->GetLength();
	//			std::vector<char> data;
	//			data.resize(size);
	//			reader->Read(data.data(), size);

	//			auto material = Load(data.data(), (int32_t)size, ::Effekseer::MaterialFileType::Code);

	//			return material;
	//		}
	//	}

	//	return nullptr;
	//}

	//::Effekseer::MaterialData* MaterialLoader::LoadAcutually(::Effekseer::Material& material, ::Effekseer::CompiledMaterialBinary* binary)
	//{
	//	auto materialData = new ::Effekseer::MaterialData();
	//	materialData->IsSimpleVertex = material.GetIsSimpleVertex();
	//	materialData->IsRefractionRequired = material.GetHasRefraction();

	//	std::array<Effekseer::MaterialShaderType, 2> shaderTypes;
	//	std::array<Effekseer::MaterialShaderType, 2> shaderTypesModel;

	//	shaderTypes[0] = Effekseer::MaterialShaderType::Standard;
	//	shaderTypes[1] = Effekseer::MaterialShaderType::Refraction;
	//	shaderTypesModel[0] = Effekseer::MaterialShaderType::Model;
	//	shaderTypesModel[1] = Effekseer::MaterialShaderType::RefractionModel;
	//	int32_t shaderTypeCount = 1;

	//	if (material.GetHasRefraction())
	//	{
	//		shaderTypeCount = 2;
	//	}

	//	for (int32_t st = 0; st < shaderTypeCount; st++)
	//	{
	//		Shader* shader = nullptr;
	//		auto parameterGenerator = EffekseerRenderer::MaterialShaderParameterGenerator(material, false, st, 1);

	//		if (materialData->IsSimpleVertex)
	//		{
	//			LLGI::CompilerResult resultVS;
	//			LLGI::CompilerResult resultPS;

	//			Deserialize((uint8_t*)binary->GetVertexShaderData(shaderTypes[st]), binary->GetVertexShaderSize(shaderTypes[st]), resultVS);
	//			Deserialize((uint8_t*)binary->GetPixelShaderData(shaderTypes[st]), binary->GetPixelShaderSize(shaderTypes[st]), resultPS);

	//			std::array<DataStructure, 4> dataVS;
	//			std::array<DataStructure, 4> dataPS;

	//			for (size_t i = 0; i < resultVS.Binary.size(); i++)
	//			{
	//				dataVS[i].Data = resultVS.Binary[i].data();
	//				dataVS[i].Size = resultVS.Binary[i].size();
	//			}

	//			for (size_t i = 0; i < resultPS.Binary.size(); i++)
	//			{
	//				dataPS[i].Data = resultPS.Binary[i].data();
	//				dataPS[i].Size = resultPS.Binary[i].size();
	//			}

	//			// Pos(3) Color(1) UV(2)
	//			std::vector<LayoutElement> layouts;
	//			layouts =
	//			{
	//			 {0, 0, 3, VT_FLOAT32},
	//			 {1, 0, 4,  VT_UINT8},
	//			 {2, 0, 2, VT_FLOAT32}
	//			};
	//			//binary shader not support
	//			std::abort();
	//			/*shader = Shader::Create(GraphicsDE_->graphicsDevice,
	//				(uint8_t*)binary->GetVertexShaderData(shaderTypes[st]),
	//				binary->GetVertexShaderSize(shaderTypes[st]),
	//				(uint8_t*)binary->GetPixelShaderData(shaderTypes[st]),
	//				binary->GetPixelShaderSize(shaderTypes[st]),
	//				"MaterialStandardRenderer",
	//				layouts,
	//				true);*/
	//		}
	//		else
	//		{
	//			LLGI::CompilerResult resultVS;
	//			LLGI::CompilerResult resultPS;

	//			Deserialize((uint8_t*)binary->GetVertexShaderData(shaderTypes[st]), binary->GetVertexShaderSize(shaderTypes[st]), resultVS);
	//			Deserialize((uint8_t*)binary->GetPixelShaderData(shaderTypes[st]), binary->GetPixelShaderSize(shaderTypes[st]), resultPS);

	//			std::array<DataStructure, 4> dataVS;
	//			std::array<DataStructure, 4> dataPS;

	//			for (size_t i = 0; i < resultVS.Binary.size(); i++)
	//			{
	//				dataVS[i].Data = resultVS.Binary[i].data();
	//				dataVS[i].Size = resultVS.Binary[i].size();
	//			}

	//			for (size_t i = 0; i < resultPS.Binary.size(); i++)
	//			{
	//				dataPS[i].Data = resultPS.Binary[i].data();
	//				dataPS[i].Size = resultPS.Binary[i].size();
	//			}

	//			// Pos(3) Color(1) Normal(1) Tangent(1) UV(2) UV(2)
	//			std::vector<VertexLayout> layouts =
	//			{
	//			 {0, 0, 3, VT_FLOAT32},
	//			 {1, 0, 4,  VT_UINT8},
	//			 {2, 0, 4,  VT_UINT8},
	//			 {3, 0, 4,  VT_UINT8},
	//			 {4, 0, 2, VT_FLOAT32},
	//			 {5, 0, 2, VT_FLOAT32},
	//			};;
	//			/*layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "POSITION", 0 });
	//			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 0 });
	//			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 1 });
	//			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 2 });
	//			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 0 });
	//			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 1 });*/

	//			int32_t offset = 40;
	//			int count = 6;
	//			int index = 2;

	//			auto getFormat = [](int32_t i,const size_t s) -> VertexLayout {
	//				Uint32 sec = (Uint32)s;
	//				if (i == 1)
	//					assert(false);
	//				if (i == 2)
	//					return VertexLayout{ sec, 0, 2, VT_FLOAT32 };
	//				if (i == 3)
	//					return VertexLayout{ sec, 0, 3, VT_FLOAT32 };
	//				if (i == 4)
	//					return  VertexLayout{ sec, 0,4, VT_FLOAT32 };
	//			};
	//			if (material.GetCustomData1Count() > 0)
	//			{
	//				layouts.push_back(getFormat(material.GetCustomData1Count(), layouts.size()));

	//				index++;
	//				count++;
	//				offset += sizeof(float) * material.GetCustomData1Count();
	//			}

	//			if (material.GetCustomData2Count() > 0)
	//			{
	//				layouts.push_back(getFormat(material.GetCustomData2Count(), layouts.size()));

	//				index++;
	//				count++;

	//				offset += sizeof(float) * material.GetCustomData2Count();
	//			}

	//			shader = Shader::Create(GraphicsDE_->graphicsDevice,
	//				dataVS.data(),
	//				resultVS.Binary.size(),
	//				dataPS.data(),
	//				resultPS.Binary.size(),
	//				"MaterialStandardRenderer",
	//				layouts,
	//				true);
	//		}

	//		if (shader == nullptr)
	//			return nullptr;

	//		auto vertexUniformSize = parameterGenerator.VertexShaderUniformBufferSize;
	//		auto pixelUniformSize = parameterGenerator.PixelShaderUniformBufferSize;

	//		shader->SetVertexConstantBufferSize(vertexUniformSize);
	//		shader->SetVertexRegisterCount(vertexUniformSize / (sizeof(float) * 4));

	//		shader->SetPixelConstantBufferSize(pixelUniformSize);
	//		shader->SetPixelRegisterCount(pixelUniformSize / (sizeof(float) * 4));

	//		materialData->TextureCount = material.GetTextureCount();
	//		materialData->UniformCount = material.GetUniformCount();

	//		if (st == 0)
	//		{
	//			materialData->UserPtr = shader;
	//		}
	//		else
	//		{
	//			materialData->RefractionUserPtr = shader;
	//		}
	//	}

	//	for (int32_t st = 0; st < shaderTypeCount; st++)
	//	{
	//		LLGI::CompilerResult resultVS;
	//		LLGI::CompilerResult resultPS;

	//		Deserialize(
	//			(uint8_t*)binary->GetVertexShaderData(shaderTypesModel[st]), binary->GetVertexShaderSize(shaderTypesModel[st]), resultVS);
	//		Deserialize((uint8_t*)binary->GetPixelShaderData(shaderTypesModel[st]), binary->GetPixelShaderSize(shaderTypesModel[st]), resultPS);

	//		std::array<DataStructure, 4> dataVS;
	//		std::array<DataStructure, 4> dataPS;

	//		for (size_t i = 0; i < resultVS.Binary.size(); i++)
	//		{
	//			dataVS[i].Data = resultVS.Binary[i].data();
	//			dataVS[i].Size = resultVS.Binary[i].size();
	//		}

	//		for (size_t i = 0; i < resultPS.Binary.size(); i++)
	//		{
	//			dataPS[i].Data = resultPS.Binary[i].data();
	//			dataPS[i].Size = resultPS.Binary[i].size();
	//		}

	//		auto parameterGenerator = EffekseerRenderer::MaterialShaderParameterGenerator(material, true, st, 1);

	//		std::vector<VertexLayout> layouts =
	//		{
	//		 {0, 0, 3, VT_FLOAT32},
	//		 {1, 0, 3,  VT_FLOAT32},
	//		 {2, 0, 3,  VT_FLOAT32},
	//		 {3, 0, 3,  VT_FLOAT32},
	//		 {4, 0, 2, VT_FLOAT32},
	//		 {5, 0, 2, VT_FLOAT32},
	//		 {6, 0, 4,  VT_UINT8},
	//		 {7, 0, 4,  VT_UINT8},
	//		};
	//		/*layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "POSITION", 0 });
	//		layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 0 });
	//		layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 1 });
	//		layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 2 });
	//		layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 0 });
	//		layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 3 });
	//		layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UINT, "BLENDINDICES", 0 });*/

	//		// compile
	//		std::string log;

	//		auto shader = Shader::Create(GraphicsDE_->graphicsDevice,
	//			dataVS.data(),
	//			resultVS.Binary.size(),
	//			dataPS.data(),
	//			resultPS.Binary.size(),
	//			"MaterialStandardModelRenderer",
	//			layouts,
	//			true);
	//		if (shader == nullptr)
	//			return nullptr;

	//		auto vertexUniformSize = parameterGenerator.VertexShaderUniformBufferSize;
	//		auto pixelUniformSize = parameterGenerator.PixelShaderUniformBufferSize;

	//		shader->SetVertexConstantBufferSize(vertexUniformSize);
	//		shader->SetVertexRegisterCount(vertexUniformSize / (sizeof(float) * 4));

	//		shader->SetPixelConstantBufferSize(pixelUniformSize);
	//		shader->SetPixelRegisterCount(pixelUniformSize / (sizeof(float) * 4));

	//		if (st == 0)
	//		{
	//			materialData->ModelUserPtr = shader;
	//		}
	//		else
	//		{
	//			materialData->RefractionModelUserPtr = shader;
	//		}
	//	}

	//	materialData->CustomData1 = material.GetCustomData1Count();
	//	materialData->CustomData2 = material.GetCustomData2Count();
	//	materialData->TextureCount = std::min(material.GetTextureCount(), Effekseer::UserTextureSlotMax);
	//	materialData->UniformCount = material.GetUniformCount();
	//	materialData->ShadingModel = material.GetShadingModel();

	//	for (int32_t i = 0; i < materialData->TextureCount; i++)
	//	{
	//		materialData->TextureWrapTypes.at(i) = material.GetTextureWrap(i);
	//	}

	//	return materialData;
	//}

	//::Effekseer::MaterialData* MaterialLoader::Load(const void* data, int32_t size, Effekseer::MaterialFileType fileType)
	//{
	//	if (fileType == Effekseer::MaterialFileType::Compiled)
	//	{
	//		auto compiled = Effekseer::CompiledMaterial();
	//		if (!compiled.Load(static_cast<const uint8_t*>(data), size))
	//		{
	//			return nullptr;
	//		}

	//		if (!compiled.GetHasValue(platformType_))
	//		{
	//			return nullptr;
	//		}

	//		// compiled
	//		Effekseer::Material material;
	//		material.Load((const uint8_t*)compiled.GetOriginalData().data(), static_cast<int32_t>(compiled.GetOriginalData().size()));
	//		auto binary = compiled.GetBinary(platformType_);

	//		return LoadAcutually(material, binary);
	//	}
	//	else
	//	{
	//		if (materialCompiler_ == nullptr)
	//		{
	//			return nullptr;
	//		}

	//		Effekseer::Material material;
	//		material.Load((const uint8_t*)data, size);
	//		auto binary = ::Effekseer::CreateUniqueReference(materialCompiler_->Compile(&material));

	//		return LoadAcutually(material, binary.get());
	//	}
	//}

	//void MaterialLoader::Unload(::Effekseer::MaterialData* data)
	//{
	//	if (data == nullptr)
	//		return;
	//	auto shader = reinterpret_cast<Shader*>(data->UserPtr);
	//	auto modelShader = reinterpret_cast<Shader*>(data->ModelUserPtr);
	//	auto refractionShader = reinterpret_cast<Shader*>(data->RefractionUserPtr);
	//	auto refractionModelShader = reinterpret_cast<Shader*>(data->RefractionModelUserPtr);

	//	ES_SAFE_DELETE(shader);
	//	ES_SAFE_DELETE(modelShader);
	//	ES_SAFE_DELETE(refractionShader);
	//	ES_SAFE_DELETE(refractionModelShader);
	//	ES_SAFE_DELETE(data);
	//}
	bool PiplineStateKey::operator<(const PiplineStateKey& v) const
	{
		if (shader != v.shader)
			return shader < v.shader;
		if (state.AlphaBlend != v.state.AlphaBlend)
			return state.AlphaBlend < v.state.AlphaBlend;
		if (state.CullingType != v.state.CullingType)
			return state.CullingType < v.state.CullingType;
		if (state.DepthTest != v.state.DepthTest)
			return v.state.DepthTest;
		if (state.DepthWrite != v.state.DepthWrite)
			return v.state.DepthWrite;

		for (int i = 0; i < 4; i++)
		{
			if (state.TextureFilterTypes[i] != v.state.TextureFilterTypes[i])
				return state.TextureFilterTypes[i] < v.state.TextureFilterTypes[i];
			if (state.TextureWrapTypes[i] != v.state.TextureWrapTypes[i])
				return state.TextureWrapTypes[i] < v.state.TextureWrapTypes[i];
		}

		if (topologyType != v.topologyType)
			return topologyType < v.topologyType;

		if (renderPassPipelineState != v.renderPassPipelineState)
			return renderPassPipelineState < v.renderPassPipelineState;

		return false;
	}

	bool ConstantBuffer::Initialize(Diligent::IRenderDevice* graphics, int32_t size)
	{
		memSize_ = size;
		bvdesc.ByteWidth = (size + 255) & ~255; // buffer size should be multiple of 256
		Diligent::BufferDesc VertBuffDesc;
		VertBuffDesc.Name = "Effekseer ConstantBuffer buffer";
		VertBuffDesc.Usage = USAGE_DYNAMIC;
		VertBuffDesc.BindFlags = BIND_SHADER_RESOURCE;
		VertBuffDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
		VertBuffDesc.uiSizeInBytes = size;

		graphics->CreateBuffer(VertBuffDesc, nullptr, &constantBuffer_);
		return (constantBuffer_ != nullptr);
	}
	bool ConstantBuffer::InitializeAsShortTime(SingleFrameMemoryPool* memoryPool, int32_t size)
	{
		auto old = constantBuffer_;

		auto size_ = (size + 255) & ~255; // buffer size should be multiple of 256
		if (memoryPool->GetConstantBuffer(size_, constantBuffer_, bvdesc.ByteOffset))
		{
			SafeAddRef(constantBuffer_);
			SafeRelease(old);
			memSize_ = size;
			bvdesc.ByteWidth = size_;
			return true;
		}
		else
		{
			return false;
		}
	}

	ConstantBuffer::ConstantBuffer()
	{
		bvdesc.ViewType= BUFFER_VIEW_SHADER_RESOURCE;
	}

	void ConstantBuffer::WriteTo(IDeviceContext* pContext, const void* p, const size_t sz) {
		/*const auto state = constantBuffer_->GetState();
		constantBuffer_->SetState(Diligent::RESOURCE_STATE::RESOURCE_STATE_CONSTANT_BUFFER);
		if(state!= RESOURCE_STATE::RESOURCE_STATE_CONSTANT_BUFFER)*/
		/*pContext->MapBuffer
		(constantBuffer_, MAP_WRITE, MAP_FLAG_DISCARD, (PVoid&)mapped_);
		std::memcpy(mapped_ + bvdesc.ByteOffset, p, sz);
		pContext->UnmapBuffer(constantBuffer_, MAP_WRITE);*/
		pContext->UpdateBuffer(constantBuffer_, bvdesc.ByteOffset, sz, p, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}

	InternalSingleFrameMemoryPool::InternalSingleFrameMemoryPool(GraphicsDE* graphics,
		int32_t constantBufferPoolSize,
		int32_t drawingCount)
	{
		//constexpr auto p255 = constantBufferPoolSize + 255;
		constantBufferSize_ = (constantBufferPoolSize + 255) & (~255); // buffer size should be multiple of 256
		Diligent::BufferDesc VertBuffDesc;
		VertBuffDesc.Name = "Effekseer InternalSingleFrameMemoryPool buffer";
		VertBuffDesc.Usage = USAGE_DEFAULT;
		VertBuffDesc.BindFlags = BIND_UNIFORM_BUFFER;
		//VertBuffDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
		VertBuffDesc.uiSizeInBytes = constantBufferSize_;
		VertBuffDesc.Mode = BUFFER_MODE_STRUCTURED;
		VertBuffDesc.ElementByteStride = 256;
		graphics->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &constantBuffer_);
	}

	InternalSingleFrameMemoryPool ::~InternalSingleFrameMemoryPool() { SafeRelease(constantBuffer_); }

	bool InternalSingleFrameMemoryPool::GetConstantBuffer(int32_t size, IBuffer*& resource, Uint32& offset)
	{
		if (constantBufferOffset_ + size > constantBufferSize_)
			return false;

		resource = constantBuffer_;
		offset = constantBufferOffset_;
		constantBufferOffset_ += size;
		return true;
	}
	void InternalSingleFrameMemoryPool::Reset() { constantBufferOffset_ = 0; }

	SingleFrameMemoryPool::SingleFrameMemoryPool(
		GraphicsDE* graphics, bool isStrongRef, int32_t swapBufferCount, int32_t constantBufferPoolSize, int32_t drawingCount)
		: swapBufferCount_(swapBufferCount), graphics_(graphics), isStrongRef_(isStrongRef), drawingCount_(drawingCount)
	{

		/*for (int i = 0; i < swapBufferCount_; i++)
		{
			offsets_.push_back(0);
			constantBuffers_.push_back(std::vector<ConstantBuffer*>());
		}
		if (isStrongRef)
		{
			SafeAddRef(graphics_);
		}*/

		for (int32_t i = 0; i < swapBufferCount; i++)
		{
			offsets_.push_back(0);
			constantBuffers_.push_back(std::vector<ConstantBuffer*>());
			auto memoryPool = std::make_shared<InternalSingleFrameMemoryPool>(graphics, constantBufferPoolSize, drawingCount);
			memoryPools.push_back(memoryPool);
		}

		currentSwap_ = -1;
	}
	SingleFrameMemoryPool* SingleFrameMemoryPool::CreateSingleFrameMemoryPool
	(GraphicsDE* gd, size_t sz, int32_t swapBufferCount ) {
		return new SingleFrameMemoryPool(gd, true, swapBufferCount, sz, 128);
	}
	SingleFrameMemoryPool* SingleFrameMemoryPool::CreateSingleFrameMemoryPool(::EffekseerRenderer::Renderer* renderer)
	{
		EffekseerRendererDE::RendererImplemented* rimp = static_cast<EffekseerRendererDE::RendererImplemented*>(renderer);
		return nullptr;
	}
	SingleFrameMemoryPool::~SingleFrameMemoryPool()
	{
		memoryPools.clear();

		if (isStrongRef_)
		{
			SafeRelease(graphics_);
		}
	}

	ConstantBuffer* SingleFrameMemoryPool::CreateConstantBufferInternal(int32_t size)
	{
		auto obj = new ConstantBuffer();
		if (!obj->InitializeAsShortTime(this, size))
		{
			SafeRelease(obj);
			return nullptr;
		}

		return obj;
	}

	ConstantBuffer* SingleFrameMemoryPool::ReinitializeConstantBuffer(ConstantBuffer* cb, int32_t size)
	{
		auto obj = static_cast<ConstantBuffer*>(cb);
		if (!obj->InitializeAsShortTime(this, size))
		{
			return nullptr;
		}

		return obj;
	}

	bool SingleFrameMemoryPool::GetConstantBuffer(int32_t size, IBuffer*& resource, Uint32& offset)
	{
		assert(currentSwap_ >= 0);
		return memoryPools[currentSwap_]->GetConstantBuffer(size, resource, offset);
	}

	InternalSingleFrameMemoryPool* SingleFrameMemoryPool::GetInternal() { return memoryPools[currentSwap_].get(); }

	int32_t SingleFrameMemoryPool::GetDrawingCount() const { return drawingCount_; }

	void SingleFrameMemoryPool::NewFrame()
	{
		currentSwap_++;
		currentSwap_ %= memoryPools.size();
		memoryPools[currentSwap_]->Reset();
		currentSwapBuffer_++;
		currentSwapBuffer_ %= swapBufferCount_;
		offsets_[currentSwapBuffer_] = 0;

		assert(currentSwap_ == currentSwapBuffer_);
	}
	ConstantBuffer* SingleFrameMemoryPool::CreateConstantBuffer(int32_t size)
	{
		assert(currentSwapBuffer_ >= 0);

		if (static_cast<int32_t>(constantBuffers_[currentSwapBuffer_].size()) <= offsets_[currentSwapBuffer_])
		{
			auto cb = CreateConstantBufferInternal(size);
			if (cb == nullptr)
			{
				return nullptr;
			}

			constantBuffers_[currentSwapBuffer_].push_back(cb);
			SafeAddRef(cb);
			offsets_[currentSwapBuffer_]++;
			return cb;
		}
		else
		{
			auto cb = constantBuffers_[currentSwapBuffer_][offsets_[currentSwapBuffer_]];
			auto newCb = ReinitializeConstantBuffer(cb, size);
			if (newCb == nullptr)
			{
				return nullptr;
			}

			SafeAddRef(newCb);
			offsets_[currentSwapBuffer_]++;
			return newCb;
		}
	}

	IndexBuffer::~IndexBuffer() { SafeRelease(indexBuffer_); indexBuffer_->Release(); }

	IndexBuffer* IndexBuffer::Create(GraphicsDE* graphicsDevice, int maxCount, bool isDynamic, bool hasRefCount)
	{
		auto indexBuffer = CreateIndexBuffer(graphicsDevice->GetDevice(), 4, maxCount);
		if (indexBuffer == nullptr)
			return nullptr;

		return new IndexBuffer(graphicsDevice, indexBuffer, maxCount, isDynamic, hasRefCount);
	}

	void IndexBuffer::Lock()
	{
		assert(!m_isLock);

		m_isLock = true;
		m_resource = new Uint8[m_indexMaxCount*4];
		m_indexCount = 0;
	}

	void IndexBuffer::Unlock()
	{
		assert(m_isLock);
		graphicsDevice_->GetContext()->UpdateBuffer
		(indexBuffer_, 0, m_indexMaxCount, m_resource, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		StateTransitionDesc Barrier(indexBuffer_, RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_INDEX_BUFFER, true);
		graphicsDevice_->GetContext()->TransitionResourceStates(1, &Barrier);
		delete[] m_resource;
		m_resource = NULL;
		m_isLock = false;
	}
	inline void CommandList::End() {
		auto& PCtx = gd->ImmediateContext;
		currentCommandList_ = nullptr;
		if(doesBeginWithPlatform_){
			PCtx->FinishCommandList(&currentCommandList_);
			doesBeginWithPlatform_ = false;
		}
	}
	void CommandList::SetVertexBuffer(Vbuf* vertexBuffer, int32_t stride, int32_t offset) {
		auto vbf = vertexBuffer->Get();
		Uint32 Offset = offset;
		isVertexBufferDirtied |=
			bindingVertexBuffer.vertexBuffer != vbf || bindingVertexBuffer.stride != stride || bindingVertexBuffer.offset != offset;
		//if (isVertexBufferDirtied)
		{
			pCtx->SetVertexBuffers(0, 1, &vbf, &Offset, RESOURCE_STATE_TRANSITION_MODE_VERIFY, SET_VERTEX_BUFFERS_FLAG_NONE);
			bindingVertexBuffer.vertexBuffer = vbf;
			bindingVertexBuffer.stride = stride;
			bindingVertexBuffer.offset = offset;
		}
	}
	void CommandList::SetIndexBuffer(IndexBuffer* indexBuffer, int32_t offset)
	{
		const auto ibf = indexBuffer;
		isCurrentIndexBufferDirtied |= bindingIndexBuffer.indexBuffer != ibf || bindingIndexBuffer.offset != offset;
		if (isCurrentIndexBufferDirtied) {
			pCtx->SetIndexBuffer(ibf->Get(), offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		}
		else
		{
			pCtx->SetIndexBuffer(ibf->Get(), offset, RESOURCE_STATE_TRANSITION_MODE_VERIFY);
			bindingIndexBuffer.indexBuffer = ibf;
			bindingIndexBuffer.offset = offset;
		}

	}
	void CommandList::Draw(int32_t primitiveCount, Shader* target, int32_t instanceCount)
	{
		using namespace Diligent;
		doesBeginWithPlatform_ = true;
		//assert(currentCommandList_ != nullptr);
		auto& vb_ = bindingVertexBuffer;
		auto& ib_ = bindingIndexBuffer;
		ConstantBuffer* cb = nullptr;
		PipelineState* pip_ = currentPipelineState;

		bool& isVBDirtied = isVertexBufferDirtied;
		bool& isIBDirtied = isCurrentIndexBufferDirtied;
		bool& isPipDirtied = isPipelineDirtied;


		assert(vb_.vertexBuffer != nullptr);
		//assert(ib_.indexBuffer != nullptr);
		assert(pip_ != nullptr);

		auto vb = (vb_.vertexBuffer);
		//auto ib = (ib_.indexBuffer);
		//auto pip = static_cast<PipelineState*>(pip_);

		int indexPerPrim = 0;
		//if (pip != nullptr)
		{
			isPipDirtied = true;
		}
		switch (pip_->GetDesc().GraphicsPipeline.PrimitiveTopology)
		{
		case PRIMITIVE_TOPOLOGY_TRIANGLE_LIST:
			indexPerPrim = 3;
			break;
		case PRIMITIVE_TOPOLOGY_LINE_LIST:
			indexPerPrim = 2;
			break;
		case PRIMITIVE_TOPOLOGY_POINT_LIST:
			indexPerPrim = 1;
			break;
		default:
			break;
		}
		Diligent::DrawIndexedAttribs drawAttrs(primitiveCount * indexPerPrim, VT_UINT16, DRAW_FLAG_VERIFY_ALL, instanceCount, 0, 0, 0);
		



		// count descriptor
		int32_t requiredCBDescriptorCount = 2;
		int32_t requiredSamplerDescriptorCount = 1;

		for (int stage_ind = 0; stage_ind < static_cast<int>(ShaderStageType::Max); stage_ind++)
		{
			for (size_t unit_ind = 0; unit_ind < currentTextures[stage_ind].size(); unit_ind++)
			{
				if (currentTextures[stage_ind][unit_ind].texture != nullptr)
				{
					requiredSamplerDescriptorCount = std::max(requiredSamplerDescriptorCount, static_cast<int32_t>(unit_ind) + 1);
				}
			}
		}

		requiredCBDescriptorCount += requiredSamplerDescriptorCount;
		// constant buffer


		// setup a topology (triangle)

		// draw polygon
		pCtx->DrawIndexed(drawAttrs);

		isVertexBufferDirtied = false;
		isCurrentIndexBufferDirtied = false;
		isPipelineDirtied = false;
		//CommandList::Draw(primitiveCount, instanceCount);
	}
	ModelLoader::ModelLoader(GraphicsDevice* graphicsDevice, ::Effekseer::FileInterface* fileInterface)
		: graphicsDevice_(graphicsDevice), m_fileInterface(fileInterface)
	{
		//LLGI::SafeAddRef(graphicsDevice_);

		if (m_fileInterface == NULL)
		{
			m_fileInterface = &m_defaultFileInterface;
		}
	}

	ModelLoader::~ModelLoader() { }

	void* ModelLoader::Load(const EFK_CHAR* path)
	{
		std::unique_ptr<::Effekseer::FileReader> reader(m_fileInterface->OpenRead(path));
		if (reader.get() == NULL)
			return nullptr;

		if (reader.get() != NULL)
		{
			size_t size_model = reader->GetLength();
			uint8_t* data_model = new uint8_t[size_model];
			reader->Read(data_model, size_model);

			Model* model = (Model*)Load(data_model, size_model);

			delete[] data_model;

			return (void*)model;
		}

		return NULL;
	}

	void* ModelLoader::Load(const void* data, int32_t size) {
		Model* model = new Model(static_cast<uint8_t*>(const_cast<void*>(data)), size, graphicsDevice_);

		model->ModelCount = Effekseer::Min(Effekseer::Max(model->GetModelCount(), 1), 40);

		model->InternalModels = new Model::InternalModel[model->GetFrameCount()];

		return model;
	}

	void ModelLoader::Unload(void* data)
	{
		if (data != NULL)
		{
			Model* model = (Model*)data;
			delete model;
		}
	}
	RendererImplemented::RendererImplemented(int32_t squareMaxCount)
		: graphicsDevice_(nullptr)
		, m_vertexBuffer(NULL)
		, m_indexBuffer(NULL)
		, m_squareMaxCount(squareMaxCount)
		, m_coordinateSystem(::Effekseer::CoordinateSystem::RH)
		, m_renderState(NULL)

		, m_shader(nullptr)
		, m_shader_distortion(nullptr)
		, m_standardRenderer(nullptr)
		, m_distortingCallback(nullptr)
	{
		m_background.UserPtr = nullptr;
	}
	RendererImplemented::~RendererImplemented()
	{
		// to prevent objects to be disposed before finish renderings.

		if (waitFunc_ != nullptr)
		{
			waitFunc_();
		}
		for (auto p : piplineStates_)
		{
			p->Release();
		}
		piplineStates_.clear();

		ES_SAFE_RELEASE(renderPassPipelineState_);

		ES_SAFE_RELEASE(commandList_);

		GetImpl()->DeleteProxyTextures(this);

		ES_SAFE_DELETE(m_distortingCallback);

		auto p = (Tex*)m_background.UserPtr;
		ES_SAFE_RELEASE(p);

		ES_SAFE_DELETE(m_standardRenderer);

		ES_SAFE_DELETE(m_shader);
		ES_SAFE_DELETE(m_shader_lighting);
		ES_SAFE_DELETE(m_shader_distortion);

		ES_SAFE_DELETE(m_renderState);
		ES_SAFE_DELETE(m_vertexBuffer);
		ES_SAFE_DELETE(m_indexBuffer);
		ES_SAFE_DELETE(m_indexBufferForWireframe);

		if (materialCompiler_ != nullptr)
		{
			materialCompiler_->Release();
			materialCompiler_ = nullptr;
		}
		//LLGI::SafeRelease(graphicsDevice_);
	}
	void RendererImplemented::Destroy() { Release(); }

	void RendererImplemented::SetRestorationOfStatesFlag(bool flag) {}
	bool RendererImplemented::Initialize(GraphicsDE* graphicsDevice, Diligent::IPipelineState* renderPassPipelineState, bool isReversedDepth)
	{
		GDlocal = *graphicsDevice;
		graphicsDevice_ = &GDlocal;
		renderPassPipelineState_ = renderPassPipelineState;
		isReversedDepth_ = isReversedDepth;

		/*LLGI::SafeAddRef(graphicsDevice_);
		LLGI::SafeAddRef(renderPassPipelineState_);*/

		// Generate vertex buffer
		{
			GenerateVertexBuffer();
			if (m_vertexBuffer == NULL)
				return false;
		}

		// Generate index buffer
		{
			GenerateIndexBuffer();
			if (m_indexBuffer == NULL)
				return false;
		}

		// Generate index buffer for rendering wireframes
		{
			m_indexBufferForWireframe = IndexBuffer::Create(graphicsDevice_, m_squareMaxCount * 8, false, false);
			if (m_indexBufferForWireframe == NULL)
				return false;

			m_indexBufferForWireframe->Lock();

			for (int i = 0; i < m_squareMaxCount; i++)
			{
				uint16_t* buf = (uint16_t*)m_indexBufferForWireframe->GetBufferDirect(8);
				buf[0] = 0 + 4 * i;
				buf[1] = 1 + 4 * i;
				buf[2] = 2 + 4 * i;
				buf[3] = 3 + 4 * i;
				buf[4] = 0 + 4 * i;
				buf[5] = 2 + 4 * i;
				buf[6] = 1 + 4 * i;
				buf[7] = 3 + 4 * i;
			}

			m_indexBufferForWireframe->Unlock();
		}

		m_renderState = new RenderState(this);

		// shader
		// pos(3) color(1) uv(2)
		std::vector<LayoutElement> layouts;
		layouts =
		{
		 {0, 0, 3, VT_FLOAT32},
		 {1, 0, 4,  VT_UINT8},
		 {2, 0, 2, VT_FLOAT32}
		};
		std::vector<VertexLayout> layouts_distort =
		{
		 {0, 0, 3, VT_FLOAT32},
		 {1, 0, 4,  VT_UINT8},
		 {2, 0, 2, VT_FLOAT32},
		 {3, 0, 3, VT_FLOAT32},
		 {4, 0, 3, VT_FLOAT32},
		};
		/*layouts_distort.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "POSITION", 0 });
		layouts_distort.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 0 });
		layouts_distort.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 0 });
		layouts_distort.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 1 });
		layouts_distort.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 2 });*/
		auto graphicsDevice_ = this->graphicsDevice_;
		m_shader = Shader::Create(graphicsDevice_,
			fixedShader_.StandardTexture_VS.data(),
			fixedShader_.StandardTexture_PS.data(),
			"StandardRenderer Shader",
			layouts,
			false);
		if (m_shader == NULL)
			return false;

		m_shader_distortion = Shader::Create(graphicsDevice_,
			fixedShader_.StandardDistortedTexture_VS.data(),
			fixedShader_.StandardDistortedTexture_PS.data(),
			"StandardRenderer Distortion Shader",
			layouts_distort,
			false);
		if (m_shader_distortion == NULL)
			return false;

		if (fixedShader_.StandardLightingTexture_VS.size() > 0 && fixedShader_.StandardLightingTexture_PS.size() > 0)
		{
			std::vector<VertexLayout> layouts_lighting =
			{
			 {0, 0, 3, VT_FLOAT32},
			 {1, 0, 4,  VT_UINT8},
			 {2, 0, 4,  VT_UINT8},
			 {3, 0, 4,  VT_UINT8},
			 {4, 0, 2, VT_FLOAT32},
			 {5, 0, 2, VT_FLOAT32},
			};;
			/*layouts_lighting.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "POSITION", 0 });
			layouts_lighting.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 0 });
			layouts_lighting.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 1 });
			layouts_lighting.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 2 });
			layouts_lighting.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 0 });
			layouts_lighting.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 1 });*/

			m_shader_lighting = Shader::Create(graphicsDevice_,
				fixedShader_.StandardLightingTexture_VS.data(),
				fixedShader_.StandardLightingTexture_PS.data(),
				"StandardRenderer Lighting Shader",
				layouts_lighting,
				false);

			m_shader_lighting->SetVertexConstantBufferSize(sizeof(Effekseer::Matrix44) * 2 + sizeof(float) * 4);
			m_shader_lighting->SetVertexRegisterCount(8 + 1);

			m_shader_lighting->SetPixelConstantBufferSize(sizeof(float) * 4 * 3);
			m_shader_lighting->SetPixelRegisterCount(12);
		}

		m_shader->SetVertexConstantBufferSize(sizeof(Effekseer::Matrix44) * 2 + sizeof(float) * 4);
		m_shader->SetVertexRegisterCount(8 + 1);

		m_shader_distortion->SetVertexConstantBufferSize(sizeof(Effekseer::Matrix44) * 2 + sizeof(float) * 4);
		m_shader_distortion->SetVertexRegisterCount(8 + 1);

		m_shader_distortion->SetPixelConstantBufferSize(sizeof(float) * 4 + sizeof(float) * 4);
		m_shader_distortion->SetPixelRegisterCount(1 + 1);

		m_standardRenderer =
			new EffekseerRenderer::StandardRenderer<RendererImplemented, Shader, Vertex, VertexDistortion>(this, m_shader, m_shader_distortion);

		GetImpl()->CreateProxyTextures(this);

		return true;
	}
	//
	//	void RendererImplemented::Destroy() { Release(); }
	//
	//	void RendererImplemented::SetRestorationOfStatesFlag(bool flag) {}
	//	bool RendererImplemented::BeginRendering()
	//	{
	//		assert(graphicsDevice_ != NULL);
	//
	//		impl->CalculateCameraProjectionMatrix();
	//
	//		// initialize states
	//		m_renderState->GetActiveState().Reset();
	//		m_renderState->Update(true);
	//
	//		if (commandList_ == nullptr)
	//		{
	//			GetCurrentCommandList()->Begin();
	//			// GetCurrentCommandList()->BeginRenderPass(nullptr);
	//		}
	//
	//		// reset renderer
	//		m_standardRenderer->ResetAndRenderingIfRequired();
	//
	//		return true;
	//	}
	//	bool RendererImplemented::EndRendering()
	//	{
	//		assert(graphicsDevice_ != NULL);
	//
	//		// reset renderer
	//		m_standardRenderer->ResetAndRenderingIfRequired();
	//
	//		if (commandList_ == nullptr)
	//		{
	//			// GetCurrentCommandList()->EndRenderPass();
	//			GetCurrentCommandList()->End();
	//			GetGraphics()->Execute(GetCurrentCommandList());
	//		}
	//		return true;
	//	}
	//
	//	VertexBuffer* RendererImplemented::GetVertexBuffer() { return m_vertexBuffer; }
	//
	//	IndexBuffer* RendererImplemented::GetIndexBuffer()
	//	{
	//		if (m_renderMode == ::Effekseer::RenderMode::Wireframe)
	//		{
	//			return m_indexBufferForWireframe;
	//		}
	//		else
	//		{
	//			return m_indexBuffer;
	//		}
	//	}
	//
	//	void RendererImplemented::SetCommandList(EffekseerRenderer::CommandList* commandList)
	//	{
	//
	//		ES_SAFE_ADDREF(commandList);
	//		ES_SAFE_RELEASE(commandList_);
	//
	//		commandList_ = static_cast<CommandList*>(commandList);
	//	}
	int32_t RendererImplemented::GetSquareMaxCount() const { return m_squareMaxCount; }

	::EffekseerRenderer::RenderStateBase* RendererImplemented::GetRenderState() { return m_renderState; }

	::Effekseer::SpriteRenderer* RendererImplemented::CreateSpriteRenderer()
	{
		return new ::EffekseerRenderer::SpriteRendererBase<RendererImplemented, Vertex, VertexDistortion>(this);
	}

	::Effekseer::RibbonRenderer* RendererImplemented::CreateRibbonRenderer()
	{
		return new ::EffekseerRenderer::RibbonRendererBase<RendererImplemented, Vertex, VertexDistortion>(this);
	}

	::Effekseer::RingRenderer* RendererImplemented::CreateRingRenderer()
	{
		return new ::EffekseerRenderer::RingRendererBase<RendererImplemented, Vertex, VertexDistortion>(this);
	}

	::Effekseer::ModelRenderer* RendererImplemented::CreateModelRenderer() { return ModelRenderer::Create(this, &fixedShader_); }

	::Effekseer::TrackRenderer* RendererImplemented::CreateTrackRenderer()
	{
		return new ::EffekseerRenderer::TrackRendererBase<RendererImplemented, Vertex, VertexDistortion>(this);
	}

	::Effekseer::TextureLoader* RendererImplemented::CreateTextureLoader(::Effekseer::FileInterface* fileInterface)
	{
		return new TextureLoader(graphicsDevice_, fileInterface);
	}

	//	::Effekseer::ModelLoader* RendererImplemented::CreateModelLoader(::Effekseer::FileInterface* fileInterface)
	//	{
	//#ifdef __EFFEKSEER_RENDERER_INTERNAL_LOADER__
	//		return new ModelLoader(graphicsDevice_, fileInterface);
	//#else
	//		return NULL;
	//#endif
	//	}
	//
	//	::Effekseer::MaterialLoader* RendererImplemented::CreateMaterialLoader(::Effekseer::FileInterface* fileInterface)
	//	{
	//		return new MaterialLoader(graphicsDevice_, fileInterface, platformType_, materialCompiler_);
	//	}
	//
	//	Effekseer::TextureData* RendererImplemented::GetBackground()
	//	{
	//		if (m_background.UserPtr == nullptr)
	//			return nullptr;
	//		return &m_background;
	//	}
	//
	//	void RendererImplemented::SetBackground(LLGI::Texture* background)
	//	{
	//		ES_SAFE_ADDREF(background);
	//
	//		auto p = (LLGI::Texture*)m_background.UserPtr;
	//		ES_SAFE_RELEASE(p);
	//		m_background.UserPtr = background;
	//	}
	//
	//	void RendererImplemented::SetBackgroundTexture(Effekseer::TextureData* textuerData)
	//	{
	//		if (textuerData == nullptr)
	//		{
	//			auto back = (LLGI::Texture*)m_background.UserPtr;
	//			ES_SAFE_RELEASE(back);
	//			m_background.UserPtr = nullptr;
	//			return;
	//		}
	//
	//		auto texture = static_cast<LLGI::Texture*>(textuerData->UserPtr);
	//		ES_SAFE_ADDREF(texture);
	//
	//		auto back = (LLGI::Texture*)m_background.UserPtr;
	//		ES_SAFE_RELEASE(back);
	//
	//		m_background.UserPtr = texture;
	//	}
	//
	//	EffekseerRenderer::DistortingCallback* RendererImplemented::GetDistortingCallback() { return m_distortingCallback; }
	//
	//	void RendererImplemented::SetDistortingCallback(EffekseerRenderer::DistortingCallback* callback)
	//	{
	//		ES_SAFE_DELETE(m_distortingCallback);
	//		m_distortingCallback = callback;
	//	}

		//bool RendererImplemented::Initialize(GraphicsDE* graphics, RenderPassPipelineState* renderPassPipelineState, bool isReversedDepth)
		//{
		//	//ES_SAFE_RELEASE(gd);

		//	return Initialize(graphics, renderPassPipelineState, isReversedDepth);
		//}
	namespace EffVar {

		const ShaderResourceVariableDesc Vars[] =
		{
			{SHADER_TYPE_VERTEX, "VSConstantBuffer", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			{SHADER_TYPE_PIXEL, "PSConstantBuffer", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			{SHADER_TYPE_PIXEL, "g_texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			{SHADER_TYPE_PIXEL, "g_backTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			{SHADER_TYPE_PIXEL, "g_colorTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			{SHADER_TYPE_PIXEL, "g_normalTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		};

		constexpr auto varsz = _countof(Vars);
	}
	Diligent::IPipelineState* RendererImplemented::GetOrCreatePiplineState()
	{
		size_t pso;
		for (pso = 0; pso < piplineStates_.size(); ++pso)
		{
			const auto& des = piplineStates_[pso]->GetDesc();
			const auto& PSOLayout = des.GraphicsPipeline.InputLayout;
			const auto InputLayout = currentShader->GetVertexLayouts();
			const auto shader = pipKeys_[pso].shader;
			bool IsSameLayout =shader==currentShader&&
				/*des.GraphicsPipeline.pVS==currentShader->GetVertexShader()&&
				des.GraphicsPipeline.pPS == currentShader->GetPixelShader()&&*/
				currentTopologyType_ == des.GraphicsPipeline.PrimitiveTopology &&
				PSOLayout.NumElements == InputLayout.size();
				//&&memcmp(PSOLayout.LayoutElements, InputLayout.data(), sizeof(LayoutElement) * InputLayout.size()) == 0;

			if (IsSameLayout)
				return piplineStates_[pso];
		}

		PiplineStateKey key;
		key.state = m_renderState->GetActiveState();
		key.shader = currentShader;
		key.topologyType = currentTopologyType_;
		key.renderPassPipelineState = renderPassPipelineState_;
		static std::vector<ShaderResourceVariableDesc> sd(32);
		sd.clear();
		for (size_t i = 0; i < EffVar::varsz; i++)
		{
			sd.emplace_back(EffVar::Vars[i]);
		}
		const auto pixelvars = currentShader->GetPixelVariableDesc();
		sd.insert(sd.end(),pixelvars.begin(), pixelvars.end());
		auto& Vars = sd;
		//constexpr auto varsz = EffVar::varsz;
		Diligent::TEXTURE_ADDRESS_MODE ws[2];
		ws[(int)Effekseer::TextureWrapType::Clamp] = Diligent::TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_CLAMP;
		ws[(int)Effekseer::TextureWrapType::Repeat] = Diligent::TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
		Diligent::FILTER_TYPE fs[2];
		fs[(int)Effekseer::TextureFilterType::Linear] = FILTER_TYPE::FILTER_TYPE_LINEAR;
		fs[(int)Effekseer::TextureFilterType::Nearest] = FILTER_TYPE::FILTER_TYPE_POINT;
		PipelineStateCreateInfo PSOCreateInfo;
		PipelineStateDesc& PSODesc = PSOCreateInfo.PSODesc;
		const auto state = key.state;
		std::vector< StaticSamplerDesc>StaticSamplers;
		/*for (int i = 0; i < pixelVarsnames.size(); i++) {
			const Diligent::FILTER_TYPE filt = fs[(int)state.TextureFilterTypes[i]];
			const Diligent::TEXTURE_ADDRESS_MODE wt = ws[(int)state.TextureWrapTypes[i]];
			SamplerDesc samplerDesc(filt, filt, filt, wt, wt, wt);
			StaticSamplers.emplace_back(
				SHADER_TYPE_PIXEL, pixelVarsnames[i], samplerDesc
			);
		}*/
		if (isReversedDepth_)
		{
			PSODesc.GraphicsPipeline.DepthStencilDesc.DepthFunc = COMPARISON_FUNCTION::COMPARISON_FUNC_GREATER_EQUAL;
		}
		else
		{
			PSODesc.GraphicsPipeline.DepthStencilDesc.DepthFunc = COMPARISON_FUNCTION::COMPARISON_FUNC_LESS_EQUAL;
		}
		/*for (auto i = 0; i < currentShader->GetVertexLayouts().size(); i++)
		{
			piplineState->VertexLayouts[i] = currentShader->GetVertexLayouts()[i].Format;
			piplineState->VertexLayoutNames[i] = currentShader->GetVertexLayouts()[i].Name;
			piplineState->VertexLayoutSemantics[i] = currentShader->GetVertexLayouts()[i].Semantic;
		}
		piplineState->VertexLayoutCount = currentShader->GetVertexLayouts().size();
*/
		PSODesc.ResourceLayout.Variables = Vars.data();
		PSODesc.ResourceLayout.NumVariables = Vars.size();
		PSODesc.ResourceLayout.StaticSamplers = StaticSamplers.data();
		PSODesc.ResourceLayout.NumStaticSamplers = StaticSamplers.size();
		PSODesc.Name = currentShader->name;
		PSODesc.GraphicsPipeline.pVS = currentShader->GetVertexShader();
		PSODesc.GraphicsPipeline.pPS = currentShader->GetPixelShader();
		auto& InputLayout = PSODesc.GraphicsPipeline.InputLayout;
		InputLayout.LayoutElements = currentShader->GetVertexLayouts().data();
		InputLayout.NumElements = currentShader->GetVertexLayouts().size();
		PSODesc.GraphicsPipeline.PrimitiveTopology = currentTopologyType_;

		StencilOpDesc stencilDesc(
			STENCIL_OP::STENCIL_OP_KEEP, STENCIL_OP::STENCIL_OP_KEEP, STENCIL_OP::STENCIL_OP_REPLACE, COMPARISON_FUNC_ALWAYS
		);
		PSODesc.GraphicsPipeline.DepthStencilDesc.DepthEnable = key.state.DepthTest | key.state.DepthWrite;
		PSODesc.GraphicsPipeline.DepthStencilDesc.DepthWriteEnable = key.state.DepthWrite;
		PSODesc.GraphicsPipeline.DepthStencilDesc.BackFace = stencilDesc;
		PSODesc.GraphicsPipeline.DepthStencilDesc.FrontFace = stencilDesc;
		auto m_pSwapChain = graphicsDevice_->m_pSwapChain;
		PSODesc.GraphicsPipeline.RTVFormats[0] = m_pSwapChain->GetDesc().ColorBufferFormat;
		PSODesc.GraphicsPipeline.DSVFormat = m_pSwapChain->GetDesc().DepthBufferFormat;
		PSODesc.GraphicsPipeline.NumRenderTargets = 1;
		switch (key.state.CullingType)
		{
		case Effekseer::CullingType::Double:
			PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE::CULL_MODE_NONE;
			break;
		case Effekseer::CullingType::Front:
			PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE::CULL_MODE_FRONT;
			break;
		case Effekseer::CullingType::Back:
			PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE::CULL_MODE_BACK;
			break;
		default:
			break;
		}
		auto& BlendState = PSODesc.GraphicsPipeline.BlendDesc.RenderTargets[0];
		BlendState.BlendEnable = true;
		BlendState.SrcBlendAlpha = BLEND_FACTOR_ONE;
		BlendState.DestBlendAlpha = BLEND_FACTOR_ONE;
		BlendState.BlendOpAlpha = BLEND_OPERATION_MAX;
		BlendState.LogicOperationEnable = false;
		BlendState.LogicOp = LOGIC_OP_NOOP;
		/*piplineState->BlendSrcFuncAlpha = LLGI::BlendFuncType::One;
		piplineState->BlendDstFuncAlpha = LLGI::BlendFuncType::One;
		piplineState->BlendEquationAlpha = LLGI::BlendEquationType::Max;*/

		if (key.state.AlphaBlend == Effekseer::AlphaBlendType::Opacity)
		{
			BlendState.DestBlend = BLEND_FACTOR_ZERO;
			BlendState.SrcBlend = BLEND_FACTOR_ONE;
			BlendState.BlendOp = BLEND_OPERATION_ADD;
			/*piplineState->BlendDstFunc = LLGI::BlendFuncType::Zero;
			piplineState->BlendSrcFunc = LLGI::BlendFuncType::One;
			piplineState->BlendEquationRGB = LLGI::BlendEquationType::Add;*/
		}
		else
		if (key.state.AlphaBlend == Effekseer::AlphaBlendType::Blend)
		{
			BlendState.DestBlend = BLEND_FACTOR_INV_BLEND_FACTOR;
			BlendState.SrcBlend = BLEND_FACTOR_SRC_COLOR;
			BlendState.BlendOp = BLEND_OPERATION_ADD;
			/*piplineState->BlendDstFunc = LLGI::BlendFuncType::OneMinusSrcAlpha;
			piplineState->BlendSrcFunc = LLGI::BlendFuncType::SrcAlpha;
			piplineState->BlendEquationRGB = LLGI::BlendEquationType::Add;*/
		}
		else
		if (key.state.AlphaBlend == Effekseer::AlphaBlendType::Add)
		{
			BlendState.DestBlend = BLEND_FACTOR_ONE;
			BlendState.SrcBlend = BLEND_FACTOR_SRC_COLOR;
			BlendState.BlendOp = BLEND_OPERATION_ADD;
			/*piplineState->BlendDstFunc = LLGI::BlendFuncType::One;
			piplineState->BlendSrcFunc = LLGI::BlendFuncType::SrcAlpha;
			piplineState->BlendEquationRGB = LLGI::BlendEquationType::Add;*/
		}
		else
		if (key.state.AlphaBlend == Effekseer::AlphaBlendType::Sub)
		{
			BlendState.DestBlend = BLEND_FACTOR_ONE;
			BlendState.SrcBlend = BLEND_FACTOR_SRC_COLOR;
			BlendState.BlendOp = BLEND_OPERATION_REV_SUBTRACT;
			BlendState.SrcBlendAlpha = BLEND_FACTOR_ZERO;
			BlendState.DestBlendAlpha = BLEND_FACTOR_ONE;
			BlendState.BlendOpAlpha = BLEND_OPERATION_ADD;
			/*piplineState->BlendDstFunc = LLGI::BlendFuncType::One;
			piplineState->BlendSrcFunc = LLGI::BlendFuncType::SrcAlpha;
			piplineState->BlendEquationRGB = LLGI::BlendEquationType::ReverseSub;
			piplineState->BlendSrcFuncAlpha = LLGI::BlendFuncType::Zero;
			piplineState->BlendDstFuncAlpha = LLGI::BlendFuncType::One;
			piplineState->BlendEquationAlpha = LLGI::BlendEquationType::Add;*/
		}
		else
		if (key.state.AlphaBlend == Effekseer::AlphaBlendType::Mul)
		{
			BlendState.DestBlend = BLEND_FACTOR_SRC_COLOR;
			BlendState.SrcBlend = BLEND_FACTOR_ZERO;
			BlendState.BlendOp = BLEND_OPERATION_ADD;
			BlendState.SrcBlendAlpha = BLEND_FACTOR_ZERO;
			BlendState.DestBlendAlpha = BLEND_FACTOR_ONE;
			BlendState.BlendOpAlpha = BLEND_OPERATION_ADD;
			/*piplineState->BlendDstFunc = LLGI::BlendFuncType::SrcColor;
			piplineState->BlendSrcFunc = LLGI::BlendFuncType::Zero;
			piplineState->BlendEquationRGB = LLGI::BlendEquationType::Add;
			piplineState->BlendSrcFuncAlpha = LLGI::BlendFuncType::Zero;
			piplineState->BlendDstFuncAlpha = LLGI::BlendFuncType::One;
			piplineState->BlendEquationAlpha = LLGI::BlendEquationType::Add;*/
		}
		IPipelineState* piplineState=nullptr;
		GetGraphics()->CreatePipelineState(PSOCreateInfo, &piplineState);
		pipKeys_.emplace_back(key);
		piplineStates_.emplace_back(piplineState);

		return piplineState;
	}
	void RendererImplemented::GenerateVertexBuffer()
	{
		m_vertexBuffer = VertexBuffer::Create(graphicsDevice_, EffekseerRenderer::GetMaximumVertexSizeInAllTypes() * m_squareMaxCount * 4, true, false);
	}

	void RendererImplemented::GenerateIndexBuffer()
	{
		m_indexBuffer = IndexBuffer::Create(graphicsDevice_, m_squareMaxCount * 6, false, false);
		if (m_indexBuffer == nullptr)
			return;

		m_indexBuffer->Lock();

		for (int i = 0; i < m_squareMaxCount; i++)
		{
			uint16_t* buf = (uint16_t*)m_indexBuffer->GetBufferDirect(6);
			buf[0] = 3 + 4 * i;
			buf[1] = 1 + 4 * i;
			buf[2] = 0 + 4 * i;
			buf[3] = 3 + 4 * i;
			buf[4] = 0 + 4 * i;
			buf[5] = 2 + 4 * i;
		}

		m_indexBuffer->Unlock();
	}
	void loadshader(const std::string shaderpath, const std::string shadername, IShader*& pVS, IShader*& pPS, GraphicsDE* graphicsDevice) {
		ShaderCreateInfo                               ShaderCI;
		RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;
		auto m_pEngineFactory = graphicsDevice->m_pEngineFactory;
		auto m_pDevice = graphicsDevice->GetDevice();
		m_pEngineFactory->CreateDefaultShaderSourceStreamFactory(shaderpath.c_str(), &pShaderSourceFactory);
		ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;
		ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
		ShaderCI.UseCombinedTextureSamplers = true;

		//ShaderMacroHelper Macros;
		// clang-format on
		//ShaderCI.Macros = Macros;

		constexpr size_t StringBufferSize = 4096;
		char ShaderName[StringBufferSize];
		memset(ShaderName, '\0', sizeof(ShaderName));
		std::strcat(ShaderName, (shaderpath.c_str()));
		std::strcat(ShaderName,shadername.c_str());
		std::strcat(ShaderName, "_VS.fx");
		ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
		ShaderCI.Desc.Name = ShaderName;// (shadername + "_VS.fx").c_str();
		ShaderCI.EntryPoint = "VS";
		ShaderCI.FilePath = ShaderCI.Desc.Name;
		m_pDevice->CreateShader(ShaderCI, &pVS);

		memset(ShaderName, '\0', sizeof(ShaderName));
		std::strcat(ShaderName, shaderpath.c_str());
		std::strcat(ShaderName, shadername.c_str());
		std::strcat(ShaderName, "_PS.fx");
		ShaderCI.Desc.Name = ShaderName;//(shadername + "_PS.fx").c_str();
		ShaderCI.EntryPoint = "PS";
		ShaderCI.FilePath = ShaderCI.Desc.Name;
		ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;

		m_pDevice->CreateShader(ShaderCI, &pPS);
	}
	namespace fs = std::filesystem;
	EffekseerRenderer::Renderer* Create(GraphicsDE* graphicsDevice,
		const TEXTURE_FORMAT* renderTargetFormats,
		int32_t renderTargetCount,
		const TEXTURE_FORMAT depthFormat,
		bool isReversedDepth,
		int32_t squareMaxCount, fs::path curdir)
	{
		auto* renderer = new EffekseerRendererDE::RendererImplemented(squareMaxCount);
		/*auto ps = fs::current_path().string();
		std::vector<char> p2(ps.size() + 100);
		ps.copy(&p2[0], ps.size());
		fs::path curdir(&p2[0]);
		curdir /= "Shader";*/
		/* auto allocate_ = [&](std::vector<DataStructure>& ds, const BYTE* data, int32_t size) -> void {
			IShader* pVS;
			IShader* pPS;
			loadshader(curdir.string(), "model_renderer_distortion", pVS, pPS, graphicsDevice);
			ds.emplace_back((data, size));
			return;
		};*/
		 IShader* pVS=nullptr;
		 IShader* pPS=nullptr;
		 std::vector<ShaderResourceVariableDesc> sd = {
				 {SHADER_TYPE_PIXEL, "g_texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		 };
		 loadshader(curdir.string(), "standard_renderer", pVS, pPS, graphicsDevice);
		 renderer->fixedShader_.StandardTexture_VS.emplace_back(pVS, -1);
		 renderer->fixedShader_.StandardTexture_PS.emplace_back(pPS, -1, sd);
		 assert(pVS != nullptr && pPS != nullptr);
		 pPS = pVS = nullptr;
		/* auto ct = ((Diligent::IShader*)renderer->fixedShader_.StandardTexture_VS[0].Data)->GetReferenceCounters()->GetNumStrongRefs();
		 ct = ((Diligent::IShader*)renderer->fixedShader_.StandardTexture_VS[0].Data)->GetReferenceCounters()->GetNumWeakRefs();*/
		 sd = {
				{SHADER_TYPE_PIXEL, "g_texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
				{SHADER_TYPE_PIXEL, "g_backTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		 };
		 loadshader(curdir.string(), "standard_renderer_distortion", pVS, pPS, graphicsDevice);
		 renderer->fixedShader_.StandardDistortedTexture_VS.emplace_back(pVS, -1);
		 renderer->fixedShader_.StandardDistortedTexture_PS.emplace_back(pPS, -1, sd);
		 assert(pVS != nullptr && pPS != nullptr);
		 sd = {
			   {SHADER_TYPE_PIXEL, "g_colorTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			   {SHADER_TYPE_PIXEL, "g_normalTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		 };
		 pPS = pVS = nullptr;
		 loadshader(curdir.string(), "standard_renderer_lighting", pVS, pPS, graphicsDevice);
		 renderer->fixedShader_.StandardLightingTexture_VS.emplace_back(pVS, -1);
		 renderer->fixedShader_.StandardLightingTexture_PS.emplace_back(pPS, -1, sd);
		 assert(pVS != nullptr && pPS != nullptr);
		 sd = {
				{SHADER_TYPE_PIXEL, "g_colorTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
				{SHADER_TYPE_PIXEL, "g_normalTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		 };
		 pPS = pVS = nullptr;
		 loadshader(curdir.string(), "model_renderer_texture", pVS, pPS, graphicsDevice);
		 renderer->fixedShader_.ModelShaderTexture_VS.emplace_back(pVS, -1);
		 renderer->fixedShader_.ModelShaderTexture_PS.emplace_back(pPS, -1, sd);
		 assert(pVS != nullptr && pPS != nullptr);
		 sd = {
			   {SHADER_TYPE_PIXEL, "g_texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			   {SHADER_TYPE_PIXEL, "g_backTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		 };
		 pPS = pVS = nullptr;
		 loadshader(curdir.string(), "model_renderer_distortion", pVS, pPS, graphicsDevice);
		 renderer->fixedShader_.ModelShaderDistortionTexture_VS.emplace_back(pVS, -1);
		 renderer->fixedShader_.ModelShaderDistortionTexture_PS.emplace_back(pPS, -1, sd);
		 assert(pVS != nullptr && pPS != nullptr);
		 sd = {
			   {SHADER_TYPE_PIXEL, "g_colorTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
			   {SHADER_TYPE_PIXEL, "g_normalTexture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
		 };
		 pPS = pVS = nullptr;
		 loadshader(curdir.string(), "model_renderer_lighting_texture_normal", pVS, pPS, graphicsDevice);
		 renderer->fixedShader_.ModelShaderLightingTextureNormal_VS.emplace_back(pVS, -1);
		 renderer->fixedShader_.ModelShaderLightingTextureNormal_PS.emplace_back(pPS, -1, sd);
		 assert(pVS != nullptr && pPS != nullptr);
	/*	const BYTE* data = Standard_VS::g_VS;
		allocate_(renderer->fixedShader_.StandardTexture_VS, data, (int32_t)sizeof(Standard_VS::g_VS));
		allocate_(renderer->fixedShader_.StandardTexture_PS, Standard_PS::g_PS, sizeof(Standard_PS::g_PS));

		allocate_(renderer->fixedShader_.StandardDistortedTexture_VS, Standard_Distortion_VS::g_VS, sizeof(Standard_Distortion_VS::g_VS));
		allocate_(renderer->fixedShader_.StandardDistortedTexture_PS, Standard_Distortion_PS::g_PS, sizeof(Standard_Distortion_PS::g_PS));

		allocate_(renderer->fixedShader_.ModelShaderTexture_VS, ShaderTexture_::g_VS, sizeof(ShaderTexture_::g_VS));
		allocate_(renderer->fixedShader_.ModelShaderTexture_PS, ShaderTexture_::g_PS, sizeof(ShaderTexture_::g_PS));

		allocate_(renderer->fixedShader_.ModelShaderLightingTextureNormal_VS,
			ShaderLightingTextureNormal_::g_VS,
			sizeof(ShaderLightingTextureNormal_::g_VS));
		allocate_(renderer->fixedShader_.ModelShaderLightingTextureNormal_PS,
			ShaderLightingTextureNormal_::g_PS,
			sizeof(ShaderLightingTextureNormal_::g_PS));

		allocate_(
			renderer->fixedShader_.ModelShaderDistortionTexture_VS, ShaderDistortionTexture_::g_VS, sizeof(ShaderDistortionTexture_::g_VS));
		allocate_(
			renderer->fixedShader_.ModelShaderDistortionTexture_PS, ShaderDistortionTexture_::g_PS, sizeof(ShaderDistortionTexture_::g_PS));

		allocate_(renderer->fixedShader_.StandardLightingTexture_VS, ShaderStandardLighting_::g_VS, sizeof(ShaderStandardLighting_::g_VS));
		allocate_(renderer->fixedShader_.StandardLightingTexture_PS, ShaderStandardLighting_::g_PS, sizeof(ShaderStandardLighting_::g_PS));
*/
		renderer->platformType_ = Effekseer::CompiledMaterialPlatformType::DirectX12;
		renderer->materialCompiler_ = nullptr;//new Effekseer::MaterialCompilerDX12();

		//PipelineStateCreateInfo PSOCreateInfo;
		//PipelineStateDesc& PSODesc = PSOCreateInfo.PSODesc;

		//RenderPassPipelineStateKey key;
		//key.RenderTargetFormats.resize(renderTargetCount);

		//for (size_t i = 0; i < key.RenderTargetFormats.size(); i++)
		//{
		//	key.RenderTargetFormats.at(i) = LLGI::ConvertFormat(renderTargetFormats[i]);
		//}

		//key.DepthFormat = LLGI::ConvertFormat(depthFormat);

		auto& gd = graphicsDevice;// static_cast<EffekseerRendererLLGI::GraphicsDevice*>(graphicsDevice);

		//auto pipelineState = gd->GetGraphics()->CreateRenderPassPipelineState(key);

		if (renderer->Initialize(gd, nullptr, isReversedDepth))
		{
			//ES_SAFE_RELEASE(pipelineState);
			return renderer;
		}

		//ES_SAFE_RELEASE(pipelineState);

		ES_SAFE_DELETE(renderer);

		return nullptr;
	}
	//VertexBuffer::VertexBuffer() {}
	VertexBuffer::VertexBuffer(GraphicsDE* graphicsDevice, Diligent::IBuffer* buffer, int size, bool isDynamic, bool hasRefCount)
		: VertexBufferBase(size, isDynamic),graphics_(*graphicsDevice)
		//, DeviceObject(graphicsDevice)
		, m_vertexRingOffset(0)
		, m_ringBufferLock(false)
		, m_ringLockedOffset(0)
		, m_ringLockedSize(0) {
		vertexBuffers.emplace_back(buffer, size);
		lockedResource_ = new uint8_t[size];
		/*void* data = lockedResource_;
		auto& pContext = (GetGraphicsDevice()).ImmediateContext;
		auto ibuf = vertexBuffers[currentIndex].Get();
		auto ct = buffer->GetReferenceCounters()->GetNumStrongRefs();
		lockedResource_ = nullptr;
		pContext->MapBuffer(buffer, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, lockedResource_);*/
	}

	VertexBuffer::~VertexBuffer() {
		for (size_t i = 0; i < vertexBuffers.size(); i++)
		{
			vertexBuffers[i].Get()->Release();
		}
	}

	bool VertexBuffer::Initialize(GraphicsDE* graphics, int32_t size)
	{
		assert(false);
		//graphics_ = *graphics;
		//Diligent::BufferDesc VertBuffDesc;
		//VertBuffDesc.Name = "Effekseer vertex buffer";
		//VertBuffDesc.Usage = USAGE_DYNAMIC;
		//VertBuffDesc.BindFlags = BIND_VERTEX_BUFFER;
		//VertBuffDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
		//VertBuffDesc.uiSizeInBytes = size;
		//graphics->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &vertexBuffer_);
		///*vertexBuffer_ = graphics->CreateResource(
		//	D3D12_HEAP_TYPE_UPLOAD, DXGI_FORMAT_UNKNOWN, D3D12_RESOURCE_DIMENSION_BUFFER, D3D12_RESOURCE_STATE_GENERIC_READ, Vec2I(size, 1));*/
		//size_ = size;
		return false;
	}
	VertexBuffer* VertexBuffer::Create(GraphicsDE* graphicsDevice, int size, bool isDynamic, bool hasRefCount)
	{
		IBuffer* vertexBuffer = nullptr;
		Diligent::BufferDesc VertBuffDesc;
		VertBuffDesc.Name = "Effekseer vertex buffer";
		VertBuffDesc.Usage = USAGE_DEFAULT;
		VertBuffDesc.BindFlags = BIND_VERTEX_BUFFER;
		//VertBuffDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
		VertBuffDesc.uiSizeInBytes = size;
		graphicsDevice->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &vertexBuffer);
		if (vertexBuffer == nullptr)
			return nullptr;
		StateTransitionDesc Barriers[] = {
			{vertexBuffer, RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_VERTEX_BUFFER, true} };
		graphicsDevice->GetContext()->TransitionResourceStates(1, Barriers);
		return new VertexBuffer(graphicsDevice, vertexBuffer, size, isDynamic, hasRefCount);
	}

	void VertexBuffer::Lock()
	{
		assert(!m_isLock);
		assert(!m_ringBufferLock);

		m_isLock = true;
		//m_resource = (uint8_t*)lockedResource_;

		auto& pContext = (GetGraphicsDevice()).ImmediateContext;
		const auto ibuf = vertexBuffers[currentIndex].Get();
		pContext->MapBuffer(ibuf, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, (PVoid&)m_resource);
		m_offset = 0;

		/* 次のRingBufferLockは強制的にDiscard */
		m_vertexRingOffset = m_size;
	}

	bool VertexBuffer::RingBufferLock(int32_t size, int32_t& offset, void*& data, int32_t alignment)
	{
		assert(!m_isLock);
		assert(!m_ringBufferLock);
		assert(this->m_isDynamic);

		if (size > m_size)
			return false;

		m_vertexRingOffset = (m_vertexRingOffset + alignment - 1) / alignment * alignment;

		if ((int32_t)m_vertexRingOffset + size > m_size)
		{
			offset = 0;
			m_ringLockedOffset = 0;
			m_ringLockedSize = size;

			m_vertexRingOffset = size;
		}
		else
		{
			offset = m_vertexRingOffset;
			m_ringLockedOffset = offset;
			m_ringLockedSize = size;

			m_vertexRingOffset += size;
		}
		auto& pContext = (GetGraphicsDevice()).ImmediateContext;
		const auto ibuf = vertexBuffers[currentIndex].Get();
		//pContext->MapBuffer(ibuf, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, (PVoid&)lockedResource_);
		data = (uint8_t*)lockedResource_;// +m_ringLockedOffset;
		//m_resource = (uint8_t*)lockedResource_;
		m_ringBufferLock = true;

		return true;
	}

	void VertexBuffer::Unlock()
	{
		assert(m_isLock || m_ringBufferLock);

		if (m_isLock)
		{
			auto& pContext = (GetGraphicsDevice()).ImmediateContext;
			uint8_t* data;
			const auto ibuf = vertexBuffers[currentIndex].Get();
			
			/*pContext->MapBuffer(ibuf, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, (PVoid&)data);

			memcpy(data, m_resource, m_size);*/
			pContext->UnmapBuffer(ibuf, MAP_WRITE);
			//vertexBuffers[currentIndex]->Unlock();
		}

		if (m_ringBufferLock)
		{
			auto& pContext = (GetGraphicsDevice()).ImmediateContext;
			const auto ibuf = vertexBuffers[currentIndex].Get();
			/*void* data = nullptr;

			pContext->MapBuffer(ibuf, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, data);
			uint8_t* dst = (uint8_t*)data;
			dst += m_ringLockedOffset;

			uint8_t* src = (uint8_t*)m_resource;

			memcpy(dst, src, m_ringLockedSize);*/
			//pContext->UnmapBuffer(ibuf, MAP_WRITE);
			pContext->UpdateBuffer(ibuf, m_ringLockedOffset,m_ringLockedSize,lockedResource_, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		}
		m_resource = NULL;
		m_isLock = false;
		m_ringBufferLock = false;
	}
	bool VertexBuffer::TryRingBufferLock(int32_t size, int32_t& offset, void*& data, int32_t alignment)
	{
		if ((int32_t)m_vertexRingOffset + size > m_size)
			return false;

		return RingBufferLock(size, offset, data, alignment);
	}

	//void VertexBuffer::Unlock()
	//{

	//	/*auto& pContext = (*GetGraphicsDevice()).ImmediateContext;
	//	pContext->UnmapBuffer(vertexBuffer_, MAP_WRITE);
	//	mapped_ = nullptr;*/
	//}

	int32_t VertexBuffer::GetSize() { return size_; }


	//vertexbuffer* graphicsde::createvertexbuffer(int32_t size)
	//{
	//	auto obj = new vertexbufferdx12();
	//	if (!obj->initialize(this, size))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}

	//	return obj;
	//}

	//indexbuffer* graphicsde::createindexbuffer(int32_t stride, int32_t count)
	//{
	//	auto obj = new indexbufferdx12();
	//	if (!obj->initialize(this, stride, count))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}

	//	return obj;
	//}

	//constantbuffer* graphicsde::createconstantbuffer(int32_t size)
	//{
	//	auto obj = new ConstantBuffer();
	//	if (!obj->initialize(this, size))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}

	//	return obj;
	//}

	//shader* graphicsde::createshader(datastructure* data, int32_t count)
	//{
	//	auto obj = new shaderdx12();
	//	if (!obj->initialize(data, count))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}
	//	return obj;
	//}

	//pipelinestate* graphicsde::createpiplinestate() { return new pipelinestatedx12(this); }

	//singleframememorypool* graphicsde::createsingleframememorypool(int32_t constantbufferpoolsize, int32_t drawingcount)
	//{
	//	 driver issue
	//	if (drawingcount > 512)
	//	{
	//		log(logtype::warning, "drawingcount is too large. it must be lower than 512");
	//		 drawingcount = 512;
	//	}

	//	return new SingleFrameMemoryPool(this, true, swapbuffercount_, constantbufferpoolsize, drawingcount);
	//}

	//commandlist* graphicsde::createcommandlist(singleframememorypool* memorypool)
	//{
	//	auto mp = static_cast<SingleFrameMemoryPool*>(memorypool);

	//	auto obj = new commandlistdx12();
	//	if (!obj->initialize(this, mp->getdrawingcount()))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}
	//	return obj;
	//}

	//renderpass* graphicsde::createrenderpass(texture** textures, int32_t texturecount, texture* depthtexture)
	//{
	//	auto renderpass = new renderpassdx12(this->device_);
	//	if (!renderpass->initialize((texturedx12**)textures, texturecount, (texturedx12*)depthtexture, nullptr, nullptr))
	//	{
	//		saferelease(renderpass);
	//	}

	//	return renderpass;
	//}

	//renderpass* graphicsde::createrenderpass(texture* texture, texture* resolvedtexture, texture* depthtexture, texture* resolveddepthtexture)
	//{
	//	auto renderpass = new renderpassdx12(this->device_);

	//	std::array<texturedx12*, 1> t;
	//	t[0] = const_cast<texturedx12*>(static_cast<const texturedx12*>(texture));

	//	if (!renderpass->initialize(t.data(),
	//		static_cast<int32_t>(t.size()),
	//		(texturedx12*)depthtexture,
	//		(texturedx12*)resolvedtexture,
	//		(texturedx12*)resolveddepthtexture))
	//	{
	//		saferelease(renderpass);
	//	}

	//	return renderpass;
	//}

	//texture* graphicsde::createtexture(uint64_t id)
	//{
	//	auto obj = new texturedx12(this, true);
	//	if (!obj->initialize(reinterpret_cast<id3d12resource*>(id)))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}
	//	return obj;
	//}

	//texture* graphicsde::createtexture(const textureinitializationparameter& parameter)
	//{
	//	auto obj = new texturedx12(this, true);
	//	if (!obj->initialize(parameter.size, texturetype::color, parameter.format, 1))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}
	//	return obj;
	//}

	//texture* graphicsde::createrendertexture(const rendertextureinitializationparameter& parameter)
	//{
	//	auto obj = new texturedx12(this, true);
	//	if (!obj->initialize(parameter.size, texturetype::render, parameter.format, parameter.samplingcount))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}
	//	return obj;
	//}

	//texture* graphicsde::createdepthtexture(const depthtextureinitializationparameter& parameter)
	//{
	//	auto obj = new texturedx12(this, true);

	//	auto format = textureformattype::d32;
	//	if (parameter.mode == depthtexturemode::depthstencil)
	//	{
	//		format = textureformattype::d24s8;
	//	}

	//	if (!obj->initialize(parameter.size, texturetype::depth, format, parameter.samplingcount))
	//	{
	//		saferelease(obj);
	//		return nullptr;
	//	}
	//	return obj;
	//}

	//renderpasspipelinestate* graphicsde::createrenderpasspipelinestate(renderpass* renderpass)
	//{
	//	auto renderpass_ = static_cast<renderpassdx12*>(renderpass);
	//	auto key = renderpass_->getkey();
	//	return createrenderpasspipelinestate(key);
	//}

	//renderpasspipelinestate* graphicsde::createrenderpasspipelinestate(const renderpasspipelinestatekey& key)
	//{
	//	 already?
	//	{
	//		auto it = renderpasspipelinestates_.find(key);

	//		if (it != renderpasspipelinestates_.end())
	//		{
	//			auto ret = it->second;

	//			if (ret != nullptr)
	//			{
	//				auto ptr = ret.get();
	//				safeaddref(ptr);
	//				return ptr;
	//			}
	//		}
	//	}

	//	auto ret = createsharedptr<>(new renderpasspipelinestatedx12());
	//	renderpasspipelinestates_[key] = ret;
	//	ret->key = key;

	//	{
	//		auto ptr = ret.get();
	//		safeaddref(ptr);
	//		return ptr;
	//	}
	//}

	//diligent::irenderdevice* graphicsde::getdevice() { return device_; }

	//int32_t graphicsde::getswapbuffercount() const { return swapbuffercount_; }

	//id3d12resource* graphicsde::createresource(d3d12_heap_type heaptype,
	//	dxgi_format format,
	//	d3d12_resource_dimension resourcedimention,
	//	d3d12_resource_states resourcestate,
	//	d3d12_resource_flags flags,
	//	vec2i size)
	//{
	//	return createresourcebuffer(device_, heaptype, format, resourcedimention, resourcestate, flags, size, 1);
	//}

	//std::vector<uint8_t> graphicsde::capturerendertarget(texture* rendertarget)
	//{
	//	if (!rendertarget)
	//	{
	//		return std::vector<uint8_t>();
	//	}

	//	if (rendertarget->getformat() != textureformattype::r8g8b8a8_unorm &&
	//		rendertarget->getformat() != textureformattype::r8g8b8a8_unorm_srgb &&
	//		rendertarget->getformat() != textureformattype::r32g32b32a32_float && rendertarget->getformat() != textureformattype::r8_unorm)
	//	{
	//		log(logtype::error, "unimplemented.");
	//		return std::vector<uint8_t>();
	//	}

	//	auto device = getdevice();

	//	std::vector<uint8_t> result;
	//	auto texture = static_cast<texturedx12*>(rendertarget);
	//	auto size = texture->getsizeas2d();
	//	d3d12_texture_copy_location src = {}, dst = {};

	//	auto dstfootprint = texture->getfootprint().footprint;

	//	bufferdx12 dstbuffer;
	//	if (!dstbuffer.initialize(this, dstfootprint.rowpitch * dstfootprint.height))
	//	{
	//		auto msg = (std::string("error : ") + std::string(__file__) + " : " + std::to_string(__line__) + std::string(" : "));
	//		::llgi::log(::llgi::logtype::error, msg.c_str());
	//		goto failed_exit;
	//	}
	//	id3d12commandallocator* commandallocator = nullptr;
	//	id3d12graphicscommandlist* commandlist = nullptr;

	//	auto hr = device->createcommandallocator(d3d12_command_list_type_direct, iid_ppv_args(&commandallocator));
	//	if (failed(hr))
	//	{
	//		auto msg = (std::string("error : ") + std::string(__file__) + " : " + std::to_string(__line__) + std::string(" : ") +
	//			std::system_category().message(hr));
	//		::llgi::log(::llgi::logtype::error, msg.c_str());
	//		goto failed_exit;
	//	}

	//	hr = device->createcommandlist(0, d3d12_command_list_type_direct, commandallocator, null, iid_ppv_args(&commandlist));
	//	if (failed(hr))
	//	{
	//		auto msg = (std::string("error : ") + std::string(__file__) + " : " + std::to_string(__line__) + std::string(" : ") +
	//			std::system_category().message(hr));
	//		::llgi::log(::llgi::logtype::error, msg.c_str());
	//		saferelease(commandallocator);
	//		goto failed_exit;
	//	}

	//	d3d12_placed_subresource_footprint footprint;
	//	uint64 totalsize;
	//	auto texturedesc = texture->get()->getdesc();
	//	device->getcopyablefootprints(&texturedesc, 0, 1, 0, &footprint, nullptr, nullptr, &totalsize);

	//	src.presource = texture->get();
	//	src.type = d3d12_texture_copy_type_subresource_index;
	//	src.subresourceindex = 0;

	//	dst.presource = dstbuffer.get();
	//	dst.type = d3d12_texture_copy_type_placed_footprint;
	//	dst.placedfootprint = footprint;

	//	texture->resourcebarrior(commandlist, d3d12_resource_state_copy_source);
	//	commandlist->copytextureregion(&dst, 0, 0, 0, &src, nullptr);
	//	texture->resourcebarrior(commandlist, d3d12_resource_state_generic_read);

	//	commandlist->close();
	//	id3d12commandlist* list[] = { commandlist };
	//	getcommandqueue()->executecommandlists(1, list);

	//	 todo optimize it
	//	waitfinish();
	//	saferelease(commandlist);
	//	saferelease(commandallocator);

	//	if (gettexturememorysize(rendertarget->getformat(), rendertarget->getsizeas2d()) != dstbuffer.getsize())
	//	{
	//		result.resize(gettexturememorysize(rendertarget->getformat(), rendertarget->getsizeas2d()));
	//		auto raw = static_cast<uint8_t*>(dstbuffer.lock());

	//		for (int32_t y = 0; y < rendertarget->getsizeas2d().y; y++)
	//		{
	//			auto pitch = gettexturememorysize(rendertarget->getformat(), rendertarget->getsizeas2d()) / rendertarget->getsizeas2d().y;
	//			memcpy(result.data() + pitch * y, raw + dstfootprint.rowpitch * y, pitch);
	//		}

	//		dstbuffer.unlock();
	//	}
	//	else
	//	{
	//		result.resize(dstbuffer.getsize());
	//		auto raw = dstbuffer.lock();
	//		memcpy(result.data(), raw, result.size());
	//		dstbuffer.unlock();
	//	}

	//	return result;

	//failed_exit:
	//	saferelease(commandlist);
	//	return std::vector<uint8_t>();
	//}

	RenderState::~RenderState() {}
	void RenderState::Update(bool forced)
	{
		bool changeDepth = forced;
		bool changeRasterizer = forced;
		bool changeBlend = forced;

		if (m_active.DepthTest != m_next.DepthTest || forced)
		{
			changeDepth = true;
		}

		if (m_active.DepthWrite != m_next.DepthWrite || forced)
		{
			changeDepth = true;
		}

		if (changeDepth)
		{
		}

		if (m_active.CullingType != m_next.CullingType || forced)
		{
			changeRasterizer = true;
		}

		if (changeRasterizer)
		{
			auto cullingType = (int32_t)m_next.CullingType;
		}

		if (m_active.AlphaBlend != m_next.AlphaBlend || forced)
		{
			changeBlend = true;
		}

		if (changeBlend)
		{
			auto alphaBlend = (int32_t)m_next.AlphaBlend;
		}

		for (int32_t i = 0; i < Effekseer::TextureSlotMax; i++)
		{
			bool changeSampler = forced;

			if (m_active.TextureFilterTypes[i] != m_next.TextureFilterTypes[i] || forced)
			{
				changeSampler = true;
			}

			if (m_active.TextureWrapTypes[i] != m_next.TextureWrapTypes[i] || forced)
			{
				changeSampler = true;
			}

			if (changeSampler)
			{
				auto filter = (int32_t)m_next.TextureFilterTypes[i];
				auto wrap = (int32_t)m_next.TextureWrapTypes[i];
			}
		}

		m_active = m_next;
	}

	void RendererImplemented::SetVertexBuffer(IBuffer* vertexBuffer, int32_t stride)
	{
		//if (currentVertexBuffer_->Get() != vertexBuffer)
		{
			Barriers.emplace_back(vertexBuffer, RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_VERTEX_BUFFER, true);
			currentVertexBuffer_=(vertexBuffer);
			currentVertexBufferStride_ = stride;
		}
	}
	void RendererImplemented::SetVertexBuffer(VertexBuffer* vertexBuffer, int32_t stride)
	{
		currentVertexBuffer_ = vertexBuffer->GetVertexBuffer()->Get();
		currentVertexBufferStride_ = stride;
		Barriers.emplace_back(currentVertexBuffer_, RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_VERTEX_BUFFER, true);
	}

	void RendererImplemented::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		currentIndexBuffer_ = indexBuffer->Get();
		//Barriers.emplace_back(indexBuffer->Get(), RESOURCE_STATE_INDEX_BUFFER, RESOURCE_STATE_INDEX_BUFFER, true);

		/*if(!currentIndexBuffer_||indexBuffer->Get()!=currentIndexBuffer_)
		{
			Barriers.emplace_back(indexBuffer->Get(), RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_INDEX_BUFFER, true);
			currentIndexBuffer_ = indexBuffer;
		}*/
	}

	void RendererImplemented::SetIndexBuffer(IBuffer* indexBuffer) {
		//if (currentIndexBuffer_ != indexBuffer) 
		{
			//Barriers.emplace_back(indexBuffer, RESOURCE_STATE_INDEX_BUFFER, RESOURCE_STATE_INDEX_BUFFER, true);
			currentIndexBuffer_=(indexBuffer);
		}
	}
	void RendererImplemented::SetLayout(Shader* shader)
	{
		if (m_renderMode == Effekseer::RenderMode::Normal)
		{
			currentTopologyType_ = PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;;
		}
		else
		{
			currentTopologyType_ = PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_LINE_LIST;
		}
	}
	void RendererImplemented::DrawSprites(int32_t spriteCount, int32_t vertexOffset)
	{
		auto& pCtx = graphicsDevice_->GetContext();
		//using ConstantBuffer = Diligent::IBuffer;
		ConstantBuffer* constantBufferVS = nullptr;
		ConstantBuffer* constantBufferPS = nullptr;

		auto m_pSwapChain = graphicsDevice_->m_pSwapChain;
		auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
		pCtx->SetRenderTargets(1, &pRTV, m_pSwapChain->GetDepthBufferDSV(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		auto piplineState = GetOrCreatePiplineState();
		if(currentShader->VCB==nullptr){
			const auto Vars = EffVar::Vars;
			constexpr auto varsz = EffVar::varsz;
			/*piplineState->SetRenderPassPipelineState(renderPassPipelineState_);
			piplineState->Compile();*/
			auto& p_SRB = currentShader->m_SRB;
			piplineState->CreateShaderResourceBinding(&p_SRB, true);
			currentShader->SetVPCB(
			p_SRB->GetVariableByName(SHADER_TYPE_VERTEX, "VSConstantBuffer"),
			p_SRB->GetVariableByName(SHADER_TYPE_PIXEL, "PSConstantBuffer"));
			const auto svdes = currentShader->GetPixelVariableDesc();
			for (size_t i = 0; i < svdes.size(); i++)
			{
				auto ptr = p_SRB->GetVariableByName(SHADER_TYPE_PIXEL,svdes[i].Name);
				currentShader->TexSrv_.emplace_back(ptr);
			}
			//currentShader->VCB = piplineState->GetStaticVariableByName(SHADER_TYPE_VERTEX, "VSConstantBuffer");
		}
		/*if (currentShader->TexSrv_.size() < 2)
			return;*/
		pCtx->SetPipelineState(piplineState);

		if (Barriers.size() > 0) {
			graphicsDevice_->GetContext()->TransitionResourceStates(Barriers.size(), Barriers.data());
			Barriers.clear();
		}
		currentShader->Writecb(pCtx);
		/*if (currentShader->GetPixelConstantBufferSize() > 0)
		{
			constantBufferPS = commandList_->GetMemoryPooll()->CreateConstantBuffer(currentShader->GetPixelConstantBufferSize());
			assert(constantBufferPS != nullptr);
			constantBufferPS->WriteTo(pCtx, currentShader->GetPixelConstantBuffer(), currentShader->GetPixelConstantBufferSize());
		}*/
		impl->drawcallCount++;
		impl->drawvertexCount += spriteCount * 4;
		pCtx->SetIndexBuffer(currentIndexBuffer_, 0, RESOURCE_STATE_TRANSITION_MODE_VERIFY);

		//GetCurrentCommandList()->SetIndexBuffer(currentIndexBuffer_, 0);
		auto vbf = currentVertexBuffer_;
		Uint32 Offset = vertexOffset* currentVertexBufferStride_;
		pCtx->SetVertexBuffers(0, 1, &vbf, &Offset, RESOURCE_STATE_TRANSITION_MODE_VERIFY, SET_VERTEX_BUFFERS_FLAG_NONE);

		pCtx->CommitShaderResources(currentShader->m_SRB, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		//Diligent::DrawIndexedAttribs drawAttrs(3 * spriteCount * 2, VT_UINT16, DRAW_FLAG_VERIFY_ALL, 1, 0, 0, 0);
		
		if (m_renderMode == Effekseer::RenderMode::Normal)
		{
			/*GetCurrentCommandList()->SetVertexBuffer(
				currentVertexBuffer_, currentVertexBufferStride_, vertexOffset * currentVertexBufferStride_);*/
			Diligent::DrawIndexedAttribs drawAttrs(3 * spriteCount * 2, VT_UINT16, DRAW_FLAG_VERIFY_ALL, 1, 0, 0, 0);
			pCtx->DrawIndexed(drawAttrs);
			//GetCurrentCommandList()->Draw(spriteCount * 2, currentShader);
		}
		else
		{
			Diligent::DrawIndexedAttribs drawAttrs(3 * spriteCount * 4, VT_UINT16, DRAW_FLAG_VERIFY_ALL, 1, 0, 0, 0);
			pCtx->DrawIndexed(drawAttrs);
			//GetCurrentCommandList()->Draw(spriteCount * 4, currentShader);
		}
		//pCtx->DrawIndexed(drawAttrs);
		SafeRelease(constantBufferVS);
		SafeRelease(constantBufferPS);
	}

	void RendererImplemented::DrawPolygon(int32_t vertexCount, int32_t indexCount)
	{
		auto& pCtx = graphicsDevice_->GetContext();
		// constant buffer
	/*	ConstantBuffer* constantBufferVS = nullptr;
		ConstantBuffer* constantBufferPS = nullptr;*/

		auto m_pSwapChain = graphicsDevice_->m_pSwapChain;
		auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
		pCtx->SetRenderTargets(1, &pRTV, m_pSwapChain->GetDepthBufferDSV(), RESOURCE_STATE_TRANSITION_MODE_VERIFY);
		if (Barriers.size() > 0) {
			graphicsDevice_->GetContext()->TransitionResourceStates(Barriers.size(), Barriers.data());
			Barriers.clear();
		}
		auto piplineState = GetOrCreatePiplineState();
		if (currentShader->VCB == nullptr) {
			const auto Vars = EffVar::Vars;
			constexpr auto varsz = EffVar::varsz;
			/*piplineState->SetRenderPassPipelineState(renderPassPipelineState_);
			piplineState->Compile();*/
			auto& p_SRB = currentShader->m_SRB;
			piplineState->CreateShaderResourceBinding(&p_SRB, true);
			currentShader->SetVPCB(
				p_SRB->GetVariableByName(SHADER_TYPE_VERTEX, "VSConstantBuffer"),
				p_SRB->GetVariableByName(SHADER_TYPE_PIXEL, "PSConstantBuffer"));
			const auto svdes = currentShader->GetPixelVariableDesc();
			for (size_t i = 0; i < svdes.size(); i++)
			{
				auto ptr = p_SRB->GetVariableByName(SHADER_TYPE_PIXEL, svdes[i].Name);
				currentShader->TexSrv_.emplace_back(ptr);
			}
		}
		pCtx->SetPipelineState(piplineState);	
		std::random_device rd; // 真随机数生成器（但有些编译器没有实现），用于生成伪随机数生成器的种子
		std::mt19937 eng(rd()); // 使用梅森旋转法作为伪随机数生成器，随机程度较好
		std::uniform_int_distribution<> distrib(0, 3);
		int a = distrib(rd);
		if (a==0)
		currentShader->Writecb(pCtx);
		auto vbf = currentVertexBuffer_;
		Uint32 Offset = 0;
		impl->drawcallCount++;
		impl->drawvertexCount += vertexCount;
		pCtx->SetIndexBuffer(currentIndexBuffer_, 0, RESOURCE_STATE_TRANSITION_MODE_VERIFY);

		//GetCurrentCommandList()->SetIndexBuffer(currentIndexBuffer_, 0);

		pCtx->SetVertexBuffers(0, 1, &vbf, &Offset, RESOURCE_STATE_TRANSITION_MODE_VERIFY, SET_VERTEX_BUFFERS_FLAG_NONE);
		//pCtx->SetStencilRef(UINT32_MAX);
		pCtx->CommitShaderResources(currentShader->m_SRB, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		DrawAttribs drawAttrs(indexCount, DRAW_FLAG_VERIFY_ALL);
		pCtx->Draw(drawAttrs);
		/*Diligent::DrawIndexedAttribs drawAttrs(indexCount , VT_UINT32, DRAW_FLAG_VERIFY_ALL);
		pCtx->DrawIndexed(drawAttrs);*/
	}
	void RendererImplemented::SetVertexBufferToShader(const void* data, int32_t size, int32_t dstOffset)
	{
		assert(currentShader != nullptr);
		auto p = static_cast<uint8_t*>(currentShader->GetVertexConstantBuffer()) + dstOffset;
		memcpy(p, data, size);
	}

	void RendererImplemented::SetPixelBufferToShader(const void* data, int32_t size, int32_t dstOffset)
	{
		assert(currentShader != nullptr);
		auto p = static_cast<uint8_t*>(currentShader->GetPixelConstantBuffer()) + dstOffset;
		memcpy(p, data, size);
	}
	void RendererImplemented::SetTextures(Shader* shader, Effekseer::TextureData** textures, int32_t count)
	{
		Diligent::TEXTURE_ADDRESS_MODE ws[2];
		ws[(int)Effekseer::TextureWrapType::Clamp] = Diligent::TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_CLAMP;
		ws[(int)Effekseer::TextureWrapType::Repeat] = Diligent::TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_WRAP;
		Diligent::FILTER_TYPE fs[2];
		fs[(int)Effekseer::TextureFilterType::Linear] = FILTER_TYPE::FILTER_TYPE_LINEAR;
		fs[(int)Effekseer::TextureFilterType::Nearest] = FILTER_TYPE::FILTER_TYPE_POINT;
		auto state = GetRenderState()->GetActiveState();
		for (int32_t i = 0; i < count; i++)
		{
			const Diligent::FILTER_TYPE filt = fs[(int)state.TextureFilterTypes[i]];
			const Diligent::TEXTURE_ADDRESS_MODE wt = ws[(int)state.TextureWrapTypes[i]];
			SamplerDesc samplerDesc(filt, filt, filt, wt, wt, wt);
			bool pipexist = true;
			/*for (size_t i = 0; i < shader->ps_.size(); i++)
			{
				auto ps = (shader->ps_[i]);
				const auto desc = ps->GetDesc();
				if (desc.ResourceLayout.StaticSamplers[0].Desc == samplerDesc) {
					continue;
				}
				else {
					pipexist = false;
				}
			}*/
			/*if (!pipexist) {
				GetOrCreatePiplineState();
			}*/
			//if (textures[i] == nullptr)
			{
				/*auto t = (Tex*)(textures[i]->UserPtr);
				if (t->sampler->GetDesc() == samplerDesc) {
					return;
				}
				t->sampler->Release();
				CommandList& cml = *GetCurrentCommandList();
				auto& currentTextures= cml.currentTextures;
				Tex* t=&currentTextures[static_cast<int>(ShaderStageType::Vertex)][i];
				if (t->tex) {
					t->tex->Release();
					t = nullptr;
				}
				if (!(t->sampler->GetDesc() == samplerDesc))
				{
					t->sampler->Release();
					graphicsDevice_->GetDevice()->CreateSampler(samplerDesc, &t->sampler);
				}

				t = &cml.currentTextures[static_cast<int>(ShaderStageType::Pixel)][i];
				if (t->tex) {
					t->tex->Release();
					t = nullptr;
				}
				if (t->sampler->GetDesc() == samplerDesc) {
					return;
				}
				else
				{
					t->sampler->Release();
					graphicsDevice_->GetDevice()->CreateSampler(samplerDesc, &t->sampler);
				}
*/
			}
			//else
			{
				auto t0 = (Tex*)(textures[i]->UserPtr);
				CommandList& cml = *GetCurrentCommandList();
				auto t = &cml.currentTextures[static_cast<int>(ShaderStageType::Pixel)][i];
				auto& sd = shader->TexSrv_;
				//t->texture != t0->texture&&
				if (sd.size()>0) {
					/*StateTransitionDesc Barriers = { t0->texture,         RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_SHADER_RESOURCE, true };
					graphicsDevice_->GetContext()->TransitionResourceStates(1, &Barriers);*/
					{
						t=(t0);
						auto srv = t->GetView(samplerDesc, graphicsDevice_);
						int k = sd.size() - 1;
						int clamp = std::min(k, i);
						bool isbound = sd[clamp]->IsBound(0);
						if (isbound)
							return;
						sd[clamp]->Set(srv);
					}
				}
				/*GetCurrentCommandList()->SetTexture(
					t, ws[(int)state.TextureWrapTypes[i]], fs[(int)state.TextureFilterTypes[i]], i, LLGI::ShaderStageType::Vertex);
				GetCurrentCommandList()->SetTexture(
					t, ws[(int)state.TextureWrapTypes[i]], fs[(int)state.TextureFilterTypes[i]], i, LLGI::ShaderStageType::Pixel);*/
			}
		}
	}
	::Effekseer::ModelLoader* RendererImplemented::CreateModelLoader(::Effekseer::FileInterface* fileInterface)
	{
		return new ModelLoader(graphicsDevice_, fileInterface);
	}
	::Effekseer::MaterialLoader* RendererImplemented::CreateMaterialLoader(::Effekseer::FileInterface* fileInterface)
	{
		return new MaterialLoader(graphicsDevice_, fileInterface);
	}

	Effekseer::TextureData* RendererImplemented::GetBackground()
	{
		if (m_background.UserPtr == nullptr)
			return nullptr;
		return &m_background;
	}

	void RendererImplemented::SetBackground(Tex* background)
	{
		ES_SAFE_ADDREF(background);

		auto p = (Tex*)m_background.UserPtr;
		ES_SAFE_RELEASE(p);
		m_background.UserPtr = background;
	}
	/*void RendererImplemented::SetBackground(Tex* background)
	{
		ES_SAFE_ADDREF(background);

		auto p = (Tex*)m_background.UserPtr;
		ES_SAFE_RELEASE(p);
		m_background.UserPtr = background;
	}*/
	void RendererImplemented::SetBackgroundTexture(Effekseer::TextureData* textuerData) {

		if (textuerData == nullptr)
		{
			auto back = (Tex*)m_background.UserPtr;
			ES_SAFE_RELEASE(back);
			m_background.UserPtr = nullptr;
			return;
		}

		auto texture = static_cast<Tex*>(textuerData->UserPtr);
		ES_SAFE_ADDREF(texture);

		auto back = (Tex*)m_background.UserPtr;
		ES_SAFE_RELEASE(back);

		m_background.UserPtr = texture;
	}

	void RendererImplemented::SetDistortingCallback(EffekseerRenderer::DistortingCallback* callback)
	{
		ES_SAFE_DELETE(m_distortingCallback);
		m_distortingCallback = callback;
	}
	void RendererImplemented::BeginShader(Shader* shader) {
		currentShader = shader;
		Barriers.clear();
	}

	void RendererImplemented::EndShader(Shader* shader) { currentShader = nullptr; }
	Effekseer::TextureData* RendererImplemented::CreateProxyTexture(EffekseerRenderer::ProxyTextureType type)
	{
		using namespace Diligent;
		using namespace EffekseerRendererDE;
		std::array<uint8_t, 4> buf;

		static constexpr Uint32 TexDim = 16;
		std::array<Uint32, TexDim* TexDim>     Data;
		if (type == EffekseerRenderer::ProxyTextureType::White)
		{
			buf.fill(255);
			for (size_t i = 0; i < Data.size(); i++)
			{
				std::memcpy(&Data[i], buf.data(), 4);
			}
		}
		else if (type == EffekseerRenderer::ProxyTextureType::Normal)
		{
			buf.fill(127);
			buf[2] = 255;
			buf[3] = 255;
			for (size_t i = 0; i < Data.size(); i++)
			{
				std::memcpy(&Data[i], buf.data(), 4);
			}
		}
		else
		{
			assert(0);
		}
		Diligent::TextureDesc TexDesc;
		TexDesc.Name = "White texture for Effekseer renderer";
		TexDesc.Type = RESOURCE_DIM_TEX_2D;
		TexDesc.Usage = USAGE_STATIC;
		TexDesc.BindFlags = BIND_SHADER_RESOURCE;
		TexDesc.Width = 16;
		TexDesc.Height = 16;
		TexDesc.Format = TEX_FORMAT_RGBA8_UNORM;
		TexDesc.MipLevels = 1;
		TextureSubResData       Level0Data{ Data.data(), TexDim * 4 };
		TextureData             InitData{ &Level0Data, 1 };
		GraphicsDE* graphicsDevice = graphicsDevice_;
		auto texture = Tex::CreateTexture(graphicsDevice, TexDesc, InitData);
		auto textureData = new Effekseer::TextureData();
		textureData->UserPtr = texture;
		textureData->UserID = 0;
		textureData->TextureFormat = Effekseer::TextureFormatType::ABGR8;
		textureData->Width = 16;
		textureData->Height = 16;
		StateTransitionDesc Barriers[] =
		{
			{texture->texture,  RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_SHADER_RESOURCE, true}
		};
		// clang-format on
		graphicsDevice->GetContext()->TransitionResourceStates(_countof(Barriers), Barriers);
		return textureData;
	}
	void RendererImplemented::ResetRenderState()
	{
		m_renderState->GetActiveState().Reset();
		m_renderState->Update(true);
	}
	bool Model::LoadToGPU()
	{

		if (IsLoadedOnGPU)
		{
			return false;
		}
		constexpr auto maxb = 32;
		std::array<StateTransitionDesc, maxb> barr;
		int c = 0;
		//std::vector<StateTransitionDesc> Barriers;
		for (int32_t f = 0; f < GetFrameCount(); f++)
		{
			InternalModels[f].VertexCount = GetVertexCount(f);

			{
				std::vector<Effekseer::Model::VertexWithIndex> vs;
				for (int32_t m = 0; m < ModelCount; m++)
				{
					for (int32_t i = 0; i < GetVertexCount(f); i++)
					{
						Effekseer::Model::VertexWithIndex v;
						v.Position = GetVertexes(f)[i].Position;
						v.Normal = GetVertexes(f)[i].Normal;
						v.Binormal = GetVertexes(f)[i].Binormal;
						v.Tangent = GetVertexes(f)[i].Tangent;
						v.UV = GetVertexes(f)[i].UV;
						v.VColor = GetVertexes(f)[i].VColor;
						v.Index[0] = m;

						vs.push_back(v);
					}
				}

				if (InternalModels[f].VertexBuffer)
					continue;
				auto vb_size = sizeof(Effekseer::Model::VertexWithIndex) * GetVertexCount(f) * ModelCount;
				IBuffer* bf = nullptr;
				BufferDesc BuffDesc;
				BuffDesc.Name = "Effekseer Model vertex buffer";
				BuffDesc.Usage = USAGE_DEFAULT;
				BuffDesc.BindFlags = BIND_VERTEX_BUFFER;
				BuffDesc.uiSizeInBytes = sizeof(Effekseer::Model::VertexWithIndex) * vs.size();
				BuffDesc.ElementByteStride = sizeof(Effekseer::Model::VertexWithIndex);
				BufferData VBData;
				VBData.pData = vs.data();
				VBData.DataSize = BuffDesc.uiSizeInBytes;
				graphicsDevice_->GetDevice()->CreateBuffer(BuffDesc, &VBData, &bf);
				InternalModels[f].VertexBuffer = bf;
				barr[c++] = { bf,RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_VERTEX_BUFFER, true };
			}

			InternalModels[f].FaceCount = GetFaceCount(f);
			InternalModels[f].IndexCount = InternalModels[f].FaceCount * 3;

			{
				std::vector<Effekseer::Model::Face> fs;
				for (int32_t m = 0; m < ModelCount; m++)
				{
					for (int32_t i = 0; i < InternalModels[f].FaceCount; i++)
					{
						Effekseer::Model::Face face;
						face.Indexes[0] = GetFaces(f)[i].Indexes[0] + GetVertexCount(f) * m;
						face.Indexes[1] = GetFaces(f)[i].Indexes[1] + GetVertexCount(f) * m;
						face.Indexes[2] = GetFaces(f)[i].Indexes[2] + GetVertexCount(f) * m;
						fs.push_back(face);
					}
				}
				if (InternalModels[f].IndexBuffer)
					continue;
				IBuffer* bf = nullptr;
				BufferDesc BuffDesc;
				BuffDesc.Name = "Effekseer Model index buffer";
				BuffDesc.Usage = USAGE_DEFAULT;
				BuffDesc.BindFlags = BIND_INDEX_BUFFER;
				BuffDesc.uiSizeInBytes = sizeof(int32_t) * 3 * InternalModels[f].FaceCount * ModelCount;
				BuffDesc.ElementByteStride = sizeof(int32_t) ;
				BufferData VBData;
				VBData.pData = fs.data();
				VBData.DataSize = BuffDesc.uiSizeInBytes;

				graphicsDevice_->GetDevice()->CreateBuffer(BuffDesc, &VBData, &bf);
				InternalModels[f].IndexBuffer = bf;
				barr[c++] = { InternalModels[f].IndexBuffer, RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_INDEX_BUFFER, true };
				//Barriers.emplace_back(InternalModels[f].IndexBuffer, RESOURCE_STATE_UNKNOWN, RESOURCE_STATE_SHADER_RESOURCE, true);
			}
		}
		assert(c < maxb);
		graphicsDevice_->GetContext()->TransitionResourceStates(c, barr.data());
		IsLoadedOnGPU = true;
		return true;
	}
	/*bool Model::LoadToGPU()
	{
		if (IsLoadedOnGPU)
		{
			return false;
		}

		for (int32_t f = 0; f < GetFrameCount(); f++)
		{
			InternalModels[f].VertexCount = GetVertexCount(f);

			{
				std::vector<Effekseer::Model::VertexWithIndex> vs;
				for (int32_t m = 0; m < ModelCount; m++)
				{
					for (int32_t i = 0; i < GetVertexCount(f); i++)
					{
						Effekseer::Model::VertexWithIndex v;
						v.Position = GetVertexes(f)[i].Position;
						v.Normal = GetVertexes(f)[i].Normal;
						v.Binormal = GetVertexes(f)[i].Binormal;
						v.Tangent = GetVertexes(f)[i].Tangent;
						v.UV = GetVertexes(f)[i].UV;
						v.VColor = GetVertexes(f)[i].VColor;
						v.Index[0] = m;

						vs.push_back(v);
					}
				}

				auto vb_size = sizeof(Effekseer::Model::VertexWithIndex) * GetVertexCount(f) * ModelCount;
				IBuffer* vertexBuffer = nullptr;
				BufferDesc VertBuffDesc;
				VertBuffDesc.Name = "Effekseer Model vertex buffer";
				VertBuffDesc.Usage = USAGE_DYNAMIC;
				VertBuffDesc.BindFlags = BIND_VERTEX_BUFFER;
				VertBuffDesc.uiSizeInBytes = sizeof(Effekseer::Model::VertexWithIndex) * vs.size();
				BufferData VBData;
				VBData.pData = vs.data();
				VBData.DataSize = VertBuffDesc.uiSizeInBytes;
				graphicsDevice_->GetDevice()->CreateBuffer(VertBuffDesc, nullptr, &vertexBuffer);
				InternalModels[f].VertexBuffer = vertexBuffer;

				void* mapped_ = nullptr;
				graphicsDevice_->GetContext()->MapBuffer(vertexBuffer, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, (PVoid&)mapped_);

				memcpy(mapped_, vs.data(), sizeof(Effekseer::Model::VertexWithIndex) * vs.size());
			}

			InternalModels[f].FaceCount = GetFaceCount(f);
			InternalModels[f].IndexCount = InternalModels[f].FaceCount * 3;

			{
				std::vector<Effekseer::Model::Face> fs;
				for (int32_t m = 0; m < ModelCount; m++)
				{
					for (int32_t i = 0; i < InternalModels[f].FaceCount; i++)
					{
						Effekseer::Model::Face face;
						face.Indexes[0] = GetFaces(f)[i].Indexes[0] + GetVertexCount(f) * m;
						face.Indexes[1] = GetFaces(f)[i].Indexes[1] + GetVertexCount(f) * m;
						face.Indexes[2] = GetFaces(f)[i].Indexes[2] + GetVertexCount(f) * m;
						fs.push_back(face);
					}
				}
				InternalModels[f].IndexBuffer =
					IndexBuffer::CreateIndexBuffer(graphicsDevice_->GetDevice(), 4, sizeof(int32_t) * 3 * InternalModels[f].FaceCount * ModelCount);

				void* mapped_ = nullptr;
				graphicsDevice_->GetContext()->MapBuffer(InternalModels[f].IndexBuffer, MAP_WRITE, MAP_FLAG_NO_OVERWRITE, (PVoid&)mapped_);

				memcpy(mapped_, fs.data(), sizeof(Effekseer::Model::Face) * fs.size());
			}
		}

		IsLoadedOnGPU = true;
		return true;
	}*/
	void RendererImplemented::SetRenderPassPipelineState(Diligent::IPipelineState* renderPassPipelineState)
	{
		renderPassPipelineState->Release();
		ES_SAFE_RELEASE(renderPassPipelineState_);
		renderPassPipelineState_ = renderPassPipelineState;
		SafeAddRef(renderPassPipelineState_);
	}
	Shader* RendererImplemented::GetShader(bool useTexture, ::Effekseer::RendererMaterialType materialType) const
	{
		if (materialType == ::Effekseer::RendererMaterialType::BackDistortion)
		{
			if (useTexture && GetRenderMode() == Effekseer::RenderMode::Normal)
			{
				return m_shader_distortion;
			}
			else
			{
				return m_shader_distortion;
			}
		}
		else if (materialType == ::Effekseer::RendererMaterialType::Lighting)
		{
			if (useTexture && GetRenderMode() == Effekseer::RenderMode::Normal)
			{
				if (m_shader_lighting != nullptr)
				{
					return m_shader_lighting;
				}
				return m_shader;
			}
			else
			{
				if (m_shader_lighting != nullptr)
				{
					return m_shader_lighting;
				}
				return m_shader;
			}
		}
		else
		{
			return m_shader;
			if (useTexture && GetRenderMode() == Effekseer::RenderMode::Normal)
			{
				return m_shader;
			}
			else
			{
				return m_shader;
			}
		}
	}
	bool RendererImplemented::BeginRendering()
	{
		impl->CalculateCameraProjectionMatrix();

		// initialize states
		m_renderState->GetActiveState().Reset();
		m_renderState->Update(true);

		//if (commandList_ == nullptr)
		//{
		//	GetCurrentCommandList()->Begin();
		//	// GetCurrentCommandList()->BeginRenderPass(nullptr);
		//}

		// reset renderer
		m_standardRenderer->ResetAndRenderingIfRequired();

		return true;
	}
	bool RendererImplemented::EndRendering()
	{
		assert(graphicsDevice_ != NULL);

		// reset renderer
		m_standardRenderer->ResetAndRenderingIfRequired();

		return true;
	}
	void RendererImplemented::SetCommandList(CommandList* commandList)
	{

		/*ES_SAFE_ADDREF(commandList);
		ES_SAFE_RELEASE(commandList_);*/
		//SafeRelease(commandList_);
		//if (commandList) {
		//	/*auto rct=commandList_->currentCommandList_->GetReferenceCounters();
		//	auto srf = rct->GetNumStrongRefs();
		//	commandList_->currentCommandList_ = nullptr;*/
		//}
		//else
		//{
		//	if (commandList_->currentCommandList_)
		//	graphicsDevice_->GetContext()->FinishFrame();
		//}
		//graphicsDevice_->GetContext()->FinishFrame();
		commandList_ = (commandList);
	}
	ITextureView* Tex::GetView(const SamplerDesc samplerDesc, GraphicsDE* graphicsDevice) {
		for (size_t i = 0; i < tvs.size(); i++)
		{
			auto& tv = tvs[i];
			//auto sampler = tvs[i]->GetSampler();
			if (!tv) {
				ISampler* sampler = nullptr;
				TextureViewDesc td;
				td.ViewType = TEXTURE_VIEW_SHADER_RESOURCE;
				//texture->CreateView();
				tv = texture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
				graphicsDevice->GetDevice()->CreateSampler(samplerDesc, &sampler);
				tv->SetSampler(sampler);
				return tv;
			}
			else
				if (tvs[i]->GetSampler()->GetDesc() == samplerDesc) {
					return tv;
				}
		}
		assert(false);
	}
}