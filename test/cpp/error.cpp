/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/iojs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

#define V1(NAME)                                                               \
NAN_METHOD(Throw ## NAME ## 1) {                                               \
  return NanThrow ## NAME("errmsg");                                           \
}

#define V2(NAME)                                                               \
NAN_METHOD(Throw ## NAME ## 2) {                                               \
  return NanThrow ## NAME(NanNew("errmsg"));                                   \
}

#define V3(NAME)                                                               \
NAN_METHOD(Throw ## NAME ## 3) {                                               \
  return NanThrowError(Nan ## NAME("errmsg"));                                 \
}

#define V4(NAME)                                                               \
NAN_METHOD(Throw ## NAME ## 4) {                                               \
  return NanThrowError(Nan ## NAME(NanNew("errmsg")));                         \
}

#define V(NAME)                                                                \
V1(NAME)                                                                       \
V2(NAME)                                                                       \
V3(NAME)                                                                       \
V4(NAME)

V(Error)
V(RangeError)
V(ReferenceError)
V(SyntaxError)
V(TypeError)

#undef V
#undef V4
#undef V3
#undef V2
#undef V1

#define V(NAME)                                                                \
target->Set(NanNew(#NAME), NanNew<v8::FunctionTemplate>(NAME)->GetFunction());

#define EXPORT(NAME)                                                           \
V(Throw ## NAME ## 1)                                                          \
V(Throw ## NAME ## 2)                                                          \
V(Throw ## NAME ## 3)                                                          \
V(Throw ## NAME ## 4)

void Init (v8::Handle<v8::Object> target) {
  EXPORT(Error)
  EXPORT(RangeError)
  EXPORT(ReferenceError)
  EXPORT(SyntaxError)
  EXPORT(TypeError)
}

#undef EXPORT
#undef V

NODE_MODULE(error, Init)
