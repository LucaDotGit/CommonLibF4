#pragma once

#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	class IMenu;
}

namespace Scaleform::GFx
{
	class Movie;
}

namespace F4SE::Menus
{
	class ILoadableMenuAsset : public std::enable_shared_from_this<ILoadableMenuAsset>
	{
	public:
		ILoadableMenuAsset() noexcept = default;
		virtual ~ILoadableMenuAsset() noexcept = default;

		ILoadableMenuAsset(const ILoadableMenuAsset&) noexcept = default;
		ILoadableMenuAsset(ILoadableMenuAsset&&) noexcept = default;

		auto operator=(const ILoadableMenuAsset&) noexcept -> ILoadableMenuAsset& = default;
		auto operator=(ILoadableMenuAsset&&) noexcept -> ILoadableMenuAsset& = default;

		virtual auto LoadAssetForMenu(RE::IMenu& a_menu) const -> bool = 0;

		virtual void OnAssetLoadSuccess(const Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie) const;
		virtual void OnAssetLoadFailure(const Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie) const;

	protected:
		class AssetLoadSuccessCallback final : public Scaleform::GFx::FunctionHandler
		{
		public:
			explicit AssetLoadSuccessCallback(std::weak_ptr<const ILoadableMenuAsset> a_menuAsset);
			~AssetLoadSuccessCallback() noexcept override;

			AssetLoadSuccessCallback(const AssetLoadSuccessCallback&) = delete;
			AssetLoadSuccessCallback(AssetLoadSuccessCallback&&) = delete;

			auto operator=(const AssetLoadSuccessCallback&) -> AssetLoadSuccessCallback& = delete;
			auto operator=(AssetLoadSuccessCallback&&) -> AssetLoadSuccessCallback& = delete;

			void Call(const Scaleform::GFx::FunctionHandler::Params& a_params) override;

		private:
			std::weak_ptr<const ILoadableMenuAsset> _menuAsset;
		};

		class AssetLoadFailureCallback final : public Scaleform::GFx::FunctionHandler
		{
		public:
			explicit AssetLoadFailureCallback(std::weak_ptr<const ILoadableMenuAsset> a_menuAsset);
			~AssetLoadFailureCallback() noexcept override;

			AssetLoadFailureCallback(const AssetLoadFailureCallback&) = delete;
			AssetLoadFailureCallback(AssetLoadFailureCallback&&) = delete;

			auto operator=(const AssetLoadFailureCallback&) -> AssetLoadFailureCallback& = delete;
			auto operator=(AssetLoadFailureCallback&&) -> AssetLoadFailureCallback& = delete;

			void Call(const Scaleform::GFx::FunctionHandler::Params& a_params) override;

		private:
			std::weak_ptr<const ILoadableMenuAsset> _menuAsset;
		};
	};
}
