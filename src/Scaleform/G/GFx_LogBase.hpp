#pragma once

namespace Scaleform::GFx
{
	template <class T>
	class __declspec(novtable) LogBase
	{
	public:
		virtual ~LogBase() = default; // 0x00

		// add
		virtual auto IsVerboseActionErrors() const -> bool // 0x01
		{
			return true;
		}
	};
}
