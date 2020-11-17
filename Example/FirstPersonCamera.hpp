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

#include "BasicMath.hpp"
//#include "common/Math1.h"
#include "InputController.hpp"
#include "GraphicsTypes.h"

namespace Diligent
{

	class Camera
	{
		//using mapf3 = math::Map<const math::Vector3f>;
	public:
		static Camera* mainCam;
		static Camera& Main() {
			return *mainCam;
		}
		Camera() { Camera::mainCam = this; }
		void Update(InputController& Controller, float ElapsedTime);
		void SetRotation(float Yaw, float Pitch);
		void SetLookAt(const float3& LookAt);
		void SetMoveSpeed(float MoveSpeed) { m_fMoveSpeed = MoveSpeed; }
		void SetRotationSpeed(float RotationSpeed) { m_fRotationSpeed = RotationSpeed; }
		void SetPos(const float3& Pos) { m_Pos = Pos; }
		void SetProjAttribs(Float32 NearClipPlane, Float32 FarClipPlane, Uint32 Width, Uint32 Height, Float32 FOV, SURFACE_TRANSFORM SrfPreTransform, bool IsGL);
		// AspectRatio = width / height accounting for surface pretransform
		// (i.e. logical widht / logical height)
		void m_Camera(Float32           NearClipPlane,
			Float32           FarClipPlane,
			Uint32            Width,
			Uint32            Height,
			Float32           FOV,
			SURFACE_TRANSFORM SrfPreTransform,
			bool              IsGL);
		void SetSpeedUpScales(Float32 SpeedUpScale, Float32 SuperSpeedUpScale);


		// clang-format off
		const float4x4& GetViewMatrix()  const { return m_ViewMatrix; }
		const float4x4& GetWorldMatrix() const { return m_WorldMatrix; }
		const float4x4& GetProjMatrix()  const { return m_ProjMatrix; }

		float3 GetWorldRight() const { return float3(m_ViewMatrix._11, m_ViewMatrix._21, m_ViewMatrix._31); }
		float3 GetWorldUp()    const { return float3(m_ViewMatrix._12, m_ViewMatrix._22, m_ViewMatrix._32); }
		float3 GetWorldAhead() const { return float3(m_ViewMatrix._13, m_ViewMatrix._23, m_ViewMatrix._33); }
		// clang-format on
		//void getRay(const float2& screen_pos, math::float3& origin, math::float3& dir) const
		//{
		//	origin = mapf3(m_Pos.Data());
		//	const float w = m_ProjAttribs.Width, h = m_ProjAttribs.Height;
		//	if (m_ProjAttribs.AspectRatio <= 0) {
		//		std::abort();
		//		//dir = rot.rotate(Vec3(0, 0, 1));
		//		return;
		//	}

		//	const float nx = 2 * (screen_pos.x / w) - 1;
		//	const float ny = 1-2 * ((screen_pos.y) / h);

		//	const auto projection_matrix = m_ProjMatrix;

		//	/*if (is_ortho) {
		//		const Vec3 x = rot * Vec3(1, 0, 0);
		//		const Vec3 y = rot * Vec3(0, 1, 0);
		//		float ratio = h > 0 ? w / (float)h : 1;
		//		origin += x * nx * ortho_size * ratio
		//			+ y * ny * ortho_size;
		//	}*/

		//	const auto view_matrix = m_ViewMatrix;
		//	auto inverted = (CameraViewProj).Inverse();

		//	float4 p0 = (inverted * float4(nx, ny,0,1));
		//	float4 p1 = inverted * float4(nx, ny,1, 1);
		//	
		//	p0 *= 1/p0.w;
		//	/*p1 *= 1 / p1.w;*/
		//	//origin = p0;
		//	dir=(mapf3(p0.Data())-origin).normalized();
		//	//if (is_ortho) dir *= -1.f;
		//}

		float3 GetPos() const { return m_Pos; }
		float  GetCurrentSpeed() const { return m_fCurrentSpeed; }

		struct ProjectionAttribs
		{
			Uint32            Width = 0;
			Uint32            Height = 0;
			Float32           NearClipPlane = 1.f;
			Float32           FarClipPlane = 1000.f;
			Float32           AspectRatio = 1.f;
			Float32           FOV = PI_F / 4.f;
			SURFACE_TRANSFORM PreTransform = SURFACE_TRANSFORM_IDENTITY;
			bool              IsGL = false;
		};
		const ProjectionAttribs& GetProjAttribs() { return m_ProjAttribs; }

		void SetReferenceAxes(const float3& ReferenceRightAxis, const float3& ReferenceUpAxis, bool IsRightHanded = false);

		void SetHandness(bool IsRightHanded)
		{
			m_fHandness = IsRightHanded ? +1.f : -1.f;
		}

		float4x4 m_ViewMatrix;
		float4x4 m_WorldMatrix;
		float4x4 m_ProjMatrix;
		float4x4 SrfPreTransform;
		float4x4 CameraViewProj;
		float3 m_ReferenceRightAxis = float3{ 0, 1, 0 };
		float3 m_ReferenceUpAxis = float3{ 0, 0, 1 };
		float3 m_ReferenceAheadAxis = float3{ 1, 0, 0 };
		//protected:
		float4x4 GetReferenceRotiation() const;

		ProjectionAttribs m_ProjAttribs;

		MouseState m_LastMouseState;


		float3 m_Pos;

		float    m_fRotationSpeed = 0.01f;
		float    m_fMoveSpeed = 1.f;
		float    m_fCurrentSpeed = 0.f;

		float m_fYawAngle = 0; // Yaw angle of camera
		float m_fPitchAngle = 0; // Pitch angle of camera
		float m_fSpeedUpScale = 1.f;
		float m_fSuperSpeedUpScale = 1.f;
		float m_fHandness = 1.f; // -1 - left handed
										  // +1 - right handed
	};
} // namespace Diligent
