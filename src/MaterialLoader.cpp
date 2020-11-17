#include <Effekseer.h>
#include "../Effekseer/Effekseer/Material/Effekseer.MaterialCompiler.h"
#include"EffekseerRendererDE.h"
#include"ShaderGenerator.h"
namespace Effekseer
{
	class Material;
	class CompiledMaterialBinary;
}
namespace DX12
{

#define _DIRECTX12 1
#include "HLSL.h"

}
namespace EffekseerRendererDE
{
	using MaterialShaderType = Effekseer::MaterialShaderType;
	class MaterialShaders{
	private:
		std::array<DataStructure, static_cast<int32_t>(MaterialShaderType::Max)> vertexShaders_;

		std::array<DataStructure, static_cast<int32_t>(MaterialShaderType::Max)> pixelShaders_;

	public:

		void SetVertexShaderData(int type, const DataStructure& data)
		{
			vertexShaders_.at(static_cast<int>(type)) = data;
		}

		void SetPixelShaderData(MaterialShaderType type, const  DataStructure& data) { pixelShaders_.at(static_cast<int>(type)) = data; }

		const DataStructure* GetVertexShaderData(MaterialShaderType type) const { return &vertexShaders_.at(static_cast<int>(type)); }

		int32_t GetVertexShaderSize(MaterialShaderType type) const { return vertexShaders_.at(static_cast<int>(type)).size_bytes(); }

		const DataStructure* GetPixelShaderData(MaterialShaderType type) const { return &pixelShaders_.at(static_cast<int>(type)); }

		int32_t GetPixelShaderSize(MaterialShaderType type) const { return pixelShaders_.at(static_cast<int>(type)).size_bytes(); }

		//int AddRef() override { return ReferenceObject::AddRef(); }

		//int Release() override { return ReferenceObject::Release(); }

		//int GetRef() override { return ReferenceObject::GetRef(); }
	};
	//MaterialLoader ::~MaterialLoader() {
	//	/*ES_SAFE_RELEASE(materialCompiler_);
	//	ES_SAFE_RELEASE(GraphicsDE_);*/
	//}

	::Effekseer::MaterialData* MaterialLoader::Load(const EFK_CHAR* path)
	{
		// code file
		{
			auto binaryPath = std::u16string(path) + u"d";
			std::unique_ptr<Effekseer::FileReader> reader(fileInterface_->OpenRead(binaryPath.c_str()));

			if (reader.get() != nullptr)
			{
				size_t size = reader->GetLength();
				std::vector<char> data;
				data.resize(size);
				reader->Read(data.data(), size);

				auto material = Load(data.data(), (int32_t)size, ::Effekseer::MaterialFileType::Compiled);

				if (material != nullptr)
				{
					return material;
				}
			}
		}

		// code file
		//if (materialCompiler_ != nullptr)
		{
			std::unique_ptr<Effekseer::FileReader> reader(fileInterface_->OpenRead(path));

			if (reader.get() != nullptr)
			{
				size_t size = reader->GetLength();
				std::vector<char> data;
				data.resize(size);
				reader->Read(data.data(), size);

				auto material = Load(data.data(), (int32_t)size, ::Effekseer::MaterialFileType::Code);

				return material;
			}
		}

		return nullptr;
	}

	::Effekseer::MaterialData* MaterialLoader::LoadAcutually(::Effekseer::Material& material, void* binary0)
	{
		auto binary=reinterpret_cast<MaterialShaders*>(binary0);
		auto materialData = new ::Effekseer::MaterialData();
		materialData->IsSimpleVertex = material.GetIsSimpleVertex();
		materialData->IsRefractionRequired = material.GetHasRefraction();

		std::array<Effekseer::MaterialShaderType, 2> shaderTypes;
		std::array<Effekseer::MaterialShaderType, 2> shaderTypesModel;

		shaderTypes[0] = Effekseer::MaterialShaderType::Standard;
		shaderTypes[1] = Effekseer::MaterialShaderType::Refraction;
		shaderTypesModel[0] = Effekseer::MaterialShaderType::Model;
		shaderTypesModel[1] = Effekseer::MaterialShaderType::RefractionModel;
		int32_t shaderTypeCount = 1;

		if (material.GetHasRefraction())
		{
			shaderTypeCount = 2;
		}
		for (int32_t st = 0; st < shaderTypeCount; st++)
		{
			Shader* shader = nullptr;
			auto parameterGenerator = EffekseerRenderer::MaterialShaderParameterGenerator(material, false, st, 1);

			if (materialData->IsSimpleVertex)
			{
				/*LLGI::CompilerResult resultVS;
				LLGI::CompilerResult resultPS;

				Deserialize((uint8_t*)binary->GetVertexShaderData(shaderTypes[st]), binary->GetVertexShaderSize(shaderTypes[st]), resultVS);
				Deserialize((uint8_t*)binary->GetPixelShaderData(shaderTypes[st]), binary->GetPixelShaderSize(shaderTypes[st]), resultPS);

				std::array<DataStructure, 4> dataVS;
				std::array<DataStructure, 4> dataPS;

				for (size_t i = 0; i < resultVS.Binary.size(); i++)
				{
					dataVS[i].Data = resultVS.Binary[i].data();
					dataVS[i].Size = resultVS.Binary[i].size();
				}

				for (size_t i = 0; i < resultPS.Binary.size(); i++)
				{
					dataPS[i].Data = resultPS.Binary[i].data();
					dataPS[i].Size = resultPS.Binary[i].size();
				}*/

				// Pos(3) Color(1) UV(2)
				std::vector<LayoutElement>layouts=
				{
				 {0, 0, 3, VT_FLOAT32},
				 {1, 0, 4,  VT_UINT8},
				 {2, 0, 2, VT_FLOAT32}
				};
				IShader* sdd=reinterpret_cast<IShader*>(binary->GetPixelShaderData(shaderTypes[st])->Data);
				sdd->GetDesc().Name;
				shader = Shader::Create(GraphicsDE_,
					binary->GetVertexShaderData(shaderTypes[st]),
					binary->GetPixelShaderData(shaderTypes[st]),
					sdd->GetDesc().Name,
					layouts,
					true);
			}
			else
			{/*
				LLGI::CompilerResult resultVS;
				LLGI::CompilerResult resultPS;

				Deserialize((uint8_t*)binary->GetVertexShaderData(shaderTypes[st]), binary->GetVertexShaderSize(shaderTypes[st]), resultVS);
				Deserialize((uint8_t*)binary->GetPixelShaderData(shaderTypes[st]), binary->GetPixelShaderSize(shaderTypes[st]), resultPS);

				std::array<DataStructure, 4> dataVS;
				std::array<DataStructure, 4> dataPS;

				for (size_t i = 0; i < resultVS.Binary.size(); i++)
				{
					dataVS[i].Data = resultVS.Binary[i].data();
					dataVS[i].Size = resultVS.Binary[i].size();
				}

				for (size_t i = 0; i < resultPS.Binary.size(); i++)
				{
					dataPS[i].Data = resultPS.Binary[i].data();
					dataPS[i].Size = resultPS.Binary[i].size();
				}*/

				// Pos(3) Color(1) Normal(1) Tangent(1) UV(2) UV(2)
				std::vector<VertexLayout> layouts =
				{
				 {0, 0, 3, VT_FLOAT32},
				 {1, 0, 4,  VT_UINT8},
				 {2, 0, 4,  VT_UINT8},
				 {3, 0, 4,  VT_UINT8},
				 {4, 0, 2, VT_FLOAT32},
				 {5, 0, 2, VT_FLOAT32},
				};
				/*layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "POSITION", 0 });
				layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 0 });
				layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 1 });
				layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 2 });
				layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 0 });
				layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 1 });*/

				int32_t offset = 40;
				int count = 6;
				int index = 2;

				auto getFormat = [](int32_t i, Uint32 sec) -> VertexLayout {
					
					if (i == 1)
						assert(false);
					if (i == 2)
						return VertexLayout{ sec, 0, 2, VT_FLOAT32 };
					if (i == 3)
						return VertexLayout{ sec, 0, 3, VT_FLOAT32 };
					if (i == 4)
						return  VertexLayout{ sec, 0,4, VT_FLOAT32 };
						return  VertexLayout{ sec, 0,1, VT_FLOAT32 };
				};
				if (material.GetCustomData1Count() > 0)
				{
					layouts.push_back(getFormat(material.GetCustomData1Count(), layouts.size()));

					index++;
					count++;
					offset += sizeof(float) * material.GetCustomData1Count();
				}

				if (material.GetCustomData2Count() > 0)
				{
					layouts.push_back(getFormat(material.GetCustomData2Count(), layouts.size()));

					index++;
					count++;

					offset += sizeof(float) * material.GetCustomData2Count();
				}

				IShader* sdd = reinterpret_cast<IShader*>(binary->GetPixelShaderData(shaderTypes[st])->Data);
				sdd->GetDesc().Name;
				shader = Shader::Create(GraphicsDE_,
					binary->GetVertexShaderData(shaderTypes[st]),
					binary->GetPixelShaderData(shaderTypes[st]),
					sdd->GetDesc().Name,
					layouts,
					true);
				/*shader = Shader::Create(GraphicsDE_,
					binary->GetVertexShaderData(shaderTypes[st]),
					binary->GetPixelShaderData(shaderTypes[st]),
					"MaterialStandardRenderer6",
					layouts,
					true);*/
			}

			if (shader == nullptr)
				return nullptr;

			auto vertexUniformSize = parameterGenerator.VertexShaderUniformBufferSize;
			auto pixelUniformSize = parameterGenerator.PixelShaderUniformBufferSize;

			shader->SetVertexConstantBufferSize(vertexUniformSize);
			shader->SetVertexRegisterCount(vertexUniformSize / (sizeof(float) * 4));

			shader->SetPixelConstantBufferSize(pixelUniformSize);
			shader->SetPixelRegisterCount(pixelUniformSize / (sizeof(float) * 4));

			materialData->TextureCount = material.GetTextureCount();
			materialData->UniformCount = material.GetUniformCount();

			if (st == 0)
			{
				materialData->UserPtr = shader;
			}
			else
			{
				materialData->RefractionUserPtr = shader;
			}
		}

		for (int32_t st = 0; st < shaderTypeCount; st++)
		{
			/*LLGI::CompilerResult resultVS;
			LLGI::CompilerResult resultPS;

			Deserialize(
				(uint8_t*)binary->GetVertexShaderData(shaderTypesModel[st]), binary->GetVertexShaderSize(shaderTypesModel[st]), resultVS);
			Deserialize((uint8_t*)binary->GetPixelShaderData(shaderTypesModel[st]), binary->GetPixelShaderSize(shaderTypesModel[st]), resultPS);

			std::array<DataStructure, 4> dataVS;
			std::array<DataStructure, 4> dataPS;

			for (size_t i = 0; i < resultVS.Binary.size(); i++)
			{
				dataVS[i].Data = resultVS.Binary[i].data();
				dataVS[i].Size = resultVS.Binary[i].size();
			}

			for (size_t i = 0; i < resultPS.Binary.size(); i++)
			{
				dataPS[i].Data = resultPS.Binary[i].data();
				dataPS[i].Size = resultPS.Binary[i].size();
			}*/

			auto parameterGenerator = EffekseerRenderer::MaterialShaderParameterGenerator(material, true, st, 1);

			std::vector<VertexLayout> layouts =
			{
			 {0, 0, 3, VT_FLOAT32},
			 {1, 0, 3,  VT_FLOAT32},
			 {2, 0, 3,  VT_FLOAT32},
			 {3, 0, 3,  VT_FLOAT32},
			 {4, 0, 2, VT_FLOAT32},
			 {5, 0, 2, VT_FLOAT32},
			 {6, 0, 4,  VT_UINT8},
			 {7, 0, 4,  VT_UINT8},
			};
			/*layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "POSITION", 0 });
			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 0 });
			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 1 });
			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32B32_FLOAT, "NORMAL", 2 });
			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R32G32_FLOAT, "TEXCOORD", 0 });
			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UNORM, "NORMAL", 3 });
			layouts.push_back(VertexLayout{ LLGI::VertexLayoutFormat::R8G8B8A8_UINT, "BLENDINDICES", 0 });*/

			// compile
			std::string log;
			IShader* sdd = reinterpret_cast<IShader*>(binary->GetPixelShaderData(shaderTypes[st])->Data);
			sdd->GetDesc().Name;
			auto shader = Shader::Create(GraphicsDE_,
				binary->GetVertexShaderData(shaderTypes[st]),
				binary->GetPixelShaderData(shaderTypes[st]),
				sdd->GetDesc().Name,
				layouts,
				true);
			/*auto shader = Shader::Create(GraphicsDE_,
				binary->GetVertexShaderData(shaderTypes[st]),
				binary->GetPixelShaderData(shaderTypes[st]),
				"MaterialStandardRenderer8",
				layouts,
				true);*/
			if (shader == nullptr)
				return nullptr;

			auto vertexUniformSize = parameterGenerator.VertexShaderUniformBufferSize;
			auto pixelUniformSize = parameterGenerator.PixelShaderUniformBufferSize;

			shader->SetVertexConstantBufferSize(vertexUniformSize);
			shader->SetVertexRegisterCount(vertexUniformSize / (sizeof(float) * 4));

			shader->SetPixelConstantBufferSize(pixelUniformSize);
			shader->SetPixelRegisterCount(pixelUniformSize / (sizeof(float) * 4));

			if (st == 0)
			{
				materialData->ModelUserPtr = shader;
			}
			else
			{
				materialData->RefractionModelUserPtr = shader;
			}
		}

		materialData->CustomData1 = material.GetCustomData1Count();
		materialData->CustomData2 = material.GetCustomData2Count();
		materialData->TextureCount = std::min(material.GetTextureCount(), Effekseer::UserTextureSlotMax);
		materialData->UniformCount = material.GetUniformCount();
		materialData->ShadingModel = material.GetShadingModel();

		for (int32_t i = 0; i < materialData->TextureCount; i++)
		{
			materialData->TextureWrapTypes.at(i) = material.GetTextureWrap(i);
		}

		return materialData;
	}
 // namespace DX12
	::Effekseer::MaterialData* MaterialLoader::Load(const void* data, int32_t size, Effekseer::MaterialFileType fileType)
	{
		const auto CrSh = [](Effekseer::DirectX::ShaderData& sd, GraphicsDE* graphicsDevice, Effekseer::MaterialShaderType type, MaterialShaders* res) {
			ShaderCreateInfo                               ShaderCI;
			IShader* S = nullptr;
			DataStructure dc;
			static int sdi =0 ;
			auto m_pEngineFactory = graphicsDevice->m_pEngineFactory;
			auto m_pDevice = graphicsDevice->GetDevice();
			ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
			ShaderCI.UseCombinedTextureSamplers = true;
			ShaderCI.Source = sd.CodeVS.c_str();
			ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
			ShaderCI.Desc.Name = "Effekseer Material SHADER_TYPE_VERTEX";
			ShaderCI.EntryPoint = "main";
			m_pDevice->CreateShader(ShaderCI, (IShader**)(&dc.Data));
			int i = static_cast<int>(type);
			res->SetVertexShaderData(i, dc);
			ShaderCI.Source = sd.CodePS.c_str();
			ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
			char* Name = new char[256];
			std::strcpy(Name, "Effekseer Material SHADER_TYPE_PIXEL  ");
			std::strcat(Name, std::to_string(sdi++).c_str());
			ShaderCI.Desc.Name = Name;
			ShaderCI.EntryPoint = "main";

			std::vector<Diligent::ShaderResourceVariableDesc>& srv=dc._srvd;
			srv.reserve(32);
			dc.Data = nullptr;
			constexpr char* target = "Texture2D";
			auto targetlen = std::strlen(target);
			auto p = std::strstr(sd.CodePS.c_str(), target);
			auto cp = p;
			auto start = sd.CodePS.c_str();
			while (p)
			{
				p += targetlen + 1;
				auto edp = std::strchr(p, ' ');
				std::string nme(p, edp);
				char* nm = new char[256];
				std::strcpy(nm, nme.c_str());
				srv.emplace_back(SHADER_TYPE_PIXEL, nm, SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE);
				//std::getline(std::cin,std::string(p));
				while (cp != start && (--cp)[0] != '\n')
				{
					if ((cp)[0] == '/') {
						p += targetlen;
						p = std::strchr(p, '\n');
						break;
					}
				}
				p = std::strstr(p, target);
				cp = p;
			}
			m_pDevice->CreateShader(ShaderCI, (IShader**)(&dc.Data));
			i = static_cast<int>(type);
			res->SetPixelShaderData(type, dc);
		};
		if (fileType == Effekseer::MaterialFileType::Compiled)
		{
			assert(false);
			//auto compiled = Effekseer::CompiledMaterial();
			//if (!compiled.Load(static_cast<const uint8_t*>(data), size))
			//{
			//	return nullptr;
			//}

			//if (!compiled.GetHasValue(platformType_))
			//{
			//	return nullptr;
			//}

			//// compiled
			//Effekseer::Material material;
			//material.Load((const uint8_t*)compiled.GetOriginalData().data(), static_cast<int32_t>(compiled.GetOriginalData().size()));
			//auto binary = compiled.GetBinary(platformType_);
			return nullptr;
			//return LoadAcutually(material, binary);
		}
		else
		{
		
			Effekseer::Material material0;
			material0.Load((const uint8_t*)data, size);
			auto generator = Effekseer::DirectX::ShaderGenerator(DX12::material_common_define,
				DX12::material_common_vs_functions,
				DX12::material_sprite_vs_pre,
				DX12::material_sprite_vs_pre_simple,
				DX12::model_vs_pre,
				DX12::material_sprite_vs_suf1,
				DX12::material_sprite_vs_suf1_simple,
				DX12::model_vs_suf1,
				DX12::material_sprite_vs_suf2,
				DX12::model_vs_suf2,
				DX12::g_material_ps_pre,
				DX12::g_material_ps_suf1,
				DX12::g_material_ps_suf2_lit,
				DX12::g_material_ps_suf2_unlit,
				DX12::g_material_ps_suf2_refraction,
				Effekseer::DirectX::ShaderGeneratorTarget::DirectX12);
			auto material = &material0;
			auto maximumTextureCount = 6;
			MaterialShaders binary;
			auto type = Effekseer::MaterialShaderType::Refraction;

		
			if (material->GetHasRefraction())
			{
				auto shader = generator.GenerateShader(material, type, maximumTextureCount, 0, 1);
				CrSh(shader, GraphicsDE_, type, &binary);
				type = MaterialShaderType::RefractionModel;
				shader = generator.GenerateShader(material, type, maximumTextureCount, 0, 1);
				CrSh(shader, GraphicsDE_, type, &binary);
			}
			type = Effekseer::MaterialShaderType::Standard;

			auto shader = generator.GenerateShader(material, type, maximumTextureCount, 0, 1);
			CrSh(shader, GraphicsDE_, type, &binary);
			type = Effekseer::MaterialShaderType::Model;
			shader = generator.GenerateShader(material, type, maximumTextureCount, 0, 1);
			CrSh(shader, GraphicsDE_, type, &binary);
			return LoadAcutually(*material, &binary);
		}
	}


void MaterialLoader::Unload(::Effekseer::MaterialData* data)
{
	if (data == nullptr)
		return;
	auto shader = reinterpret_cast<Shader*>(data->UserPtr);
	auto modelShader = reinterpret_cast<Shader*>(data->ModelUserPtr);
	auto refractionShader = reinterpret_cast<Shader*>(data->RefractionUserPtr);
	auto refractionModelShader = reinterpret_cast<Shader*>(data->RefractionModelUserPtr);

	ES_SAFE_DELETE(shader);
	ES_SAFE_DELETE(modelShader);
	ES_SAFE_DELETE(refractionShader);
	ES_SAFE_DELETE(refractionModelShader);
	ES_SAFE_DELETE(data);
}
}