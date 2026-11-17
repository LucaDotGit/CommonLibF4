#pragma once

#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class ASMovieRootBase;
	class Movie;
	class Value;

	class /*__declspec(novtable)*/ FunctionHandler : public RefCountBase<FunctionHandler, 2> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__GFx__FunctionHandler;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__GFx__FunctionHandler;

		using RegisterFunctor = Value(Movie& a_movie, Value& a_self, std::span<const Value> a_args) const;

		class Params
		{
		public:
			[[nodiscard]]
			auto GetMovie() const noexcept -> Ptr<Movie>;

			[[nodiscard]]
			auto GetArgs() const noexcept -> std::span<const Value>;
			[[nodiscard]]
			auto GetArgsWithThisRef() const noexcept -> std::span<const Value>;

			[[nodiscard]]
			auto GetNthArgOrNull(std::uint32_t a_index) const noexcept -> const Value&;

			// members
			mutable Value* returnValue; // 0x00
			mutable Movie* movie;		// 0x08
			mutable Value* self;		// 0x10
			Value* argsWithThisRef;		// 0x18
			Value* args;				// 0x20
			std::uint32_t argCount;		// 0x28
			void* userData;				// 0x30
		};

		static_assert(sizeof(Params) == 0x38);

		FunctionHandler();

		~FunctionHandler() override = default; // 0x00

		// add
		virtual void Call(const Params& a_params) = 0; // 0x01

		[[nodiscard]]
		static auto GetNthArgOrNull(std::span<const Value> a_args, std::size_t a_index) -> const Value&;

		static auto RegisterFunction(
			Movie& a_movie,
			Value& a_value,
			const char* a_name,
			const Ptr<FunctionHandler>& a_func,
			bool a_terminateOnFailure = false) -> bool;
		static auto RegisterFunction(
			Movie& a_movie,
			Value& a_value,
			const char* a_name,
			std::move_only_function<RegisterFunctor> a_func,
			bool a_terminateOnFailure = false) -> bool;
	};

	static_assert(sizeof(FunctionHandler) == 0x10);
}

#define SCALEFORM_BASIC_REGISTER_FUNCTION(a_menuRoot, a_codeObject, a_funcName, a_func, a_terminateOnFailure) \
	::Scaleform::GFx::FunctionHandler::RegisterFunction(                                                      \
		a_menuRoot,                                                                                           \
		a_codeObject,                                                                                         \
		a_funcName,                                                                                           \
		a_func,                                                                                               \
		a_terminateOnFailure)

#define SCALEFORM_REGISTER_FUNCTION(a_menuRoot, a_codeObject, a_funcType, ...) \
	SCALEFORM_BASIC_REGISTER_FUNCTION(                                         \
		a_menuRoot,                                                            \
		a_codeObject,                                                          \
		#a_funcType,                                                           \
		::Scaleform::make_shared<a_funcType>(__VA_ARGS__),                     \
		false)

#define SCALEFORM_REGISTER_FUNCTION_STUB(a_menuRoot, a_codeObject, a_func)              \
	SCALEFORM_BASIC_REGISTER_FUNCTION(a_menuRoot, a_codeObject, #a_func, a_func, false)

#define SCALEFORM_REGISTER_FUNCTION_OR_FAIL(a_menuRoot, a_codeObject, a_funcType, ...) \
	SCALEFORM_BASIC_REGISTER_FUNCTION(                                                 \
		a_menuRoot,                                                                    \
		a_codeObject,                                                                  \
		#a_funcType,                                                                   \
		::Scaleform::make_shared<a_funcType>(__VA_ARGS__),                             \
		true)

#define SCALEFORM_REGISTER_FUNCTION_STUB_OR_FAIL(a_menuRoot, a_codeObject, a_func)     \
	SCALEFORM_BASIC_REGISTER_FUNCTION(a_menuRoot, a_codeObject, #a_func, a_func, true)
