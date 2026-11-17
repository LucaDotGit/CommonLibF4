#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)

	struct __declspec(novtable, uuid("00000000-0000-0000-C000-000000000046")) IUnknown
	{
		virtual auto QueryInterface(const IID& a_iid, void** a_object) -> HRESULT = 0;
		virtual auto AddRef() -> std::uint32_t = 0;
		virtual auto Release() -> std::uint32_t = 0;

		template <class T>
		[[nodiscard]]
		auto QueryInterface(T** a_object) -> HRESULT
		{
			return QueryInterface(
				*reinterpret_cast<const IID*>(std::addressof(__uuidof(T))),
				static_cast<void**>(a_object));
		}
	};

	// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}

namespace REX::W32
{
	inline constexpr auto IID_IUnknown =
		IID{0x0000'0000, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
}
