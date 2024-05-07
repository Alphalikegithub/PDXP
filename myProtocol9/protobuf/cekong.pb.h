// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cekong.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_cekong_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_cekong_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_cekong_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_cekong_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_cekong_2eproto;
class MyMessageBody;
struct MyMessageBodyDefaultTypeInternal;
extern MyMessageBodyDefaultTypeInternal _MyMessageBody_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::MyMessageBody* Arena::CreateMaybeMessage<::MyMessageBody>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class MyMessageBody final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MyMessageBody) */ {
 public:
  inline MyMessageBody() : MyMessageBody(nullptr) {}
  ~MyMessageBody() override;
  explicit PROTOBUF_CONSTEXPR MyMessageBody(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MyMessageBody(const MyMessageBody& from);
  MyMessageBody(MyMessageBody&& from) noexcept
    : MyMessageBody() {
    *this = ::std::move(from);
  }

  inline MyMessageBody& operator=(const MyMessageBody& from) {
    CopyFrom(from);
    return *this;
  }
  inline MyMessageBody& operator=(MyMessageBody&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MyMessageBody& default_instance() {
    return *internal_default_instance();
  }
  static inline const MyMessageBody* internal_default_instance() {
    return reinterpret_cast<const MyMessageBody*>(
               &_MyMessageBody_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MyMessageBody& a, MyMessageBody& b) {
    a.Swap(&b);
  }
  inline void Swap(MyMessageBody* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MyMessageBody* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MyMessageBody* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MyMessageBody>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MyMessageBody& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MyMessageBody& from) {
    MyMessageBody::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MyMessageBody* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MyMessageBody";
  }
  protected:
  explicit MyMessageBody(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDeviceStatusFieldNumber = 2,
    kCurrentTimeFieldNumber = 1,
    kAzimuthFieldNumber = 3,
    kElevationFieldNumber = 4,
    kAzimuthOffsetFieldNumber = 5,
    kElevationOffsetFieldNumber = 6,
    kVelocityFieldNumber = 7,
    kDistanceFieldNumber = 8,
    kBrightnessFieldNumber = 9,
  };
  // string device_status = 2;
  void clear_device_status();
  const std::string& device_status() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_device_status(ArgT0&& arg0, ArgT... args);
  std::string* mutable_device_status();
  PROTOBUF_NODISCARD std::string* release_device_status();
  void set_allocated_device_status(std::string* device_status);
  private:
  const std::string& _internal_device_status() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_device_status(const std::string& value);
  std::string* _internal_mutable_device_status();
  public:

  // uint64 current_time = 1;
  void clear_current_time();
  uint64_t current_time() const;
  void set_current_time(uint64_t value);
  private:
  uint64_t _internal_current_time() const;
  void _internal_set_current_time(uint64_t value);
  public:

  // float azimuth = 3;
  void clear_azimuth();
  float azimuth() const;
  void set_azimuth(float value);
  private:
  float _internal_azimuth() const;
  void _internal_set_azimuth(float value);
  public:

  // float elevation = 4;
  void clear_elevation();
  float elevation() const;
  void set_elevation(float value);
  private:
  float _internal_elevation() const;
  void _internal_set_elevation(float value);
  public:

  // int32 azimuth_offset = 5;
  void clear_azimuth_offset();
  int32_t azimuth_offset() const;
  void set_azimuth_offset(int32_t value);
  private:
  int32_t _internal_azimuth_offset() const;
  void _internal_set_azimuth_offset(int32_t value);
  public:

  // int32 elevation_offset = 6;
  void clear_elevation_offset();
  int32_t elevation_offset() const;
  void set_elevation_offset(int32_t value);
  private:
  int32_t _internal_elevation_offset() const;
  void _internal_set_elevation_offset(int32_t value);
  public:

  // float velocity = 7;
  void clear_velocity();
  float velocity() const;
  void set_velocity(float value);
  private:
  float _internal_velocity() const;
  void _internal_set_velocity(float value);
  public:

  // uint32 distance = 8;
  void clear_distance();
  uint32_t distance() const;
  void set_distance(uint32_t value);
  private:
  uint32_t _internal_distance() const;
  void _internal_set_distance(uint32_t value);
  public:

  // int32 brightness = 9;
  void clear_brightness();
  int32_t brightness() const;
  void set_brightness(int32_t value);
  private:
  int32_t _internal_brightness() const;
  void _internal_set_brightness(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:MyMessageBody)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr device_status_;
    uint64_t current_time_;
    float azimuth_;
    float elevation_;
    int32_t azimuth_offset_;
    int32_t elevation_offset_;
    float velocity_;
    uint32_t distance_;
    int32_t brightness_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_cekong_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MyMessageBody

// uint64 current_time = 1;
inline void MyMessageBody::clear_current_time() {
  _impl_.current_time_ = uint64_t{0u};
}
inline uint64_t MyMessageBody::_internal_current_time() const {
  return _impl_.current_time_;
}
inline uint64_t MyMessageBody::current_time() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.current_time)
  return _internal_current_time();
}
inline void MyMessageBody::_internal_set_current_time(uint64_t value) {
  
  _impl_.current_time_ = value;
}
inline void MyMessageBody::set_current_time(uint64_t value) {
  _internal_set_current_time(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.current_time)
}

// string device_status = 2;
inline void MyMessageBody::clear_device_status() {
  _impl_.device_status_.ClearToEmpty();
}
inline const std::string& MyMessageBody::device_status() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.device_status)
  return _internal_device_status();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MyMessageBody::set_device_status(ArgT0&& arg0, ArgT... args) {
 
 _impl_.device_status_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:MyMessageBody.device_status)
}
inline std::string* MyMessageBody::mutable_device_status() {
  std::string* _s = _internal_mutable_device_status();
  // @@protoc_insertion_point(field_mutable:MyMessageBody.device_status)
  return _s;
}
inline const std::string& MyMessageBody::_internal_device_status() const {
  return _impl_.device_status_.Get();
}
inline void MyMessageBody::_internal_set_device_status(const std::string& value) {
  
  _impl_.device_status_.Set(value, GetArenaForAllocation());
}
inline std::string* MyMessageBody::_internal_mutable_device_status() {
  
  return _impl_.device_status_.Mutable(GetArenaForAllocation());
}
inline std::string* MyMessageBody::release_device_status() {
  // @@protoc_insertion_point(field_release:MyMessageBody.device_status)
  return _impl_.device_status_.Release();
}
inline void MyMessageBody::set_allocated_device_status(std::string* device_status) {
  if (device_status != nullptr) {
    
  } else {
    
  }
  _impl_.device_status_.SetAllocated(device_status, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.device_status_.IsDefault()) {
    _impl_.device_status_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:MyMessageBody.device_status)
}

// float azimuth = 3;
inline void MyMessageBody::clear_azimuth() {
  _impl_.azimuth_ = 0;
}
inline float MyMessageBody::_internal_azimuth() const {
  return _impl_.azimuth_;
}
inline float MyMessageBody::azimuth() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.azimuth)
  return _internal_azimuth();
}
inline void MyMessageBody::_internal_set_azimuth(float value) {
  
  _impl_.azimuth_ = value;
}
inline void MyMessageBody::set_azimuth(float value) {
  _internal_set_azimuth(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.azimuth)
}

// float elevation = 4;
inline void MyMessageBody::clear_elevation() {
  _impl_.elevation_ = 0;
}
inline float MyMessageBody::_internal_elevation() const {
  return _impl_.elevation_;
}
inline float MyMessageBody::elevation() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.elevation)
  return _internal_elevation();
}
inline void MyMessageBody::_internal_set_elevation(float value) {
  
  _impl_.elevation_ = value;
}
inline void MyMessageBody::set_elevation(float value) {
  _internal_set_elevation(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.elevation)
}

// int32 azimuth_offset = 5;
inline void MyMessageBody::clear_azimuth_offset() {
  _impl_.azimuth_offset_ = 0;
}
inline int32_t MyMessageBody::_internal_azimuth_offset() const {
  return _impl_.azimuth_offset_;
}
inline int32_t MyMessageBody::azimuth_offset() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.azimuth_offset)
  return _internal_azimuth_offset();
}
inline void MyMessageBody::_internal_set_azimuth_offset(int32_t value) {
  
  _impl_.azimuth_offset_ = value;
}
inline void MyMessageBody::set_azimuth_offset(int32_t value) {
  _internal_set_azimuth_offset(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.azimuth_offset)
}

// int32 elevation_offset = 6;
inline void MyMessageBody::clear_elevation_offset() {
  _impl_.elevation_offset_ = 0;
}
inline int32_t MyMessageBody::_internal_elevation_offset() const {
  return _impl_.elevation_offset_;
}
inline int32_t MyMessageBody::elevation_offset() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.elevation_offset)
  return _internal_elevation_offset();
}
inline void MyMessageBody::_internal_set_elevation_offset(int32_t value) {
  
  _impl_.elevation_offset_ = value;
}
inline void MyMessageBody::set_elevation_offset(int32_t value) {
  _internal_set_elevation_offset(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.elevation_offset)
}

// float velocity = 7;
inline void MyMessageBody::clear_velocity() {
  _impl_.velocity_ = 0;
}
inline float MyMessageBody::_internal_velocity() const {
  return _impl_.velocity_;
}
inline float MyMessageBody::velocity() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.velocity)
  return _internal_velocity();
}
inline void MyMessageBody::_internal_set_velocity(float value) {
  
  _impl_.velocity_ = value;
}
inline void MyMessageBody::set_velocity(float value) {
  _internal_set_velocity(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.velocity)
}

// uint32 distance = 8;
inline void MyMessageBody::clear_distance() {
  _impl_.distance_ = 0u;
}
inline uint32_t MyMessageBody::_internal_distance() const {
  return _impl_.distance_;
}
inline uint32_t MyMessageBody::distance() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.distance)
  return _internal_distance();
}
inline void MyMessageBody::_internal_set_distance(uint32_t value) {
  
  _impl_.distance_ = value;
}
inline void MyMessageBody::set_distance(uint32_t value) {
  _internal_set_distance(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.distance)
}

// int32 brightness = 9;
inline void MyMessageBody::clear_brightness() {
  _impl_.brightness_ = 0;
}
inline int32_t MyMessageBody::_internal_brightness() const {
  return _impl_.brightness_;
}
inline int32_t MyMessageBody::brightness() const {
  // @@protoc_insertion_point(field_get:MyMessageBody.brightness)
  return _internal_brightness();
}
inline void MyMessageBody::_internal_set_brightness(int32_t value) {
  
  _impl_.brightness_ = value;
}
inline void MyMessageBody::set_brightness(int32_t value) {
  _internal_set_brightness(value);
  // @@protoc_insertion_point(field_set:MyMessageBody.brightness)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_cekong_2eproto
