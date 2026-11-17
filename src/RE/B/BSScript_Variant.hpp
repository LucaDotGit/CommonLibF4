#pragma once

namespace RE::BSScript
{
	class Variable;

	using SharedVariant = REX::Observer<const Variable*>;
	using UniqueVariant = std::unique_ptr<Variable>;
}
