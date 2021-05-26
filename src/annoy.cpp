#include "annoy.h"

Napi::Object AnnoyIndexWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func =
      DefineClass(env,
                  "AnnoyIndexWrapper",
                  {InstanceMethod("addItem", &AnnoyIndexWrapper::addItem)});

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
  std::cout << "Annoy constructor in c++" << std::endl;

  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, "Vector size should be number").ThrowAsJavaScriptException();
    return;
  }

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
    t = new AnnoyIndex<int, double, Angular, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
  else if (metric == metrices::euclidean)
  {
    t = new AnnoyIndex<int, double, Euclidean, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
  else if (metric == metrices::manhattan)
  {
    t = new AnnoyIndex<int, double, Manhattan, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
  else if (metric == metrices::dot)
  {
    t = new AnnoyIndex<int, double, DotProduct, Kiss32Random, AnnoyIndexMultiThreadedBuildPolicy>(vector_size);
  }
}

Napi::Value AnnoyIndexWrapper::addItem(const Napi::CallbackInfo &info)
{
  std::cout << "this is add item in c++" << std::endl;
  return Napi::Number::New(info.Env(), 10);
}