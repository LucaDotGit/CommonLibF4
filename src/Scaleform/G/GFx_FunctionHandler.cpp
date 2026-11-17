#include "Scaleform/G/GFx_FunctionHandler.hpp"

#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_MovieDef.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace Scaleform::GFx
{
	auto FunctionHandler::Params::GetMovie() const noexcept -> Ptr<Movie>
	{
		return Ptr(movie);
	}

	auto FunctionHandler::Params::GetArgs() const noexcept -> std::span<const Value>
	{
		return {args, argCount};
	}

	auto FunctionHandler::Params::GetArgsWithThisRef() const noexcept -> std::span<const Value>
	{
		return {argsWithThisRef, argCount + 1};
	}

	auto FunctionHandler::Params::GetNthArgOrNull(std::uint32_t a_index) const noexcept -> const Value&
	{
		return FunctionHandler::GetNthArgOrNull(GetArgs(), a_index);
	}

	auto FunctionHandler::GetNthArgOrNull(std::span<const Value> a_args, std::size_t a_index) -> const Value&
	{
		if (a_index >= a_args.size()) {
			return GFx::NULL_VALUE;
		}

		return a_args[a_index];
	}

	// NOLINTNEXTLINE(modernize-use-equals-default)
	FunctionHandler::FunctionHandler()
	{
		// REL::EmplaceVtable(this);
	}

	auto FunctionHandler::RegisterFunction(
		Movie& a_movie,
		Value& a_value,
		const char* a_name,
		const Ptr<FunctionHandler>& a_func,
		bool a_terminateOnFailure) -> bool
	{
		if (!a_func) {
			return false;
		}

		auto funcValue = Value();
		if (a_movie.CreateFunction(std::addressof(funcValue), a_func.get()) && a_value.SetMember(a_name, funcValue))
			[[likely]] {
			return true;
		}

		if (!a_terminateOnFailure) {
			return false;
		}

		const auto* movieDef = a_movie.GetMovieDef();
		REX::Fail(
			R"(Failed to register function "{}" on menu root "{}".)"sv,
			a_name,
			movieDef ? movieDef->GetFileURL() : "[Unknown]"sv);
	}

	auto FunctionHandler::RegisterFunction(
		Movie& a_movie,
		Value& a_value,
		const char* a_name,
		std::move_only_function<RegisterFunctor> a_func,
		bool a_terminateOnFailure) -> bool
	{
		class FunctionHandlerImpl final : public FunctionHandler
		{
		public:
			explicit FunctionHandlerImpl(REX::NotNull<std::move_only_function<RegisterFunctor>> a_func) :
				_func(std::move(a_func))
			{
			}

			~FunctionHandlerImpl() noexcept override = default;

			FunctionHandlerImpl(const FunctionHandlerImpl&) = delete;
			FunctionHandlerImpl(FunctionHandlerImpl&&) = delete;

			auto operator=(const FunctionHandlerImpl&) -> FunctionHandlerImpl& = delete;
			auto operator=(FunctionHandlerImpl&&) -> FunctionHandlerImpl& = delete;

			void Call(const Params& a_params) override
			{
				auto* returnValue = a_params.returnValue;
				if (!returnValue) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				const auto movie = a_params.GetMovie();
				if (!movie) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				auto* self = a_params.self;
				if (!self) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				*returnValue = std::invoke(_func.get(), *movie, *self, a_params.GetArgs());
			}

		private:
			REX::NotNull<std::move_only_function<RegisterFunctor>> _func;
		};

		const auto funcHandler = Scaleform::make_shared<FunctionHandlerImpl>(std::move(a_func));
		return RegisterFunction(a_movie, a_value, a_name, funcHandler, a_terminateOnFailure);
	}
}
