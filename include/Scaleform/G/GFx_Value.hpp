#pragma once

#include "Scaleform/N/NewOverrideBase.hpp"
#include "Scaleform/R/Render_EdgeAAMode.hpp"
#include "Scaleform/R/Render_Matrix.hpp"

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
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__GFx__Value };

		enum class ValueType : std::int32_t
		{
			kUndefined = 0,
			kNull = 1,
			kBoolean = 2,
			kInt = 3,
			kUInt = 4,
			kNumber = 5,
			kString = 6,
			kStringW = 7,
			kObject = 8,
			kArray = 9,
			kDisplayObject = 10,
			kClosure = 11,

			kOrphanedBit = 1 << 5,
			kManagedBit = 1 << 6,
			kConvertBit = 1 << 7,

			kTypeMask = kConvertBit | 0x0F,

			kConvertBoolean = kConvertBit | kBoolean,
			kConvertInt = kConvertBit | kInt,
			kConvertUInt = kConvertBit | kUInt,
			kConvertNumber = kConvertBit | kNumber,
			kConvertString = kConvertBit | kString,
			kConvertStringW = kConvertBit | kStringW
		};

		union ValueUnion
		{
		public:
			ValueUnion() noexcept;
			~ValueUnion() noexcept;

			explicit ValueUnion(std::nullptr_t) noexcept;
			explicit ValueUnion(bool a_rhs) noexcept;
			explicit ValueUnion(std::int32_t a_rhs) noexcept;
			explicit ValueUnion(std::uint32_t a_rhs) noexcept;
			explicit ValueUnion(REX::Float64 a_rhs) noexcept;
			explicit ValueUnion(const char* a_rhs) noexcept;
			explicit ValueUnion(const wchar_t* a_rhs) noexcept;
			explicit ValueUnion(REX::zstring_view a_rhs) noexcept;
			explicit ValueUnion(REX::zwstring_view a_rhs) noexcept;

			ValueUnion(const ValueUnion& a_rhs) noexcept;
			ValueUnion(ValueUnion&& a_rhs) noexcept;

			ValueUnion& operator=(std::nullptr_t) noexcept;
			ValueUnion& operator=(bool a_rhs) noexcept;
			ValueUnion& operator=(std::int32_t a_rhs) noexcept;
			ValueUnion& operator=(std::uint32_t a_rhs) noexcept;
			ValueUnion& operator=(REX::Float64 a_rhs) noexcept;
			ValueUnion& operator=(const char* a_rhs) noexcept;
			ValueUnion& operator=(const wchar_t* a_rhs) noexcept;
			ValueUnion& operator=(REX::zstring_view a_rhs) noexcept;
			ValueUnion& operator=(REX::zwstring_view a_rhs) noexcept;

			ValueUnion& operator=(const ValueUnion& a_rhs) noexcept;
			ValueUnion& operator=(ValueUnion&& a_rhs) noexcept;

			std::nullptr_t null;
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
				kNone = 0,
				kX = 1 << 0,
				kY = 1 << 1,
				kRotation = 1 << 2,
				kXScale = 1 << 3,
				kYScale = 1 << 4,
				kAlpha = 1 << 5,
				kVisible = 1 << 6,
				kZ = 1 << 7,
				kXRotation = 1 << 8,
				kYRotation = 1 << 9,
				kZScale = 1 << 10,
				kFOV = 1 << 11,
				kProjMatrix3D = 1 << 12,
				kViewMatrix3D = 1 << 13,
				kEdgeAAMode = 1 << 14
			};

			DisplayInfo() noexcept = default;
			~DisplayInfo() noexcept = default;

			DisplayInfo(const DisplayInfo&) noexcept = default;
			DisplayInfo(DisplayInfo&&) noexcept = default;

			DisplayInfo& operator=(const DisplayInfo&) noexcept = default;
			DisplayInfo& operator=(DisplayInfo&&) noexcept = default;

			[[nodiscard]] REX::Float64 GetX() const noexcept;
			[[nodiscard]] REX::Float64 GetY() const noexcept;
			[[nodiscard]] REX::Float64 GetZ() const noexcept;
			[[nodiscard]] REX::Float64 GetXScale() const noexcept;
			[[nodiscard]] REX::Float64 GetYScale() const noexcept;
			[[nodiscard]] REX::Float64 GetZScale() const noexcept;
			[[nodiscard]] REX::Float64 GetRotation() const noexcept;
			[[nodiscard]] REX::Float64 GetXRotation() const noexcept;
			[[nodiscard]] REX::Float64 GetYRotation() const noexcept;
			[[nodiscard]] REX::Float64 GetAlpha() const noexcept;
			[[nodiscard]] bool GetVisible() const noexcept;
			[[nodiscard]] REX::Float64 GetFOV() const noexcept;
			[[nodiscard]] const Render::Matrix3x4<REX::Float32>* GetViewMatrix3D() const noexcept;
			[[nodiscard]] const Render::Matrix4x4<REX::Float32>* GetProjectionMatrix3D() const noexcept;
			[[nodiscard]] Render::EdgeAAMode GetEdgeAAMode() const noexcept;

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
			void SetViewMatrix3D(const Render::Matrix3x4<REX::Float32>* a_matrix) noexcept;
			void SetProjectionMatrix3D(const Render::Matrix4x4<REX::Float32>* a_matrix) noexcept;
			void SetEdgeAAMode(Render::EdgeAAMode a_mode) noexcept;

		private:
			// members
			REX::Float64 _x{ 0.0_f64 };																	 // 00
			REX::Float64 _y{ 0.0_f64 };																	 // 08
			REX::Float64 _rotation{ 0.0_f64 };															 // 10
			REX::Float64 _xScale{ 0.0_f64 };															 // 18
			REX::Float64 _yScale{ 0.0_f64 };															 // 20
			REX::Float64 _alpha{ 0.0_f64 };																 // 28
			REX::Float64 _z{ 0.0_f64 };																	 // 30
			REX::Float64 _xRotation{ 0.0_f64 };															 // 38
			REX::Float64 _yRotation{ 0.0_f64 };															 // 40
			REX::Float64 _zScale{ 0.0_f64 };															 // 48
			REX::Float64 _fov{ 0.0_f64 };																 // 50
			alignas(0x10) Render::Matrix3x4<REX::Float32> _viewMatrix3D{};								 // 60
			Render::Matrix4x4<REX::Float32> _projectionMatrix3D{};										 // 90
			REX::EnumSet<Render::EdgeAAMode, std::uint32_t> _edgeAAMode{ Render::EdgeAAMode::kInherit }; // D0
			REX::EnumSet<SetFlags, std::uint16_t> _varsSet{ SetFlags::kNone };							 // D4
			bool _visible{ false };																		 // D6
		};
		static_assert(sizeof(DisplayInfo) == 0xE0);

		class __declspec(novtable) ObjectInterface
			: public NewOverrideBase<327>
		{
		public:
			class __declspec(novtable) ObjVisitor
			{
			public:
				virtual ~ObjVisitor() = default; // 00

				// add
				virtual bool IncludeAS3PublicMembers() const { return false; }	  // 01
				virtual void Visit(const char* a_name, const Value& a_value) = 0; // 02
			};
			static_assert(sizeof(ObjVisitor) == 0x08);

			class __declspec(novtable) ArrVisitor
			{
			public:
				inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__GFx__Value__ObjectInterface__ArrVisitor };
				inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__GFx__Value__ObjectInterface__ArrVisitor };

				virtual ~ArrVisitor() = default; // 00

				// add
				virtual void Visit(std::uint32_t a_index, const Value& a_value) = 0; // 00
			};
			static_assert(sizeof(ArrVisitor) == 0x08);

			virtual ~ObjectInterface() = default; // 00

			void ObjectAddRef(Value* a_value, void* a_object);
			void ObjectRelease(Value* a_value, void* a_object);

			[[nodiscard]] bool IsInstanceOf(void* a_data, const char* a_className) const;
			bool GetParent(void* a_data, Value* a_value) const;
			bool HasMember(void* a_data, const char* a_name, bool a_isDisplayObject) const;
			bool GetMember(void* a_data, const char* a_name, Value* a_value, bool a_isDisplayObject) const;
			bool SetMember(void* a_data, const char* a_name, const Value& a_value, bool a_isDisplayObject);
			bool DeleteMember(void* a_data, const char* a_name, bool a_isDisplayObject);
			void VisitMembers(void* a_data, ObjVisitor* a_visitor, bool a_isDisplayObject) const;

			[[nodiscard]] std::uint32_t GetArraySize(void* a_data) const;
			bool SetArraySize(void* a_data, std::uint32_t a_size);
			bool GetElement(void* a_data, std::uint32_t a_index, Value* a_value) const;
			bool SetElement(void* a_data, std::uint32_t a_index, const Value& a_value);
			bool PushBack(void* a_data, const Value& a_value);
			bool PopBack(void* a_data, Value* a_value);
			bool RemoveElements(void* a_data, std::uint32_t a_startIndex, std::int32_t a_count);
			void VisitElements(void* a_data, ArrVisitor* a_visitor, std::uint32_t a_startIndex, std::int32_t a_count) const;

			bool GetDisplayInfo(void* a_data, DisplayInfo* a_info) const;
			bool SetDisplayInfo(void* a_data, const DisplayInfo& a_info);
			bool GetDisplayMatrix(void* a_data, Render::Matrix2x4<REX::Float32>* a_matrix) const;
			bool SetDisplayMatrix(void* a_data, const Render::Matrix2x4<REX::Float32>* a_matrix);
			bool GetCxform(void* a_data, Render::Cxform* a_cxform) const;
			bool SetCxform(void* a_data, const Render::Cxform* a_cxform);
			bool AttachMovie(void* a_data, Value* a_movieClip, const char* a_symbolName, const char* a_instanceName, std::int32_t a_depth, const MemberValueSet* a_initList);
			bool CreateEmptyMovieClip(void* a_data, Value* a_movieClip, const char* a_instanceName, std::int32_t a_depth);
			bool GotoAndPlay(void* a_data, std::uint32_t a_frame, bool a_stop);
			bool GotoAndPlay(void* a_data, const char* a_frame, bool a_stop);

			bool Invoke(void* a_data, Value* a_result, const char* a_name, const Value* a_args, std::size_t a_numArgs, bool a_isDisplayObject);

			// members
			MovieImpl* movieRoot{ nullptr }; // 08
		};
		static_assert(sizeof(ObjectInterface) == 0x10);

		using ObjectVisitor = ObjectInterface::ObjVisitor;
		using ArrayVisitor = ObjectInterface::ArrVisitor;

		using ObjectVisitFunctor = std::function<void(const char* a_name, const Value& a_value)>;
		using ArrayVisitFunctor = std::function<void(std::uint32_t a_index, const Value& a_value)>;

		Value() noexcept;
		~Value() noexcept;

		explicit Value(std::nullptr_t) noexcept;
		explicit Value(bool a_rhs) noexcept;
		explicit Value(std::int32_t a_rhs) noexcept;
		explicit Value(std::uint32_t a_rhs) noexcept;
		explicit Value(REX::Float64 a_rhs) noexcept;
		explicit Value(const char* a_rhs) noexcept;
		explicit Value(const wchar_t* a_rhs) noexcept;
		explicit Value(REX::zstring_view a_rhs) noexcept;
		explicit Value(REX::zwstring_view a_rhs) noexcept;

		Value(const Value& a_rhs) noexcept;
		Value(Value&& a_rhs) noexcept;

		Value& operator=(std::nullptr_t) noexcept;
		Value& operator=(bool a_rhs) noexcept;
		Value& operator=(std::int32_t a_rhs) noexcept;
		Value& operator=(std::uint32_t a_rhs) noexcept;
		Value& operator=(REX::Float64 a_rhs) noexcept;
		Value& operator=(const char* a_rhs) noexcept;
		Value& operator=(const wchar_t* a_rhs) noexcept;
		Value& operator=(REX::zstring_view a_rhs) noexcept;
		Value& operator=(REX::zwstring_view a_rhs) noexcept;

		Value& operator=(const Value& a_rhs) noexcept;
		Value& operator=(Value&& a_rhs) noexcept;

		SF_HEAP_REDEFINE_NEW(Value);

		[[nodiscard]] bool operator==(const Value& a_rhs) const noexcept;
		[[nodiscard]] bool operator!=(const Value& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering operator<=>(const Value& a_rhs) const noexcept;

		[[nodiscard]] ValueType GetType() const noexcept;

		[[nodiscard]] bool IsNull() const noexcept;
		[[nodiscard]] bool IsUndefined() const noexcept;
		[[nodiscard]] bool IsBoolean() const noexcept;
		[[nodiscard]] bool IsInt() const noexcept;
		[[nodiscard]] bool IsUInt() const noexcept;
		[[nodiscard]] bool IsNumber() const noexcept;
		[[nodiscard]] bool IsString() const noexcept;
		[[nodiscard]] bool IsStringW() const noexcept;
		[[nodiscard]] bool IsObject() const noexcept;
		[[nodiscard]] bool IsArray() const noexcept;
		[[nodiscard]] bool IsDisplayObject() const noexcept;
		[[nodiscard]] bool IsClosure() const noexcept;

		[[nodiscard]] bool IsConvertBoolean() const noexcept;
		[[nodiscard]] bool IsConvertInt() const noexcept;
		[[nodiscard]] bool IsConvertUInt() const noexcept;
		[[nodiscard]] bool IsConvertNumber() const noexcept;
		[[nodiscard]] bool IsConvertString() const noexcept;
		[[nodiscard]] bool IsConvertStringW() const noexcept;

		[[nodiscard]] bool IsNullOrUndefined() const noexcept;
		[[nodiscard]] bool IsAnyInt() const noexcept;
		[[nodiscard]] bool IsAnyNumber() const noexcept;
		[[nodiscard]] bool IsAnyString() const noexcept;
		[[nodiscard]] bool IsAnyObject() const noexcept;

		[[nodiscard]] bool IsOrphaned() const noexcept;
		[[nodiscard]] bool IsManaged() const noexcept;
		[[nodiscard]] bool IsConversion() const noexcept;

		[[nodiscard]] bool IsFunction() const;
		[[nodiscard]] bool IsMovieClip() const;

		[[nodiscard]] bool Equals(const Value& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering Compare(const Value& a_rhs) const noexcept;

		[[nodiscard]] std::nullptr_t GetNull() const noexcept;
		[[nodiscard]] std::nullptr_t GetUndefined() const noexcept;
		[[nodiscard]] bool GetBoolean() const noexcept;
		[[nodiscard]] std::int32_t GetInt() const noexcept;
		[[nodiscard]] std::uint32_t GetUInt() const noexcept;
		[[nodiscard]] REX::Float64 GetNumber() const noexcept;
		[[nodiscard]] const char* GetString() const noexcept;
		[[nodiscard]] const wchar_t* GetWString() const noexcept;
		[[nodiscard]] REX::zstring_view GetStringView() const noexcept;
		[[nodiscard]] REX::zwstring_view GetWStringView() const noexcept;

		[[nodiscard]] void* GetUserData() const noexcept;

		void SetNull() noexcept;
		void SetUndefined() noexcept;
		void SetBoolean(bool a_value) noexcept;
		void SetInt(std::int32_t a_value) noexcept;
		void SetUInt(std::uint32_t a_value) noexcept;
		void SetNumber(REX::Float64 a_value) noexcept;
		void SetString(const char* a_value) noexcept;
		void SetWString(const wchar_t* a_value) noexcept;
		void SetStringView(REX::zstring_view a_value) noexcept;
		void SetWStringView(REX::zwstring_view a_value) noexcept;

		void SetConvertBoolean() noexcept;
		void SetConvertInt() noexcept;
		void SetConvertUInt() noexcept;
		void SetConvertNumber() noexcept;
		void SetConvertString() noexcept;
		void SetConvertStringW() noexcept;

		[[nodiscard]] bool IsInstanceOf(const char* a_className) const;
		bool GetParent(Value* a_value) const;
		bool HasMember(const char* a_name) const;
		bool GetMember(const char* a_name, Value* a_value) const;
		bool SetMember(const char* a_name, const Value& a_value);
		bool DeleteMember(const char* a_name);
		void VisitMembers(REX::NotNull<ObjectVisitor*> a_visitor) const;
		void VisitMembers(REX::NotNull<ObjectVisitFunctor> a_visitor) const;

		[[nodiscard]] std::uint32_t GetArraySize() const;
		bool SetArraySize(std::uint32_t a_size);
		bool GetElement(std::uint32_t a_index, Value* a_value) const;
		bool SetElement(std::uint32_t a_index, const Value& a_value);
		bool PushBack(const Value& a_value);
		bool PopBack(Value* a_value = nullptr);
		bool RemoveElements(std::uint32_t a_startIndex, std::int32_t a_count = -1);
		bool RemoveElement(std::uint32_t a_index);
		bool ClearElements();
		void VisitElements(REX::NotNull<ArrayVisitor*> a_visitor, std::uint32_t a_startIndex = 0, std::int32_t a_count = -1) const;
		void VisitElements(REX::NotNull<ArrayVisitFunctor> a_visitor, std::uint32_t a_startIndex = 0, std::int32_t a_count = -1) const;

		[[nodiscard]] Movie* GetMovie() const;
		[[nodiscard]] MovieImpl* GetMovieImpl() const;
		bool GetDisplayInfo(DisplayInfo* a_info) const;
		bool SetDisplayInfo(const DisplayInfo& a_info);
		bool GetDisplayMatrix(Render::Matrix2x4<REX::Float32>* a_matrix) const;
		bool SetDisplayMatrix(const Render::Matrix2x4<REX::Float32>* a_matrix);
		bool GetCxform(Render::Cxform* a_cxform) const;
		bool SetCxform(const Render::Cxform* a_cxform);
		bool AttachMovie(Value* a_movieClip, const char* a_symbolName, const char* a_instanceName, std::int32_t a_depth = -1, const MemberValueSet* a_initList = nullptr);
		bool CreateEmptyMovieClip(Value* a_movieClip, const char* a_instanceName, std::int32_t a_depth = -1);
		bool GotoAndPlay(std::uint32_t a_frame);
		bool GotoAndPlay(const char* a_frame);
		bool GotoAndStop(std::uint32_t a_frame);
		bool GotoAndStop(const char* a_frame);

		bool Invoke(const char* a_name, Value* a_result = nullptr, const Value* a_args = nullptr, std::uint32_t a_numArgs = 0);
		bool Invoke(const char* a_name, std::span<const Value> a_args);
		bool Invoke(const char* a_name, Value* a_result, std::span<const Value> a_args);

		bool InvokeFunction(Value* a_result = nullptr, const Value* a_args = nullptr, std::uint32_t a_numArgs = 0);
		bool InvokeFunction(std::span<const Value> a_args);
		bool InvokeFunction(Value* a_result, std::span<const Value> a_args);

		bool ApplyFunction(Value* a_result, const Value* a_args);
		bool ApplyFunction(const Value* a_args);

		void swap(Value& a_other) noexcept;

	private:
		[[nodiscard]] bool IsManagedValue() const noexcept;
		void AcquireManagedValue(const Value& a_rhs) noexcept;
		void ReleaseManagedValue() noexcept;

		// members
		ObjectInterface* _objectInterface{ nullptr };						   // 00
		REX::EnumSet<ValueType, std::uint32_t> _type{ ValueType::kUndefined }; // 08
		ValueUnion _value;													   // 10
		std::size_t _dataAux{ 0 };											   // 18
	};
	static_assert(sizeof(Value) == 0x20);

	void swap(Value& a_lhs, Value& a_rhs) noexcept;

	inline const auto NULL_VALUE = Value(nullptr);
}

namespace std
{
	template <>
	struct hash<Scaleform::GFx::Value>
	{
	public:
		[[nodiscard]] std::size_t operator()(const Scaleform::GFx::Value& a_key) const noexcept;
	};
}
