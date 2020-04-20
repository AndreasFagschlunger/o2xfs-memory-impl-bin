#include <Windows.h>
#include "o2xfs-common.h"
#include "at_o2xfs_memory_impl_win32_Win32MemorySystem.h"

JNIEXPORT jbyteArray JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_allocate0(JNIEnv *env, jobject obj, jbyteArray value) {
	LPVOID p = malloc(env->GetArrayLength(value));
	return o2xfs::ToArray(env, p);
}

JNIEXPORT void JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_free0(JNIEnv *env, jobject obj, jbyteArray address) {
	LPVOID p = o2xfs::ToPointer(env, address);
	free(p);
}

JNIEXPORT jbyteArray JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_read0(JNIEnv *env, jobject obj, jbyteArray address, jint offset, jint len) {
	LPVOID p = o2xfs::ToPointer(env, address);
	jbyteArray result = env->NewByteArray(len);
	env->SetByteArrayRegion(result, 0, len, (jbyte*) p + offset);
	return result;
}

JNIEXPORT jint JNICALL Java_at_o2xfs_memory_impl_win32_Win32MemorySystem_sizeof(JNIEnv* env, jclass cls) {
	return sizeof(LPVOID);
}
