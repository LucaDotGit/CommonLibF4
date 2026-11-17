#include "Scaleform/G/GFx_Value.hpp"

#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_MovieImpl.hpp"

namespace Scaleform::GFx
{
	Value::ValueUnion::ValueUnion(std::nullptr_t) noexcept
	{
	}

	Value::ValueUnion::ValueUnion(bool a_rhs) noexcept :
		boolean(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(std::int32_t a_rhs) noexcept :
		int32(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(std::uint32_t a_rhs) noexcept :
		uint32(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(REX::Float64 a_rhs) noexcept :
		number(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(const char* a_rhs) noexcept :
		string(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(const wchar_t* a_rhs) noexcept :
		wstring(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(REX::ZStringView a_rhs) noexcept :
		string(a_rhs.data())
	{
	}

	Value::ValueUnion::ValueUnion(REX::ZWStringView a_rhs) noexcept :
		wstring(a_rhs.data())
	{
	}

	auto Value::ValueUnion::operator=(std::nullptr_t) noexcept -> Value::ValueUnion&
	{
		data = nullptr;
		return *this;
	}

	auto Value::ValueUnion::operator=(bool a_rhs) noexcept -> Value::ValueUnion&
	{
		boolean = a_rhs;
		return *this;
	}

	auto Value::ValueUnion::operator=(std::int32_t a_rhs) noexcept -> Value::ValueUnion&
	{
		int32 = a_rhs;
		return *this;
	}

	auto Value::ValueUnion::operator=(std::uint32_t a_rhs) noexcept -> Value::ValueUnion&
	{
		uint32 = a_rhs;
		return *this;
	}

	auto Value::ValueUnion::operator=(REX::Float64 a_rhs) noexcept -> Value::ValueUnion&
	{
		number = a_rhs;
		return *this;
	}

	auto Value::ValueUnion::operator=(const char* a_rhs) noexcept -> Value::ValueUnion&
	{
		string = a_rhs;
		return *this;
	}

	auto Value::ValueUnion::operator=(const wchar_t* a_rhs) noexcept -> Value::ValueUnion&
	{
		wstring = a_rhs;
		return *this;
	}

	auto Value::ValueUnion::operator=(REX::ZStringView a_rhs) noexcept -> Value::ValueUnion&
	{
		string = a_rhs.data();
		return *this;
	}

	auto Value::ValueUnion::operator=(REX::ZWStringView a_rhs) noexcept -> Value::ValueUnion&
	{
		wstring = a_rhs.data();
		return *this;
	}

	void Value::ValueUnion::swap(ValueUnion& a_other) noexcept
	{
		if (this == std::addressof(a_other)) {
			return;
		}

		std::swap(data, a_other.data);
	}

	auto Value::DisplayInfo::GetX() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::kX));
		return _x;
	}

	auto Value::DisplayInfo::GetY() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::kY));
		return _y;
	}

	auto Value::DisplayInfo::GetZ() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::kZ));
		return _z;
	}

	auto Value::DisplayInfo::GetXScale() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::XScale));
		return _xScale;
	}

	auto Value::DisplayInfo::GetYScale() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::YScale));
		return _yScale;
	}

	auto Value::DisplayInfo::GetZScale() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::ZScale));
		return _zScale;
	}

	auto Value::DisplayInfo::GetRotation() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::Rotation));
		return _rotation;
	}

	auto Value::DisplayInfo::GetXRotation() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::XRotation));
		return _xRotation;
	}

	auto Value::DisplayInfo::GetYRotation() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::YRotation));
		return _yRotation;
	}

	auto Value::DisplayInfo::GetAlpha() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::Alpha));
		return _alpha;
	}

	auto Value::DisplayInfo::GetVisible() const noexcept -> bool
	{
		REX::Assert(_varsSet.any(SetFlags::Visible));
		return _visible;
	}

	auto Value::DisplayInfo::GetFOV() const noexcept -> REX::Float64
	{
		REX::Assert(_varsSet.any(SetFlags::FOV));
		return _fov;
	}

	auto Value::DisplayInfo::GetViewMatrix3D() const noexcept -> const Render::Matrix3x4<REX::Float32>*
	{
		return _varsSet.any(SetFlags::ViewMatrix3D) ? std::addressof(_viewMatrix3D) : nullptr;
	}

	auto Value::DisplayInfo::GetProjectionMatrix3D() const noexcept -> const Render::Matrix4x4F*
	{
		return _varsSet.any(SetFlags::ProjMatrix3D) ? std::addressof(_projectionMatrix3D) : nullptr;
	}

	auto Value::DisplayInfo::GetEdgeAAMode() const noexcept -> Render::EdgeAAMode
	{
		REX::Assert(_varsSet.any(SetFlags::EdgeAAMode));
		return _edgeAAMode.get();
	}

	void Value::DisplayInfo::SetX(REX::Float64 a_x) noexcept
	{
		_varsSet.set(SetFlags::kX);
		_x = a_x;
	}

	void Value::DisplayInfo::SetY(REX::Float64 a_y) noexcept
	{
		_varsSet.set(SetFlags::kY);
		_y = a_y;
	}

	void Value::DisplayInfo::SetZ(REX::Float64 a_z) noexcept
	{
		_varsSet.set(SetFlags::kZ);
		_z = a_z;
	}

	void Value::DisplayInfo::SetXScale(REX::Float64 a_xScale) noexcept
	{
		_varsSet.set(SetFlags::XScale);
		_xScale = a_xScale;
	}

	void Value::DisplayInfo::SetYScale(REX::Float64 a_yScale) noexcept
	{
		_varsSet.set(SetFlags::YScale);
		_yScale = a_yScale;
	}

	void Value::DisplayInfo::SetZScale(REX::Float64 a_zScale) noexcept
	{
		_varsSet.set(SetFlags::ZScale);
		_zScale = a_zScale;
	}

	void Value::DisplayInfo::SetRotation(REX::Float64 a_rotation) noexcept
	{
		_varsSet.set(SetFlags::Rotation);
		_rotation = a_rotation;
	}

	void Value::DisplayInfo::SetXRotation(REX::Float64 a_xRotation) noexcept
	{
		_varsSet.set(SetFlags::XRotation);
		_xRotation = a_xRotation;
	}

	void Value::DisplayInfo::SetYRotation(REX::Float64 a_yRotation) noexcept
	{
		_varsSet.set(SetFlags::YRotation);
		_yRotation = a_yRotation;
	}

	void Value::DisplayInfo::SetAlpha(REX::Float64 a_alpha) noexcept
	{
		_varsSet.set(SetFlags::Alpha);
		_alpha = a_alpha;
	}

	void Value::DisplayInfo::SetVisible(bool a_visible) noexcept
	{
		_varsSet.set(SetFlags::Visible);
		_visible = a_visible;
	}

	void Value::DisplayInfo::SetFOV(REX::Float64 a_fov) noexcept
	{
		_varsSet.set(SetFlags::FOV);
		_fov = a_fov;
	}

	void Value::DisplayInfo::SetViewMatrix3D(std::optional<Render::Matrix3x4<REX::Float32>> a_matrix) noexcept
	{
		if (!a_matrix) {
			_varsSet.reset(SetFlags::ViewMatrix3D);
			return;
		}

		_varsSet.set(SetFlags::ViewMatrix3D);
		_viewMatrix3D = *a_matrix;
	}

	void Value::DisplayInfo::SetProjectionMatrix3D(std::optional<Render::Matrix4x4F> a_matrix) noexcept
	{
		if (!a_matrix) {
			_varsSet.reset(SetFlags::ProjMatrix3D);
			return;
		}

		_varsSet.set(SetFlags::ProjMatrix3D);
		_projectionMatrix3D = *a_matrix;
	}

	void Value::DisplayInfo::SetEdgeAAMode(Render::EdgeAAMode a_mode) noexcept
	{
		_varsSet.set(SetFlags::EdgeAAMode);
		_edgeAAMode = a_mode;
	}

	void Value::DisplayInfo::swap(DisplayInfo& a_other) noexcept
	{
		std::swap(_x, a_other._x);
		std::swap(_y, a_other._y);
		std::swap(_z, a_other._z);
		std::swap(_xScale, a_other._xScale);
		std::swap(_yScale, a_other._yScale);
		std::swap(_zScale, a_other._zScale);
		std::swap(_rotation, a_other._rotation);
		std::swap(_xRotation, a_other._xRotation);
		std::swap(_yRotation, a_other._yRotation);
		std::swap(_alpha, a_other._alpha);
		std::swap(_visible, a_other._visible);
		std::swap(_fov, a_other._fov);
		std::swap(_viewMatrix3D, a_other._viewMatrix3D);
		std::swap(_projectionMatrix3D, a_other._projectionMatrix3D);
		std::swap(_edgeAAMode, a_other._edgeAAMode);
		std::swap(_varsSet, a_other._varsSet);
	}

	void Value::ObjectInterface::ObjectAddRef(Value* a_value, void* a_object)
	{
		using FuncType = decltype(&ObjectInterface::ObjectRelease);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::ObjectAddRef);
		std::invoke(FUNC, this, a_value, a_object);
	}

	void Value::ObjectInterface::ObjectRelease(Value* a_value, void* a_object)
	{
		using FuncType = decltype(&ObjectInterface::ObjectRelease);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::ObjectRelease);
		std::invoke(FUNC, this, a_value, a_object);
	}

	auto Value::ObjectInterface::IsInstanceOf(void* a_data, const char* a_className) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::IsInstanceOf);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::IsInstanceOf);
		return std::invoke(FUNC, this, a_data, a_className);
	}

	auto Value::ObjectInterface::GetParent(void* a_data, Value* a_value) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::GetParent);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetParent);
		return std::invoke(FUNC, this, a_data, a_value);
	}

	auto Value::ObjectInterface::HasMember(void* a_data, const char* a_name, bool a_isDisplayObject) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::HasMember);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::HasMember);
		return std::invoke(FUNC, this, a_data, a_name, a_isDisplayObject);
	}

	auto Value::ObjectInterface::GetMember(void* a_data, const char* a_name, Value* a_value, bool a_isDisplayObject)
		const -> bool
	{
		using FuncType = decltype(&ObjectInterface::GetMember);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetMember);
		return std::invoke(FUNC, this, a_data, a_name, a_value, a_isDisplayObject);
	}

	auto Value::ObjectInterface::SetMember(
		void* a_data,
		const char* a_name,
		const Value& a_value,
		bool a_isDisplayObject) -> bool
	{
		using FuncType = decltype(&ObjectInterface::SetMember);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::SetMember);
		return std::invoke(FUNC, this, a_data, a_name, a_value, a_isDisplayObject);
	}

	auto Value::ObjectInterface::DeleteMember(void* a_data, const char* a_name, bool a_isDisplayObject) -> bool
	{
		using FuncType = decltype(&ObjectInterface::DeleteMember);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::DeleteMember);
		return std::invoke(FUNC, this, a_data, a_name, a_isDisplayObject);
	}

	void Value::ObjectInterface::VisitMembers(void* a_data, ObjVisitor* a_visitor, bool a_isDisplayObject) const
	{
		using FuncType = decltype(&ObjectInterface::VisitMembers);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::VisitMembers);
		std::invoke(FUNC, this, a_data, a_visitor, a_isDisplayObject);
	}

	auto Value::ObjectInterface::GetArraySize(void* a_data) const -> std::uint32_t
	{
		using FuncType = decltype(&ObjectInterface::GetArraySize);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetArraySize);
		return std::invoke(FUNC, this, a_data);
	}

	auto Value::ObjectInterface::SetArraySize(void* a_data, std::uint32_t a_size) -> bool
	{
		using FuncType = decltype(&ObjectInterface::SetArraySize);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::SetArraySize);
		return std::invoke(FUNC, this, a_data, a_size);
	}

	auto Value::ObjectInterface::GetElement(void* a_data, std::uint32_t a_index, Value* a_value) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::GetElement);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetElement);
		return std::invoke(FUNC, this, a_data, a_index, a_value);
	}

	auto Value::ObjectInterface::SetElement(void* a_data, std::uint32_t a_index, const Value& a_value) -> bool
	{
		using FuncType = decltype(&ObjectInterface::SetElement);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::SetElement);
		return std::invoke(FUNC, this, a_data, a_index, a_value);
	}

	auto Value::ObjectInterface::PushBack(void* a_data, const Value& a_value) -> bool
	{
		using FuncType = decltype(&ObjectInterface::PushBack);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::PushBack);
		return std::invoke(FUNC, this, a_data, a_value);
	}

	auto Value::ObjectInterface::PopBack(void* a_data, Value* a_value) -> bool
	{
		using FuncType = decltype(&ObjectInterface::PopBack);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::PopBack);
		return std::invoke(FUNC, this, a_data, a_value);
	}

	auto Value::ObjectInterface::RemoveElements(void* a_data, std::uint32_t a_startIndex, std::int32_t a_count) -> bool
	{
		using FuncType = decltype(&ObjectInterface::RemoveElements);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::RemoveElements);
		return std::invoke(FUNC, this, a_data, a_startIndex, a_count);
	}

	void Value::ObjectInterface::VisitElements(
		void* a_data,
		ArrVisitor* a_visitor,
		std::uint32_t a_startIndex,
		std::int32_t a_count) const
	{
		using FuncType = decltype(&ObjectInterface::VisitElements);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::VisitElements);
		std::invoke(FUNC, this, a_data, a_visitor, a_startIndex, a_count);
	}

	auto Value::ObjectInterface::GetDisplayInfo(void* a_data, DisplayInfo* a_info) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::GetDisplayInfo);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetDisplayInfo);
		return std::invoke(FUNC, this, a_data, a_info);
	}

	auto Value::ObjectInterface::SetDisplayInfo(void* a_data, const DisplayInfo& a_info) -> bool
	{
		using FuncType = decltype(&ObjectInterface::SetDisplayInfo);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::SetDisplayInfo);
		return std::invoke(FUNC, this, a_data, a_info);
	}

	auto Value::ObjectInterface::GetDisplayMatrix(void* a_data, Render::Matrix2x4F* a_matrix) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::GetDisplayMatrix);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetDisplayMatrix);
		return std::invoke(FUNC, this, a_data, a_matrix);
	}

	auto Value::ObjectInterface::SetDisplayMatrix(void* a_data, const Render::Matrix2x4F* a_matrix) -> bool
	{
		using FuncType = decltype(&ObjectInterface::SetDisplayMatrix);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::SetDisplayMatrix);
		return std::invoke(FUNC, this, a_data, a_matrix);
	}

	auto Value::ObjectInterface::GetCxform(void* a_data, Render::Cxform* a_cxform) const -> bool
	{
		using FuncType = decltype(&ObjectInterface::GetCxform);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GetCxform);
		return std::invoke(FUNC, this, a_data, a_cxform);
	}

	auto Value::ObjectInterface::SetCxform(void* a_data, const Render::Cxform* a_cxform) -> bool
	{
		using FuncType = decltype(&ObjectInterface::SetCxform);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::SetCxform);
		return std::invoke(FUNC, this, a_data, a_cxform);
	}

	auto Value::ObjectInterface::AttachMovie(
		void* a_data,
		Value* a_movieClip,
		const char* a_symbolName,
		const char* a_instanceName,
		std::int32_t a_depth,
		const MemberValueSet* a_initList) -> bool
	{
		using FuncType = decltype(&ObjectInterface::AttachMovie);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::AttachMovie);
		return std::invoke(FUNC, this, a_data, a_movieClip, a_symbolName, a_instanceName, a_depth, a_initList);
	}

	auto Value::ObjectInterface::CreateEmptyMovieClip(
		void* a_data,
		Value* a_movieClip,
		const char* a_instanceName,
		std::int32_t a_depth) -> bool
	{
		using FuncType = decltype(&ObjectInterface::CreateEmptyMovieClip);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::CreateEmptyMovieClip);
		return std::invoke(FUNC, this, a_data, a_movieClip, a_instanceName, a_depth);
	}

	auto Value::ObjectInterface::GotoAndPlay(void* a_data, std::uint32_t a_frame, bool a_stop) -> bool
	{
		using FuncType = bool (ObjectInterface::*)(void*, std::int32_t, bool);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GotoAndPlay_Int);
		return std::invoke(FUNC, this, a_data, a_frame, a_stop);
	}

	auto Value::ObjectInterface::GotoAndPlay(void* a_data, const char* a_frame, bool a_stop) -> bool
	{
		using FuncType = bool (ObjectInterface::*)(void*, const char*, bool);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::GotoAndPlay_String);
		return std::invoke(FUNC, this, a_data, a_frame, a_stop);
	}

	auto Value::ObjectInterface::Invoke(
		void* a_data,
		Value* a_result,
		const char* a_name,
		const Value* a_args,
		std::size_t a_numArgs,
		bool a_isDisplayObject) -> bool
	{
		using FuncType = decltype(&ObjectInterface::Invoke);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Value::Invoke);
		return std::invoke(FUNC, this, a_data, a_result, a_name, a_args, a_numArgs, a_isDisplayObject);
	}

	Value::~Value() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::Undefined;
	}

	Value::Value(std::nullptr_t) noexcept :
		_type(ValueType::Null)
	{
	}

	Value::Value(bool a_rhs) noexcept :
		_type(ValueType::Boolean),
		_value(a_rhs)
	{
	}

	Value::Value(std::int32_t a_rhs) noexcept :
		_type(ValueType::Int),
		_value(a_rhs)
	{
	}

	Value::Value(std::uint32_t a_rhs) noexcept :
		_type(ValueType::UInt),
		_value(a_rhs)
	{
	}

	Value::Value(REX::Float64 a_rhs) noexcept :
		_type(ValueType::Number),
		_value(a_rhs)
	{
	}

	Value::Value(const char* a_rhs) noexcept :
		_type(ValueType::String),
		_value(a_rhs)
	{
	}

	Value::Value(const wchar_t* a_rhs) noexcept :
		_type(ValueType::StringW),
		_value(a_rhs)
	{
	}

	Value::Value(REX::ZStringView a_rhs) noexcept :
		_type(ValueType::String),
		_value(a_rhs.data())
	{
	}

	Value::Value(REX::ZWStringView a_rhs) noexcept :
		_type(ValueType::StringW),
		_value(a_rhs.data())
	{
	}

	Value::Value(const Value& a_rhs) noexcept :
		_type(a_rhs._type),
		_value(a_rhs._value),
		_dataAux(a_rhs._dataAux)
	{
		if (a_rhs.IsManagedValue()) {
			AcquireManagedValue(a_rhs);
		}
	}

	Value::Value(Value&& a_rhs) noexcept :
		_objectInterface(std::exchange(a_rhs._objectInterface, nullptr)),
		_type(std::exchange(a_rhs._type, ValueType::Undefined)),
		_value(a_rhs._value),
		_dataAux(std::exchange(a_rhs._dataAux, 0))
	{
	}

	auto Value::operator=(std::nullptr_t) noexcept -> Value&
	{
		SetNull();
		return *this;
	}

	auto Value::operator=(bool a_rhs) noexcept -> Value&
	{
		SetBoolean(a_rhs);
		return *this;
	}

	auto Value::operator=(std::int32_t a_rhs) noexcept -> Value&
	{
		SetInt(a_rhs);
		return *this;
	}

	auto Value::operator=(std::uint32_t a_rhs) noexcept -> Value&
	{
		SetUInt(a_rhs);
		return *this;
	}

	auto Value::operator=(REX::Float64 a_rhs) noexcept -> Value&
	{
		SetNumber(a_rhs);
		return *this;
	}

	auto Value::operator=(const char* a_rhs) noexcept -> Value&
	{
		SetString(a_rhs);
		return *this;
	}

	auto Value::operator=(const wchar_t* a_rhs) noexcept -> Value&
	{
		SetWString(a_rhs);
		return *this;
	}

	auto Value::operator=(REX::ZStringView a_rhs) noexcept -> Value&
	{
		SetStringView(a_rhs);
		return *this;
	}

	auto Value::operator=(REX::ZWStringView a_rhs) noexcept -> Value&
	{
		SetWStringView(a_rhs);
		return *this;
	}

	auto Value::operator=(const Value& a_rhs) noexcept -> Value&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = a_rhs._type;
		_value = a_rhs._value;
		_dataAux = a_rhs._dataAux;

		if (a_rhs.IsManagedValue()) {
			AcquireManagedValue(a_rhs);
		}

		return *this;
	}

	auto Value::operator=(Value&& a_rhs) noexcept -> Value&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_objectInterface = std::exchange(a_rhs._objectInterface, nullptr);
		_type = std::exchange(a_rhs._type, ValueType::Undefined);
		_value = a_rhs._value;
		_dataAux = std::exchange(a_rhs._dataAux, 0);

		return *this;
	}

	auto Value::operator==(const Value& a_rhs) const noexcept -> bool
	{
		return Equals(a_rhs);
	}

	auto Value::operator<=>(const Value& a_rhs) const noexcept -> std::partial_ordering
	{
		return Compare(a_rhs);
	}

	auto Value::GetType() const noexcept -> Value::ValueType
	{
		return (_type & ValueType::_TypeMask).get();
	}

	auto Value::IsNull() const noexcept -> bool
	{
		return GetType() == ValueType::Null;
	}

	auto Value::IsUndefined() const noexcept -> bool
	{
		return GetType() == ValueType::Undefined;
	}

	auto Value::IsBoolean() const noexcept -> bool
	{
		return GetType() == ValueType::Boolean;
	}

	auto Value::IsInt() const noexcept -> bool
	{
		return GetType() == ValueType::Int;
	}

	auto Value::IsUInt() const noexcept -> bool
	{
		return GetType() == ValueType::UInt;
	}

	auto Value::IsNumber() const noexcept -> bool
	{
		return GetType() == ValueType::Number;
	}

	auto Value::IsString() const noexcept -> bool
	{
		return GetType() == ValueType::String;
	}

	auto Value::IsStringW() const noexcept -> bool
	{
		return GetType() == ValueType::StringW;
	}

	auto Value::IsObject() const noexcept -> bool
	{
		return GetType() == ValueType::Object;
	}

	auto Value::IsArray() const noexcept -> bool
	{
		return GetType() == ValueType::Array;
	}

	auto Value::IsDisplayObject() const noexcept -> bool
	{
		return GetType() == ValueType::DisplayObject;
	}

	auto Value::IsClosure() const noexcept -> bool
	{
		return GetType() == ValueType::Closure;
	}

	auto Value::IsConvertBoolean() const noexcept -> bool
	{
		return GetType() == ValueType::ConvertBoolean;
	}

	auto Value::IsConvertInt() const noexcept -> bool
	{
		return GetType() == ValueType::ConvertInt;
	}

	auto Value::IsConvertUInt() const noexcept -> bool
	{
		return GetType() == ValueType::ConvertUInt;
	}

	auto Value::IsConvertNumber() const noexcept -> bool
	{
		return GetType() == ValueType::ConvertNumber;
	}

	auto Value::IsConvertString() const noexcept -> bool
	{
		return GetType() == ValueType::ConvertString;
	}

	auto Value::IsConvertStringW() const noexcept -> bool
	{
		return GetType() == ValueType::ConvertStringW;
	}

	auto Value::IsNullOrUndefined() const noexcept -> bool
	{
		switch (GetType()) {
			case ValueType::Null:
			case ValueType::Undefined: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto Value::IsAnyInt() const noexcept -> bool
	{
		switch (GetType()) {
			case ValueType::Int:
			case ValueType::UInt: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto Value::IsAnyNumber() const noexcept -> bool
	{
		switch (GetType()) {
			case ValueType::Int:
			case ValueType::UInt:
			case ValueType::Number: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto Value::IsAnyString() const noexcept -> bool
	{
		switch (GetType()) {
			case ValueType::String:
			case ValueType::StringW: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto Value::IsAnyObject() const noexcept -> bool
	{
		switch (GetType()) {
			case ValueType::Object:
			case ValueType::DisplayObject:
			case ValueType::Array: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto Value::IsOrphaned() const noexcept -> bool
	{
		return _type.any(ValueType::OrphanedBit);
	}

	auto Value::IsManaged() const noexcept -> bool
	{
		return _type.any(ValueType::ManagedBit);
	}

	auto Value::IsConversion() const noexcept -> bool
	{
		return _type.any(ValueType::ConvertBit);
	}

	auto Value::IsFunction() const -> bool
	{
		if (!IsAnyObject()) {
			return false;
		}

		return _objectInterface->IsInstanceOf(_value.data, "Function");
	}

	auto Value::IsMovieClip() const -> bool
	{
		if (!IsAnyObject()) {
			return false;
		}

		return _objectInterface->IsInstanceOf(_value.data, "flash.display.MovieClip");
	}

	auto Value::Equals(const Value& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftType = GetType();
		const auto rightType = a_rhs.GetType();

		if (leftType != rightType) {
			return false;
		}

		switch (leftType) {
			case ValueType::Null:
			case ValueType::Undefined: {
				return true;
			}
			case ValueType::Boolean: {
				return GetBoolean() == a_rhs.GetBoolean();
			}
			case ValueType::Int: {
				return GetInt() == a_rhs.GetInt();
			}
			case ValueType::UInt: {
				return GetUInt() == a_rhs.GetUInt();
			}
			case ValueType::Number: {
				return GetNumber() == a_rhs.GetNumber();
			}
			case ValueType::String: {
				return REX::Equals(GetStringView(), a_rhs.GetStringView());
			}
			case ValueType::StringW: {
				return REX::Equals(GetWStringView(), a_rhs.GetWStringView());
			}
			case ValueType::Object:
			case ValueType::DisplayObject:
			case ValueType::Array:
			case ValueType::Closure: {
				return GetUserData() == a_rhs.GetUserData();
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Value::Compare(const Value& a_rhs) const noexcept -> std::partial_ordering
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftType = GetType();
		const auto rightType = a_rhs.GetType();

		if (leftType != rightType) {
			return leftType <=> rightType;
		}

		switch (leftType) {
			case ValueType::Null:
			case ValueType::Undefined: {
				return std::partial_ordering::equivalent;
			}
			case ValueType::Boolean: {
				return GetBoolean() <=> a_rhs.GetBoolean();
			}
			case ValueType::Int: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case ValueType::UInt: {
				return GetUInt() <=> a_rhs.GetUInt();
			}
			case ValueType::Number: {
				return GetNumber() <=> a_rhs.GetNumber();
			}
			case ValueType::String: {
				return GetStringView() <=> a_rhs.GetStringView();
			}
			case ValueType::StringW: {
				return GetWStringView() <=> a_rhs.GetWStringView();
			}
			case ValueType::Object:
			case ValueType::DisplayObject:
			case ValueType::Array:
			case ValueType::Closure: {
				return GetUserData() <=> a_rhs.GetUserData();
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Value::GetNull() const noexcept -> std::nullptr_t
	{
		REX::Assert(IsNull());
		REX::Assert(_value.null == nullptr);
		return nullptr;
	}

	auto Value::GetUndefined() const noexcept -> std::nullptr_t
	{
		REX::Assert(IsUndefined());
		REX::Assert(_value.undefined == nullptr);
		return nullptr;
	}

	auto Value::GetBoolean() const noexcept -> bool
	{
		REX::Assert(IsBoolean());
		return _value.boolean;
	}

	auto Value::GetInt() const noexcept -> std::int32_t
	{
		REX::Assert(IsInt());
		return _value.int32;
	}

	auto Value::GetUInt() const noexcept -> std::uint32_t
	{
		REX::Assert(IsUInt());
		return _value.uint32;
	}

	auto Value::GetNumber() const noexcept -> REX::Float64
	{
		REX::Assert(IsNumber());
		return _value.number;
	}

	auto Value::GetString() const noexcept -> const char*
	{
		REX::Assert(IsString());
		return IsManagedValue() ? *_value.mstring : _value.string;
	}

	auto Value::GetWString() const noexcept -> const wchar_t*
	{
		REX::Assert(IsStringW());
		return _value.wstring;
	}

	auto Value::GetStringView() const noexcept -> REX::ZStringView
	{
		return GetString();
	}

	auto Value::GetWStringView() const noexcept -> REX::ZWStringView
	{
		return GetWString();
	}

	auto Value::GetUserData() const noexcept -> void*
	{
		REX::Assert(IsAnyObject());
		return _value.data;
	}

	void Value::SetNull() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::Null;
		_value.null = nullptr;
	}

	void Value::SetUndefined() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::Undefined;
		_value.undefined = nullptr;
	}

	void Value::SetBoolean(bool a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::Boolean;
		_value = a_value;
	}

	void Value::SetInt(std::int32_t a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::Int;
		_value = a_value;
	}

	void Value::SetUInt(std::uint32_t a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::UInt;
		_value = a_value;
	}

	void Value::SetNumber(REX::Float64 a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::Number;
		_value = a_value;
	}

	void Value::SetString(const char* a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::String;
		_value = a_value;
	}

	void Value::SetWString(const wchar_t* a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::StringW;
		_value = a_value;
	}

	void Value::SetStringView(REX::ZStringView a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::String;
		_value = a_value.data();
	}

	void Value::SetWStringView(REX::ZWStringView a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::StringW;
		_value = a_value.data();
	}

	void Value::SetConvertBoolean() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::ConvertBoolean;
	}

	void Value::SetConvertInt() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::ConvertInt;
	}

	void Value::SetConvertUInt() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::ConvertUInt;
	}

	void Value::SetConvertNumber() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::ConvertNumber;
	}

	void Value::SetConvertString() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::ConvertString;
	}

	void Value::SetConvertStringW() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::ConvertStringW;
	}

	auto Value::IsInstanceOf(const char* a_className) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->IsInstanceOf(_value.data, a_className);
	}

	auto Value::GetParent(Value* a_value) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->GetParent(_value.data, a_value);
	}

	auto Value::HasMember(const char* a_name) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->HasMember(_value.data, a_name, IsDisplayObject());
	}

	auto Value::GetMember(const char* a_name, Value* a_value) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->GetMember(_value.data, a_name, a_value, IsDisplayObject());
	}

	auto Value::SetMember(const char* a_name, const Value& a_value) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->SetMember(_value.data, a_name, a_value, IsDisplayObject());
	}

	auto Value::DeleteMember(const char* a_name) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->DeleteMember(_value.data, a_name, IsDisplayObject());
	}

	void Value::VisitMembers(REX::NotNull<ObjectVisitor*> a_visitor) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		_objectInterface->VisitMembers(_value.data, a_visitor.get(), IsDisplayObject());
	}

	void Value::VisitMembers(REX::NotNull<std::move_only_function<ObjectVisitFunctor>> a_visitor) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		class MemberVisitor final : public ObjectInterface::ObjVisitor
		{
		public:
			explicit MemberVisitor(REX::NotNull<std::move_only_function<ObjectVisitFunctor>> a_func) noexcept :
				_func(std::move(a_func))
			{
			}

			~MemberVisitor() noexcept override = default;

			MemberVisitor(const MemberVisitor&) = delete;
			MemberVisitor(MemberVisitor&&) = delete;

			auto operator=(const MemberVisitor&) -> MemberVisitor& = delete;
			auto operator=(MemberVisitor&&) -> MemberVisitor& = delete;

			auto IncludeAS3PublicMembers() const noexcept -> bool override
			{
				return true;
			}

			void Visit(const char* a_name, const Value& a_value) override
			{
				std::invoke(_func.get(), a_name, a_value);
			}

		private:
			REX::NotNull<std::move_only_function<ObjectVisitFunctor>> _func;
		};

		auto visitor = MemberVisitor(std::move(a_visitor));
		_objectInterface->VisitMembers(_value.data, std::addressof(visitor), IsDisplayObject());
	}

	auto Value::GetArraySize() const -> std::uint32_t
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->GetArraySize(_value.data);
	}

	auto Value::SetArraySize(std::uint32_t a_size) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->SetArraySize(_value.data, a_size);
	}

	auto Value::GetElement(std::uint32_t a_index, Value* a_value) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->GetElement(_value.data, a_index, a_value);
	}

	auto Value::SetElement(std::uint32_t a_index, const Value& a_value) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->SetElement(_value.data, a_index, a_value);
	}

	auto Value::PushBack(const Value& a_value) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->PushBack(_value.data, a_value);
	}

	auto Value::PopBack(Value* a_value) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->PopBack(_value.data, a_value);
	}

	auto Value::RemoveElements(std::uint32_t a_startIndex, std::int32_t a_count) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->RemoveElements(_value.data, a_startIndex, a_count);
	}

	auto Value::RemoveElement(std::uint32_t a_index) -> bool
	{
		return RemoveElements(a_index, 1);
	}

	auto Value::ClearElements() -> bool
	{
		return RemoveElements(0);
	}

	void Value::VisitElements(REX::NotNull<ArrayVisitor*> a_visitor, std::uint32_t a_startIndex, std::int32_t a_count)
		const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		_objectInterface->VisitElements(_value.data, a_visitor.get(), a_startIndex, a_count);
	}

	void Value::VisitElements(
		REX::NotNull<std::move_only_function<ArrayVisitFunctor>> a_visitor,
		std::uint32_t a_startIndex,
		std::int32_t a_count) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		class ElementVisitor final : public ObjectInterface::ArrVisitor
		{
		public:
			explicit ElementVisitor(REX::NotNull<std::move_only_function<ArrayVisitFunctor>> a_func) noexcept :
				_func(std::move(a_func))
			{
			}

			~ElementVisitor() noexcept override = default;

			ElementVisitor(const ElementVisitor&) = delete;
			ElementVisitor(ElementVisitor&&) = delete;

			auto operator=(const ElementVisitor&) -> ElementVisitor& = delete;
			auto operator=(ElementVisitor&&) -> ElementVisitor& = delete;

			void Visit(std::uint32_t a_index, const Value& a_value) override
			{
				std::invoke(_func.get(), a_index, a_value);
			}

		private:
			REX::NotNull<std::move_only_function<ArrayVisitFunctor>> _func;
		};

		auto visitor = ElementVisitor(std::move(a_visitor));
		_objectInterface->VisitElements(_value.data, std::addressof(visitor), a_startIndex, a_count);
	}

	auto Value::GetMovie() const -> Ptr<Movie>
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return Ptr(RE::DynamicCast<Movie*>(_objectInterface->movieRoot));
	}

	auto Value::GetMovieImpl() const -> Ptr<MovieImpl>
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return Ptr(_objectInterface->movieRoot);
	}

	auto Value::GetDisplayInfo(DisplayInfo* a_info) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GetDisplayInfo(_value.data, a_info);
	}

	auto Value::SetDisplayInfo(const DisplayInfo& a_info) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->SetDisplayInfo(_value.data, a_info);
	}

	auto Value::GetDisplayMatrix(Render::Matrix2x4F* a_matrix) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GetDisplayMatrix(_value.data, a_matrix);
	}

	auto Value::SetDisplayMatrix(const Render::Matrix2x4F* a_matrix) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->SetDisplayMatrix(_value.data, a_matrix);
	}

	auto Value::GetCxform(Render::Cxform* a_cxform) const -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GetCxform(_value.data, a_cxform);
	}

	auto Value::SetCxform(const Render::Cxform* a_cxform) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->SetCxform(_value.data, a_cxform);
	}

	auto Value::AttachMovie(
		Value* a_movieClip,
		const char* a_symbolName,
		const char* a_instanceName,
		std::int32_t a_depth,
		const MemberValueSet* a_initList) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->AttachMovie(
			_value.data,
			a_movieClip,
			a_symbolName,
			a_instanceName,
			a_depth,
			a_initList);
	}

	auto Value::CreateEmptyMovieClip(Value* a_movieClip, const char* a_instanceName, std::int32_t a_depth) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->CreateEmptyMovieClip(_value.data, a_movieClip, a_instanceName, a_depth);
	}

	auto Value::GotoAndPlay(std::uint32_t a_frame) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, false);
	}

	auto Value::GotoAndPlay(const char* a_frame) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, false);
	}

	auto Value::GotoAndStop(std::uint32_t a_frame) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, true);
	}

	auto Value::GotoAndStop(const char* a_frame) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, true);
	}

	auto Value::Invoke(const char* a_name, Value* a_result, const Value* a_args, std::uint32_t a_numArgs) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->Invoke(_value.data, a_result, a_name, a_args, a_numArgs, IsDisplayObject());
	}

	auto Value::Invoke(const char* a_name, std::span<const Value> a_args) -> bool
	{
		return Invoke(a_name, nullptr, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	auto Value::Invoke(const char* a_name, Value* a_result, std::span<const Value> a_args) -> bool
	{
		return Invoke(a_name, a_result, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	auto Value::InvokeFunction(Value* a_result, const Value* a_args, std::uint32_t a_numArgs) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsFunction());

		auto thisArg = NULL_VALUE;

		auto callArgs = std::vector<Value, StlAllocator<Value>>();
		callArgs.reserve(a_numArgs + 1);

		callArgs.push_back(std::move(thisArg));
		callArgs.insert(callArgs.end(), a_args, a_args + a_numArgs);

		return _objectInterface->Invoke(
			_value.data,
			a_result,
			"call",
			callArgs.data(),
			static_cast<std::uint32_t>(callArgs.size()),
			false);
	}

	auto Value::InvokeFunction(std::span<const Value> a_args) -> bool
	{
		return InvokeFunction(nullptr, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	auto Value::InvokeFunction(Value* a_result, std::span<const Value> a_args) -> bool
	{
		return InvokeFunction(a_result, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	auto Value::ApplyFunction(Value* a_result, const Value* a_args) -> bool
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsFunction());
		REX::Assert(a_args == nullptr || a_args->IsNull() || a_args->IsArray());

		auto thisArg = NULL_VALUE;
		auto applyArgs = std::array<Value, 2>();

		applyArgs[0] = std::move(thisArg);
		applyArgs[1] = a_args ? *a_args : NULL_VALUE;

		return _objectInterface->Invoke(
			_value.data,
			a_result,
			"apply",
			applyArgs.data(),
			static_cast<std::uint32_t>(applyArgs.size()),
			false);
	}

	auto Value::ApplyFunction(const Value* a_args) -> bool
	{
		return ApplyFunction(nullptr, a_args);
	}

	auto Value::IsManagedValue() const noexcept -> bool
	{
		const auto managed = _type.all(ValueType::ManagedBit);
		REX::Assert(managed ? _objectInterface != nullptr : true);
		return managed;
	}

	void Value::AcquireManagedValue(const Value& a_rhs) noexcept
	{
		REX::Assert(a_rhs._value.data != nullptr);
		REX::Assert(a_rhs._objectInterface != nullptr);

		try {
			_objectInterface = a_rhs._objectInterface;
			_objectInterface->ObjectAddRef(this, _value.data);
		}
		catch (...) {
			REX::Fail("Failed to acquire ref value."sv);
		}
	}

	void Value::ReleaseManagedValue() noexcept
	{
		REX::Assert(_value.data != nullptr);
		REX::Assert(_objectInterface != nullptr);

		try {
			_objectInterface->ObjectRelease(this, _value.data);
			_objectInterface = nullptr;
		}
		catch (...) {
			REX::Fail("Failed to release ref value."sv);
		}
	}

	void Value::swap(Value& a_other) noexcept
	{
		std::swap(_objectInterface, a_other._objectInterface);
		std::swap(_type, a_other._type);
		std::swap(_value, a_other._value);
		std::swap(_dataAux, a_other._dataAux);
	}
}

namespace std
{
	auto hash<Scaleform::GFx::Value>::operator()(const Scaleform::GFx::Value& a_key) const noexcept -> std::size_t
	{
		using ValueType = Scaleform::GFx::Value::ValueType;

		const auto type = a_key.GetType();
		switch (type) {
			case ValueType::Null: {
				return REX::HashCombine(type, a_key.GetNull());
			}
			case ValueType::Undefined: {
				return REX::HashCombine(type, a_key.GetUndefined());
			}
			case ValueType::Boolean: {
				return REX::HashCombine(type, a_key.GetBoolean());
			}
			case ValueType::Int: {
				return REX::HashCombine(type, a_key.GetInt());
			}
			case ValueType::UInt: {
				return REX::HashCombine(type, a_key.GetUInt());
			}
			case ValueType::Number: {
				return REX::HashCombine(type, a_key.GetNumber());
			}
			case ValueType::String: {
				return REX::HashCombine(type, a_key.GetStringView());
			}
			case ValueType::StringW: {
				return REX::HashCombine(type, a_key.GetWStringView());
			}
			case ValueType::Object:
			case ValueType::DisplayObject:
			case ValueType::Array:
			case ValueType::Closure: {
				return REX::HashCombine(type, a_key.GetUserData());
			}
			default: {
				std::unreachable();
			}
		}
	}
}
