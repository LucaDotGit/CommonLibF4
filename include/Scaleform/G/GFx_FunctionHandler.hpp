#pragma once

#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class ASMovieRootBase;
	class Movie;
	class Value;

	class __declspec(novtable) FunctionHandler
		: public RefCountBase<FunctionHandler, 2> // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__GFx__FunctionHandler };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__GFx__FunctionHandler };

		class Params
		{
		public:
			[[nodiscard]] Ptr<Movie> GetMovie() const;
			[[nodiscard]] Ptr<ASMovieRootBase> GetMovieRoot() const;

			[[nodiscard]] std::span<const Value> GetArgs() const noexcept;
			[[nodiscard]] std::span<const Value> GetArgsWithThisRef() const noexcept;

			[[nodiscard]] const Value& GetNthArgOrNull(std::uint32_t a_index) const noexcept;

			// members
			mutable Value* returnValue; // 00
			mutable Movie* movie;		// 08
			mutable Value* self;		// 10
			Value* argsWithThisRef;		// 18
			Value* args;				// 20
			std::uint32_t argCount;		// 28
			void* userData;				// 30
		};
		static_assert(sizeof(Params) == 0x38);

		~FunctionHandler() override = default; // 00

		// add
		virtual void Call(const Params& a_params) = 0; // 01
	};
	static_assert(sizeof(FunctionHandler) == 0x10);
}

#define RE_REGISTER_SF_FUNCTION(a_menuRoot, a_codeObject, a_func, ...)                    \
	{                                                                                     \
		auto a_func##Val = ::Scaleform::GFx::Value();                                     \
		a_menuRoot->CreateFunction(std::addressof(a_func##Val), new a_func(__VA_ARGS__)); \
		if (!a_codeObject->SetMember(#a_func, a_func##Val)) [[unlikely]] {                \
			REX::Assert(false);                                                           \
		}                                                                                 \
	}
