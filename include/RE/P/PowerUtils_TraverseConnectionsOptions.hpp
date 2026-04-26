#pragma once

namespace RE::PowerUtils
{
	class TraverseConnectionsOptions
	{
	public:
		// members
		std::uint32_t ignoreMode; // 00
		bool wiredOnly;			  // 04
		bool inputsOnly;		  // 05
	};
	static_assert(sizeof(TraverseConnectionsOptions) == 0x08);
}
