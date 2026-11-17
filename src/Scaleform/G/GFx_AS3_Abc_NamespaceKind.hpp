#pragma once

namespace Scaleform::GFx::AS3::Abc
{
	enum class NamespaceKind : std::int32_t
	{
		Undefined = -1,
		Public = 0,
		Protected = 1,
		StaticProtected = 2,
		Private = 3,
		Explicit = 4,
		PackageInternal = 5
	};
}
