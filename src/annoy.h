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
  Napi::Value build(const Napi::CallbackInfo &info);
  Napi::Value save(const Napi::CallbackInfo &info);
  Napi::Value load(const Napi::CallbackInfo &info);
  Napi::Value unload(const Napi::CallbackInfo &info);
  Napi::Value get_nns_by_item(const Napi::CallbackInfo &info);
  Napi::Value get_nns_by_vector(const Napi::CallbackInfo &info);
  Napi::Value get_item_vector(const Napi::CallbackInfo &info);
  Napi::Value get_distance(const Napi::CallbackInfo &info);
  Napi::Value get_n_items(const Napi::CallbackInfo &info);
  Napi::Value on_disk_build(const Napi::CallbackInfo &info);
};

#endif