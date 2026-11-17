#pragma once

#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiFrustum.hpp"
#include "RE/N/NiRect.hpp"

namespace RE
{
	class __declspec(novtable) NiCamera : public NiAVObject // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiCamera;
		inline static constexpr const auto& VTABLE = VTABLE::NiCamera;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiCamera;

		~NiCamera() override; // 0x00

		// override (NiAVObject)
		auto GetRTTI() const -> const NiRTTI* override;						   // 0x02
		auto CreateClone(NiCloningProcess& a_cloneData) -> NiObject* override; // 0x1A
		void LoadBinary(NiStream& a_stream) override;						   // 0x1B
		void LinkObject(NiStream& a_stream) override;						   // 0x1C
		auto RegisterStreamables(NiStream& a_stream) -> bool override;		   // 0x1D
		void SaveBinary(NiStream& a_stream) override;						   // 0x1E
		auto IsEqual(NiObject* a_object) -> bool override;					   // 0x1F
		void UpdateWorldBound() override;									   // 0x33
		void UpdateWorldData(NiUpdateData* a_data) override;				   // 0x34

		[[nodiscard]]
		static auto BoundInFrustum(const NiBound& a_bound, NiCamera* a_camera) -> bool
		{
			using FuncType = decltype(&NiCamera::BoundInFrustum);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiCamera::BoundInFrustum);
			return std::invoke(FUNC, a_bound, a_camera);
		}

		[[nodiscard]]
		auto NodeInFrustum(NiAVObject* a_node) -> bool
		{
			if (!a_node) {
				return false;
			}

			return BoundInFrustum(a_node->worldBound, this);
		}

		[[nodiscard]]
		auto PointInFrustum(const NiPoint3& a_point, REX::Float32 a_radius) -> bool
		{
			const auto bound = NiBound{.center = a_point, .radius = {.float32 = a_radius}};
			return BoundInFrustum(bound, this);
		}

		void ViewPointToRay(REX::Float32 a_vx, REX::Float32 a_vy, NiPoint3* a_origin, NiPoint3* a_dir) const
		{
			using FuncType = decltype(&NiCamera::ViewPointToRay);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiCamera::ViewPointToRay);
			std::invoke(FUNC, this, a_vx, a_vy, a_origin, a_dir);
		}

		auto WorldPtToScreenPt3(
			const NiPoint3& a_point,
			REX::Float32& a_x,
			REX::Float32& a_y,
			REX::Float32& a_z,
			REX::Float32 a_zeroTolerance) const -> bool
		{
			return WorldPtToScreenPt3(worldToCam, port, a_point, a_x, a_y, a_z, a_zeroTolerance);
		}

		static auto WorldPtToScreenPt3(
			std::array<std::array<REX::Float32, 4>, 4> a_matrix,
			const NiRectF& a_port,
			const NiPoint3& a_point,
			REX::Float32& a_x,
			REX::Float32& a_y,
			REX::Float32& a_z,
			REX::Float32 a_zeroTolerance) -> bool
		{
			using FuncType = bool (*)(
				std::array<std::array<REX::Float32, 4>, 4>,
				const NiRectF&,
				const NiPoint3&,
				REX::Float32&,
				REX::Float32&,
				REX::Float32&,
				REX::Float32);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiCamera::WorldPtToScreenPt3);
			return std::invoke(FUNC, a_matrix, a_port, a_point, a_x, a_y, a_z, a_zeroTolerance);
		}

		// members
		std::array<std::array<REX::Float32, 4>, 4> worldToCam; // 0x120
		NiFrustum viewFrustum;								   // 0x160
		REX::Float32 minNearPlaneDist;						   // 0x17C
		REX::Float32 maxFarNearRatio;						   // 0x180
		NiRectF port;										   // 0x184
		REX::Float32 lodAdjust;								   // 0x194
	};

	static_assert(sizeof(NiCamera) == 0x1A0);
}
