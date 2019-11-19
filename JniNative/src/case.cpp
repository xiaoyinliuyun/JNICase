#include "com_sankuai_jnicase_JniNativeClassCase.h"
#include <iostream>
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

	  jboolean checkResult1 = env->ExceptionCheck();
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