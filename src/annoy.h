#ifndef ANNOYINDEXWRAPPEAR_H
#define ANNOYINDEXWRAPPEAR_H

#include <napi.h>
#include "iostream";
#include "annoylib.h"
#include "kissrandom.h"
#include "map"

class AnnoyIndexWrapper : public Napi::ObjectWrap<AnnoyIndexWrapper>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  AnnoyIndexWrapper(const Napi::CallbackInfo &info);
  AnnoyIndexInterface<int, double, Kiss32Random::seed_type> *t;

private:
  Napi::Value addItem(const Napi::CallbackInfo &info);
};

#endif