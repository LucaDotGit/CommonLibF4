#include "Scaleform/G/GFx_ASMovieRootBase.hpp"

#include "Scaleform/G/GFx_Value.hpp"

namespace Scaleform::GFx
{
	void ASMovieRootBase::CreateObject(Value* a_value, const char* a_className, std::span<const Value> a_args)
	{
		CreateObject(a_value, a_className, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	void ASMovieRootBase::CreateArray(Value* a_value, std::uint32_t a_size)
	{
		CreateArray(a_value);

		if (a_size == 0 || !a_value || !a_value->IsArray()) {
			return;
		}

		a_value->SetArraySize(a_size);
	}

	bool ASMovieRootBase::Invoke(const char* a_methodName, std::span<const Value> a_args)
	{
		return Invoke(a_methodName, nullptr, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	bool ASMovieRootBase::Invoke(const char* a_methodName, Value* a_result, std::span<const Value> a_args)
	{
		return Invoke(a_methodName, a_result, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}
}
