#include "annoy.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return AnnoyIndexWrapper::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)