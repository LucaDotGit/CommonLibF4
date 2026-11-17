#pragma once

namespace Scaleform::Render
{
	class LinearHeap;
}

namespace Scaleform::Render::ContextImpl
{
	class Entry;

	class __declspec(novtable) EntryData
	{
	public:
		enum class EntryType : std::int16_t
		{
			Base = 0,
			Root = 1,
			Container = 2,
			Shape = 3,
			Mesh = 4,
			Text = 5
		};

		virtual ~EntryData(); // 0x00

		// add
		virtual auto ConstructCopy(LinearHeap& a_heap) const -> EntryData* = 0; // 0x01
		virtual void CopyTo(void* a_target) const = 0;							// 0x02
		virtual void ReleaseNodes() const;										// 0x03 - { return; }
		virtual void Destroy() = 0;												// 0x04
		virtual auto PropagateUp(Entry* a_entry) const -> bool;					// 0x05

		// members
		REX::Enum<EntryType, std::int16_t> type; // 0x08
		std::uint16_t flags;					 // 0x0A
	};

	static_assert(sizeof(EntryData) == 0x10);
}
