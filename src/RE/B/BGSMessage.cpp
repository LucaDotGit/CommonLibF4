#include "RE/B/BGSMessage.hpp"

#include "RE/M/MESSAGEBOX_BUTTON.hpp"

namespace RE
{
	void BGSMessage::SetButtons(std::span<std::unique_ptr<MESSAGEBOX_BUTTON>> a_buttons)
	{
		ClearButtons();

		for (auto& button : a_buttons) {
			if (!button) {
				continue;
			}

			buttonList.push_back(button.release());
		}
	}

	void BGSMessage::ClearButtons()
	{
		for (auto*& button : buttonList) {
			if (!button) {
				continue;
			}

			delete button;
			button = nullptr;
		}

		buttonList.clear();
	}
}
