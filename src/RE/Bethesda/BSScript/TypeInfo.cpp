#include "RE/Bethesda/BSScript/TypeInfo.hpp"

#include "RE/Bethesda/BSScript/IComplexType.hpp"

namespace RE::BSScript
{
	TypeInfo::RawType TypeInfo::GetRawType() const
	{
		if (IsComplex()) {
			const auto complex =
				reinterpret_cast<IComplexType*>(
					reinterpret_cast<std::uintptr_t>(data.complexTypeInfo) &
					~static_cast<std::uintptr_t>(1));
			auto rtype = static_cast<uint32_t>(complex->GetRawType());
			if (IsArray()) {
				rtype += std::to_underlying(RawType::kArrayStart);
			}
			return static_cast<RawType>(rtype);
		}
		else {
			return *data.rawType;
		}
	}

	IComplexType* TypeInfo::GetComplexType() const
	{
		return IsComplex() ? reinterpret_cast<IComplexType*>(
								 reinterpret_cast<std::uintptr_t>(data.complexTypeInfo) &
								 ~static_cast<std::uintptr_t>(1))
						   : nullptr;
	}

	void TypeInfo::SetArray(bool a_set) noexcept
	{
		if (IsComplex()) {
			if (a_set) {
				assert(!IsArray());
				data.rawType.set(RawType::kObject);
			}
			else {
				assert(IsArray());
				data.rawType.reset(RawType::kObject);
			}
		}
		else {
			if (a_set) {
				assert(!IsArray());
				data.rawType += RawType::kArrayStart;
			}
			else {
				assert(IsArray());
				data.rawType -= RawType::kArrayEnd;
			}
		}
	}
}
