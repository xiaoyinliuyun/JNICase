#include <jni.h>
#include <Windows.h>
#include <iostream>

using namespace std;


typedef jint (__stdcall *JNICreateJavaVM)(JavaVM **vm, void**env, void *args);
typedef jint (__stdcall *JNIGetDefaultJavaVMInitArgs)(void*vm_args);
typedef jint (__stdcall *JNIGetCreateJavaVMs)(JavaVM**, jsize, jsize*);
typedef jint (__stdcall *JNIOnLoad)(JavaVM*, void*reserved);
typedef jint (__stdcall *JNIOnUnload)(JavaVM*, void*reserved);

JNICreateJavaVM jniCreateJavaVM;
JNIGetDefaultJavaVMInitArgs jniGetDefaultJavaVMInitArgs;
JNIGetCreateJavaVMs jniGetCreateJavaVMs;
JNIOnLoad jniOnLoad;
JNIOnUnload jniOnUnload;

/*int WinMain(
            HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR lpCmdLine,
            int nCmdShow
            ){*/
int main(){
	WCHAR* path = L"E:\\meituan\\JNICase\\JNIEXE\\Debug\\jre1.8.0_221\\bin\\client\\jvm.dll";
	HINSTANCE dll = LoadLibraryW(path);
	//free(path);
	//创建JVM
	jniCreateJavaVM = (JNICreateJavaVM)GetProcAddress(dll,"JNI_CreateJavaVM");
	jniGetDefaultJavaVMInitArgs = (JNIGetDefaultJavaVMInitArgs)GetProcAddress(dll,"JNI_GetDefaultJavaVMInitArgs");
	jniGetCreateJavaVMs = (JNIGetCreateJavaVMs)GetProcAddress(dll,"JNI_GetCreateJavaVMs");
	GetProcAddress(dll,"JNI_OnLoad");
	jniOnLoad = (JNIOnLoad)GetProcAddress(dll,"JNI_OnLoad");
	jniOnUnload = (JNIOnUnload)GetProcAddress(dll,"JNI_OnUnload");

	
	JavaVM *jvm;
	JNIEnv *env;
	JavaVMInitArgs vm_args;
	
	JavaVMOption options[4];
	options[0].optionString = "-Djava.compiler=NONE";
	options[1].optionString = "-Djava.class.path=E:\\meituan\\erp-peripheral-hid\\windemo\\build\\libs\\windemo-all.jar";
	options[2].optionString = "-Djava.library.path=E:\\meituan\\JNICase\\JNIEXE\\Debug\\jre1.8.0_221\\bin\\client";
	options[3].optionString = "-verbose:NONE";//用于跟踪运行时的信息
	
	//初始化参数init
	memset(&vm_args,0,sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_8;
	vm_args.options = options;
	vm_args.nOptions = 4;
	vm_args.ignoreUnrecognized = JNI_TRUE;

	jint status = jniCreateJavaVM(&jvm,(void**)&env,&vm_args);
	cout << "status -> " << status << endl;
	
	/*
	JavaVMInitArgs* p_vm_args = new JavaVMInitArgs();
	jint res = jniGetDefaultJavaVMInitArgs(p_vm_args);
	cout << "get args res " << res << endl;
	cout <<"vm version -> " << p_vm_args->version <<endl;
	cout <<"vm nOptions -> " << p_vm_args->nOptions << endl;
	cout <<"vm ignoreUnrecognized -> " << p_vm_args->ignoreUnrecognized <<endl;
	JavaVMOption* op = p_vm_args->options;
	
	cout <<"vm option 0 -> " << op->optionString << endl;
	cout <<"vm option 1 -> " << op->optionString << endl;
	cout <<"vm option 2 -> " << op->optionString << endl;
	cout <<"vm option 3 -> " << op->optionString << endl;
	
	*/

	JavaVM * vm;
	jsize nVMs;
	jint resGet = jniGetCreateJavaVMs(&vm,1,&nVMs);
	cout <<"resGet -> " << resGet << endl;

	jclass mainClazz = env->FindClass("com/sankuan/windemo/MainFileLog");
	jmethodID mainId = env->GetStaticMethodID(mainClazz,"main","([Ljava/lang/String;)V");
	env->CallStaticVoidMethod(mainClazz,mainId,NULL);

	
	
	long time = 1000*60*60*24*365;
	Sleep(time);
	return 0;
}