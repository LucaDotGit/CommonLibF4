#include "RE/B/BSResource_Archive2_Index.hpp"

namespace RE::BSResource::Archive2
{
	auto Index::EntryHeader::GetDataFileIndex() noexcept
		-> std::variant<std::reference_wrapper<std::uint8_t>, std::reference_wrapper<std::uint16_t>>
	{
		if (F4SE::IsRuntimeAtLeastAE()) {
			return REL::GetMemberAt<std::uint16_t>(
				Offset::BSResource::Archive2::Index::EntryHeader::DataFileIndex,
				this);
		}

		return REL::GetMemberAt<std::uint8_t>(Offset::BSResource::Archive2::Index::EntryHeader::DataFileIndex, this);
	}

	auto Index::EntryHeader::GetDataFileIndex() const noexcept
		-> std::variant<std::reference_wrapper<const std::uint8_t>, std::reference_wrapper<const std::uint16_t>>
	{
		if (F4SE::IsRuntimeAtLeastAE()) {
			return REL::GetMemberAt<std::uint16_t>(
				Offset::BSResource::Archive2::Index::EntryHeader::DataFileIndex,
				this);
		}

		return REL::GetMemberAt<std::uint8_t>(Offset::BSResource::Archive2::Index::EntryHeader::DataFileIndex, this);
	}

	auto Index::EntryHeader::GetRuntimeData() noexcept -> Index::EntryHeader::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::BSResource::Archive2::Index::EntryHeader::RuntimeData, this);
	}

	auto Index::EntryHeader::GetRuntimeData() const noexcept -> const Index::EntryHeader::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::BSResource::Archive2::Index::EntryHeader::RuntimeData, this);
	}

	auto Index::EntryHeader::IsChunk() const noexcept -> bool
	{
		return GetRuntimeData().chunkOffsetOrType != 0;
	}

	auto Index::EntryHeader::IsLoose() const noexcept -> bool
	{
		return GetRuntimeData().chunkOffsetOrType == 0;
	}

	auto Index::GetRuntimeDataFiles() noexcept
		-> std::variant<std::reference_wrapper<RuntimeDataFiles01>, std::reference_wrapper<RuntimeDataFiles02>>
	{
		if (F4SE::IsRuntimeAtLeastAE()) {
			return REL::GetMemberAt<RuntimeDataFiles02>(Offset::BSResource::Archive2::Index::RuntimeDataFiles, this);
		}

		return REL::GetMemberAt<RuntimeDataFiles01>(Offset::BSResource::Archive2::Index::RuntimeDataFiles, this);
	}

	auto Index::GetRuntimeDataFiles() const noexcept -> std::variant<
		std::reference_wrapper<const RuntimeDataFiles01>,
		std::reference_wrapper<const RuntimeDataFiles02>>
	{
		if (F4SE::IsRuntimeAtLeastAE()) {
			return REL::GetMemberAt<RuntimeDataFiles02>(Offset::BSResource::Archive2::Index::RuntimeDataFiles, this);
		}

		return REL::GetMemberAt<RuntimeDataFiles01>(Offset::BSResource::Archive2::Index::RuntimeDataFiles, this);
	}

	auto Index::GetRuntimeData() noexcept -> Index::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::BSResource::Archive2::Index::RuntimeData, this);
	}

	auto Index::GetRuntimeData() const noexcept -> const Index::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::BSResource::Archive2::Index::RuntimeData, this);
	}
}
