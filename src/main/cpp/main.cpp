#include <Windows.h>
#include "at_o2xfs_memory_impl_win32_Win32MemorySystem.h"

LPVOID ToPointer(JNIEnv*, jbyteArray);

LPVOID ToPointer(JNIEnv* env, jbyteArray buf) {
	void* result = NULL;
	env->GetByteArrayRegion(buf, 0, env->GetArrayLength(buf), (jbyte*)& result);
	return result;
}

JNIEXPORT jbyteArray JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_allocate0(JNIEnv *env, jobject obj, jbyteArray value) {
	LPVOID p = malloc(env->GetArrayLength(value));
	env->GetByteArrayRegion(value, 0, env->GetArrayLength(value), (jbyte*) p);
	jbyteArray result = env->NewByteArray(sizeof(p));
	if (result != NULL) {
		env->SetByteArrayRegion(result, 0, env->GetArrayLength(result), (jbyte*) &p);
	}
	return result;
}

JNIEXPORT void JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_free0(JNIEnv *env, jobject obj, jbyteArray address) {
	LPVOID p = ToPointer(env, address);
	free(p);
}

JNIEXPORT jbyteArray JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_read0(JNIEnv *env, jobject obj, jbyteArray address, jint offset, jint len) {
	LPVOID p = ToPointer(env, address);
	jbyteArray result = env->NewByteArray(len);
	env->SetByteArrayRegion(result, 0, len, (jbyte*) p + offset);
	return result;
}

JNIEXPORT jint JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_sizeof(JNIEnv* env, jclass cls) {
	return sizeof(LPVOID);
}
