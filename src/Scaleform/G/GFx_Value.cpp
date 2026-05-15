#include "Scaleform/G/GFx_Value.hpp"

#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_MovieImpl.hpp"

namespace Scaleform::GFx
{
	Value::ValueUnion::ValueUnion() noexcept
		: undefined(nullptr)
	{
	}

	Value::ValueUnion::~ValueUnion() noexcept
	{
	}

	Value::ValueUnion::ValueUnion(std::nullptr_t) noexcept
		: null(nullptr)
	{
	}

	Value::ValueUnion::ValueUnion(bool a_rhs) noexcept
		: boolean(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(std::int32_t a_rhs) noexcept
		: int32(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(std::uint32_t a_rhs) noexcept
		: uint32(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(REX::Float64 a_rhs) noexcept
		: number(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(const char* a_rhs) noexcept
		: string(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(const wchar_t* a_rhs) noexcept
		: wstring(a_rhs)
	{
	}

	Value::ValueUnion::ValueUnion(REX::zstring_view a_rhs) noexcept
		: string(a_rhs.data())
	{
	}

	Value::ValueUnion::ValueUnion(REX::zwstring_view a_rhs) noexcept
		: wstring(a_rhs.data())
	{
	}

	Value::ValueUnion::ValueUnion(const ValueUnion& a_rhs) noexcept
		: data(a_rhs.data)
	{
	}

	Value::ValueUnion::ValueUnion(ValueUnion&& a_rhs) noexcept
		: data(std::exchange(a_rhs.data, nullptr))
	{
	}

	Value::ValueUnion& Value::ValueUnion::operator=(std::nullptr_t) noexcept
	{
		data = nullptr;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(bool a_rhs) noexcept
	{
		boolean = a_rhs;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(std::int32_t a_rhs) noexcept
	{
		int32 = a_rhs;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(std::uint32_t a_rhs) noexcept
	{
		uint32 = a_rhs;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(REX::Float64 a_rhs) noexcept
	{
		number = a_rhs;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(const char* a_rhs) noexcept
	{
		string = a_rhs;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(const wchar_t* a_rhs) noexcept
	{
		wstring = a_rhs;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(REX::zstring_view a_rhs) noexcept
	{
		string = a_rhs.data();
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(REX::zwstring_view a_rhs) noexcept
	{
		wstring = a_rhs.data();
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(const ValueUnion& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		data = a_rhs.data;
		return *this;
	}

	Value::ValueUnion& Value::ValueUnion::operator=(ValueUnion&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		data = std::exchange(a_rhs.data, nullptr);
		return *this;
	}

	REX::Float64 Value::DisplayInfo::GetX() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kX));
		return _x;
	}

	REX::Float64 Value::DisplayInfo::GetY() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kY));
		return _y;
	}

	REX::Float64 Value::DisplayInfo::GetZ() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kZ));
		return _z;
	}

	REX::Float64 Value::DisplayInfo::GetXScale() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kXScale));
		return _xScale;
	}

	REX::Float64 Value::DisplayInfo::GetYScale() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kYScale));
		return _yScale;
	}

	REX::Float64 Value::DisplayInfo::GetZScale() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kZScale));
		return _zScale;
	}

	REX::Float64 Value::DisplayInfo::GetRotation() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kRotation));
		return _rotation;
	}

	REX::Float64 Value::DisplayInfo::GetXRotation() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kXRotation));
		return _xRotation;
	}

	REX::Float64 Value::DisplayInfo::GetYRotation() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kYRotation));
		return _yRotation;
	}

	REX::Float64 Value::DisplayInfo::GetAlpha() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kAlpha));
		return _alpha;
	}

	bool Value::DisplayInfo::GetVisible() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kVisible));
		return _visible;
	}

	REX::Float64 Value::DisplayInfo::GetFOV() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kFOV));
		return _fov;
	}

	const Render::Matrix3x4<REX::Float32>* Value::DisplayInfo::GetViewMatrix3D() const noexcept
	{
		return _varsSet.any(SetFlags::kViewMatrix3D) ? std::addressof(_viewMatrix3D) : nullptr;
	}

	const Render::Matrix4x4<REX::Float32>* Value::DisplayInfo::GetProjectionMatrix3D() const noexcept
	{
		return _varsSet.any(SetFlags::kProjMatrix3D) ? std::addressof(_projectionMatrix3D) : nullptr;
	}

	Render::EdgeAAMode Value::DisplayInfo::GetEdgeAAMode() const noexcept
	{
		REX::Assert(_varsSet.any(SetFlags::kEdgeAAMode));
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
		_varsSet.set(SetFlags::kXScale);
		_xScale = a_xScale;
	}

	void Value::DisplayInfo::SetYScale(REX::Float64 a_yScale) noexcept
	{
		_varsSet.set(SetFlags::kYScale);
		_yScale = a_yScale;
	}

	void Value::DisplayInfo::SetZScale(REX::Float64 a_zScale) noexcept
	{
		_varsSet.set(SetFlags::kZScale);
		_zScale = a_zScale;
	}

	void Value::DisplayInfo::SetRotation(REX::Float64 a_rotation) noexcept
	{
		_varsSet.set(SetFlags::kRotation);
		_rotation = a_rotation;
	}

	void Value::DisplayInfo::SetXRotation(REX::Float64 a_xRotation) noexcept
	{
		_varsSet.set(SetFlags::kXRotation);
		_xRotation = a_xRotation;
	}

	void Value::DisplayInfo::SetYRotation(REX::Float64 a_yRotation) noexcept
	{
		_varsSet.set(SetFlags::kYRotation);
		_yRotation = a_yRotation;
	}

	void Value::DisplayInfo::SetAlpha(REX::Float64 a_alpha) noexcept
	{
		_varsSet.set(SetFlags::kAlpha);
		_alpha = a_alpha;
	}

	void Value::DisplayInfo::SetVisible(bool a_visible) noexcept
	{
		_varsSet.set(SetFlags::kVisible);
		_visible = a_visible;
	}

	void Value::DisplayInfo::SetFOV(REX::Float64 a_fov) noexcept
	{
		_varsSet.set(SetFlags::kFOV);
		_fov = a_fov;
	}

	void Value::DisplayInfo::SetViewMatrix3D(const Render::Matrix3x4<REX::Float32>* a_matrix) noexcept
	{
		if (a_matrix) {
			_varsSet.set(SetFlags::kViewMatrix3D);
			_viewMatrix3D = *a_matrix;
		}
		else {
			_varsSet.reset(SetFlags::kViewMatrix3D);
		}
	}

	void Value::DisplayInfo::SetProjectionMatrix3D(const Render::Matrix4x4<REX::Float32>* a_matrix) noexcept
	{
		if (a_matrix) {
			_varsSet.set(SetFlags::kProjMatrix3D);
			_projectionMatrix3D = *a_matrix;
		}
		else {
			_varsSet.reset(SetFlags::kProjMatrix3D);
		}
	}

	void Value::DisplayInfo::SetEdgeAAMode(Render::EdgeAAMode a_mode) noexcept
	{
		_varsSet.set(SetFlags::kEdgeAAMode);
		_edgeAAMode = a_mode;
	}

	void Value::ObjectInterface::ObjectAddRef(Value* a_value, void* a_object)
	{
		using FuncType = decltype(&ObjectInterface::ObjectRelease);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::ObjectAddRef };
		std::invoke(FUNC, this, a_value, a_object);
	}

	void Value::ObjectInterface::ObjectRelease(Value* a_value, void* a_object)
	{
		using FuncType = decltype(&ObjectInterface::ObjectRelease);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::ObjectRelease };
		std::invoke(FUNC, this, a_value, a_object);
	}

	bool Value::ObjectInterface::IsInstanceOf(void* a_data, const char* a_className) const
	{
		using FuncType = decltype(&ObjectInterface::IsInstanceOf);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::IsInstanceOf };
		return std::invoke(FUNC, this, a_data, a_className);
	}

	bool Value::ObjectInterface::GetParent(void* a_data, Value* a_value) const
	{
		using FuncType = decltype(&ObjectInterface::GetParent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetParent };
		return std::invoke(FUNC, this, a_data, a_value);
	}

	bool Value::ObjectInterface::HasMember(void* a_data, const char* a_name, bool a_isDisplayObject) const
	{
		using FuncType = decltype(&ObjectInterface::HasMember);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::HasMember };
		return std::invoke(FUNC, this, a_data, a_name, a_isDisplayObject);
	}

	bool Value::ObjectInterface::GetMember(void* a_data, const char* a_name, Value* a_value, bool a_isDisplayObject) const
	{
		using FuncType = decltype(&ObjectInterface::GetMember);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetMember };
		return std::invoke(FUNC, this, a_data, a_name, a_value, a_isDisplayObject);
	}

	bool Value::ObjectInterface::SetMember(void* a_data, const char* a_name, const Value& a_value, bool a_isDisplayObject)
	{
		using FuncType = decltype(&ObjectInterface::SetMember);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::SetMember };
		return std::invoke(FUNC, this, a_data, a_name, a_value, a_isDisplayObject);
	}

	bool Value::ObjectInterface::DeleteMember(void* a_data, const char* a_name, bool a_isDisplayObject)
	{
		using FuncType = decltype(&ObjectInterface::DeleteMember);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::DeleteMember };
		return std::invoke(FUNC, this, a_data, a_name, a_isDisplayObject);
	}

	void Value::ObjectInterface::VisitMembers(void* a_data, ObjVisitor* a_visitor, bool a_isDisplayObject) const
	{
		using FuncType = decltype(&ObjectInterface::VisitMembers);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::VisitMembers };
		std::invoke(FUNC, this, a_data, a_visitor, a_isDisplayObject);
	}

	std::uint32_t Value::ObjectInterface::GetArraySize(void* a_data) const
	{
		using FuncType = decltype(&ObjectInterface::GetArraySize);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetArraySize };
		return std::invoke(FUNC, this, a_data);
	}

	bool Value::ObjectInterface::SetArraySize(void* a_data, std::uint32_t a_size)
	{
		using FuncType = decltype(&ObjectInterface::SetArraySize);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::SetArraySize };
		return std::invoke(FUNC, this, a_data, a_size);
	}

	bool Value::ObjectInterface::GetElement(void* a_data, std::uint32_t a_index, Value* a_value) const
	{
		using FuncType = decltype(&ObjectInterface::GetElement);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetElement };
		return std::invoke(FUNC, this, a_data, a_index, a_value);
	}

	bool Value::ObjectInterface::SetElement(void* a_data, std::uint32_t a_index, const Value& a_value)
	{
		using FuncType = decltype(&ObjectInterface::SetElement);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::SetElement };
		return std::invoke(FUNC, this, a_data, a_index, a_value);
	}

	bool Value::ObjectInterface::PushBack(void* a_data, const Value& a_value)
	{
		using FuncType = decltype(&ObjectInterface::PushBack);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::PushBack };
		return std::invoke(FUNC, this, a_data, a_value);
	}

	bool Value::ObjectInterface::PopBack(void* a_data, Value* a_value)
	{
		using FuncType = decltype(&ObjectInterface::PopBack);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::PopBack };
		return std::invoke(FUNC, this, a_data, a_value);
	}

	bool Value::ObjectInterface::RemoveElements(void* a_data, std::uint32_t a_startIndex, std::int32_t a_count)
	{
		using FuncType = decltype(&ObjectInterface::RemoveElements);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::RemoveElements };
		return std::invoke(FUNC, this, a_data, a_startIndex, a_count);
	}

	void Value::ObjectInterface::VisitElements(void* a_data, ArrVisitor* a_visitor, std::uint32_t a_startIndex, std::int32_t a_count) const
	{
		using FuncType = decltype(&ObjectInterface::VisitElements);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::VisitElements };
		std::invoke(FUNC, this, a_data, a_visitor, a_startIndex, a_count);
	}

	bool Value::ObjectInterface::GetDisplayInfo(void* a_data, DisplayInfo* a_info) const
	{
		using FuncType = decltype(&ObjectInterface::GetDisplayInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetDisplayInfo };
		return std::invoke(FUNC, this, a_data, a_info);
	}

	bool Value::ObjectInterface::SetDisplayInfo(void* a_data, const DisplayInfo& a_info)
	{
		using FuncType = decltype(&ObjectInterface::SetDisplayInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::SetDisplayInfo };
		return std::invoke(FUNC, this, a_data, a_info);
	}

	bool Value::ObjectInterface::GetDisplayMatrix(void* a_data, Render::Matrix2x4<REX::Float32>* a_matrix) const
	{
		using FuncType = decltype(&ObjectInterface::GetDisplayMatrix);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetDisplayMatrix };
		return std::invoke(FUNC, this, a_data, a_matrix);
	}

	bool Value::ObjectInterface::SetDisplayMatrix(void* a_data, const Render::Matrix2x4<REX::Float32>* a_matrix)
	{
		using FuncType = decltype(&ObjectInterface::SetDisplayMatrix);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::SetDisplayMatrix };
		return std::invoke(FUNC, this, a_data, a_matrix);
	}

	bool Value::ObjectInterface::GetCxform(void* a_data, Render::Cxform* a_cxform) const
	{
		using FuncType = decltype(&ObjectInterface::GetCxform);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GetCxform };
		return std::invoke(FUNC, this, a_data, a_cxform);
	}

	bool Value::ObjectInterface::SetCxform(void* a_data, const Render::Cxform* a_cxform)
	{
		using FuncType = decltype(&ObjectInterface::SetCxform);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::SetCxform };
		return std::invoke(FUNC, this, a_data, a_cxform);
	}

	bool Value::ObjectInterface::AttachMovie(void* a_data, Value* a_movieClip, const char* a_symbolName, const char* a_instanceName, std::int32_t a_depth, const MemberValueSet* a_initList)
	{
		using FuncType = decltype(&ObjectInterface::AttachMovie);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::AttachMovie };
		return std::invoke(FUNC, this, a_data, a_movieClip, a_symbolName, a_instanceName, a_depth, a_initList);
	}

	bool Value::ObjectInterface::CreateEmptyMovieClip(void* a_data, Value* a_movieClip, const char* a_instanceName, std::int32_t a_depth)
	{
		using FuncType = decltype(&ObjectInterface::CreateEmptyMovieClip);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::CreateEmptyMovieClip };
		return std::invoke(FUNC, this, a_data, a_movieClip, a_instanceName, a_depth);
	}

	bool Value::ObjectInterface::GotoAndPlay(void* a_data, std::uint32_t a_frame, bool a_stop)
	{
		using FuncType = bool (ObjectInterface::*)(void*, std::int32_t, bool);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GotoAndPlay_Int };
		return std::invoke(FUNC, this, a_data, a_frame, a_stop);
	}

	bool Value::ObjectInterface::GotoAndPlay(void* a_data, const char* a_frame, bool a_stop)
	{
		using FuncType = bool (ObjectInterface::*)(void*, const char*, bool);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::GotoAndPlay_String };
		return std::invoke(FUNC, this, a_data, a_frame, a_stop);
	}

	bool Value::ObjectInterface::Invoke(void* a_data, Value* a_result, const char* a_name, const Value* a_args, std::size_t a_numArgs, bool a_isDisplayObject)
	{
		using FuncType = decltype(&ObjectInterface::Invoke);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Value::Invoke };
		return std::invoke(FUNC, this, a_data, a_result, a_name, a_args, a_numArgs, a_isDisplayObject);
	}

	Value::Value() noexcept
		: _type(ValueType::kUndefined)
	{
	}

	Value::~Value() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kUndefined;
	}

	Value::Value(std::nullptr_t) noexcept
		: _type(ValueType::kNull)
	{
	}

	Value::Value(bool a_rhs) noexcept
		: _type(ValueType::kBoolean),
		  _value(a_rhs)
	{
	}

	Value::Value(std::int32_t a_rhs) noexcept
		: _type(ValueType::kInt),
		  _value(a_rhs)
	{
	}

	Value::Value(std::uint32_t a_rhs) noexcept
		: _type(ValueType::kUInt),
		  _value(a_rhs)
	{
	}

	Value::Value(REX::Float64 a_rhs) noexcept
		: _type(ValueType::kNumber),
		  _value(a_rhs)
	{
	}

	Value::Value(const char* a_rhs) noexcept
		: _type(ValueType::kString),
		  _value(a_rhs)
	{
	}

	Value::Value(const wchar_t* a_rhs) noexcept
		: _type(ValueType::kStringW),
		  _value(a_rhs)
	{
	}

	Value::Value(REX::zstring_view a_rhs) noexcept
		: _type(ValueType::kString),
		  _value(a_rhs.data())
	{
	}

	Value::Value(REX::zwstring_view a_rhs) noexcept
		: _type(ValueType::kStringW),
		  _value(a_rhs.data())
	{
	}

	Value::Value(const Value& a_rhs) noexcept
		: _type(a_rhs._type),
		  _value(a_rhs._value),
		  _dataAux(a_rhs._dataAux)
	{
		if (a_rhs.IsManagedValue()) {
			AcquireManagedValue(a_rhs);
		}
	}

	Value::Value(Value&& a_rhs) noexcept
		: _objectInterface(std::exchange(a_rhs._objectInterface, nullptr)),
		  _type(std::exchange(a_rhs._type, ValueType::kUndefined)),
		  _value(std::move(a_rhs._value)),
		  _dataAux(std::exchange(a_rhs._dataAux, 0))
	{
	}

	Value& Value::operator=(std::nullptr_t) noexcept
	{
		SetNull();
		return *this;
	}

	Value& Value::operator=(bool a_rhs) noexcept
	{
		SetBoolean(a_rhs);
		return *this;
	}

	Value& Value::operator=(std::int32_t a_rhs) noexcept
	{
		SetInt(a_rhs);
		return *this;
	}

	Value& Value::operator=(std::uint32_t a_rhs) noexcept
	{
		SetUInt(a_rhs);
		return *this;
	}

	Value& Value::operator=(REX::Float64 a_rhs) noexcept
	{
		SetNumber(a_rhs);
		return *this;
	}

	Value& Value::operator=(const char* a_rhs) noexcept
	{
		SetString(a_rhs);
		return *this;
	}

	Value& Value::operator=(const wchar_t* a_rhs) noexcept
	{
		SetWString(a_rhs);
		return *this;
	}

	Value& Value::operator=(REX::zstring_view a_rhs) noexcept
	{
		SetStringView(a_rhs);
		return *this;
	}

	Value& Value::operator=(REX::zwstring_view a_rhs) noexcept
	{
		SetWStringView(a_rhs);
		return *this;
	}

	Value& Value::operator=(const Value& a_rhs) noexcept
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

	Value& Value::operator=(Value&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_objectInterface = std::exchange(a_rhs._objectInterface, nullptr);
		_type = std::exchange(a_rhs._type, ValueType::kUndefined);
		_value = std::move(a_rhs._value);
		_dataAux = std::exchange(a_rhs._dataAux, 0);

		return *this;
	}

	bool Value::operator==(const Value& a_rhs) const noexcept
	{
		return Equals(a_rhs);
	}

	bool Value::operator!=(const Value& a_rhs) const noexcept
	{
		return !(*this == a_rhs);
	}

	std::partial_ordering Value::operator<=>(const Value& a_rhs) const noexcept
	{
		return Compare(a_rhs);
	}

	Value::ValueType Value::GetType() const noexcept
	{
		return *(_type & ValueType::kTypeMask);
	}

	bool Value::IsNull() const noexcept
	{
		return GetType() == ValueType::kNull;
	}

	bool Value::IsUndefined() const noexcept
	{
		return GetType() == ValueType::kUndefined;
	}

	bool Value::IsBoolean() const noexcept
	{
		return GetType() == ValueType::kBoolean;
	}

	bool Value::IsInt() const noexcept
	{
		return GetType() == ValueType::kInt;
	}

	bool Value::IsUInt() const noexcept
	{
		return GetType() == ValueType::kUInt;
	}

	bool Value::IsNumber() const noexcept
	{
		return GetType() == ValueType::kNumber;
	}

	bool Value::IsString() const noexcept
	{
		return GetType() == ValueType::kString;
	}

	bool Value::IsStringW() const noexcept
	{
		return GetType() == ValueType::kStringW;
	}

	bool Value::IsObject() const noexcept
	{
		return GetType() == ValueType::kObject;
	}

	bool Value::IsArray() const noexcept
	{
		return GetType() == ValueType::kArray;
	}

	bool Value::IsDisplayObject() const noexcept
	{
		return GetType() == ValueType::kDisplayObject;
	}

	bool Value::IsClosure() const noexcept
	{
		return GetType() == ValueType::kClosure;
	}

	bool Value::IsConvertBoolean() const noexcept
	{
		return GetType() == ValueType::kConvertBoolean;
	}

	bool Value::IsConvertInt() const noexcept
	{
		return GetType() == ValueType::kConvertInt;
	}

	bool Value::IsConvertUInt() const noexcept
	{
		return GetType() == ValueType::kConvertUInt;
	}

	bool Value::IsConvertNumber() const noexcept
	{
		return GetType() == ValueType::kConvertNumber;
	}

	bool Value::IsConvertString() const noexcept
	{
		return GetType() == ValueType::kConvertString;
	}

	bool Value::IsConvertStringW() const noexcept
	{
		return GetType() == ValueType::kConvertStringW;
	}

	bool Value::IsNullOrUndefined() const noexcept
	{
		switch (GetType()) {
			case ValueType::kNull:
			case ValueType::kUndefined: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool Value::IsAnyInt() const noexcept
	{
		switch (GetType()) {
			case ValueType::kInt:
			case ValueType::kUInt: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool Value::IsAnyNumber() const noexcept
	{
		switch (GetType()) {
			case ValueType::kInt:
			case ValueType::kUInt:
			case ValueType::kNumber: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool Value::IsAnyString() const noexcept
	{
		switch (GetType()) {
			case ValueType::kString:
			case ValueType::kStringW: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool Value::IsAnyObject() const noexcept
	{
		switch (GetType()) {
			case ValueType::kObject:
			case ValueType::kDisplayObject:
			case ValueType::kArray: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	bool Value::IsOrphaned() const noexcept
	{
		return _type.any(ValueType::kOrphanedBit);
	}

	bool Value::IsManaged() const noexcept
	{
		return _type.any(ValueType::kManagedBit);
	}

	bool Value::IsConversion() const noexcept
	{
		return _type.any(ValueType::kConvertBit);
	}

	bool Value::IsFunction() const
	{
		if (!IsAnyObject()) {
			return false;
		}

		return _objectInterface->IsInstanceOf(_value.data, "Function");
	}

	bool Value::IsMovieClip() const
	{
		if (!IsAnyObject()) {
			return false;
		}

		return _objectInterface->IsInstanceOf(_value.data, "flash.display.MovieClip");
	}

	bool Value::Equals(const Value& a_rhs) const noexcept
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
			case ValueType::kNull:
			case ValueType::kUndefined: {
				return true;
			}
			case ValueType::kBoolean: {
				return GetBoolean() == a_rhs.GetBoolean();
			}
			case ValueType::kInt: {
				return GetInt() == a_rhs.GetInt();
			}
			case ValueType::kUInt: {
				return GetUInt() == a_rhs.GetUInt();
			}
			case ValueType::kNumber: {
				return GetNumber() == a_rhs.GetNumber();
			}
			case ValueType::kString: {
				return REX::Equals(GetStringView(), a_rhs.GetStringView());
			}
			case ValueType::kStringW: {
				return REX::Equals(GetWStringView(), a_rhs.GetWStringView());
			}
			case ValueType::kObject:
			case ValueType::kDisplayObject:
			case ValueType::kArray:
			case ValueType::kClosure: {
				return GetUserData() == a_rhs.GetUserData();
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::partial_ordering Value::Compare(const Value& a_rhs) const noexcept
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
			case ValueType::kNull:
			case ValueType::kUndefined: {
				return std::partial_ordering::equivalent;
			}
			case ValueType::kBoolean: {
				return GetBoolean() <=> a_rhs.GetBoolean();
			}
			case ValueType::kInt: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case ValueType::kUInt: {
				return GetUInt() <=> a_rhs.GetUInt();
			}
			case ValueType::kNumber: {
				return GetNumber() <=> a_rhs.GetNumber();
			}
			case ValueType::kString: {
				return GetStringView() <=> a_rhs.GetStringView();
			}
			case ValueType::kStringW: {
				return GetWStringView() <=> a_rhs.GetWStringView();
			}
			case ValueType::kObject:
			case ValueType::kDisplayObject:
			case ValueType::kArray:
			case ValueType::kClosure: {
				return GetUserData() <=> a_rhs.GetUserData();
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::nullptr_t Value::GetNull() const noexcept
	{
		REX::Assert(IsNull());
		REX::Assert(_value.null == nullptr);
		return nullptr;
	}

	std::nullptr_t Value::GetUndefined() const noexcept
	{
		REX::Assert(IsUndefined());
		REX::Assert(_value.undefined == nullptr);
		return nullptr;
	}

	bool Value::GetBoolean() const noexcept
	{
		REX::Assert(IsBoolean());
		return _value.boolean;
	}

	std::int32_t Value::GetInt() const noexcept
	{
		REX::Assert(IsInt());
		return _value.int32;
	}

	std::uint32_t Value::GetUInt() const noexcept
	{
		REX::Assert(IsUInt());
		return _value.uint32;
	}

	REX::Float64 Value::GetNumber() const noexcept
	{
		REX::Assert(IsNumber());
		return _value.number;
	}

	const char* Value::GetString() const noexcept
	{
		REX::Assert(IsString());
		return IsManagedValue() ? *_value.mstring : _value.string;
	}

	const wchar_t* Value::GetWString() const noexcept
	{
		REX::Assert(IsStringW());
		return _value.wstring;
	}

	REX::zstring_view Value::GetStringView() const noexcept
	{
		return GetString();
	}

	REX::zwstring_view Value::GetWStringView() const noexcept
	{
		return GetWString();
	}

	void* Value::GetUserData() const noexcept
	{
		REX::Assert(IsAnyObject());
		return _value.data;
	}

	void Value::SetNull() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kNull;
		_value.null = nullptr;
	}

	void Value::SetUndefined() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kUndefined;
		_value.undefined = nullptr;
	}

	void Value::SetBoolean(bool a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kBoolean;
		_value = a_value;
	}

	void Value::SetInt(std::int32_t a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kInt;
		_value = a_value;
	}

	void Value::SetUInt(std::uint32_t a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kUInt;
		_value = a_value;
	}

	void Value::SetNumber(REX::Float64 a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kNumber;
		_value = a_value;
	}

	void Value::SetString(const char* a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kString;
		_value = a_value;
	}

	void Value::SetWString(const wchar_t* a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kStringW;
		_value = a_value;
	}

	void Value::SetStringView(REX::zstring_view a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kString;
		_value = a_value.data();
	}

	void Value::SetWStringView(REX::zwstring_view a_value) noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kStringW;
		_value = a_value.data();
	}

	void Value::SetConvertBoolean() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kConvertBoolean;
	}

	void Value::SetConvertInt() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kConvertInt;
	}

	void Value::SetConvertUInt() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kConvertUInt;
	}

	void Value::SetConvertNumber() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kConvertNumber;
	}

	void Value::SetConvertString() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kConvertString;
	}

	void Value::SetConvertStringW() noexcept
	{
		if (IsManagedValue()) {
			ReleaseManagedValue();
		}

		_type = ValueType::kConvertStringW;
	}

	bool Value::IsInstanceOf(const char* a_className) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->IsInstanceOf(_value.data, a_className);
	}

	bool Value::GetParent(Value* a_value) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->GetParent(_value.data, a_value);
	}

	bool Value::HasMember(const char* a_name) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->HasMember(_value.data, a_name, IsDisplayObject());
	}

	bool Value::GetMember(const char* a_name, Value* a_value) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->GetMember(_value.data, a_name, a_value, IsDisplayObject());
	}

	bool Value::SetMember(const char* a_name, const Value& a_value)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->SetMember(_value.data, a_name, a_value, IsDisplayObject());
	}

	bool Value::DeleteMember(const char* a_name)
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

	void Value::VisitMembers(REX::NotNull<ObjectVisitFunctor> a_visitor) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		class MemberVisitor final
			: public ObjectInterface::ObjVisitor
		{
		public:
			MemberVisitor(REX::NotNull<ObjectVisitFunctor>&& a_func)
				: _func(std::move(a_func))
			{
			}

			~MemberVisitor() override = default;

			MemberVisitor(const MemberVisitor&) = delete;
			MemberVisitor(MemberVisitor&&) = delete;

			MemberVisitor& operator=(const MemberVisitor&) = delete;
			MemberVisitor& operator=(MemberVisitor&&) = delete;

			bool IncludeAS3PublicMembers() const override
			{
				return true;
			}

			void Visit(const char* a_name, const Value& a_value) override
			{
				std::invoke(*_func, a_name, a_value);
			}

		private:
			REX::NotNull<ObjectVisitFunctor> _func;
		};

		auto visitor = MemberVisitor(std::move(a_visitor));
		_objectInterface->VisitMembers(_value.data, std::addressof(visitor), IsDisplayObject());
	}

	std::uint32_t Value::GetArraySize() const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->GetArraySize(_value.data);
	}

	bool Value::SetArraySize(std::uint32_t a_size)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->SetArraySize(_value.data, a_size);
	}

	bool Value::GetElement(std::uint32_t a_index, Value* a_value) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->GetElement(_value.data, a_index, a_value);
	}

	bool Value::SetElement(std::uint32_t a_index, const Value& a_value)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->SetElement(_value.data, a_index, a_value);
	}

	bool Value::PushBack(const Value& a_value)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->PushBack(_value.data, a_value);
	}

	bool Value::PopBack(Value* a_value)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->PopBack(_value.data, a_value);
	}

	bool Value::RemoveElements(std::uint32_t a_startIndex, std::int32_t a_count)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		return _objectInterface->RemoveElements(_value.data, a_startIndex, a_count);
	}

	bool Value::RemoveElement(std::uint32_t a_index)
	{
		return RemoveElements(a_index, 1);
	}

	bool Value::ClearElements()
	{
		return RemoveElements(0);
	}

	void Value::VisitElements(REX::NotNull<ArrayVisitor*> a_visitor, std::uint32_t a_startIndex, std::int32_t a_count) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		_objectInterface->VisitElements(_value.data, a_visitor.get(), a_startIndex, a_count);
	}

	void Value::VisitElements(REX::NotNull<ArrayVisitFunctor> a_visitor, std::uint32_t a_startIndex, std::int32_t a_count) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsArray());

		class ElementVisitor final
			: public ObjectInterface::ArrVisitor
		{
		public:
			ElementVisitor(REX::NotNull<ArrayVisitFunctor>&& a_func)
				: _func(std::move(a_func))
			{
			}

			~ElementVisitor() override = default;

			ElementVisitor(const ElementVisitor&) = delete;
			ElementVisitor(ElementVisitor&&) = delete;

			ElementVisitor& operator=(const ElementVisitor&) = delete;
			ElementVisitor& operator=(ElementVisitor&&) = delete;

			void Visit(std::uint32_t a_index, const Value& a_value) override
			{
				std::invoke(*_func, a_index, a_value);
			}

		private:
			REX::NotNull<ArrayVisitFunctor> _func;
		};

		auto visitor = ElementVisitor(std::move(a_visitor));
		_objectInterface->VisitElements(_value.data, std::addressof(visitor), a_startIndex, a_count);
	}

	Movie* Value::GetMovie() const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return static_cast<Movie*>(_objectInterface->movieRoot);
	}

	MovieImpl* Value::GetMovieImpl() const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->movieRoot;
	}

	bool Value::GetDisplayInfo(DisplayInfo* a_info) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GetDisplayInfo(_value.data, a_info);
	}

	bool Value::SetDisplayInfo(const DisplayInfo& a_info)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->SetDisplayInfo(_value.data, a_info);
	}

	bool Value::GetDisplayMatrix(Render::Matrix2x4<REX::Float32>* a_matrix) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GetDisplayMatrix(_value.data, a_matrix);
	}

	bool Value::SetDisplayMatrix(const Render::Matrix2x4<REX::Float32>* a_matrix)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->SetDisplayMatrix(_value.data, a_matrix);
	}

	bool Value::GetCxform(Render::Cxform* a_cxform) const
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GetCxform(_value.data, a_cxform);
	}

	bool Value::SetCxform(const Render::Cxform* a_cxform)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->SetCxform(_value.data, a_cxform);
	}

	bool Value::AttachMovie(Value* a_movieClip, const char* a_symbolName, const char* a_instanceName, std::int32_t a_depth, const MemberValueSet* a_initList)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->AttachMovie(_value.data, a_movieClip, a_symbolName, a_instanceName, a_depth, a_initList);
	}

	bool Value::CreateEmptyMovieClip(Value* a_movieClip, const char* a_instanceName, std::int32_t a_depth)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->CreateEmptyMovieClip(_value.data, a_movieClip, a_instanceName, a_depth);
	}

	bool Value::GotoAndPlay(std::uint32_t a_frame)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, false);
	}

	bool Value::GotoAndPlay(const char* a_frame)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, false);
	}

	bool Value::GotoAndStop(std::uint32_t a_frame)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, true);
	}

	bool Value::GotoAndStop(const char* a_frame)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsDisplayObject());

		return _objectInterface->GotoAndPlay(_value.data, a_frame, true);
	}

	bool Value::Invoke(const char* a_name, Value* a_result, const Value* a_args, std::uint32_t a_numArgs)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsAnyObject());

		return _objectInterface->Invoke(_value.data, a_result, a_name, a_args, a_numArgs, IsDisplayObject());
	}

	bool Value::Invoke(const char* a_name, std::span<const Value> a_args)
	{
		return Invoke(a_name, nullptr, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	bool Value::Invoke(const char* a_name, Value* a_result, std::span<const Value> a_args)
	{
		return Invoke(a_name, a_result, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	bool Value::InvokeFunction(Value* a_result, const Value* a_args, std::uint32_t a_numArgs)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsFunction());

		auto thisArg = Value(nullptr);

		auto callArgs = std::vector<Value>();
		callArgs.reserve(a_numArgs + 1);

		callArgs.push_back(std::move(thisArg));
		callArgs.insert(callArgs.end(), a_args, a_args + a_numArgs);

		return _objectInterface->Invoke(_value.data, a_result, "call", callArgs.data(), static_cast<std::uint32_t>(callArgs.size()), false);
	}

	bool Value::InvokeFunction(std::span<const Value> a_args)
	{
		return InvokeFunction(nullptr, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	bool Value::InvokeFunction(Value* a_result, std::span<const Value> a_args)
	{
		return InvokeFunction(a_result, a_args.data(), static_cast<std::uint32_t>(a_args.size()));
	}

	bool Value::ApplyFunction(Value* a_result, const Value* a_args)
	{
		REX::Assert(_objectInterface != nullptr);
		REX::Assert(IsFunction());
		REX::Assert(a_args == nullptr || a_args->IsNull() || a_args->IsArray());

		auto thisArg = Value(nullptr);
		auto applyArgs = std::array<Value, 2>();

		applyArgs[0] = std::move(thisArg);
		applyArgs[1] = a_args ? *a_args : Value(nullptr);

		return _objectInterface->Invoke(_value.data, a_result, "apply", applyArgs.data(), static_cast<std::uint32_t>(applyArgs.size()), false);
	}

	bool Value::ApplyFunction(const Value* a_args)
	{
		return ApplyFunction(nullptr, a_args);
	}

	bool Value::IsManagedValue() const noexcept
	{
		const auto managed = _type.all(ValueType::kManagedBit);
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

	void swap(Value& a_lhs, Value& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace std
{
	std::size_t hash<Scaleform::GFx::Value>::operator()(const Scaleform::GFx::Value& a_key) const noexcept
	{
		using ValueType = Scaleform::GFx::Value::ValueType;

		const auto type = a_key.GetType();
		switch (type) {
			case ValueType::kNull: {
				return REX::HashCombine(type, a_key.GetNull());
			}
			case ValueType::kUndefined: {
				return REX::HashCombine(type, a_key.GetUndefined());
			}
			case ValueType::kBoolean: {
				return REX::HashCombine(type, a_key.GetBoolean());
			}
			case ValueType::kInt: {
				return REX::HashCombine(type, a_key.GetInt());
			}
			case ValueType::kUInt: {
				return REX::HashCombine(type, a_key.GetUInt());
			}
			case ValueType::kNumber: {
				return REX::HashCombine(type, a_key.GetNumber());
			}
			case ValueType::kString: {
				return REX::HashCombine(type, a_key.GetStringView());
			}
			case ValueType::kStringW: {
				return REX::HashCombine(type, a_key.GetWStringView());
			}
			case ValueType::kObject:
			case ValueType::kDisplayObject:
			case ValueType::kArray:
			case ValueType::kClosure: {
				return REX::HashCombine(type, a_key.GetUserData());
			}
			default: {
				std::unreachable();
			}
		}
	}
}
