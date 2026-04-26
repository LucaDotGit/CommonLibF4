#pragma once

namespace Scaleform::GFx::AS3::ClassTraits
{
	class Traits;
}

namespace Scaleform::GFx::AS3::Instances
{
	class Function;
	class ThunkFunction;
}

namespace Scaleform::GFx::AS3::Instances::fl
{
	class Namespace;
}

namespace Scaleform::GFx::AS3::InstanceTraits
{
	class Traits;
}

namespace Scaleform::GFx::AS3
{
	class ASStringNode;
	class Class;
	class Object;
	class ThunkInfo;
	class Traits;
	class WeakProxy;

	class Value
	{
	public:
		class Extra
		{
		public:
			// members
			WeakProxy* weakProxy; // 00
		};
		static_assert(sizeof(Extra) == 0x08);

		union V1U
		{
		public:
			bool vbool;
			std::int32_t vint;
			std::uint32_t vuint;
			ASStringNode* vstr;
			Object* vobj;
			Class* vclass;
			Instances::Function* vfunct;
			const ThunkInfo* vthunk;
			Instances::ThunkFunction* vthunkfunct;
			Instances::fl::Namespace* vnamespace;
			InstanceTraits::Traits* instanceTraits;
			ClassTraits::Traits* classTraits;
		};

		union V2U
		{
		public:
			Object* vobj;
			const Traits* traits;
		};

		class VStruct
		{
		public:
			// members
			V1U v1; // 00
			V2U v2; // 08
		};
		static_assert(sizeof(VStruct) == 0x10);

		union VU
		{
		public:
			REX::Float64 vnumber;
			VStruct vstruct;
		};

		// members
		std::uint32_t flags; // 00
		Extra bonus;		 // 08
		VU value;			 // 10
	};
	static_assert(sizeof(Value) == 0x20);
}
