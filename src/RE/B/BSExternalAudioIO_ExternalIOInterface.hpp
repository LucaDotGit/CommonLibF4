#pragma once

namespace RE::BSResource
{
	enum class ErrorCode : std::int32_t;

	class ID;
}

namespace RE::BSExternalAudioIO
{
	class ExternalLoad;

	class __declspec(novtable) ExternalIOInterface
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSExternalAudioIO__ExternalIOInterface;
		inline static constexpr const auto& VTABLE = VTABLE::BSExternalAudioIO__ExternalIOInterface;

		virtual ~ExternalIOInterface(); // 0x00

		// add
		virtual auto Request(const BSResource::ID*, BSExternalAudioIO::ExternalLoad**) -> BSResource::ErrorCode; // 0x01
	};

	static_assert(sizeof(ExternalIOInterface) == 0x08);
}
