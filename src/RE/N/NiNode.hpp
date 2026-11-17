#pragma once

#include "RE/B/BSTAtomicValue.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) NiNode : public NiAVObject // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiNode;
		inline static constexpr const auto& VTABLE = VTABLE::NiNode;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiNode;

#define RUNTIME_DATA_CONTENT                                                 \
	NiTObjectArray<NiPointer<NiAVObject>> children;					/* 00 */ \
	BSTAtomicValue<std::uint32_t> dirtyState;						/* 18 */ \
	REX::Float32 meshLODFadeAmount{static_cast<REX::Float32>(0.0)}; /* 1C */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT; // 0x00
		};

		static_assert(sizeof(RuntimeData) == 0x20);

		NiNode();

		explicit NiNode(std::uint32_t a_numChildren);

		~NiNode() override; // 0x00

		// add
		virtual void AttachChild(NiAVObject* a_child, bool a_firstAvailable);							   // 0x3A
		virtual void InsertChildAt(std::uint32_t a_index, NiAVObject* a_child);							   // 0x3B
		virtual void DetachChild(NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject);				   // 0x3C
		virtual void DetachChild(NiAVObject* a_child);													   // 0x3D
		virtual void DetachChildAt(std::uint32_t a_index, NiPointer<NiAVObject>& a_avObject);			   // 0x3E
		virtual void DetachChildAt(std::uint32_t a_index);												   // 0x3F
		virtual void SetAt(std::uint32_t a_index, NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject); // 0x40
		virtual void SetAt(std::uint32_t a_index, NiAVObject* a_child);									   // 0x41
		virtual void UpdateUpwardPass(NiUpdateData& a_data);											   // 0x42

		[[nodiscard]]
		auto GetRuntimeData() noexcept -> RuntimeData&;
		[[nodiscard]]
		auto GetRuntimeData() const noexcept -> const RuntimeData&;

		[[nodiscard]]
		auto GetChildCount() const -> std::uint32_t;
		[[nodiscard]]
		auto GetChildAt(std::uint32_t a_index) const -> NiPointer<NiAVObject>;
		auto SetChildAt(std::uint32_t a_index, NiPointer<NiAVObject> a_child) -> bool;

		auto ForEachChild(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<NiAVObject>&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;

		// members
#if (COMMONLIB_RUNTIME_VR == 0)
		RUNTIME_DATA_CONTENT; // 0x120
#elif (COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0)
		std::array<std::uint32_t, 0x10> unk120; // 0x120
		RUNTIME_DATA_CONTENT;					// 0x160
#endif
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(NiNode) == 0x140);
#elif (COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(NiNode) == 0x180);
#else
	static_assert(sizeof(NiNode) == 0x120);
#endif
}

#undef RUNTIME_DATA_CONTENT
