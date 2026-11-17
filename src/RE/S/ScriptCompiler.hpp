#pragma once

namespace RE
{
	class ScriptCompiler
	{
	public:
		constexpr ScriptCompiler() noexcept = default;
		constexpr ~ScriptCompiler() noexcept = default;

		constexpr ScriptCompiler(const ScriptCompiler&) = delete;
		constexpr ScriptCompiler(ScriptCompiler&&) noexcept = default;

		constexpr auto operator=(const ScriptCompiler&) -> ScriptCompiler& = delete;
		constexpr auto operator=(ScriptCompiler&&) noexcept -> ScriptCompiler& = default;
	};

	static_assert(std::is_empty_v<ScriptCompiler>);
}
