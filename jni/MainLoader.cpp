#include <jni.h>
#include <iostream>

#include "MainLoader.h"

JNIEXPORT void JNICALL Java_MainLoader_get(
  JNIEnv *env,
  jobject thisObj,
  jstring key,
  jstring value) {

   const char* keyStr = env->GetStringUTFChars(env, key);
   std::cout << "Getting key: " << keyStr << std::endl;
}

JNIEXPORT void JNICALL Java_MainLoader_put(
    JNIEnv *env,
    jobject thisObj,
    jstring key,
    jstring value) {

  const char* keyStr = env->GetStringUTFChars(env, key);
  const char* valueStr = env->GetStringUTFChars(env, value);
  std::cout << "Writing key: " << keyStr
            << ", value: " << valueStr << std::endl;
}
