#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/TypeInfo.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTObjectArena.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/BSTTuple.hpp"
#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	namespace BSScript
	{
		class TypeInfo;

		namespace Internal
		{
			class VDescTable
			{
			public:
				using value_type = BSTTuple<BSFixedString, TypeInfo>;
				using size_type = std::uint16_t;

				VDescTable(size_type a_params, size_type a_locals) :
					paramCount(a_params),
					totalEntries(a_params + a_locals)
				{
					const auto total = paramCount + totalEntries;
					if (total > 0) {
						entries = new value_type[total];
					}
				}

				~VDescTable() { delete[] entries; }

				// members
				value_type* entries{ nullptr }; // 00
				size_type paramCount{ 0 };		// 08
				size_type totalEntries{ 0 };	// 0A
			};
			static_assert(sizeof(VDescTable) == 0x10);
		}
	}
}
