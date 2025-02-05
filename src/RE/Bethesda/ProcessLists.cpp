#include "RE/Bethesda/ProcessLists.hpp"

#include "RE/Bethesda/BSContainer.hpp"

namespace RE
{
	BSContainer::ForEachResult ProcessLists::ForEachActor(std::function<BSContainer::ForEachResult(Actor*)> a_callback) const
	{
		for (const auto* list : allProcesses) {
			if (!list) {
				continue;
			}

			for (const auto actorHandle : *list) {
				if (actorHandle && a_callback(actorHandle.get().get()) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult ProcessLists::ForEachActorInProcess(PROCESS_LEVEL a_processLevel, std::function<BSContainer::ForEachResult(Actor*)> a_callback) const
	{
		if (a_processLevel > PROCESS_LEVEL::kProcessLevel_Max) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto* list = allProcesses[a_processLevel];
		if (!list) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (const auto actorHandle : *list) {
			if (actorHandle && a_callback(actorHandle.get().get()) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult ProcessLists::ForEachHighActor(std::function<BSContainer::ForEachResult(Actor*)> a_callback) const
	{
		return ForEachActorInProcess(PROCESS_LEVEL::kProcessLevel_High, a_callback);
	}

	BSContainer::ForEachResult ProcessLists::ForEachMagicTempEffect(std::function<BSContainer::ForEachResult(BSTempEffect*)> a_callback) const
	{
		const auto lock = BSAutoLock{ magicEffectsLock };

		for (const auto tempEffectPtr : magicEffects) {
			auto* tempEffect = tempEffectPtr.get();
			if (tempEffect && a_callback(tempEffect) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult ProcessLists::ForEachModelEffect(std::function<BSContainer::ForEachResult(ModelReferenceEffect*)> a_callback) const
	{
		return ForEachMagicTempEffect([&](BSTempEffect* a_tempEffect) {
			auto* modelEffect = a_tempEffect->As<ModelReferenceEffect>();
			if (modelEffect && a_callback(modelEffect) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		});
	}

	BSContainer::ForEachResult ProcessLists::ForEachShaderEffect(std::function<BSContainer::ForEachResult(ShaderReferenceEffect*)> a_callback) const
	{
		return ForEachMagicTempEffect([&](BSTempEffect* a_tempEffect) {
			auto* shaderEffect = a_tempEffect->As<ShaderReferenceEffect>();
			if (shaderEffect && a_callback(shaderEffect) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		});
	}
}
