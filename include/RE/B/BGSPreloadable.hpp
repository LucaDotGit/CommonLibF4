#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	enum class IO_TASK_PRIORITY : std::int32_t;

	class QueuedFile;
	class TBO_InstanceData;

	class __declspec(novtable) BGSPreloadable
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPreloadable };
		inline static constexpr auto VTABLE{ VTABLE::BGSPreloadable };

		~BGSPreloadable() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual void QueueModelsImpl(void* a_queued, IO_TASK_PRIORITY a_taskPriority, QueuedFile* a_file, const TBO_InstanceData* a_instanceData) = 0; // 07
	};
	static_assert(sizeof(BGSPreloadable) == 0x08);
}
