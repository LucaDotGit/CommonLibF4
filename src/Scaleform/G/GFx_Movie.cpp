#include "Scaleform/G/GFx_Movie.hpp"

#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace Scaleform::GFx
{
	bool Movie::IsAvailable(const char* a_pathToVar) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->IsAvailable(a_pathToVar);
	}

	bool Movie::CreateString(Value* a_value, const char* a_string) const
	{
		if (!asMovieRoot) {
			return false;
		}

		asMovieRoot->CreateString(a_value, a_string);
		return true;
	}

	bool Movie::CreateStringW(Value* a_value, const wchar_t* a_string) const
	{
		if (!asMovieRoot) {
			return false;
		}

		asMovieRoot->CreateStringW(a_value, a_string);
		return true;
	}

	bool Movie::CreateObject(Value* a_value, const char* a_className, const Value* a_args, std::uint32_t a_numArgs) const
	{
		if (!asMovieRoot) {
			return false;
		}

		asMovieRoot->CreateObject(a_value, a_className, a_args, a_numArgs);
		return true;
	}

	bool Movie::CreateObject(Value* a_value, const char* a_className, std::span<const Value> a_args) const
	{
		if (!asMovieRoot) {
			return false;
		}

		asMovieRoot->CreateObject(a_value, a_className, a_args);
		return true;
	}

	bool Movie::CreateArray(Value* a_value, std::uint32_t a_size) const
	{
		if (!asMovieRoot) {
			return false;
		}

		asMovieRoot->CreateArray(a_value, a_size);
		return true;
	}

	bool Movie::CreateFunction(Value* a_value, FunctionHandler* a_func, void* a_userData) const
	{
		if (!asMovieRoot) {
			return false;
		}

		asMovieRoot->CreateFunction(a_value, a_func, a_userData);
		return true;
	}

	bool Movie::GetVariable(Value* a_val, const char* a_pathToVar) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->GetVariable(a_val, a_pathToVar);
	}

	bool Movie::SetVariable(const char* a_pathToVar, const Value& a_value, Movie::SetVarType a_setType) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->SetVariable(a_pathToVar, a_value, a_setType);
	}

	bool Movie::GetVariableArray(Movie::SetArrayType a_type, const char* a_pathToVar, std::uint32_t a_index, void* a_data, std::uint32_t a_count) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->GetVariableArray(a_type, a_pathToVar, a_index, a_data, a_count);
	}

	bool Movie::SetVariableArray(Movie::SetArrayType a_type, const char* a_pathToVar, std::uint32_t a_index, const void* a_data, std::uint32_t a_count, Movie::SetVarType a_setType) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->SetVariableArray(a_type, a_pathToVar, a_index, a_data, a_count, a_setType);
	}

	std::uint32_t Movie::GetVariableArraySize(const char* a_pathToVar) const
	{
		if (!asMovieRoot) {
			return 0;
		}

		return asMovieRoot->GetVariableArraySize(a_pathToVar);
	}

	bool Movie::SetVariableArraySize(const char* a_pathToVar, std::uint32_t a_count, Movie::SetVarType a_setType) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->SetVariableArraySize(a_pathToVar, a_count, a_setType);
	}

	bool Movie::Invoke(const char* a_pathToMethod, Value* a_result, const Value* a_args, std::uint32_t a_numArgs) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->Invoke(a_pathToMethod, a_result, a_args, a_numArgs);
	}

	bool Movie::Invoke(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, ...) const // NOLINT(modernize-avoid-variadic-functions)
	{
		if (!asMovieRoot) {
			return false;
		}

		auto* args = va_list();
		va_start(args, a_argFmt);
		const auto result = asMovieRoot->InvokeArgs(a_pathToMethod, a_result, a_argFmt, args);
		va_end(args);
		return result;
	}

	bool Movie::InvokeArgs(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, std::va_list a_args) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->InvokeArgs(a_pathToMethod, a_result, a_argFmt, a_args);
	}

	bool Movie::Invoke(const char* a_methodName, std::span<const Value> a_args) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->Invoke(a_methodName, nullptr, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	bool Movie::Invoke(const char* a_methodName, Value* a_result, std::span<const Value> a_args) const
	{
		if (!asMovieRoot) {
			return false;
		}

		return asMovieRoot->Invoke(a_methodName, a_result, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	void Movie::Release()
	{
		using FuncType = decltype(&Movie::Release);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Movie::Release };
		FUNC(this);
	}
}
