#include "Scaleform/G/GFx_FunctionHandler.hpp"

#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace Scaleform::GFx
{
	Ptr<Movie> FunctionHandler::Params::GetMovie() const
	{
		return Ptr{ movie };
	}

	Ptr<ASMovieRootBase> FunctionHandler::Params::GetMovieRoot() const
	{
		return movie ? movie->asMovieRoot : nullptr;
	}

	std::span<const Value> FunctionHandler::Params::GetArgs() const noexcept
	{
		return { args, argCount };
	}

	std::span<const Value> FunctionHandler::Params::GetArgsWithThisRef() const noexcept
	{
		return { argsWithThisRef, argCount + 1 };
	}

	const Value& FunctionHandler::Params::GetNthArgOrNull(std::uint32_t a_index) const noexcept
	{
		if (a_index >= argCount) {
			return NULL_VALUE;
		}

		return args[a_index];
	}
}
