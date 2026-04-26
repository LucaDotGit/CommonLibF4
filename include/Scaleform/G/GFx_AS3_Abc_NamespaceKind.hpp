#pragma once

namespace Scaleform::GFx::AS3::Abc
{
	enum class NamespaceKind : std::int32_t
	{
		kUndefined = -1,
		kPublic = 0,
		kProtected = 1,
		kStaticProtected = 2,
		kPrivate = 3,
		kExplicit = 4,
		kPackageInternal = 5
	};
}
