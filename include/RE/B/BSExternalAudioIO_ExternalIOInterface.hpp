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
		inline static constexpr auto RTTI{ RTTI::BSExternalAudioIO__ExternalIOInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSExternalAudioIO__ExternalIOInterface };

		virtual ~ExternalIOInterface(); // 00

		// add
		virtual BSResource::ErrorCode Request(const BSResource::ID*, BSExternalAudioIO::ExternalLoad**); // 01
	};
	static_assert(sizeof(ExternalIOInterface) == 0x08);
}
