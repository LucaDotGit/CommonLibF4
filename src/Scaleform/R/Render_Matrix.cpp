#include "Scaleform/R/Render_Matrix.hpp"

namespace Scaleform::Render
{
	template class Matrix2x4<REX::Float32>;
	static_assert(sizeof(Matrix2x4<REX::Float32>) == 0x20);

	template void swap(Matrix2x4<REX::Float32>&, Matrix2x4<REX::Float32>&) noexcept;

	template class Matrix3x4<REX::Float32>;
	static_assert(sizeof(Matrix3x4<REX::Float32>) == 0x30);

	template void swap(Matrix3x4<REX::Float32>&, Matrix3x4<REX::Float32>&) noexcept;

	template class Matrix4x4<REX::Float32>;
	static_assert(sizeof(Matrix4x4<REX::Float32>) == 0x40);

	template void swap(Matrix4x4<REX::Float32>&, Matrix4x4<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<Scaleform::Render::Matrix2x4<REX::Float32>>;
	template struct formatter<Scaleform::Render::Matrix3x4<REX::Float32>>;
	template struct formatter<Scaleform::Render::Matrix4x4<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<Scaleform::Render::Matrix2x4<REX::Float32>>;
	template struct formatter<Scaleform::Render::Matrix3x4<REX::Float32>>;
	template struct formatter<Scaleform::Render::Matrix4x4<REX::Float32>>;
}
#endif
