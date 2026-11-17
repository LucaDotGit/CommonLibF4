#include "F4SE/Menus/MenuAssetInfo.hpp"

#include "RE/B/BSScaleformManager.hpp"
#include "RE/I/IMenu.hpp"
#include "REX/Contract.hpp"
#include "REX/Exception.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace F4SE::Menus
{
	MenuAssetInfo::MenuAssetInfo(
		std::string a_menuName,
		std::filesystem::path a_assetFilePath,
		std::string a_rootVarPath) :
		_menuName(std::move(a_menuName)),
		_assetFilePath(std::move(a_assetFilePath)),
		_rootVarPath(std::move(a_rootVarPath))
	{
	}

	MenuAssetInfo::~MenuAssetInfo() noexcept = default;

	auto MenuAssetInfo::LoadAssetForMenu(RE::IMenu& a_menuInstance) const -> bool
	{
		const auto onSuccessCallback = REX::TryCatch<std::bad_weak_ptr>(
			[this]() -> Scaleform::Ptr<AssetLoadSuccessCallback> {
				return Scaleform::make_shared<AssetLoadSuccessCallback>(weak_from_this());
			},
			[](const std::bad_weak_ptr& a_error) noexcept -> Scaleform::Ptr<AssetLoadSuccessCallback> {
				std::ignore = a_error;
				REX::Assert(false);
				return nullptr;
			});

		const auto onFailureCallback = REX::TryCatch<std::bad_weak_ptr>(
			[this]() -> Scaleform::Ptr<AssetLoadFailureCallback> {
				return Scaleform::make_shared<AssetLoadFailureCallback>(weak_from_this());
			},
			[](const std::bad_weak_ptr& a_error) noexcept -> Scaleform::Ptr<AssetLoadFailureCallback> {
				std::ignore = a_error;
				REX::Assert(false);
				return nullptr;
			});

		return RE::BSScaleformManager::LoadAsset(
			a_menuInstance,
			_assetFilePath.generic_string().data(),
			_rootVarPath.data(),
			onSuccessCallback,
			onFailureCallback);
	}
}
