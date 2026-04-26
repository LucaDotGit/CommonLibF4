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

		constexpr ScriptCompiler& operator=(const ScriptCompiler&) = delete;
		constexpr ScriptCompiler& operator=(ScriptCompiler&&) noexcept = default;
	};
	static_assert(std::is_empty_v<ScriptCompiler>);
}
