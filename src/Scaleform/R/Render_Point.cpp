#include "Scaleform/R/Render_Point.hpp"

namespace Scaleform::Render
{
	template class Point<REX::Float32>;
	static_assert(sizeof(Point<REX::Float32>) == 0x08);

	template void swap(Point<REX::Float32>&, Point<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<Scaleform::Render::Point<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<Scaleform::Render::Point<REX::Float32>>;
}
#endif
