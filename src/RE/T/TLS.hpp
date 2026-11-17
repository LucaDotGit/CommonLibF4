#pragma once

namespace RE
{
	class TLS
	{
	public:
		[[nodiscard]]
		static auto GetSingleton() -> TLS*
		{
			return *static_cast<TLS**>(REX::W32::NtCurrentTeb()->threadLocalStoragePointer);
		}

		// members
		std::array<std::byte, 0x830> pad000; // 0x000
		bool consoleMode;					 // 0x830
	};

	static_assert(sizeof(TLS) == 0x831);
}
