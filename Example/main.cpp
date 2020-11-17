/*
 *  Copyright 2019-2020 Diligent Graphics LLC
 *  Copyright 2015-2019 Egor Yusov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  In no event and under no legal theory, whether in tort (including negligence),
 *  contract, or otherwise, unless required by applicable law (such as deliberate
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental,
 *  or consequential damages of any character arising as a result of this License or
 *  out of the use or inability to use the software (including but not limited to damages
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and
 *  all other commercial damages or losses), even if such Contributor has been advised
 *  of the possibility of such damages.
 */
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef PLATFORM_WIN32
#define PLATFORM_WIN32 1
#endif

#ifndef ENGINE_DLL
#define ENGINE_DLL 1
#endif
 /*
 #ifndef D3D11_SUPPORTED
 #define D3D11_SUPPORTED 1
 #endif

 #ifndef D3D12_SUPPORTED
 #define D3D12_SUPPORTED 1
 #endif

 #ifndef GL_SUPPORTED
 #define GL_SUPPORTED 1
 #endif
 */
 //#include"Common/Math1.h"
  //#include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
  //#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
  //#include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"

#ifndef VULKAN_SUPPORTED
#define VULKAN_SUPPORTED 1
#endif
#include <MapHelper.hpp>
#include <Timer.hpp>
#include"EffekseerRendererDE.h"
#include "Effekseer.h"
#include"FirstPersonCamera.hpp"
#include"InputController.hpp"
//#include <Common\FirstPersonCamera.hpp>
//#include <Common\Math1.h>
namespace fs = std::filesystem;
//namespace {
//	using namespace Diligent;
//	// For this tutorial, we will use simple vertex shader
//	// that creates a procedural triangle
//
//	// Diligent Engine can use HLSL source on all supported platforms.
//	// It will convert HLSL to GLSL in OpenGL mode, while Vulkan backend will compile it directly to SPIRV.
//
//	static const char* VSSource = R"(
//
//struct CameraAttribs
//{
//    float4 f4Position;     // Camera world position
//    float4 f4ViewportSize; // (width, height, 1/width, 1/height)
//
//    float2 f2ViewportOrigin; // (min x, min y)
//    float fNearPlaneZ; 
//    float fFarPlaneZ; // fNearPlaneZ < fFarPlaneZ
//
//#ifdef __cplusplus
//    float4x4 mViewT;
//    float4x4 mProjT;
//    float4x4 mViewProjT;
//    float4x4 mViewInvT;
//    float4x4 mProjInvT;
//    float4x4 mViewProjInvT;
//#else
//    matrix mView;
//    matrix mProj;
//    matrix mViewProj;
//    matrix mViewInv;
//    matrix mProjInv;
//    matrix mViewProjInv;
//#endif
//
//    float4 f4ExtraData[5]; // Any appliation-specific data
//    // Sizeof(CameraAttribs) == 256*2
//};
//
//cbuffer cbCameraAttribs
//{
//    CameraAttribs g_CameraAttribs;
//};
//
//struct PSInput 
//{ 
//    float4 Pos   : SV_POSITION; 
//    float3 Color : COLOR; 
//};
//
//void main(in  uint    VertId : SV_VertexID,
//          out PSInput PSIn) 
//{
//    float4 Pos[3];
//    Pos[0] = float4(-0.5, -0.5, 0.0, 1.0);
//    Pos[1] = float4( 0.0, +0.5, 0.0, 1.0);
//    Pos[2] = float4(+0.5, -0.5, 0.0, 1.0);
//
//    float3 Col[3];
//    Col[0] = float3(1.0, 0.0, 0.0); // red
//    Col[1] = float3(0.0, 1.0, 0.0); // green
//    Col[2] = float3(0.0, 0.0, 1.0); // blue
//
//    PSIn.Pos   =Pos[VertId];// mul(Pos[VertId], g_CameraAttribs.mViewProj); ;
//    PSIn.Color = Col[VertId];
//}
//)";
//
//	// Pixel shader simply outputs interpolated vertex color
//	static const char* PSSource = R"(
//Texture2D g_ColorMap;
//SamplerState g_ColorMap_sampler;
//struct PSInput 
//{ 
//    float4 Pos   : SV_POSITION; 
//    float3 Color : COLOR; 
//};
//
//struct PSOutput
//{ 
//    float4 Color : SV_TARGET; 
//};
//
//void main(in  PSInput  PSIn,
//          out PSOutput PSOut)
//{
//    PSOut.Color = float4(PSIn.Color.rgb, 1.0);
//}
//)";
//
//	namespace efs = EffekseerRendererDE;
//	class Tutorial00App
//	{
//	public:
//		Tutorial00App()
//		{
//		}
//		~Tutorial00App()
//		{
//			
//			//m_pImmediateContext->Flush();
//		}
//		Diligent::float4x4 GetSurfacePretransformMatrix(const Diligent::float3& f3CameraViewAxis) const
//		{
//			const auto& SCDesc = m_pSwapChain->GetDesc();
//			constexpr auto PI_F =3.14159265354;
//			switch (SCDesc.PreTransform)
//			{
//			case SURFACE_TRANSFORM_ROTATE_90:
//				// The image content is rotated 90 degrees clockwise.
//				return Diligent::float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F / 2.f);
//
//			case SURFACE_TRANSFORM_ROTATE_180:
//				// The image content is rotated 180 degrees clockwise.
//				return Diligent::float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F);
//
//			case SURFACE_TRANSFORM_ROTATE_270:
//				// The image content is rotated 270 degrees clockwise.
//				return Diligent::float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F * 3.f / 2.f);
//
//			case SURFACE_TRANSFORM_OPTIMAL:
//				UNEXPECTED("SURFACE_TRANSFORM_OPTIMAL is only valid as parameter during swap chain initialization.");
//				return Diligent::float4x4::Identity();
//
//			case SURFACE_TRANSFORM_HORIZONTAL_MIRROR:
//			case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90:
//			case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180:
//			case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270:
//				UNEXPECTED("Mirror transforms are not supported");
//				return Diligent::float4x4::Identity();
//
//			default:
//				return Diligent::float4x4::Identity();
//			}
//		}
//		bool InitializeDiligentEngine(HWND hWnd)
//		{
//			SwapChainDesc SCDesc;
//			//SCDesc.a = TEX_FORMAT_RGBA8_UNORM;
//			switch (RENDER_DEVICE_TYPE_VULKAN)
//			{
//#if D3D11_SUPPORTED
//			case RENDER_DEVICE_TYPE_D3D11:
//			{
//				EngineD3D11CreateInfo EngineCI;
//#ifdef DILIGENT_DEBUG
//				EngineCI.DebugFlags |=
//					D3D11_DEBUG_FLAG_CREATE_DEBUG_DEVICE |
//					D3D11_DEBUG_FLAG_VERIFY_COMMITTED_SHADER_RESOURCES;
//#endif
//#if ENGINE_DLL
//				// Load the dll and import GetEngineFactoryD3D11() function
//				auto GetEngineFactoryD3D11 = LoadGraphicsEngineD3D11();
//#endif
//				auto* pFactoryD3D11 = GetEngineFactoryD3D11();
//				pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
//				Win32NativeWindow Window{ hWnd };
//				pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
//			}
//			break;
//#endif
//
//#if D3D12_SUPPORTED
//			case RENDER_DEVICE_TYPE_D3D12:
//			{
//#if ENGINE_DLL
//				// Load the dll and import GetEngineFactoryD3D12() function
//				auto GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
//#endif
//				EngineD3D12CreateInfo EngineCI;
//#ifdef DILIGENT_DEBUG
//				// There is a bug in D3D12 debug layer that causes memory leaks in this tutorial
//				//EngineCI.EnableDebugLayer = true;
//#endif
//				auto* pFactoryD3D12 = GetEngineFactoryD3D12();
//				pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
//				Win32NativeWindow Window{ hWnd };
//				pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
//			}
//			break;
//#endif
//
//#if GL_SUPPORTED
//			case RENDER_DEVICE_TYPE_GL:
//			{
//
//#if EXPLICITLY_LOAD_ENGINE_GL_DLL
//				// Load the dll and import GetEngineFactoryOpenGL() function
//				auto GetEngineFactoryOpenGL = LoadGraphicsEngineOpenGL();
//#endif
//				auto* pFactoryOpenGL = GetEngineFactoryOpenGL();
//
//				EngineGLCreateInfo EngineCI;
//				EngineCI.Window.hWnd = hWnd;
//#ifdef DILIGENT_DEBUG
//				EngineCI.CreateDebugContext = true;
//#endif
//				pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc, &m_pSwapChain);
//			}
//			break;
//#endif
//
//#if VULKAN_SUPPORTED
//			case RENDER_DEVICE_TYPE_VULKAN:
//			{
//#if EXPLICITLY_LOAD_ENGINE_VK_DLL
//				// Load the dll and import GetEngineFactoryVk() function
//				auto GetEngineFactoryVk = LoadGraphicsEngineVk();
//#endif
//				EngineVkCreateInfo EngineCI;
//				EngineCI.DynamicHeapSize = 8 << 22;
//				EngineCI.NumDeferredContexts = std::max(std::thread::hardware_concurrency() - 1, 2u);
//#ifdef DILIGENT_DEBUG
//				EngineCI.EnableValidation = true;
//#endif
//				auto* pFactoryVk = GetEngineFactoryVk();
//				ppContexts.resize(1 + EngineCI.NumDeferredContexts);
//				pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &ppContexts[0]);
//				m_pImmediateContext.Attach(ppContexts[0]);
//				m_pEngineFactory = pFactoryVk;
//				if (!m_pSwapChain && hWnd != nullptr)
//				{
//					Win32NativeWindow Window{ hWnd };
//					pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
//				}
//			}
//			break;
//#endif
//
//			default:
//				//// Load the dll and import GetEngineFactoryVk() function
//				//auto GetEngineFactoryVk = LoadGraphicsEngineVk();
//				//EngineVkCreateInfo EngineCI;
//				//auto* pFactoryVk = GetEngineFactoryVk();
//				//pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);
//				//m_pEngineFactory = pFactoryVk;
//				//if (!m_pSwapChain && hWnd != nullptr)
//				//{
//				//	Win32NativeWindow Window{ hWnd };
//				//	pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
//				//}
//			
//				break;
//			}
//			/*float3 Translation(1.0, 2, 1);
//			float3 Scaling(1.0, 2, 1);
//			aiQuaternion RotationQ(2,34,31);
//
//			auto NodeTransformation1 = math::Translation3f(math::Map< math::float3>(&Translation[0])) *
//				math::quaternion(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z) *
//				Eigen::Scaling(math::Map< math::float3>(&Scaling[0]));
//
//			auto NodeTransformation2 = math::Translation3f(math::Map< math::float3>(&Translation[0])) *
//				math::quaternion(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z) *
//				Eigen::Scaling(math::Map< math::float3>(&Scaling[0]));*/
//
//			//m_pDevice->CreatePipelineState(m_pImGui->)
//			auto dm4 = GetSurfacePretransformMatrix(Diligent::float3(0, 1, 2));
//			auto axis = Diligent::float3(0, 1, 2);
//			auto dr90 = Diligent::float4x4::RotationArbitrary(axis, -PI_F / 2.f);
//			//m_Camera.SetPos(Diligent::float3(5, 5, 0.f));
//
//			m_Camera.SetPos(Diligent::float3(30, -30, 70));
//			m_Camera.m_fYawAngle = 4;
//			m_Camera.m_fPitchAngle = -1;
//			//m_Camera.SetRotation(PI_F / 2.f, 0);
//			m_Camera.SetRotationSpeed(0.005f);
//			m_Camera.SetMoveSpeed(5.f);
//			m_Camera.SetSpeedUpScales(5.f, 10.f);
//			m_Camera.SrfPreTransform= GetSurfacePretransformMatrix(Diligent::float3{ 0, 0, 1 });
//			WindowResize(m_pSwapChain->GetDesc().Width, m_pSwapChain->GetDesc().Height);
//			CreateUniformBuffer(m_pDevice, 256 * 2, "Camera attribs buffer", &m_CameraAttribsCB);
//			gd.graphicsDevice = m_pDevice;
//			gd.ImmediateContext = m_pImmediateContext;
//			gd.m_pEngineFactory = m_pEngineFactory;
//			gd.m_pSwapChain = m_pSwapChain;
//			auto ps = fs::current_path().string();
//			std::vector<char> p2(ps.size() + 100);
//			ps.copy(&p2[0], ps.size());
//			fs::path curdir(&p2[0]);
//			curdir /= "..";
//			curdir /= "src";
//			curdir = curdir/ "Shader";
//			curdir += fs::path::preferred_separator;
//			renderer = efs::Create(&gd, &m_pSwapChain->GetDesc().ColorBufferFormat, 1, m_pSwapChain->GetDesc().DepthBufferFormat,
//				false, 8000, curdir);
//			constexpr int swapBufferCount = 2;
//			sfMemoryPoolEfk = efs::SingleFrameMemoryPool::CreateSingleFrameMemoryPool(&gd, 1024 * 1024 * 8,m_pSwapChain->GetDesc().BufferCount);
//			commandListEfk = new efs::CommandList(sfMemoryPoolEfk);
//			manager = Effekseer::Manager::Create(8000);
//			// Sprcify rendering modules
//	// 描画モジュールの設定
//			manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
//			manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
//			manager->SetRingRenderer(renderer->CreateRingRenderer());
//			manager->SetTrackRenderer(renderer->CreateTrackRenderer());
//			manager->SetModelRenderer(renderer->CreateModelRenderer());
//
//			// Specify a texture, model and material loader
//			// It can be extended by yourself. It is loaded from a file on now.
//			// テクスチャ、モデル、マテリアルローダーの設定する。
//			// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
//			manager->SetTextureLoader(renderer->CreateTextureLoader());
//			manager->SetModelLoader(renderer->CreateModelLoader());
//			manager->SetMaterialLoader(renderer->CreateMaterialLoader());
//			char16_t pth[100]  = u"R:/Effekseer152mWin/Sample/02_Tktk03/ToonHit.efkefc";
//			effect = Effekseer::Effect::Create(manager,pth);
//			auto bc=m_pSwapChain->GetDesc().BufferCount;
//			return true;
//		}
//	
//		RefCntAutoPtr<IEngineFactory>              m_pEngineFactory;
//		RefCntAutoPtr<IBuffer>                             m_CameraAttribsCB;
//		RefCntAutoPtr<IBuffer>                             m_LightAttribsCB;
//
//		InputController m_InputController;
//		Camera m_Camera;
//		
//		bool ProcessCommandLine(const char* CmdLine)
//		{
//			const auto* Key = "-mode ";
//			const auto* pos = strstr(CmdLine, Key);
//			if (pos != nullptr)
//			{
//				pos += strlen(Key);
//				if (_stricmp(pos, "D3D11") == 0)
//				{
//#if D3D11_SUPPORTED
//					m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
//#else
//					std::cerr << "Direct3D11 is not supported. Please select another device type";
//					return false;
//#endif
//				}
//				else if (_stricmp(pos, "D3D12") == 0)
//				{
//#if D3D12_SUPPORTED
//					m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
//#else
//					std::cerr << "Direct3D12 is not supported. Please select another device type";
//					return false;
//#endif
//				}
//				else if (_stricmp(pos, "GL") == 0)
//				{
//#if GL_SUPPORTED
//					m_DeviceType = RENDER_DEVICE_TYPE_GL;
//#else
//					std::cerr << "OpenGL is not supported. Please select another device type";
//					return false;
//#endif
//				}
//				else if (_stricmp(pos, "VK") == 0)
//				{
//#if VULKAN_SUPPORTED
//					m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
//#else
//					std::cerr << "Vulkan is not supported. Please select another device type";
//					return false;
//#endif
//				}
//				else
//				{
//					std::cerr << "Unknown device type. Only the following types are supported: D3D11, D3D12, GL, VK";
//					return false;
//				}
//			}
//			else
//			{
//#if D3D12_SUPPORTED
//				m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
//#elif VULKAN_SUPPORTED
//				m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
//#elif D3D11_SUPPORTED
//				m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
//#elif GL_SUPPORTED
//				m_DeviceType = RENDER_DEVICE_TYPE_GL;
//#endif
//			}
//			return true;
//		}
//
//		struct CameraAttribs
//		{
//			using float4 = Diligent::float4;
//			using float2 = Diligent::float2;
//			float4 f4Position;     // Camera world position
//			float4 f4ViewportSize; // (width, height, 1/width, 1/height)
//
//			float2 f2ViewportOrigin; // (min x, min y)
//			float fNearPlaneZ;
//			float fFarPlaneZ; // fNearPlaneZ < fFarPlaneZ
//
//#ifdef __cplusplus
//			float4x4 mViewT;
//			float4x4 mProjT;
//			float4x4 mViewProjT;
//			float4x4 mViewInvT;
//			float4x4 mProjInvT;
//			float4x4 mViewProjInvT;
//#else
//			matrix mView;
//			matrix mProj;
//			matrix mViewProj;
//			matrix mViewInv;
//			matrix mProjInv;
//			matrix mViewProjInv;
//#endif
//
//			float4 f4ExtraData[5]; // Any appliation-specific data
//			// Sizeof(CameraAttribs) == 256*2
//		};
//		struct instData
//		{
//			using float4 = Diligent::float4;
//			uint bonelength;
//			uint frameIndex;
//			uint transformid;
//			uint base;
//			// float transitionProgress;
//			float4 color;
//		};
//		std::vector<instData> squareinst;
//
//		RefCntAutoPtr<IShaderResourceBinding> m_pSRB;
//		double m_CurrentTime;
//		float  m_fSmoothFPS = 0;
//		double m_LastFPSTime = 0;
//		Uint32 m_NumFramesRendered = 0;
//		Uint32 m_CurrentFrameNumber = 0;
//		bool m_ShowDemoWindow = true;
//		int maxIns = 1000;
//		double lastclick = -1;
//		void Update(double CurrTime = 0, double ElapsedTime = 0) {
//			const auto& SCDesc = m_pSwapChain->GetDesc();
//
//			m_CurrentTime = CurrTime;
//			
//			m_Camera.Update(m_InputController, static_cast<float>(ElapsedTime));
//			//cont.Update();
//
//			static int posmapsize = 0; 
//			const auto& mouseState = m_InputController.GetMouseState();
//			static double ClickCounter = -9;
//			static bool keydown = false;
//			
//			if (m_pDevice)
//			{
//				++m_NumFramesRendered;
//				++m_CurrentFrameNumber;
//				static const double dFPSInterval = 0.5;
//				if (CurrTime - m_LastFPSTime > dFPSInterval)
//				{
//					m_fSmoothFPS = static_cast<float>(m_NumFramesRendered / (CurrTime - m_LastFPSTime));
//					m_NumFramesRendered = 0;
//					m_LastFPSTime = CurrTime;
//				}
//			}
//		}
//		
//		int Currinstancenum = 0;
//		int time = 0;
//		Effekseer::Handle handle = 0;
//		void Render()
//		{
//			// Note that Present() unbinds the back buffer if it is set as render target.
//			ITextureView* pRTV0 = m_pSwapChain->GetCurrentBackBufferRTV();
//			ITextureView* pDSV0 = m_pSwapChain->GetDepthBufferDSV();
//			const float ClearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
//			auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
//			auto* pDSV = m_pSwapChain->GetDepthBufferDSV();
//			// Set render targets before issuing any draw command.
//			m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
//			auto SrfPreTransform = GetSurfacePretransformMatrix(Diligent::float3{ 0, 0, 1 });
//			//no transpose need since has differ mul order in shader
//			renderer->SetProjectionMatrix(reinterpret_cast<const Effekseer::Matrix44&>((m_Camera.GetProjMatrix())));
//			renderer->SetCameraMatrix(reinterpret_cast<const Effekseer::Matrix44&>    ((m_Camera.GetViewMatrix())));
//			// Clear the back buffer
//			m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
//			m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
//			auto rd = static_cast<EffekseerRendererDE::RendererImplemented*> (renderer);
//
//			{
//				MapHelper<CameraAttribs> CamAttribs(m_pImmediateContext, m_CameraAttribsCB, MAP_WRITE, MAP_FLAG_DISCARD);
//				(CamAttribs->mProjT) = (m_Camera.GetProjMatrix().Transpose());
//				CamAttribs->mViewProjT = m_Camera.CameraViewProj;
//				CamAttribs->mViewProjInvT = m_Camera.CameraViewProj.Inverse();
//				CamAttribs->f4Position = Diligent::float4(Diligent::float3::MakeVector(m_Camera.GetWorldMatrix()[3]), 1);
//				//= ex;
//			}
//			sfMemoryPoolEfk->NewFrame();
//			rd->SetCommandList(commandListEfk);
//			if (time % 120 == 0)
//			{
//				// Play an effect
//				// エフェクトの再生
//				handle = manager->Play(effect, 0, 0, 0);
//			}
//
//			if (time % 120 == 119)
//			{
//				// Stop effects
//				// エフェクトの停止
//				manager->StopEffect(handle);
//			}
//
//			// Move the effect
//			// エフェクトの移動
//			manager->AddLocation(handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));
//
//			// Update the manager
//			// マネージャーの更新
//			manager->Update();
//
//			// Begin to rendering effects
//			// エフェクトの描画開始処理を行う。
//			renderer->BeginRendering();
//
//			// Render effects
//			// エフェクトの描画を行う。
//			manager->Draw();
//
//			// Finish to rendering effects
//			// エフェクトの描画終了処理を行う。
//			renderer->EndRendering();
//			// Finish a command list
//			// コマンドリストを終了する。
//			if (commandListEfk->currentCommandList_)
//				m_pImmediateContext->ExecuteCommandList(commandListEfk->currentCommandList_);
//			//rd->SetCommandList(nullptr);
//			time++;
//
//		}
//
//		void Present()
//		{
//			m_pSwapChain->Present();
//		}
//
//		void WindowResize(Uint32 Width, Uint32 Height)
//		{
//			if (!m_pSwapChain)
//				return;
//			m_pSwapChain->Resize(Width, Height);
//
//			auto SCDesc = m_pSwapChain->GetDesc();
//
//			const auto PI_F = PI;
//			float NearPlane = 0.1f;
//			float FarPlane = 1000.f;
//			//float AspectRatio = static_cast<float>(SCDesc.Width) / static_cast<float>(SCDesc.Height);
//			m_Camera.SetProjAttribs(NearPlane, FarPlane, SCDesc.Width, SCDesc.Height, PI_F / 4.f,
//				m_pSwapChain->GetDesc().PreTransform, m_pDevice->GetDeviceCaps().IsGLDevice());
//			
//		}
//
//		RENDER_DEVICE_TYPE GetDeviceType() const { return m_DeviceType; }
//
//	private:
//		efs::GraphicsDE gd;
//		Effekseer::Manager* manager;
//		EffekseerRenderer::Renderer* renderer;
//		Effekseer::Effect* effect;
//		efs::SingleFrameMemoryPool* sfMemoryPoolEfk;
//		efs::CommandList* commandListEfk;
//		RefCntAutoPtr<IRenderDevice> m_pDevice;
//		RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
//		RefCntAutoPtr<ISwapChain> m_pSwapChain;
//		RefCntAutoPtr<IPipelineState> m_pPSO;
//		RefCntAutoPtr<IPipelineState> m_uiPSO;
//		std::vector<IDeviceContext*> ppContexts;
//		RENDER_DEVICE_TYPE m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
//	};
//
//}
//std::unique_ptr<Tutorial00App> g_pTheApp;

#include "Common/interface/RefCntAutoPtr.hpp"
#include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"

#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"


using namespace Diligent;

// For this tutorial, we will use simple vertex shader
// that creates a procedural triangle

// Diligent Engine can use HLSL source on all supported platforms.
// It will convert HLSL to GLSL in OpenGL mode, while Vulkan backend will compile it directly to SPIRV.

static const char* VSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};
void main(in  uint    VertId : SV_VertexID,
          out PSInput PSIn) 
{
    float4 Pos[3];
    Pos[0] = float4(-0.5, -0.5, 0.0, 1.0);
    Pos[1] = float4( 0.0, +0.5, 0.0, 1.0);
    Pos[2] = float4(+0.5, -0.5, 0.0, 1.0);
    float3 Col[3];
    Col[0] = float3(1.0, 0.0, 0.0); // red
    Col[1] = float3(0.0, 1.0, 0.0); // green
    Col[2] = float3(0.0, 0.0, 1.0); // blue
    PSIn.Pos   = Pos[VertId];
    PSIn.Color = Col[VertId];
}
)";

// Pixel shader simply outputs interpolated vertex color
static const char* PSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};
struct PSOutput
{ 
    float4 Color : SV_TARGET; 
};
void main(in  PSInput  PSIn,
          out PSOutput PSOut)
{
    PSOut.Color = float4(PSIn.Color.rgb, 1.0);
}
)";

namespace efs = EffekseerRendererDE;
class Tutorial00App
{
public:
    Tutorial00App()
    {
    }

    ~Tutorial00App()
    {
        m_pImmediateContext->Flush();
    }

    bool InitializeDiligentEngine(HWND hWnd)
    {
        SwapChainDesc SCDesc;
        switch (m_DeviceType)
        {
#if D3D11_SUPPORTED
        case RENDER_DEVICE_TYPE_D3D11:
        {
            EngineD3D11CreateInfo EngineCI;
#    ifdef DILIGENT_DEBUG
            EngineCI.DebugFlags |=
                D3D11_DEBUG_FLAG_CREATE_DEBUG_DEVICE |
                D3D11_DEBUG_FLAG_VERIFY_COMMITTED_SHADER_RESOURCES;
#    endif
#    if ENGINE_DLL
            // Load the dll and import GetEngineFactoryD3D11() function
            auto GetEngineFactoryD3D11 = LoadGraphicsEngineD3D11();
#    endif
            auto* pFactoryD3D11 = GetEngineFactoryD3D11();
            pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
            Win32NativeWindow Window{ hWnd };
            pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
        }
        break;
#endif


#if D3D12_SUPPORTED
        case RENDER_DEVICE_TYPE_D3D12:
        {
#    if ENGINE_DLL
            // Load the dll and import GetEngineFactoryD3D12() function
            auto GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
#    endif
            EngineD3D12CreateInfo EngineCI;
#    ifdef DILIGENT_DEBUG
            // There is a bug in D3D12 debug layer that causes memory leaks in this tutorial
            //EngineCI.EnableDebugLayer = true;
#    endif
            auto* pFactoryD3D12 = GetEngineFactoryD3D12();
            pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
            Win32NativeWindow Window{ hWnd };
            pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
        }
        break;
#endif


#if GL_SUPPORTED
        case RENDER_DEVICE_TYPE_GL:
        {

#    if EXPLICITLY_LOAD_ENGINE_GL_DLL
            // Load the dll and import GetEngineFactoryOpenGL() function
            auto GetEngineFactoryOpenGL = LoadGraphicsEngineOpenGL();
#    endif
            auto* pFactoryOpenGL = GetEngineFactoryOpenGL();

            EngineGLCreateInfo EngineCI;
            EngineCI.Window.hWnd = hWnd;
#    ifdef DILIGENT_DEBUG
            EngineCI.CreateDebugContext = true;
#    endif
            pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc, &m_pSwapChain);
        }
        break;
#endif


#if VULKAN_SUPPORTED
        case RENDER_DEVICE_TYPE_VULKAN:
        {
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
            // Load the dll and import GetEngineFactoryVk() function
            auto GetEngineFactoryVk = LoadGraphicsEngineVk();
#    endif
            EngineVkCreateInfo EngineCI;
#    ifdef DILIGENT_DEBUG
            EngineCI.EnableValidation = true;
#    endif
            auto* pFactoryVk = GetEngineFactoryVk();
            pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);

            if (!m_pSwapChain && hWnd != nullptr)
            {
                Win32NativeWindow Window{ hWnd };
                pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
            }
        }
        break;
#endif


        default:
            std::cerr << "Unknown/unsupported device type";
            return false;
            break;
        }
        WindowResize(m_pSwapChain->GetDesc().Width, m_pSwapChain->GetDesc().Height);

        return true;
    }

    bool ProcessCommandLine(const char* CmdLine)
    {
        const auto* Key = "-mode ";
        const auto* pos = strstr(CmdLine, Key);
        if (pos != nullptr)
        {
            pos += strlen(Key);
            if (_stricmp(pos, "D3D11") == 0)
            {
#if D3D11_SUPPORTED
                m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
#else
                std::cerr << "Direct3D11 is not supported. Please select another device type";
                return false;
#endif
            }
            else if (_stricmp(pos, "D3D12") == 0)
            {
#if D3D12_SUPPORTED
                m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
#else
                std::cerr << "Direct3D12 is not supported. Please select another device type";
                return false;
#endif
            }
            else if (_stricmp(pos, "GL") == 0)
            {
#if GL_SUPPORTED
                m_DeviceType = RENDER_DEVICE_TYPE_GL;
#else
                std::cerr << "OpenGL is not supported. Please select another device type";
                return false;
#endif
            }
            else if (_stricmp(pos, "VK") == 0)
            {
#if VULKAN_SUPPORTED
                m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
#else
                std::cerr << "Vulkan is not supported. Please select another device type";
                return false;
#endif
            }
            else
            {
                std::cerr << "Unknown device type. Only the following types are supported: D3D11, D3D12, GL, VK";
                return false;
            }
        }
        else
        {
#if D3D12_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
#elif VULKAN_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
#elif D3D11_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
#elif GL_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_GL;
#endif
        }
        return true;
    }


	Diligent::float4x4 GetSurfacePretransformMatrix(const Diligent::float3& f3CameraViewAxis) const
	{
		const auto& SCDesc = m_pSwapChain->GetDesc();
		constexpr auto PI_F = 3.14159265354;
		switch (SCDesc.PreTransform)
		{
		case SURFACE_TRANSFORM_ROTATE_90:
			// The image content is rotated 90 degrees clockwise.
			return Diligent::float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F / 2.f);

		case SURFACE_TRANSFORM_ROTATE_180:
			// The image content is rotated 180 degrees clockwise.
			return Diligent::float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F);

		case SURFACE_TRANSFORM_ROTATE_270:
			// The image content is rotated 270 degrees clockwise.
			return Diligent::float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F * 3.f / 2.f);

		case SURFACE_TRANSFORM_OPTIMAL:
			UNEXPECTED("SURFACE_TRANSFORM_OPTIMAL is only valid as parameter during swap chain initialization.");
			return Diligent::float4x4::Identity();

		case SURFACE_TRANSFORM_HORIZONTAL_MIRROR:
		case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90:
		case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180:
		case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270:
			UNEXPECTED("Mirror transforms are not supported");
			return Diligent::float4x4::Identity();

		default:
			return Diligent::float4x4::Identity();
		}
	}
    void CreateResources()
    {
        // Pipeline state object encompasses configuration of all GPU stages

        
        PipelineStateCreateInfo PSOCreateInfo;

        // Pipeline state name is used by the engine to report issues.
        // It is always a good idea to give objects descriptive names.
        PSOCreateInfo.PSODesc.Name = "Simple triangle PSO";

        // This is a graphics pipeline
        PSOCreateInfo.PSODesc.PipelineType = PIPELINE_TYPE_GRAPHICS;

        // clang-format off
        // This tutorial will render to a single render target
        PSOCreateInfo.PSODesc.GraphicsPipeline.NumRenderTargets = 1;
        // Set render target format which is the format of the swap chain's color buffer
        PSOCreateInfo.PSODesc.GraphicsPipeline.RTVFormats[0] = m_pSwapChain->GetDesc().ColorBufferFormat;
        // Use the depth buffer format from the swap chain
        PSOCreateInfo.PSODesc.GraphicsPipeline.DSVFormat = m_pSwapChain->GetDesc().DepthBufferFormat;
        // Primitive topology defines what kind of primitives will be rendered by this pipeline state
        PSOCreateInfo.PSODesc.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        // No back face culling for this tutorial
        PSOCreateInfo.PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_NONE;
        // Disable depth testing
        PSOCreateInfo.PSODesc.GraphicsPipeline.DepthStencilDesc.DepthEnable = False;
        // clang-format on

        ShaderCreateInfo ShaderCI;
        // Tell the system that the shader source code is in HLSL.
        // For OpenGL, the engine will convert this into GLSL under the hood
        ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
        // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
        ShaderCI.UseCombinedTextureSamplers = true;
        // Create a vertex shader
        RefCntAutoPtr<IShader> pVS;
        {
            ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
            ShaderCI.EntryPoint = "main";
            ShaderCI.Desc.Name = "Triangle vertex shader";
            ShaderCI.Source = VSSource;
            m_pDevice->CreateShader(ShaderCI, &pVS);
        }

        // Create a pixel shader
        RefCntAutoPtr<IShader> pPS;
        {
            ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
            ShaderCI.EntryPoint = "main";
            ShaderCI.Desc.Name = "Triangle pixel shader";
            ShaderCI.Source = PSSource;
            m_pDevice->CreateShader(ShaderCI, &pPS);
        }

        // Finally, create the pipeline state
        PSOCreateInfo.PSODesc.GraphicsPipeline.pVS = pVS;
        PSOCreateInfo.PSODesc.GraphicsPipeline.pPS = pPS;
        m_pDevice->CreatePipelineState(PSOCreateInfo, &m_pPSO);
		m_Camera.SetPos(Diligent::float3(30, -30, 70));
		m_Camera.m_fYawAngle = 4;
		m_Camera.m_fPitchAngle = -1;
		//m_Camera.SetRotation(PI_F / 2.f, 0);
		m_Camera.SetRotationSpeed(0.005f);
		m_Camera.SetMoveSpeed(5.f);
		m_Camera.SetSpeedUpScales(5.f, 10.f);
		m_Camera.SrfPreTransform = GetSurfacePretransformMatrix(Diligent::float3{ 0, 0, 1 });
		gd.graphicsDevice = m_pDevice;
		gd.ImmediateContext = m_pImmediateContext;
		gd.m_pSwapChain = m_pSwapChain;
        gd.m_pEngineFactory = LoadGraphicsEngineVk()();
		auto ps = fs::current_path().string();
		std::vector<char> p2(ps.size() + 100);
		ps.copy(&p2[0], ps.size());
		fs::path curdir(&p2[0]);
		curdir /= "..";
		curdir /= "src";
		curdir = curdir / "Shader";
		curdir += fs::path::preferred_separator;
		renderer = efs::Create(&gd, &m_pSwapChain->GetDesc().ColorBufferFormat, 1, m_pSwapChain->GetDesc().DepthBufferFormat,
			false, 8000, curdir);
		constexpr int swapBufferCount = 2;
		//sfMemoryPoolEfk = efs::SingleFrameMemoryPool::CreateSingleFrameMemoryPool(&gd, 1024 * 1024 * 8, m_pSwapChain->GetDesc().BufferCount);
		/*commandListEfk = new efs::CommandList(sfMemoryPoolEfk);*/
		manager = Effekseer::Manager::Create(8000);
		// Sprcify rendering modules
// 描画モジュールの設定
		manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
		manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
		manager->SetRingRenderer(renderer->CreateRingRenderer());
		manager->SetTrackRenderer(renderer->CreateTrackRenderer());
		manager->SetModelRenderer(renderer->CreateModelRenderer());

		// Specify a texture, model and material loader
		// It can be extended by yourself. It is loaded from a file on now.
		// テクスチャ、モデル、マテリアルローダーの設定する。
		// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
		manager->SetTextureLoader(renderer->CreateTextureLoader());
		manager->SetModelLoader(renderer->CreateModelLoader());
		manager->SetMaterialLoader(renderer->CreateMaterialLoader());
		char16_t pth[100] = u"../Sample/02_Tktk03/ToonHit.efkefc";
		effect = Effekseer::Effect::Create(manager, pth);
        m_CameraAttribsCB = nullptr;
		CreateUniformBuffer(m_pDevice, 256 * 2, "Camera attribs buffer", &m_CameraAttribsCB);
    }

	InputController m_InputController;
	Camera m_Camera;
	IBuffer* m_CameraAttribsCB;
	efs::GraphicsDE gd;
	Effekseer::Manager* manager;
	EffekseerRenderer::Renderer* renderer;
	Effekseer::Effect* effect;
	efs::SingleFrameMemoryPool* sfMemoryPoolEfk;
	int time=0;
	Effekseer::Handle handle = 0;


	struct CameraAttribs
	{
		using float4 = Diligent::float4;
		using float2 = Diligent::float2;
		float4 f4Position;     // Camera world position
		float4 f4ViewportSize; // (width, height, 1/width, 1/height)

		float2 f2ViewportOrigin; // (min x, min y)
		float fNearPlaneZ;
		float fFarPlaneZ; // fNearPlaneZ < fFarPlaneZ

#ifdef __cplusplus
		float4x4 mViewT;
		float4x4 mProjT;
		float4x4 mViewProjT;
		float4x4 mViewInvT;
		float4x4 mProjInvT;
		float4x4 mViewProjInvT;
#else
		matrix mView;
		matrix mProj;
		matrix mViewProj;
		matrix mViewInv;
		matrix mProjInv;
		matrix mViewProjInv;
#endif

		float4 f4ExtraData[5]; // Any appliation-specific data
		// Sizeof(CameraAttribs) == 256*2
	};
	struct instData
	{
		using float4 = Diligent::float4;
		uint bonelength;
		uint frameIndex;
		uint transformid;
		uint base;
		// float transitionProgress;
		float4 color;
	};
    void Render()
    {
        m_Camera.Update(m_InputController, static_cast<float>(0.002));
        // Set render targets before issuing any draw command.
        // Note that Present() unbinds the back buffer if it is set as render target.
        auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
        auto* pDSV = m_pSwapChain->GetDepthBufferDSV();
        m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

        // Clear the back buffer
        const float ClearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
        // Let the engine perform required state transitions
        m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

        //// Set the pipeline state in the immediate context
        //m_pImmediateContext->SetPipelineState(m_pPSO);

        //// Typically we should now call CommitShaderResources(), however shaders in this example don't
        //// use any resources.

        //DrawAttribs drawAttrs;
        //drawAttrs.NumVertices = 3; // Render 3 vertices
        //m_pImmediateContext->Draw(drawAttrs);

		//// Clear the back buffer
		//m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		//m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        renderer->SetProjectionMatrix(reinterpret_cast<const Effekseer::Matrix44&>((m_Camera.GetProjMatrix())));
        renderer->SetCameraMatrix(reinterpret_cast<const Effekseer::Matrix44&>    ((m_Camera.GetViewMatrix())));
		auto rd = static_cast<EffekseerRendererDE::RendererImplemented*> (renderer);

		{
			MapHelper<CameraAttribs> CamAttribs(m_pImmediateContext, m_CameraAttribsCB, MAP_WRITE, MAP_FLAG_DISCARD);
			(CamAttribs->mProjT) = (m_Camera.GetProjMatrix().Transpose());
			CamAttribs->mViewProjT = m_Camera.CameraViewProj;
			CamAttribs->mViewProjInvT = m_Camera.CameraViewProj.Inverse();
			CamAttribs->f4Position = Diligent::float4(Diligent::float3::MakeVector(m_Camera.GetWorldMatrix()[3]), 1);
			//= ex;
		}
		//sfMemoryPoolEfk->NewFrame();
		//rd->SetCommandList(commandListEfk);
		if (time % 120 == 0)
		{
			// Play an effect
			// エフェクトの再生
			handle = manager->Play(effect, 0, 0, 0);
		}

		if (time % 120 == 119)
		{
			// Stop effects
			// エフェクトの停止
			manager->StopEffect(handle);
		}

		// Move the effect
		// エフェクトの移動
		manager->AddLocation(handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

		// Update the manager
		// マネージャーの更新
		manager->Update();

		// Begin to rendering effects
		// エフェクトの描画開始処理を行う。
		renderer->BeginRendering();

		// Render effects
		// エフェクトの描画を行う。
		manager->Draw();

		// Finish to rendering effects
		// エフェクトの描画終了処理を行う。
		renderer->EndRendering();
		// Finish a command list
		// コマンドリストを終了する。
		/*if (commandListEfk->currentCommandList_)
			m_pImmediateContext->ExecuteCommandList(commandListEfk->currentCommandList_);*/
		time++;
       /* m_pImmediateContext->Flush();
        m_pImmediateContext->FinishFrame();*/
    }

    void Present()
    {
        m_pSwapChain->Present();
    }



    void WindowResize(Uint32 Width, Uint32 Height)
    {
        if (!m_pSwapChain)
            return;
        m_pSwapChain->Resize(Width, Height);

        auto SCDesc = m_pSwapChain->GetDesc();

        const auto PI_F = PI;
        float NearPlane = 0.1f;
        float FarPlane = 1000.f;
        //float AspectRatio = static_cast<float>(SCDesc.Width) / static_cast<float>(SCDesc.Height);
        m_Camera.SetProjAttribs(NearPlane, FarPlane, SCDesc.Width, SCDesc.Height, PI_F / 4.f,
            m_pSwapChain->GetDesc().PreTransform, m_pDevice->GetDeviceCaps().IsGLDevice());

    }
    RENDER_DEVICE_TYPE GetDeviceType() const { return m_DeviceType; }

private:
    RefCntAutoPtr<IRenderDevice>  m_pDevice;
    RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
    RefCntAutoPtr<ISwapChain>     m_pSwapChain;
    RefCntAutoPtr<IPipelineState> m_pPSO;
    RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
};

std::unique_ptr<Tutorial00App> g_pTheApp;

LRESULT CALLBACK MessageProc(HWND, UINT, WPARAM, LPARAM);
// Main
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
#if defined(_DEBUG) || defined(DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    g_pTheApp.reset(new Tutorial00App);

    const auto* cmdLine = GetCommandLineA();
    if (!g_pTheApp->ProcessCommandLine(cmdLine))
        return -1;

    std::wstring Title(L"Tutorial00: Hello Win32");
    switch (g_pTheApp->GetDeviceType())
    {
    case RENDER_DEVICE_TYPE_D3D11: Title.append(L" (D3D11)"); break;
    case RENDER_DEVICE_TYPE_D3D12: Title.append(L" (D3D12)"); break;
    case RENDER_DEVICE_TYPE_GL: Title.append(L" (GL)"); break;
    case RENDER_DEVICE_TYPE_VULKAN: Title.append(L" (VK)"); break;
    }
    // Register our window class
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, MessageProc,
                       0L, 0L, instance, NULL, NULL, NULL, NULL, L"SampleApp", NULL };
    RegisterClassEx(&wcex);

    // Create a window
    LONG WindowWidth = 1280;
    LONG WindowHeight = 1024;
    RECT rc = { 0, 0, WindowWidth, WindowHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    HWND wnd = CreateWindow(L"SampleApp", Title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, instance, NULL);
    if (!wnd)
    {
        MessageBox(NULL, L"Cannot create window", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }
    ShowWindow(wnd, cmdShow);
    UpdateWindow(wnd);

    if (!g_pTheApp->InitializeDiligentEngine(wnd))
        return -1;

    g_pTheApp->CreateResources();

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            g_pTheApp->Render();
            g_pTheApp->Present();
        }
    }

    g_pTheApp.reset();

    return (int)msg.wParam;
}

// Called every time the NativeNativeAppBase receives a message
LRESULT CALLBACK MessageProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(wnd, &ps);
        EndPaint(wnd, &ps);
        return 0;
    }
    case WM_SIZE: // Window size has been changed
        if (g_pTheApp)
        {
            g_pTheApp->WindowResize(LOWORD(lParam), HIWORD(lParam));
        }
        return 0;

    case WM_CHAR:
        if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

        lpMMI->ptMinTrackSize.x = 320;
        lpMMI->ptMinTrackSize.y = 240;
        return 0;
    }

    default:
        return DefWindowProc(wnd, message, wParam, lParam);
    }
}