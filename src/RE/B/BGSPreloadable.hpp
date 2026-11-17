#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	enum class IO_TASK_PRIORITY : std::int32_t;

	class QueuedFile;
	class TBO_InstanceData;

	class __declspec(novtable) BGSPreloadable : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSPreloadable;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPreloadable;

		~BGSPreloadable() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual void QueueModelsImpl(
			void* a_queued,
			IO_TASK_PRIORITY a_taskPriority,
			QueuedFile* a_file,
			const TBO_InstanceData* a_instanceData) = 0; // 0x07
	};

	static_assert(sizeof(BGSPreloadable) == 0x08);
}
