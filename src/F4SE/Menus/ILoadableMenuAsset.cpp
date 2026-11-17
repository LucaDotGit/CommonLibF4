#include "F4SE/Menus/ILoadableMenuAsset.hpp"

#include "REX/Contract.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace F4SE::Menus
{
	void ILoadableMenuAsset::OnAssetLoadSuccess(
		[[maybe_unused]] const Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie) const
	{
	}

	void ILoadableMenuAsset::OnAssetLoadFailure(
		[[maybe_unused]] const Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie) const
	{
	}

	ILoadableMenuAsset::AssetLoadSuccessCallback::AssetLoadSuccessCallback(
		std::weak_ptr<const ILoadableMenuAsset> a_menuAsset) :
		_menuAsset(std::move(a_menuAsset))
	{
	}

	ILoadableMenuAsset::AssetLoadSuccessCallback::~AssetLoadSuccessCallback() noexcept = default;

	void ILoadableMenuAsset::AssetLoadSuccessCallback::Call(const Scaleform::GFx::FunctionHandler::Params& a_params)
	{
		const auto movie = a_params.GetMovie();
		if (!movie) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		const auto sharedMenuAsset = _menuAsset.lock();
		if (!sharedMenuAsset) {
			return;
		}

		sharedMenuAsset->OnAssetLoadSuccess(movie);
	}

	ILoadableMenuAsset::AssetLoadFailureCallback::AssetLoadFailureCallback(
		std::weak_ptr<const ILoadableMenuAsset> a_menuAsset) :
		_menuAsset(std::move(a_menuAsset))
	{
	}

	ILoadableMenuAsset::AssetLoadFailureCallback::~AssetLoadFailureCallback() noexcept = default;

	void ILoadableMenuAsset::AssetLoadFailureCallback::Call(const Scaleform::GFx::FunctionHandler::Params& a_params)
	{
		const auto movie = a_params.GetMovie();
		if (!movie) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		const auto sharedMenuAsset = _menuAsset.lock();
		if (!sharedMenuAsset) {
			return;
		}

		sharedMenuAsset->OnAssetLoadFailure(movie);
	}
}
