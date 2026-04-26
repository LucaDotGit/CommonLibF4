#pragma once

#include "RE/B/BSTAtomicValue.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTArray.hpp"

namespace RE
{
	class __declspec(novtable) NiNode
		: public NiAVObject // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiNode };
		inline static constexpr auto VTABLE{ VTABLE::NiNode };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiNode };

#define RUNTIME_DATA_CONTENT                                  \
	NiTObjectArray<NiPointer<NiAVObject>> children; /* 120 */ \
	BSTAtomicValue<std::uint32_t> dirtyState;		/* 138 */ \
	REX::Float32 meshLODFadeAmount{ 0.0_f32 };		/* 13C */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT;
		};

		explicit NiNode();
		explicit NiNode(std::uint32_t a_numChildren);

		~NiNode() override; // 00

		// add
		virtual void AttachChild(NiAVObject* a_child, bool a_firstAvail);								   // 3A
		virtual void InsertChildAt(std::uint32_t a_index, NiAVObject* a_child);							   // 3B
		virtual void DetachChild(NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject);				   // 3C
		virtual void DetachChild(NiAVObject* a_child);													   // 3D
		virtual void DetachChildAt(std::uint32_t a_index, NiPointer<NiAVObject>& a_avObject);			   // 3E
		virtual void DetachChildAt(std::uint32_t a_index);												   // 3F
		virtual void SetAt(std::uint32_t a_index, NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject); // 40
		virtual void SetAt(std::uint32_t a_index, NiAVObject* a_child);									   // 41
		virtual void UpdateUpwardPass(NiUpdateData& a_data);											   // 42

		[[nodiscard]] RuntimeData& GetRuntimeData() noexcept;
		[[nodiscard]] const RuntimeData& GetRuntimeData() const noexcept;

		// members
#if COMMONLIB_RUNTIME_VR == 0
		RUNTIME_DATA_CONTENT;
#elif COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
		std::array<std::uint32_t, 0x10> unk120; // 120
		RUNTIME_DATA_CONTENT;
#endif
	};
#if COMMONLIB_RUNTIME_VR == 0
	static_assert(sizeof(NiNode) == 0x140);
#elif COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(NiNode) == 0x180);
#endif
}

#undef RUNTIME_DATA_CONTENT
