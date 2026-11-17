#pragma once

#include "RE/N/NiTArray.hpp"

namespace RE::BSGraphics
{
	enum class TextureFilterMode : std::int32_t;
}

namespace RE
{
	class BSTriShape;
	class ImageSpaceManager;
	class ImageSpaceEffectParam;
	class ImageSpaceTexture;

	class __declspec(novtable) ImageSpaceEffect
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffect;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffect;

		class EffectDesc
		{
		public:
			// members
			std::uint32_t startEffect;		// 0x00
			std::uint32_t lastEffect;		// 0x04
			ImageSpaceEffect* parentEffect; // 0x08
			std::uint64_t labelWait;		// 0x10
			std::uint64_t* writeLabel;		// 0x18
		};

		static_assert(sizeof(EffectDesc) == 0x20);

		class EffectInput
		{
		public:
			// members
			std::int32_t texIndex;					  // 0x00
			BSGraphics::TextureFilterMode filterMode; // 0x04
		};

		static_assert(sizeof(EffectInput) == 0x08);

		virtual ~ImageSpaceEffect(); // 0x00

		// add
		virtual void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param); // 0x01
		virtual void Dispatch(
			ImageSpaceEffectParam* a_param,
			bool a_useAsyncPipe,
			std::uint32_t a_effect,
			EffectDesc* a_effectDesc);													  // 0x02
		virtual void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param); // 0x03
		virtual void Shutdown();														  // 0x04
		virtual void BorrowTextures(ImageSpaceEffectParam* a_param);					  // 0x05
		virtual void ReturnTextures();													  // 0x06
		virtual void UpdateComputeShaderParam(std::uint32_t a_effect);					  // 0x07
		virtual auto IsActive() -> bool;												  // 0x08
		virtual auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool;				  // 0x09
		virtual auto SetRenderStates(ImageSpaceEffectParam* a_param) -> bool;			  // 0x0A
		virtual auto RestoreRenderStates(ImageSpaceEffectParam* a_param) -> bool;		  // 0x0B

		// members
		bool isActive;											   // 0x08
		bool paramsChanged;										   // 0x09
		NiTPrimitiveArray<ImageSpaceEffect*> effectList;		   // 0x10
		NiTPrimitiveArray<ImageSpaceEffectParam*> effectParamList; // 0x28
		NiTPrimitiveArray<ImageSpaceTexture*> textures;			   // 0x40
		NiTPrimitiveArray<ImageSpaceTexture*> vsTextures;		   // 0x58
		NiTPrimitiveArray<EffectInput*> effectInputs;			   // 0x70
		NiTPrimitiveArray<std::int32_t*> effectOutput;			   // 0x88
		bool isComputeShader;									   // 0xA0
		std::uint32_t nbOutput;									   // 0xA4
		bool useDynamicResolution;								   // 0xA8
	};

	static_assert(sizeof(ImageSpaceEffect) == 0xB0);
}
