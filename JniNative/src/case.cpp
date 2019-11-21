#include "com_sankuai_jnicase_JniNativeClassCase.h"
#include <iostream>
#include <Windows.h>
#include <case.h>
using namespace std;

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseDefineClass
 * Signature: (Lcom/sankuai/jnicase/CustomClassLoader;[BILjava/lang/Class;)Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseDefineClass
  (JNIEnv *env, jclass, jobject loader, jbyteArray data, jint len, jclass personClazzSource){
	  jbyte *p_data = env->GetByteArrayElements(data,false);
	  // 01.�������������class�ļ����ֽ����飬��ȡ���������
	  jclass personClazz = env->DefineClass("com/sankuai/jnicase/Person",loader,p_data,len);
	  jclass personClazzByFind = env->FindClass("com/sankuai/jnicase/Person");
	  jobject person = env->AllocObject(personClazz);
	  env->ReleaseByteArrayElements(data,p_data,0);
	  //02.���personClass ����Object������ӿ�����󣬷��ظ��������
	  jclass superClazz = env->GetSuperclass(personClazz);
	  if(superClazz == NULL){
		cout << "super clazz is null -> "<< superClazz << endl;
	  }else{
		cout << "super clazz is valid -> "<< superClazz << endl;
	  }
	  //03.�����Object����󣬷���NULL
	  jclass ssClazz = env->GetSuperclass(superClazz);
	  if(ssClazz == NULL){
		cout << "super super clazz is null -> "<< ssClazz << endl;
	  }else{
		cout << "super super clazz is valid -> "<< ssClazz << endl;
	  }
	  //04.�ж����������ת���Ƿ�ȫ��Ϊʲôͨ�����������ȡ��������������.class��ȡ�������ת���ǲ���ȫ�ģ�����
	  jboolean isSafe = env->IsAssignableFrom(personClazz,personClazzSource);
	  if(isSafe){
		  cout << "convert is safe" << endl;
	  }else{
		  cout << "convert is unsafe" << endl;
	  }
	  //05.�ж����������ת���Ƿ�ȫ��ͨ��FindClass��ȡ��������������.class��ȡ�������ת���ǰ�ȫ��
	  jboolean isSafe2 = env->IsAssignableFrom(personClazzByFind,personClazzSource);
	  if(isSafe2){
		  cout << "convert is safe" << endl;
	  }else{
		  cout << "convert is unsafe" << endl;
	  }
	  return person;
}


/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseFindClass
 * Signature: ()Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseFindClass
  (JNIEnv * env, jclass clazz){
	  //1.�ҵ��࣬ȫ·����������"/"�ָ���
	  jclass c = env->FindClass("com/sankuai/jnicase/Person");
	  //2.Ĭ�Ϲ�����
	  jobject person = env->AllocObject(c);
	  //3.��ȡ����ID, Stringǩ�������˷ֺ�;
	  jfieldID nameId = env->GetFieldID(c,"name","Ljava/lang/String;");
	  //4.�����ַ�����utf
	  jstring value = env->NewStringUTF("yangkj");
	  //5.����string���͵�����ֵ
	  env->SetObjectField(person,nameId, value);
	  //6.��ȡ����id  int���͵�����ǩ��
	  jfieldID ageId = env->GetFieldID(c,"age","I");
	  jint age = 31;
	  //7.����int���͵�����ֵ
	  env->SetIntField(person,ageId,age);
	  //8.ͷ�ļ����ɵĶ���ͳһ��jobject��
	  return person;
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseNewArray
 * Signature: ()[Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobjectArray JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseNewArray
  (JNIEnv * env, jclass){
	  jclass clazz = env->FindClass("com/sankuai/jnicase/Person");
	  //9.��ȡ����������ID:������<init> ����ǩ�� ����ֵ V
	  jmethodID con = env->GetMethodID(clazz,"<init>","(Ljava/lang/String;I)V");

	  jstring name = env->NewStringUTF("yangfan");
	  jint age = 30;
	  jobject person = env->NewObject(clazz,con,name,age);

	  //10.������ָ��jvalue�����ָ��
	  jvalue* p_v = new jvalue[10];
	  p_v[0].l = env->NewStringUTF("yangkunjian");
	  p_v[1].i = 31;
	  jobject person1 = env->NewObjectA(clazz,con,p_v);
	  /*
	  int v = 10;
	  va_list list;//��γ�ʼ��
	  va_start(list,v);
	  va_arg(list,int);
	  jobject person2 = env->NewObjectV(clazz,con,list);
	  va_end(list);
	  */
	  //11.������������
	  jobjectArray result = env->NewObjectArray(2,clazz,NULL);
	  //12.���������鸳ֵ
	  env->SetObjectArrayElement(result,0,person);
	  env->SetObjectArrayElement(result,1,person1);
	  //env->SetObjectArrayElement(result,2,person2);
	  return result;
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseConvertPersonToAnother
 * Signature: (Lcom/sankuai/jnicase/Person;)Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseConvertPersonToAnother
  (JNIEnv * env, jclass, jobject person){
	  //13.��ȡ��������
	  jobjectRefType type = env->GetObjectRefType(person);
	  cout << "type -> person : " << type << endl;
	  //14.�Ӷ����ȡ����Ϣ
	  jclass clazz = env->GetObjectClass(person);
	  jfieldID nameId = env->GetFieldID(clazz,"name","Ljava/lang/String;");
	  jobject name = env->GetObjectField(person,nameId);
	  cout << "person name -> " << name << endl;

	  jobject newPerson = env->AllocObject(clazz);
	  type = env->GetObjectRefType(newPerson);
	  cout << "type -> newPerson : " << type << endl;
	  //15.�ж��Ƿ���ָ������ʵ��
	  jboolean isSameType = env->IsInstanceOf(newPerson,clazz);
	  cout << "type is same -> " << isSameType + '0' << endl;// 49 -> 1		true
	  //16.�ж��ͷ���ͬһ������
	  jboolean isSameObject = env->IsSameObject(newPerson,person);
	  cout << "object is same -> " << isSameObject + '0'  << endl; // 48 -> 0  false
	  return newPerson;
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseInvokeInName
 * Signature: (Lcom/sankuai/jnicase/Person;)V
 */
JNIEXPORT void JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseInvokeInName
  (JNIEnv *env, jclass, jobject person){
	  jclass clazz = env->GetObjectClass(person);
	  jmethodID translateId = env->GetMethodID(clazz,"translate","(B)C");
	  jchar c = env->CallCharMethod(person,translateId,0x00);
	  cout << "translate 0x00 result -> " << c << endl;
	  c = env->CallCharMethod(person,translateId,0x01);
	  cout << "translate 0x01 result -> " << c << endl;

	  jmethodID translateId2 = env->GetMethodID(clazz,"translate","(Ljava/lang/String;)[B");
	  jstring name = env->NewStringUTF("helloworld!!!");
	  //17.���õķ�������ֵ���������ͣ���Ҫ��ǿת
	  jbyteArray result = (jbyteArray)env->CallObjectMethod(person,translateId2,name);
	  
	  //18.��ȡ���鳤��
	  jsize len = env->GetArrayLength(result);
      cout << "len -> " << len << endl;

	  //19.��ȡ����Ԫ�أ�����ָ������ͷ����ָ��
	  jbyte* p_byte = env->GetByteArrayElements(result,false);
	  //20.ͨ��ָ���������
	  for(jsize i = 0; i<len;i++){
		  cout << i << " -> " << *p_byte << endl;
		  p_byte +=1;
	  }
	  
	  jmethodID programId = env->GetMethodID(clazz,"program","(Lcom/sankuai/jnicase/Computer;J)V");

	  jclass computerClazz = env->FindClass("com/sankuai/jnicase/Computer");
	  jobject computer = env->AllocObject(computerClazz);

	  
	  jclass systemClazz = env->FindClass("java/lang/System");
	  //23.��ȡ��̬����ID
	  jfieldID outId = env->GetStaticFieldID(systemClazz,"out","Ljava/io/PrintStream;");
	  jobject out = env->GetStaticObjectField(systemClazz,outId);
	  jclass outClazz = env->GetObjectClass(out);
	  jmethodID printlnId = env->GetMethodID(outClazz,"println","(Ljava/lang/String;)V");
	  jstring text = env->NewStringUTF("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ");
	  env->CallVoidMethod(out,printlnId,text);
	  
	  //24.��ȡ��̬����ID,ע��û�в����ķ���()��û��V
	  jmethodID currentId1 = env->GetStaticMethodID(systemClazz,"getSecurityManager","()Ljava/lang/SecurityManager;");
	  
	  jmethodID currentId = env->GetStaticMethodID(systemClazz,"currentTimeMillis","()J");
	  jlong time = env->CallStaticLongMethod(systemClazz,currentId);
	  
	  jvalue* params = new jvalue[2];
	  params[0].l = computer;
	  params[1].j = time;
	  //21.����A
	  env->CallVoidMethodA(person,programId,params);
	  //22.����Ĭ�Ϸ���  timeֱ�Ӵ���ֵ �൱��ֱ��ȡ��ַ
	  env->CallVoidMethod(person,programId,computer,&time);
	  env->CallVoidMethod(person,programId,computer,time);
}


/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseCreateGlobalRef
 * Signature: (Lcom/sankuai/jnicase/Person;)Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseCreateGlobalRef
  (JNIEnv * env, jclass, jobject person){
	  return env->NewGlobalRef(person);
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseCreateLocalRef
 * Signature: (Lcom/sankuai/jnicase/Person;)Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseCreateLocalRef
  (JNIEnv *env, jclass, jobject person){
	  jint pushRes = env->PushLocalFrame(100);

	  jobject ref = env->NewLocalRef(person);
	  jint result = env->EnsureLocalCapacity(50000);
	  if(result == JNI_OK){
		  cout << "ok" << endl;
	  }else{
		  cout << "failure" << endl;
	  }
	  env->DeleteLocalRef(ref);
	  jobject ss = env->PopLocalFrame(ref);
	  return ss;
}


/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseCreateWeakGlobalRef
 * Signature: (Lcom/sankuai/jnicase/Person;)Lcom/sankuai/jnicase/Person;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseCreateWeakGlobalRef
  (JNIEnv *env, jclass, jobject person){
	  jweak ref = env->NewWeakGlobalRef(person);
	  env->DeleteWeakGlobalRef(ref);
	  return ref;
}


/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseException
 * Signature: (Lcom/sankuai/jnicase/CustomException;)V
 */
JNIEXPORT void JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseException
  (JNIEnv *env, jclass, jthrowable exception){
	  jboolean checkResult0 = env->ExceptionCheck();
	  if(checkResult0){
		  cout << "ExceptionCheck0: has exception "<< endl;
	  }else{
		  cout << "ExceptionCheck0: no exception " << endl;
	  }
	  // ��ǰû���쳣�׳�
	  jthrowable exce = env->ExceptionOccurred();
	  if(exce == NULL){
		  cout << "ExceptionOccurred: no exception "<< exce << endl;
	  }else{
		  cout << "ExceptionOccurred: exception "<< exce << endl;
	  }
	  //jint result = env->Throw(exception);
	  jclass clazz = env->FindClass("com/sankuai/jnicase/CustomException");
	  
	  // const char* message ֱ�Ӹ�ֵ
	  const char* info = "new exception ...";
	  jint result = env->ThrowNew(clazz,info);
	  if(result == 0){
		  cout << "exception throw ok " << endl;
	  }else{
		  cout << "exception throw error" << endl;
	  }
	  //��ǰ�ܼ�⵽�쳣�׳�
	  jthrowable exce1 = env->ExceptionOccurred();
	  if(exce1 == NULL){
		  cout << "ExceptionOccurred: no exception "<< exce1 << endl;
	  }else{
		  cout << "ExceptionOccurred: exception "<< exce1 << endl;
	  }
	  //�൱�ڵ���printStackTrace(); ���غ󲻻�ص���java��
	  //env->ExceptionDescribe();

	  /**
	  *if ((*env)->ExceptionCheck(env)) {  // ���JNI�����Ƿ��������쳣
       (*env)->ExceptionDescribe(env);
       (*env)->ExceptionClear(env);        // ����������쳣����Java�㲻���ӡ�쳣�Ķ�ջ��Ϣ
       (*env)->ThrowNew(env,(*env)->FindClass(env,"java/lang/Exception"),"JNI�׳����쳣��");
       //return;
   }
	  */

	  jboolean checkResult1 = env->ExceptionCheck();//�û������쳣 
	  if(checkResult1){
		  cout << "ExceptionCheck1: has exception "<< endl;
	  }else{
		  cout << "ExceptionCheck1: no exception " << endl;
	  }

	  //����쳣��Ϣ
	  env->ExceptionClear();
	  //������ֹ
	  /*
	  const char* msg = "programs end";
	  env->FatalError(msg);
	  */
	  //��ʱ������쳣�����ز����� �����⵽�쳣����
	  jboolean checkResult2 = env->ExceptionCheck();
	  if(checkResult2){
		  cout << "ExceptionCheck2: has exception "<< endl;
	  }else{
		  cout << "ExceptionCheck2: no exception " << endl;
	  }
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseJniString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseJniString
  (JNIEnv * env, jclass){
	  // Unicode �ַ��� ��4���ֽڱ�ʾ1���ַ� ���㡯 00004f60   ���á� 0000597d
	  // UTF-8 ������� 1+11(����1��ʾ�����м����ֽ�)+0+xxxx + 10+xxxxxx��xxxUCS���룩 + 10+xxxxxx��xxxUCS���룩
	  // GBK ������� ��2���ֽڱ�ʾ1���ַ� �������λ��1   GBK��UTF8����ͨ��Unicode����ת��
	  // ���ַ� == Unicode������ַ���
	  WCHAR s[] = L"���";
	  WCHAR* p_s = s;
	  int wlen = wcslen(s);
	  cout << "wchar wlen -> " << wlen << endl;
	  // unicode ת utf-8����
	  const char* utfChar = u2utf(s);
	  jstring result = env->NewString((const jchar*)p_s,wlen);
	  jstring utfRes = env->NewStringUTF(utfChar);
	  cout << "unicode Result len -> " << env->GetStringLength(result) << endl;
	  
	  // ָ���ʼ��
	  jboolean* p_is_copy = new jboolean();
	  const jchar* text = env->GetStringChars(result,p_is_copy);
	  for(int i = 0; i<wlen ; i++){
		  cout << " ----- > " << *text << endl; //unicode��ֵ
		  text+=1;
	  }
	  if(*p_is_copy){ 
		  //���ص��ַ���java�ַ����Ŀ���
		  cout << "copy -> new char" << endl; //ʵ��ִ�н��
	  }else{
		  //ָ��ָ��ԭʼjava�ַ������ڴ�
		  cout << "source -> old char" << endl;
	  }
	  int utfLen = env->GetStringUTFLength(utfRes);
	  const char* utfText = env->GetStringUTFChars(utfRes,p_is_copy);
	  cout << "utf8 Result len -> " <<utfLen << endl;
	  for(int i = 0; i< utfLen ; i++){
		  cout << " ----- > " << *utfText << endl; //��ֵ
		  utfText+=1;
	  }

	  
	  WCHAR* buf = (WCHAR*)malloc(sizeof(WCHAR));
	  env->GetStringRegion(result,0,1,(jchar*)buf);
	  jstring regionResult = env->NewString((const jchar*)buf,1);
	  WCHAR * p_Buf = L"�л����񹲺͹�";
	  jstring content = env->NewString((const jchar*)p_Buf,7);
	  WCHAR* mBuf = (WCHAR*)malloc(sizeof(WCHAR)*4);
	  env->GetStringRegion(content,1,4,(jchar*)mBuf);
	  jstring regionResult1 = env->NewString((const jchar*)mBuf,4);

	  
	  char *uBuf = new char[0];
	  env->GetStringUTFRegion(utfRes,0,1,uBuf);//len ʵ���ַ��������������ֽ�����
	  jstring ssd = env->NewStringUTF(uBuf);


	  

	  const jchar * p_str = env->GetStringCritical(content,NULL);
	  cout << "---------------index: 5 -> " << *(p_str+5) << endl;
	  env->ReleaseStringCritical(content,p_str);
		  
	  env->ReleaseStringChars(result,text-wlen);//ָ��λ����Ҫ����
	  env->ReleaseStringUTFChars(utfRes,utfText-utfLen);
	  //return result;
	  //return regionResult1;
	  //return utfRes;
	  return ssd;
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseJniArray
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseJniArray
  (JNIEnv *env, jclass clazz, jbyteArray data){
	  jsize len = env->GetArrayLength(data);
	  cout << "len -> " << len << endl;
	  //���������������� NEW
	  jbyteArray byteArray = env->NewByteArray(10);
	  // GET
	  jbyte* p_data = env->GetByteArrayElements(byteArray,NULL);
	  // RELEASE mode 0,JNI_COMMIT(1),JNI_ABORT(2)
	  env->ReleaseByteArrayElements(byteArray,p_data,JNI_COMMIT);
	  // GET Region
	  jbyte* buf = new jbyte[5];
	  env->GetByteArrayRegion(byteArray,0,5,buf);
	  // Set Region
	  env->SetByteArrayRegion(byteArray,5,5,buf);
	  // GET Critical Ϊ�˲���������
	  env->GetPrimitiveArrayCritical(byteArray,NULL);
	  // RELEASE Criticalk
	  env->ReleasePrimitiveArrayCritical(byteArray,buf,0);

	  //�������� NEW
	  jobjectArray mainArray = env->NewObjectArray(10,clazz,NULL);
	  //SET
	  jobject main = env->AllocObject(clazz);
	  env->SetObjectArrayElement(mainArray,6,main);
	  //GET
	  jobject mainGet = env->GetObjectArrayElement(mainArray,6);
	  jsize mainLen = env->GetArrayLength(mainArray);
	  cout << "mainLen -> " << mainLen << endl;
	  return len;
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseForThreadSync
 * Signature: (Lcom/sankuai/jnicase/Person;)V
 */
JNIEXPORT void JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseForThreadSync
  (JNIEnv *env, jclass jnicase, jobject person){
	  
	  jint enterOK = env->MonitorEnter(jnicase);
	  if(enterOK == JNI_OK){
		  cout << "enter ok" << endl;
	  }
	  
	  jclass clazz = env->GetObjectClass(person);
	  jfieldID ageId = env->GetFieldID(clazz,"age","I");
	  jint age = env->GetIntField(person,ageId);
	  env->SetIntField(person,ageId,age+1);
	  jint newAge = env->GetIntField(person,ageId);

	  //��ȡ��ǰ�߳�����
	  jclass threadClazz = env->FindClass("java/lang/Thread");
	  jmethodID currentThreadID = env->GetStaticMethodID(threadClazz,"currentThread","()Ljava/lang/Thread;");
	  jobject thread = env->CallStaticObjectMethod(threadClazz,currentThreadID);
	  jmethodID getNameId = env->GetMethodID(threadClazz,"getName","()Ljava/lang/String;");
	  jstring name = (jstring)env->CallObjectMethod(thread,getNameId);
	  cout << "thread name -> " << name << " age -> " << newAge << endl;
	  
	  jint exitOK = env->MonitorExit(jnicase);
	  if(exitOK == JNI_OK){
		  cout << "exitOK ok" << endl;
	  }
	  
}

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseDirectByteBuffer
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseDirectByteBuffer
  (JNIEnv *env, jclass){
	  char* address = new char[1024];
	  jobject buffer = env->NewDirectByteBuffer(address,1024);
	  int* content = (int*)env->GetDirectBufferAddress(buffer);
	  cout << "content -> " << content << endl;
	  jlong capacity = env->GetDirectBufferCapacity(buffer);
	  cout << "capacity -> " << capacity << endl;
	  return buffer;
}


/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseJniReflected
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseJniReflected
  (JNIEnv *env, jclass){
	  
	  jclass personClass = env->FindClass("com/sankuai/jnicase/Person");
	  jobject person = env->AllocObject(personClass);

	  // �໥ת��methodID��ͬ ʵ�ʳ�����
	  jmethodID passwordMId = env->GetMethodID(personClass,"password","()Ljava/lang/String;");
	  jobject method = env->ToReflectedMethod(personClass,passwordMId,false);
	  jmethodID passwordMMID = env->FromReflectedMethod(method);

	  cout << "passwordMId -> " << passwordMId << endl;
	  cout << "passwordMMID -> " << passwordMMID << endl;


	  // �໥ת��fieldID��ͬ ʵ�ʳ�����
	  jfieldID passwordFID = env->GetFieldID(personClass,"password","Ljava/lang/String;");
	  jobject field = env->ToReflectedField(personClass,passwordFID,false);
	  jfieldID passwordFFID = env->FromReflectedField(field);

	  cout << "passwordFID -> " << passwordFID << endl;
	  cout << "passwordFFID -> " << passwordFFID << endl;

	  jint version = env->GetVersion();
	  cout << "version -> " << version << endl;
}

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

/*
 * Class:     com_sankuai_jnicase_JniNativeClassCase
 * Method:    caseJVMJNI
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_sankuai_jnicase_JniNativeClassCase_caseJVMJNI
  (JNIEnv *env, jclass){
	  /*
	  JavaVM* vm = (JavaVM*)malloc(sizeof(JavaVM));
	  jint result = env->GetJavaVM(&vm);
	  cout << "result -> " << result << endl;
	  
	  JavaVMInitArgs vm_args;
	  JavaVMOption option[4];

	  option[0].optionString = "-Djava.compiler=NONE";
	  option[1].optionString = "-Djava.class.path=e:\\meituan\\JNICase\\build\\classes\\java\\main\\com\\sankuai\\jnicase";
	  option[2].optionString = "-Djava.library.path=";
	  option[3].optionString = "-verbose:jni";
	  
	  int res = JNI_CreateJavaVM(&vm,(void **)&env,&vm_args);
	  cout << "res -> " << res << endl;
	  */
	  //ͨ����ִ�г����� ����java��������в���

	  
	WCHAR* path = L"E:\\meituan\\JNICase\\JNIEXE\\Debug\\jre1.8.0_221\\bin\\client\\jvm.dll";
	HINSTANCE dll = LoadLibraryW(path);
	//free(path);
	//����JVM
	jniCreateJavaVM = (JNICreateJavaVM)GetProcAddress(dll,"JNI_CreateJavaVM");
	jniGetDefaultJavaVMInitArgs = (JNIGetDefaultJavaVMInitArgs)GetProcAddress(dll,"JNI_GetDefaultJavaVMInitArgs");
	jniGetCreateJavaVMs = (JNIGetCreateJavaVMs)GetProcAddress(dll,"JNI_GetCreateJavaVMs");
	GetProcAddress(dll,"JNI_OnLoad");
	jniOnLoad = (JNIOnLoad)GetProcAddress(dll,"JNI_OnLoad");
	jniOnUnload = (JNIOnUnload)GetProcAddress(dll,"JNI_OnUnload");
	/*
	JavaVMInitArgs* p_vm_args = (JavaVMInitArgs*)malloc(sizeof(JavaVMInitArgs) + sizeof(JavaVMOption) * 4);
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
	/*
	JavaVM * vm;
	jsize nVMs;
	jint resGet = jniGetCreateJavaVMs(&vm,1,&nVMs);
	cout <<"resGet -> " << resGet << endl;
	*/
}

JNIEXPORT jstring JNICALL caseNOh(JNIEnv *env, jclass clazz, int number){
	return env->NewStringUTF("HELLO WORLD");
}

static const char *CLASS_NAME = "com/sankuai/jnicase/JniNativeClassCase";//����

static JNINativeMethod method = {
	"caseNOh",
	"(I)Ljava/lang/String;",
	(void *)caseNOh
};

static bool bindNative(JNIEnv * env){
	jclass clazz = env->FindClass(CLASS_NAME);
	if(clazz == NULL){
		return false;
	}
	return env->RegisterNatives(clazz,&method,1);
}

static bool unBindNative(JNIEnv * env){
	jclass clazz = env->FindClass(CLASS_NAME);
	if(clazz == NULL){
		return false;
	}
	return env->UnregisterNatives(clazz);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm,void *reserved){
	JNIEnv* env = NULL;
	jint result = -1;
	if(vm->GetEnv((void **)&env,JNI_VERSION_1_8) != JNI_OK){
		return result;
	}

	bool res = bindNative(env);
	cout << "OnLoad res -> " << res << endl;
	return JNI_VERSION_1_8;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm,void *reserved){
	JNIEnv* env = NULL;
	if(vm->GetEnv((void**)&env,JNI_VERSION_1_8) != JNI_OK){
		return;
	}
	bool res = unBindNative(env);
	cout << "UnLoad res -> " << res << endl;
}


// JNIEnv ���������߳���Ч

JNIEXPORT void JNICALL attachAndDetachCurrent(JNIEnv* env,jclass clazz){
	JavaVM * vm;
	env->GetJavaVM(&vm);
	
	//�����̴߳�����env ��Ҫͨ�����淽���󶨡����JVM�����ܲ���JVM�ڵ����ݡ�
	JNIEnv* p_env;
	vm->AttachCurrentThread((void**)&p_env,nullptr);

	vm->DetachCurrentThread();
}