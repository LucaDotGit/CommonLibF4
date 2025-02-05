#include "RE/Bethesda/BSScript/StructTypeInfo.hpp"

namespace RE
{
	namespace BSScript
	{
		TypeInfo::RawType StructTypeInfo::GetRawType() const
		{
			return TypeInfo::RawType::kStruct;
		}
	}
}
