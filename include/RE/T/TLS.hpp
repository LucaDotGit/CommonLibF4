#pragma once

namespace RE
{
	class TLS
	{
	public:
		[[nodiscard]] static TLS* GetSingleton()
		{
			return *static_cast<TLS**>(REX::W32::NtCurrentTeb()->threadLocalStoragePointer);
		}

		// members
		std::array<std::byte, 0x830> pad000; // 000
		bool consoleMode;					 // 830
	};
	static_assert(sizeof(TLS) == 0x831);
}
