/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class demo_org_ichanging_jni_JniHello */

#ifndef _Included_demo_org_ichanging_jni_JniHello
#define _Included_demo_org_ichanging_jni_JniHello
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    hello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_demo_org_ichanging_jni_JniHello_hello
  (JNIEnv *, jobject);

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testReturnInt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_demo_org_ichanging_jni_JniHello_testReturnInt
  (JNIEnv *, jobject);

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testReturnBool
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_demo_org_ichanging_jni_JniHello_testReturnBool
  (JNIEnv *, jobject);

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testReturnString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_demo_org_ichanging_jni_JniHello_testReturnString
  (JNIEnv *, jobject);

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testArguments
 * Signature: (Ljava/lang/String;IZ)V
 */
JNIEXPORT void JNICALL Java_demo_org_ichanging_jni_JniHello_testArguments
  (JNIEnv *, jobject, jstring, jint, jboolean);

#ifdef __cplusplus
}
#endif
#endif
