#pragma once

#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiFrustum.hpp"
#include "RE/N/NiRect.hpp"

namespace RE
{
	class __declspec(novtable) NiCamera
		: public NiAVObject // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiCamera };
		inline static constexpr auto VTABLE{ VTABLE::NiCamera };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiCamera };

		~NiCamera() override; // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;						   // 02
		NiObject* CreateClone(NiCloningProcess& a_cloneData) override; // 1A
		void LoadBinary(NiStream& a_stream) override;				   // 1B
		void LinkObject(NiStream& a_stream) override;				   // 1C
		bool RegisterStreamables(NiStream& a_stream) override;		   // 1D
		void SaveBinary(NiStream& a_stream) override;				   // 1E
		bool IsEqual(NiObject* a_object) override;					   // 1F
		void UpdateWorldBound() override;							   // 33
		void UpdateWorldData(NiUpdateData* a_data) override;		   // 34

		[[nodiscard]] static bool BoundInFrustum(const NiBound& a_bound, NiCamera* a_camera)
		{
			using FuncType = decltype(&NiCamera::BoundInFrustum);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiCamera::BoundInFrustum };
			return std::invoke(FUNC, a_bound, a_camera);
		}

		[[nodiscard]] bool NodeInFrustum(NiAVObject* a_node)
		{
			if (!a_node) {
				return false;
			}

			return BoundInFrustum(a_node->worldBound, this);
		}

		[[nodiscard]] bool PointInFrustum(const NiPoint3& a_point, REX::Float32 a_radius)
		{
			const auto bound = NiBound{ .center = a_point, .radius = { .float32 = a_radius } };
			return BoundInFrustum(bound, this);
		}

		void ViewPointToRay(REX::Float32 a_vx, REX::Float32 a_vy, NiPoint3* a_origin, NiPoint3* a_dir) const
		{
			using FuncType = decltype(&NiCamera::ViewPointToRay);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiCamera::ViewPointToRay };
			FUNC(this, a_vx, a_vy, a_origin, a_dir);
		}

		bool WorldPtToScreenPt3(const NiPoint3& a_point, REX::Float32& a_x, REX::Float32& a_y, REX::Float32& a_z, REX::Float32 a_zeroTolerance) const
		{
			return WorldPtToScreenPt3(worldToCam, port, a_point, a_x, a_y, a_z, a_zeroTolerance);
		}

		static bool WorldPtToScreenPt3(std::array<std::array<REX::Float32, 4>, 4> a_matrix, const NiRect<REX::Float32>& a_port, const NiPoint3& a_point, REX::Float32& a_x, REX::Float32& a_y, REX::Float32& a_z, REX::Float32 a_zeroTolerance)
		{
			using FuncType = bool (*)(std::array<std::array<REX::Float32, 4>, 4>, const NiRect<REX::Float32>&, const NiPoint3&, REX::Float32&, REX::Float32&, REX::Float32&, REX::Float32);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiCamera::WorldPtToScreenPt3 };
			return std::invoke(FUNC, a_matrix, a_port, a_point, a_x, a_y, a_z, a_zeroTolerance);
		}

		// members
		std::array<std::array<REX::Float32, 4>, 4> worldToCam; // 120
		NiFrustum viewFrustum;								   // 160
		REX::Float32 minNearPlaneDist;						   // 17C
		REX::Float32 maxFarNearRatio;						   // 180
		NiRect<REX::Float32> port;							   // 184
		REX::Float32 lodAdjust;								   // 194
	};
	static_assert(sizeof(NiCamera) == 0x1A0);
}
