#pragma once

#include "Scaleform/M/Memory.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"
#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/Render_EdgeAAMode.hpp"
#include "Scaleform/R/Render_Matrix2x4.hpp"
#include "Scaleform/R/Render_Matrix3x4.hpp"
#include "Scaleform/R/Render_Matrix4x4.hpp"

namespace Scaleform::Render
{
	class Cxform;
}

namespace Scaleform::GFx
{
	class MemberValueSet;
	class Movie;
	class MovieImpl;

	class Value
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__GFx__Value;

		enum class ValueType : std::int32_t
		{
			Undefined = 0,
			Null = 1,
			Boolean = 2,
			Int = 3,
			UInt = 4,
			Number = 5,
			String = 6,
			StringW = 7,
			Object = 8,
			Array = 9,
			DisplayObject = 10,
			Closure = 11,

			OrphanedBit = 1 << 5,
			ManagedBit = 1 << 6,
			ConvertBit = 1 << 7,

			_TypeMask = ConvertBit | 0x0F,

			ConvertBoolean = ConvertBit | Boolean,
			ConvertInt = ConvertBit | Int,
			ConvertUInt = ConvertBit | UInt,
			ConvertNumber = ConvertBit | Number,
			ConvertString = ConvertBit | String,
			ConvertStringW = ConvertBit | StringW
		};

		union ValueUnion
		{
		public:
			constexpr ValueUnion() noexcept = default;
			constexpr ~ValueUnion() noexcept = default;

			explicit ValueUnion(std::nullptr_t) noexcept;
			explicit ValueUnion(bool a_rhs) noexcept;
			explicit ValueUnion(std::int32_t a_rhs) noexcept;
			explicit ValueUnion(std::uint32_t a_rhs) noexcept;
			explicit ValueUnion(REX::Float64 a_rhs) noexcept;
			explicit ValueUnion(const char* a_rhs) noexcept;
			explicit ValueUnion(const wchar_t* a_rhs) noexcept;
			explicit ValueUnion(REX::ZStringView a_rhs) noexcept;
			explicit ValueUnion(REX::ZWStringView a_rhs) noexcept;

			constexpr ValueUnion(const ValueUnion&) noexcept = default;
			constexpr ValueUnion(ValueUnion&&) noexcept = default;

			auto operator=(std::nullptr_t) noexcept -> ValueUnion&;
			auto operator=(bool a_rhs) noexcept -> ValueUnion&;
			auto operator=(std::int32_t a_rhs) noexcept -> ValueUnion&;
			auto operator=(std::uint32_t a_rhs) noexcept -> ValueUnion&;
			auto operator=(REX::Float64 a_rhs) noexcept -> ValueUnion&;
			auto operator=(const char* a_rhs) noexcept -> ValueUnion&;
			auto operator=(const wchar_t* a_rhs) noexcept -> ValueUnion&;
			auto operator=(REX::ZStringView a_rhs) noexcept -> ValueUnion&;
			auto operator=(REX::ZWStringView a_rhs) noexcept -> ValueUnion&;

			constexpr auto operator=(const ValueUnion&) noexcept -> ValueUnion& = default;
			constexpr auto operator=(ValueUnion&&) noexcept -> ValueUnion& = default;

			void swap(ValueUnion& a_other) noexcept;

			std::nullptr_t null{nullptr};
			std::nullptr_t undefined;
			bool boolean;
			std::int32_t int32;
			std::uint32_t uint32;
			REX::Float64 number;
			const char* string;
			const char** mstring;
			const wchar_t* wstring;
			void* data;
		};

		static_assert(sizeof(ValueUnion) == 0x08);

		class DisplayInfo
		{
		public:
			enum class SetFlags : std::uint16_t
			{
				None = 0,
				kX = 1 << 0,
				kY = 1 << 1,
				Rotation = 1 << 2,
				XScale = 1 << 3,
				YScale = 1 << 4,
				Alpha = 1 << 5,
				Visible = 1 << 6,
				kZ = 1 << 7,
				XRotation = 1 << 8,
				YRotation = 1 << 9,
				ZScale = 1 << 10,
				FOV = 1 << 11,
				ProjMatrix3D = 1 << 12,
				ViewMatrix3D = 1 << 13,
				EdgeAAMode = 1 << 14
			};

			constexpr DisplayInfo() noexcept = default;
			constexpr ~DisplayInfo() noexcept = default;

			constexpr DisplayInfo(const DisplayInfo&) noexcept = default;
			constexpr DisplayInfo(DisplayInfo&&) noexcept = default;

			constexpr auto operator=(const DisplayInfo&) noexcept -> DisplayInfo& = default;
			constexpr auto operator=(DisplayInfo&&) noexcept -> DisplayInfo& = default;

			[[nodiscard]]
			auto GetX() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetY() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetZ() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetXScale() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetYScale() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetZScale() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetRotation() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetXRotation() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetYRotation() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetAlpha() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetVisible() const noexcept -> bool;
			[[nodiscard]]
			auto GetFOV() const noexcept -> REX::Float64;
			[[nodiscard]]
			auto GetViewMatrix3D() const noexcept -> const Render::Matrix3x4<REX::Float32>*;
			[[nodiscard]]
			auto GetProjectionMatrix3D() const noexcept -> const Render::Matrix4x4F*;
			[[nodiscard]]
			auto GetEdgeAAMode() const noexcept -> Render::EdgeAAMode;

			void SetX(REX::Float64 a_x) noexcept;
			void SetY(REX::Float64 a_y) noexcept;
			void SetZ(REX::Float64 a_z) noexcept;
			void SetXScale(REX::Float64 a_xScale) noexcept;
			void SetYScale(REX::Float64 a_yScale) noexcept;
			void SetZScale(REX::Float64 a_zScale) noexcept;
			void SetRotation(REX::Float64 a_rotation) noexcept;
			void SetXRotation(REX::Float64 a_xRotation) noexcept;
			void SetYRotation(REX::Float64 a_yRotation) noexcept;
			void SetAlpha(REX::Float64 a_alpha) noexcept;
			void SetVisible(bool a_visible) noexcept;
			void SetFOV(REX::Float64 a_fov) noexcept;
			void SetViewMatrix3D(std::optional<Render::Matrix3x4<REX::Float32>> a_matrix) noexcept;
			void SetProjectionMatrix3D(std::optional<Render::Matrix4x4F> a_matrix) noexcept;
			void SetEdgeAAMode(Render::EdgeAAMode a_mode) noexcept;

			void swap(DisplayInfo& a_other) noexcept;

		private:
			// members
			REX::Float64 _x{static_cast<REX::Float64>(0)};											  // 0x00
			REX::Float64 _y{static_cast<REX::Float64>(0)};											  // 0x08
			REX::Float64 _rotation{static_cast<REX::Float64>(0)};									  // 0x10
			REX::Float64 _xScale{static_cast<REX::Float64>(0)};										  // 0x18
			REX::Float64 _yScale{static_cast<REX::Float64>(0)};										  // 0x20
			REX::Float64 _alpha{static_cast<REX::Float64>(0)};										  // 0x28
			REX::Float64 _z{static_cast<REX::Float64>(0)};											  // 0x30
			REX::Float64 _xRotation{static_cast<REX::Float64>(0)};									  // 0x38
			REX::Float64 _yRotation{static_cast<REX::Float64>(0)};									  // 0x40
			REX::Float64 _zScale{static_cast<REX::Float64>(0)};										  // 0x48
			REX::Float64 _fov{static_cast<REX::Float64>(0)};										  // 0x50
			alignas(0x10) Render::Matrix3x4<REX::Float32> _viewMatrix3D{};							  // 0x60
			Render::Matrix4x4F _projectionMatrix3D{};												  // 0x90
			REX::EnumSet<Render::EdgeAAMode, std::uint32_t> _edgeAAMode{Render::EdgeAAMode::Inherit}; // 0xD0
			REX::EnumSet<SetFlags, std::uint16_t> _varsSet{SetFlags::None};							  // 0xD4
			bool _visible{false};																	  // 0xD6
		};

		static_assert(sizeof(DisplayInfo) == 0xE0);

		class __declspec(novtable) ObjectInterface : public NewOverrideBase<327>
		{
		public:
			class __declspec(novtable) ObjVisitor
			{
			public:
				virtual ~ObjVisitor() = default; // 0x00

				// add
				virtual auto IncludeAS3PublicMembers() const -> bool // 0x01
				{
					return false;
				}

				virtual void Visit(const char* a_name, const Value& a_value) = 0; // 0x02
			};

			static_assert(sizeof(ObjVisitor) == 0x08);

			class __declspec(novtable) ArrVisitor
			{
			public:
				inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__GFx__Value__ObjectInterface__ArrVisitor;
				inline static constexpr const auto& VTABLE =
					RE::VTABLE::Scaleform__GFx__Value__ObjectInterface__ArrVisitor;

				virtual ~ArrVisitor() = default; // 0x00

				// add
				virtual void Visit(std::uint32_t a_index, const Value& a_value) = 0; // 0x00
			};

			static_assert(sizeof(ArrVisitor) == 0x08);

			virtual ~ObjectInterface() = default; // 0x00

			void ObjectAddRef(Value* a_value, void* a_object);
			void ObjectRelease(Value* a_value, void* a_object);

			[[nodiscard]]
			auto IsInstanceOf(void* a_data, const char* a_className) const -> bool;
			auto GetParent(void* a_data, Value* a_value) const -> bool;
			auto HasMember(void* a_data, const char* a_name, bool a_isDisplayObject) const -> bool;
			auto GetMember(void* a_data, const char* a_name, Value* a_value, bool a_isDisplayObject) const -> bool;
			auto SetMember(void* a_data, const char* a_name, const Value& a_value, bool a_isDisplayObject) -> bool;
			auto DeleteMember(void* a_data, const char* a_name, bool a_isDisplayObject) -> bool;
			void VisitMembers(void* a_data, ObjVisitor* a_visitor, bool a_isDisplayObject) const;

			[[nodiscard]]
			auto GetArraySize(void* a_data) const -> std::uint32_t;
			auto SetArraySize(void* a_data, std::uint32_t a_size) -> bool;
			auto GetElement(void* a_data, std::uint32_t a_index, Value* a_value) const -> bool;
			auto SetElement(void* a_data, std::uint32_t a_index, const Value& a_value) -> bool;
			auto PushBack(void* a_data, const Value& a_value) -> bool;
			auto PopBack(void* a_data, Value* a_value) -> bool;
			auto RemoveElements(void* a_data, std::uint32_t a_startIndex, std::int32_t a_count) -> bool;
			void VisitElements(void* a_data, ArrVisitor* a_visitor, std::uint32_t a_startIndex, std::int32_t a_count)
				const;

			auto GetDisplayInfo(void* a_data, DisplayInfo* a_info) const -> bool;
			auto SetDisplayInfo(void* a_data, const DisplayInfo& a_info) -> bool;
			auto GetDisplayMatrix(void* a_data, Render::Matrix2x4F* a_matrix) const -> bool;
			auto SetDisplayMatrix(void* a_data, const Render::Matrix2x4F* a_matrix) -> bool;
			auto GetCxform(void* a_data, Render::Cxform* a_cxform) const -> bool;
			auto SetCxform(void* a_data, const Render::Cxform* a_cxform) -> bool;
			auto AttachMovie(
				void* a_data,
				Value* a_movieClip,
				const char* a_symbolName,
				const char* a_instanceName,
				std::int32_t a_depth,
				const MemberValueSet* a_initList) -> bool;
			auto CreateEmptyMovieClip(
				void* a_data,
				Value* a_movieClip,
				const char* a_instanceName,
				std::int32_t a_depth) -> bool;
			auto GotoAndPlay(void* a_data, std::uint32_t a_frame, bool a_stop) -> bool;
			auto GotoAndPlay(void* a_data, const char* a_frame, bool a_stop) -> bool;

			auto Invoke(
				void* a_data,
				Value* a_result,
				const char* a_name,
				const Value* a_args,
				std::size_t a_numArgs,
				bool a_isDisplayObject) -> bool;

			// members
			MovieImpl* movieRoot{nullptr}; // 0x08
		};

		static_assert(sizeof(ObjectInterface) == 0x10);

		using ObjectVisitor = ObjectInterface::ObjVisitor;
		using ArrayVisitor = ObjectInterface::ArrVisitor;

		using ObjectVisitFunctor = void(const char* a_name, const Value& a_value) const;
		using ArrayVisitFunctor = void(std::uint32_t a_index, const Value& a_value) const;

		constexpr Value() noexcept = default;
		~Value() noexcept;

		explicit Value(std::nullptr_t) noexcept;
		explicit Value(bool a_rhs) noexcept;
		explicit Value(std::int32_t a_rhs) noexcept;
		explicit Value(std::uint32_t a_rhs) noexcept;
		explicit Value(REX::Float64 a_rhs) noexcept;
		explicit Value(const char* a_rhs) noexcept;
		explicit Value(const wchar_t* a_rhs) noexcept;
		explicit Value(REX::ZStringView a_rhs) noexcept;
		explicit Value(REX::ZWStringView a_rhs) noexcept;

		Value(const Value& a_rhs) noexcept;
		Value(Value&& a_rhs) noexcept;

		auto operator=(std::nullptr_t) noexcept -> Value&;
		auto operator=(bool a_rhs) noexcept -> Value&;
		auto operator=(std::int32_t a_rhs) noexcept -> Value&;
		auto operator=(std::uint32_t a_rhs) noexcept -> Value&;
		auto operator=(REX::Float64 a_rhs) noexcept -> Value&;
		auto operator=(const char* a_rhs) noexcept -> Value&;
		auto operator=(const wchar_t* a_rhs) noexcept -> Value&;
		auto operator=(REX::ZStringView a_rhs) noexcept -> Value&;
		auto operator=(REX::ZWStringView a_rhs) noexcept -> Value&;

		auto operator=(const Value& a_rhs) noexcept -> Value&;
		auto operator=(Value&& a_rhs) noexcept -> Value&;

		SCALEFORM_HEAP_REDEFINE_NEW(Value);

		[[nodiscard]]
		auto operator==(const Value& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto operator<=>(const Value& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto GetType() const noexcept -> ValueType;

		[[nodiscard]]
		auto IsNull() const noexcept -> bool;
		[[nodiscard]]
		auto IsUndefined() const noexcept -> bool;
		[[nodiscard]]
		auto IsBoolean() const noexcept -> bool;
		[[nodiscard]]
		auto IsInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsUInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsNumber() const noexcept -> bool;
		[[nodiscard]]
		auto IsString() const noexcept -> bool;
		[[nodiscard]]
		auto IsStringW() const noexcept -> bool;
		[[nodiscard]]
		auto IsObject() const noexcept -> bool;
		[[nodiscard]]
		auto IsArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsDisplayObject() const noexcept -> bool;
		[[nodiscard]]
		auto IsClosure() const noexcept -> bool;

		[[nodiscard]]
		auto IsConvertBoolean() const noexcept -> bool;
		[[nodiscard]]
		auto IsConvertInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsConvertUInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsConvertNumber() const noexcept -> bool;
		[[nodiscard]]
		auto IsConvertString() const noexcept -> bool;
		[[nodiscard]]
		auto IsConvertStringW() const noexcept -> bool;

		[[nodiscard]]
		auto IsNullOrUndefined() const noexcept -> bool;
		[[nodiscard]]
		auto IsAnyInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsAnyNumber() const noexcept -> bool;
		[[nodiscard]]
		auto IsAnyString() const noexcept -> bool;
		[[nodiscard]]
		auto IsAnyObject() const noexcept -> bool;

		[[nodiscard]]
		auto IsOrphaned() const noexcept -> bool;
		[[nodiscard]]
		auto IsManaged() const noexcept -> bool;
		[[nodiscard]]
		auto IsConversion() const noexcept -> bool;

		[[nodiscard]]
		auto IsFunction() const -> bool;
		[[nodiscard]]
		auto IsMovieClip() const -> bool;

		[[nodiscard]]
		auto Equals(const Value& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto Compare(const Value& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto GetNull() const noexcept -> std::nullptr_t;
		[[nodiscard]]
		auto GetUndefined() const noexcept -> std::nullptr_t;
		[[nodiscard]]
		auto GetBoolean() const noexcept -> bool;
		[[nodiscard]]
		auto GetInt() const noexcept -> std::int32_t;
		[[nodiscard]]
		auto GetUInt() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetNumber() const noexcept -> REX::Float64;
		[[nodiscard]]
		auto GetString() const noexcept -> const char*;
		[[nodiscard]]
		auto GetWString() const noexcept -> const wchar_t*;
		[[nodiscard]]
		auto GetStringView() const noexcept -> REX::ZStringView;
		[[nodiscard]]
		auto GetWStringView() const noexcept -> REX::ZWStringView;

		[[nodiscard]]
		auto GetUserData() const noexcept -> void*;

		void SetNull() noexcept;
		void SetUndefined() noexcept;
		void SetBoolean(bool a_value) noexcept;
		void SetInt(std::int32_t a_value) noexcept;
		void SetUInt(std::uint32_t a_value) noexcept;
		void SetNumber(REX::Float64 a_value) noexcept;
		void SetString(const char* a_value) noexcept;
		void SetWString(const wchar_t* a_value) noexcept;
		void SetStringView(REX::ZStringView a_value) noexcept;
		void SetWStringView(REX::ZWStringView a_value) noexcept;

		void SetConvertBoolean() noexcept;
		void SetConvertInt() noexcept;
		void SetConvertUInt() noexcept;
		void SetConvertNumber() noexcept;
		void SetConvertString() noexcept;
		void SetConvertStringW() noexcept;

		[[nodiscard]]
		auto IsInstanceOf(const char* a_className) const -> bool;
		auto GetParent(Value* a_value) const -> bool;
		auto HasMember(const char* a_name) const -> bool;
		auto GetMember(const char* a_name, Value* a_value) const -> bool;
		auto SetMember(const char* a_name, const Value& a_value) -> bool;
		auto DeleteMember(const char* a_name) -> bool;
		void VisitMembers(REX::NotNull<ObjectVisitor*> a_visitor) const;
		void VisitMembers(REX::NotNull<std::move_only_function<ObjectVisitFunctor>> a_visitor) const;

		[[nodiscard]]
		auto GetArraySize() const -> std::uint32_t;
		auto SetArraySize(std::uint32_t a_size) -> bool;
		auto GetElement(std::uint32_t a_index, Value* a_value) const -> bool;
		auto SetElement(std::uint32_t a_index, const Value& a_value) -> bool;
		auto PushBack(const Value& a_value) -> bool;
		auto PopBack(Value* a_value = nullptr) -> bool;
		auto RemoveElements(std::uint32_t a_startIndex, std::int32_t a_count = -1) -> bool;
		auto RemoveElement(std::uint32_t a_index) -> bool;
		auto ClearElements() -> bool;
		void VisitElements(
			REX::NotNull<ArrayVisitor*> a_visitor,
			std::uint32_t a_startIndex = 0,
			std::int32_t a_count = -1) const;
		void VisitElements(
			REX::NotNull<std::move_only_function<ArrayVisitFunctor>> a_visitor,
			std::uint32_t a_startIndex = 0,
			std::int32_t a_count = -1) const;

		[[nodiscard]]
		auto GetMovie() const -> Ptr<Movie>;
		[[nodiscard]]
		auto GetMovieImpl() const -> Ptr<MovieImpl>;
		auto GetDisplayInfo(DisplayInfo* a_info) const -> bool;
		auto SetDisplayInfo(const DisplayInfo& a_info) -> bool;
		auto GetDisplayMatrix(Render::Matrix2x4F* a_matrix) const -> bool;
		auto SetDisplayMatrix(const Render::Matrix2x4F* a_matrix) -> bool;
		auto GetCxform(Render::Cxform* a_cxform) const -> bool;
		auto SetCxform(const Render::Cxform* a_cxform) -> bool;
		auto AttachMovie(
			Value* a_movieClip,
			const char* a_symbolName,
			const char* a_instanceName,
			std::int32_t a_depth = -1,
			const MemberValueSet* a_initList = nullptr) -> bool;
		auto CreateEmptyMovieClip(Value* a_movieClip, const char* a_instanceName, std::int32_t a_depth = -1) -> bool;
		auto GotoAndPlay(std::uint32_t a_frame) -> bool;
		auto GotoAndPlay(const char* a_frame) -> bool;
		auto GotoAndStop(std::uint32_t a_frame) -> bool;
		auto GotoAndStop(const char* a_frame) -> bool;

		auto Invoke(
			const char* a_name,
			Value* a_result = nullptr,
			const Value* a_args = nullptr,
			std::uint32_t a_numArgs = 0) -> bool;
		auto Invoke(const char* a_name, std::span<const Value> a_args) -> bool;
		auto Invoke(const char* a_name, Value* a_result, std::span<const Value> a_args) -> bool;

		auto InvokeFunction(Value* a_result = nullptr, const Value* a_args = nullptr, std::uint32_t a_numArgs = 0)
			-> bool;
		auto InvokeFunction(std::span<const Value> a_args) -> bool;
		auto InvokeFunction(Value* a_result, std::span<const Value> a_args) -> bool;

		auto ApplyFunction(Value* a_result, const Value* a_args) -> bool;
		auto ApplyFunction(const Value* a_args) -> bool;

		void swap(Value& a_other) noexcept;

	private:
		[[nodiscard]]
		auto IsManagedValue() const noexcept -> bool;
		void AcquireManagedValue(const Value& a_rhs) noexcept;
		void ReleaseManagedValue() noexcept;

		// members
		ObjectInterface* _objectInterface{nullptr};					   // 0x00
		REX::EnumSet<ValueType, std::uint32_t> _type{ValueType::Null}; // 0x08
		ValueUnion _value;											   // 0x10
		std::size_t _dataAux{0};									   // 0x18
	};

	static_assert(sizeof(Value) == 0x20);

	inline const constinit auto NULL_VALUE = Value();
}

namespace std
{
	template <>
	struct hash<Scaleform::GFx::Value>
	{
	public:
		[[nodiscard]]
		auto operator()(const Scaleform::GFx::Value& a_key) const noexcept -> std::size_t;
	};
}
