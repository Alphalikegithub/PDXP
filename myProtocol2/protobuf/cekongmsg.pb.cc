// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cekongmsg.proto

#include "cekongmsg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR MyMessageBody::MyMessageBody(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.op_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.key_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.value_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct MyMessageBodyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MyMessageBodyDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MyMessageBodyDefaultTypeInternal() {}
  union {
    MyMessageBody _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MyMessageBodyDefaultTypeInternal _MyMessageBody_default_instance_;
static ::_pb::Metadata file_level_metadata_cekongmsg_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_cekongmsg_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_cekongmsg_2eproto = nullptr;

const uint32_t TableStruct_cekongmsg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::MyMessageBody, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::MyMessageBody, _impl_.op_),
  PROTOBUF_FIELD_OFFSET(::MyMessageBody, _impl_.key_),
  PROTOBUF_FIELD_OFFSET(::MyMessageBody, _impl_.value_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::MyMessageBody)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_MyMessageBody_default_instance_._instance,
};

const char descriptor_table_protodef_cekongmsg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017cekongmsg.proto\"7\n\rMyMessageBody\022\n\n\002op"
  "\030\001 \001(\t\022\013\n\003key\030\002 \001(\t\022\r\n\005value\030\003 \001(\tb\006prot"
  "o3"
  ;
static ::_pbi::once_flag descriptor_table_cekongmsg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_cekongmsg_2eproto = {
    false, false, 82, descriptor_table_protodef_cekongmsg_2eproto,
    "cekongmsg.proto",
    &descriptor_table_cekongmsg_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_cekongmsg_2eproto::offsets,
    file_level_metadata_cekongmsg_2eproto, file_level_enum_descriptors_cekongmsg_2eproto,
    file_level_service_descriptors_cekongmsg_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_cekongmsg_2eproto_getter() {
  return &descriptor_table_cekongmsg_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_cekongmsg_2eproto(&descriptor_table_cekongmsg_2eproto);

// ===================================================================

class MyMessageBody::_Internal {
 public:
};

MyMessageBody::MyMessageBody(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:MyMessageBody)
}
MyMessageBody::MyMessageBody(const MyMessageBody& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  MyMessageBody* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.op_){}
    , decltype(_impl_.key_){}
    , decltype(_impl_.value_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.op_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.op_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_op().empty()) {
    _this->_impl_.op_.Set(from._internal_op(), 
      _this->GetArenaForAllocation());
  }
  _impl_.key_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.key_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_key().empty()) {
    _this->_impl_.key_.Set(from._internal_key(), 
      _this->GetArenaForAllocation());
  }
  _impl_.value_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.value_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_value().empty()) {
    _this->_impl_.value_.Set(from._internal_value(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:MyMessageBody)
}

inline void MyMessageBody::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.op_){}
    , decltype(_impl_.key_){}
    , decltype(_impl_.value_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.op_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.op_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.key_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.key_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.value_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.value_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

MyMessageBody::~MyMessageBody() {
  // @@protoc_insertion_point(destructor:MyMessageBody)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void MyMessageBody::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.op_.Destroy();
  _impl_.key_.Destroy();
  _impl_.value_.Destroy();
}

void MyMessageBody::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void MyMessageBody::Clear() {
// @@protoc_insertion_point(message_clear_start:MyMessageBody)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.op_.ClearToEmpty();
  _impl_.key_.ClearToEmpty();
  _impl_.value_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MyMessageBody::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string op = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_op();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "MyMessageBody.op"));
        } else
          goto handle_unusual;
        continue;
      // string key = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_key();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "MyMessageBody.key"));
        } else
          goto handle_unusual;
        continue;
      // string value = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_value();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "MyMessageBody.value"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* MyMessageBody::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:MyMessageBody)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string op = 1;
  if (!this->_internal_op().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_op().data(), static_cast<int>(this->_internal_op().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MyMessageBody.op");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_op(), target);
  }

  // string key = 2;
  if (!this->_internal_key().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_key().data(), static_cast<int>(this->_internal_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MyMessageBody.key");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_key(), target);
  }

  // string value = 3;
  if (!this->_internal_value().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_value().data(), static_cast<int>(this->_internal_value().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MyMessageBody.value");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_value(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MyMessageBody)
  return target;
}

size_t MyMessageBody::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MyMessageBody)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string op = 1;
  if (!this->_internal_op().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_op());
  }

  // string key = 2;
  if (!this->_internal_key().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_key());
  }

  // string value = 3;
  if (!this->_internal_value().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_value());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MyMessageBody::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    MyMessageBody::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MyMessageBody::GetClassData() const { return &_class_data_; }


void MyMessageBody::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<MyMessageBody*>(&to_msg);
  auto& from = static_cast<const MyMessageBody&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:MyMessageBody)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_op().empty()) {
    _this->_internal_set_op(from._internal_op());
  }
  if (!from._internal_key().empty()) {
    _this->_internal_set_key(from._internal_key());
  }
  if (!from._internal_value().empty()) {
    _this->_internal_set_value(from._internal_value());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MyMessageBody::CopyFrom(const MyMessageBody& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MyMessageBody)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MyMessageBody::IsInitialized() const {
  return true;
}

void MyMessageBody::InternalSwap(MyMessageBody* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.op_, lhs_arena,
      &other->_impl_.op_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.key_, lhs_arena,
      &other->_impl_.key_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.value_, lhs_arena,
      &other->_impl_.value_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata MyMessageBody::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_cekongmsg_2eproto_getter, &descriptor_table_cekongmsg_2eproto_once,
      file_level_metadata_cekongmsg_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::MyMessageBody*
Arena::CreateMaybeMessage< ::MyMessageBody >(Arena* arena) {
  return Arena::CreateMessageInternal< ::MyMessageBody >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
