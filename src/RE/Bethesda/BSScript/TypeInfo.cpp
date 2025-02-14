#include "RE/Bethesda/BSScript/TypeInfo.hpp"

#include "RE/Bethesda/BSScript/IComplexType.hpp"

namespace RE::BSScript
{
	auto TypeInfo::GetRawType() const
		-> RawType
	{
		if (IsComplex()) {
			const auto complex =
				reinterpret_cast<IComplexType*>(
					reinterpret_cast<std::uintptr_t>(data.complexTypeInfo) &
					~static_cast<std::uintptr_t>(1));
			auto rtype = static_cast<uint32_t>(complex->GetRawType());
			if (IsArray()) {
				rtype += 10;
			}
			return static_cast<RawType>(rtype);
		}
		else {
			return *data.rawType;
		}
	}
}