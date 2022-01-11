#include "annoy.h"
#include <limits>
#include <iomanip>

Napi::Object AnnoyIndexWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func =
      DefineClass(env,
                  "AnnoyIndex",
                  {InstanceMethod("addItem", &AnnoyIndexWrapper::addItem),
                   InstanceMethod("build", &AnnoyIndexWrapper::build),
                   InstanceMethod("save", &AnnoyIndexWrapper::save),
                   InstanceMethod("load", &AnnoyIndexWrapper::load),
                   InstanceMethod("unload", &AnnoyIndexWrapper::unload),
                   InstanceMethod("get_nns_by_item", &AnnoyIndexWrapper::get_nns_by_item),
                   InstanceMethod("get_nns_by_vector", &AnnoyIndexWrapper::get_nns_by_vector)});

  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("AnnoyIndex", func);
  return exports;
}

AnnoyIndexWrapper::AnnoyIndexWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<AnnoyIndexWrapper>(info)
{
  Napi::Env env = info.Env();

  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, "Vector size should be number").ThrowAsJavaScriptException();
    return;
  }

  // also check if this number matches supported matrices ENUM
  if (!info[1].IsNumber())
  {
    Napi::TypeError::New(env, "metric should be string").ThrowAsJavaScriptException();
    return;
  }

  int vector_size = info[0].As<Napi::Number>().Int32Value();
  int metric = info[1].As<Napi::Number>().Int32Value();

  // "angular", "euclidean", "manhattan", or "dot"

  enum metrices
  {
    angular = 1,
    euclidean = 2,
    manhattan = 3,
    dot = 4
  };

  if (metric == metrices::angular)
  {
    t = new AnnoyIndex<int, float, Angular, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
  else if (metric == metrices::euclidean)
  {
    t = new AnnoyIndex<int, float, Euclidean, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
  else if (metric == metrices::manhattan)
  {
    t = new AnnoyIndex<int, float, Manhattan, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
  else if (metric == metrices::dot)
  {
    t = new AnnoyIndex<int, float, DotProduct, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
}

Napi::Value AnnoyIndexWrapper::addItem(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, " size should be number").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  if (!info[1].IsTypedArray())
  {
    Napi::TypeError::New(env, "item must be typed array").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  int item = info[0].As<Napi::Number>().Int32Value();
  Napi::Float32Array buf = info[1].As<Napi::Float32Array>();

  float *data = buf.Data();
  const int size = buf.ByteLength() / sizeof(float);

  t->add_item(item, data);

  return Napi::Number::New(info.Env(), 10);
}

Napi::Value AnnoyIndexWrapper::build(const Napi::CallbackInfo &info)
{
  // info[0] -> Number of trees
  // info[1] -> NUmber of threads to be used default -1 i.e. use all threads

  Napi::Env env = info.Env();

  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, " tree size should be valid number").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  if (!info[1].IsUndefined() && !info[1].IsNumber())
  {
    Napi::TypeError::New(env, " number of threads should be valid number").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  int tree_size = info[0].As<Napi::Number>().Int32Value();
  int threads = -1;

  if (!info[1].IsUndefined())
  {
    threads = info[1].As<Napi::Number>().Int32Value();
  }

  t->build(tree_size, threads);
  // check error
  return env.Undefined();
}

Napi::Value AnnoyIndexWrapper::save(const Napi::CallbackInfo &info)
{
  auto env = info.Env();
  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "path must be string").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  auto path = (std::string)info[0].ToString();
  t->save(path.c_str());

  // handle error
  return env.Undefined();
}

Napi::Value AnnoyIndexWrapper::load(const Napi::CallbackInfo &info)
{
  auto env = info.Env();
  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "path must be string").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  auto path = (std::string)info[0].ToString();
  t->load(path.c_str());

  return env.Undefined();
}

Napi::Value AnnoyIndexWrapper::unload(const Napi::CallbackInfo &info)
{
  auto env = info.Env();
  t->unload();

  return env.Undefined();
}

Napi::Value AnnoyIndexWrapper::get_nns_by_item(const Napi::CallbackInfo &info)
{
  auto env = info.Env();

  // info[0] is int item number
  // info[1] Number of results required

  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, "item must be number").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  if (!info[1].IsNumber())
  {
    Napi::TypeError::New(env, "n must be number").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  if (!info[2].IsBoolean())
  {
    Napi::TypeError::New(env, "includeDistance should be boolean").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  int item = info[0].As<Napi::Number>().Int32Value();
  int n = info[1].As<Napi::Number>().Int32Value();
  Napi::Boolean includeDistance = info[2].As<Napi::Boolean>();
  std::vector<int> result;
  std::vector<float> distace;

  t->get_nns_by_item(item, n, -1, &result, &distace);

  Napi::Array jsResult = Napi::Array::New(env, n);
  Napi::Object response = Napi::Object::New(env);

  for (int i = 0; i < result.size(); i++)
  {
    jsResult[i] = result[i];
  }
  response.Set("neighbours", jsResult);

  if (includeDistance)
  {
    Napi::Array distanceArray = Napi::Array::New(env, n);
    for (int i = 0; i < distace.size(); i++)
    {
      distanceArray[i] = distace[i];
    }
    response.Set("distances", distanceArray);
  }

  return response;
}

Napi::Value AnnoyIndexWrapper::get_nns_by_vector(const Napi::CallbackInfo &info)
{
  auto env = info.Env();

  // info[0] is vector
  // info[1] Number of results required

  if (!info[0].IsTypedArray())
  {
    Napi::TypeError::New(env, "item must be typed array").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  if (!info[1].IsNumber())
  {
    Napi::TypeError::New(env, "n must be number").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  if (!info[2].IsBoolean())
  {
    Napi::TypeError::New(env, "includeDistance should be boolean").ThrowAsJavaScriptException();
    return env.Undefined();
  }

  Napi::Float32Array buf = info[0].As<Napi::Float32Array>();
  float *data = buf.Data();
  int n = info[1].As<Napi::Number>().Int32Value();
  Napi::Boolean includeDistance = info[2].As<Napi::Boolean>();

  std::vector<int> result;
  std::vector<float> distace;

  t->get_nns_by_vector(data, n, -1, &result, &distace);

  Napi::Array jsResult = Napi::Array::New(env, n);
  Napi::Object response = Napi::Object::New(env);

  for (int i = 0; i < result.size(); i++)
  {
    jsResult[i] = result[i];
  }
  response.Set("neighbours", jsResult);

  if (includeDistance)
  {
    Napi::Array distanceArray = Napi::Array::New(env, n);
    for (int i = 0; i < distace.size(); i++)
    {
      distanceArray[i] = distace[i];
    }
    response.Set("distances", distanceArray);
  }

  return response;
}
