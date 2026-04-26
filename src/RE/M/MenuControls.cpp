#include "RE/M/MenuControls.hpp"

namespace RE
{
	MenuControls* MenuControls::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<MenuControls**>{ ID::MenuControls::Singleton };
		return *SINGLETON;
	}

	bool MenuControls::QueueScreenshot() const
	{
		if (!screenshotHandler || screenshotHandler->screenshotQueued) {
			return false;
		}

		screenshotHandler->screenshotQueued = true;
		return true;
	}
}
