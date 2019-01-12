#include "JniHello.h"
#include <stdio.h>
#include <stdbool.h>
#include <android/log.h>

//android studio 无法直接查看到printf数据
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    hello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_demo_org_ichanging_jni_JniHello_hello(JNIEnv * env, jobject obj)
{
	printf("========= Hello Jni =========\n");
}

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    getInt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_demo_org_ichanging_jni_JniHello_testReturnInt
  (JNIEnv *env , jobject obj)
{
	//-_-!!!
	int ret = 1024;
	
	return (jint)ret;
}

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testReturnBool
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_demo_org_ichanging_jni_JniHello_testReturnBool
 (JNIEnv * env, jobject obj)
{
	return (jboolean)true;
}

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testReturnString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_demo_org_ichanging_jni_JniHello_testReturnString
 (JNIEnv * env, jobject obj)
{
	char *  p = "hello world";
	
	jstring s = (*env)->NewStringUTF(env,p);
	
	return s;
}

/*
 * Class:     demo_org_ichanging_jni_JniHello
 * Method:    testArguments
 * Signature: (Ljava/lang/String;IZ)V
 */
JNIEXPORT void JNICALL Java_demo_org_ichanging_jni_JniHello_testArguments
  (JNIEnv *env, jobject obj, jstring s, jint i, jboolean b)
{
	const char * p = (*env)->GetStringUTFChars(env,s,0);
	
	printf("=========== testArguments [%s,%d,%s] ===========\n",p,i,(b == JNI_TRUE ? "true" : "false"));
	
	//通知虚拟机 释放String资源
	(*env)->ReleaseStringUTFChars(env,s,p);
}