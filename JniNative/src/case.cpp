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
	  // 01.根据类加载器和class文件的字节数组，获取导致类对象
	  jclass personClazz = env->DefineClass("com/sankuai/jnicase/Person",loader,p_data,len);
	  jclass personClazzByFind = env->FindClass("com/sankuai/jnicase/Person");
	  jobject person = env->AllocObject(personClazz);
	  env->ReleaseByteArrayElements(data,p_data,0);
	  //02.如果personClass 不是Object类对象或接口类对象，返回父类类对象
	  jclass superClazz = env->GetSuperclass(personClazz);
	  if(superClazz == NULL){
		cout << "super clazz is null -> "<< superClazz << endl;
	  }else{
		cout << "super clazz is valid -> "<< superClazz << endl;
	  }
	  //03.如果是Object类对象，返回NULL
	  jclass ssClazz = env->GetSuperclass(superClazz);
	  if(ssClazz == NULL){
		cout << "super super clazz is null -> "<< ssClazz << endl;
	  }else{
		cout << "super super clazz is valid -> "<< ssClazz << endl;
	  }
	  //04.判断两个类对象转换是否安全：为什么通过类加载器获取到的类对象和类名.class获取的类对象转换是不安全的？？？
	  jboolean isSafe = env->IsAssignableFrom(personClazz,personClazzSource);
	  if(isSafe){
		  cout << "convert is safe" << endl;
	  }else{
		  cout << "convert is unsafe" << endl;
	  }
	  //05.判断两个类对象转换是否安全：通过FindClass获取到的类对象和类名.class获取的类对象转换是安全的
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
	  //1.找到类，全路径类名，用"/"分隔；
	  jclass c = env->FindClass("com/sankuai/jnicase/Person");
	  //2.默认构造器
	  jobject person = env->AllocObject(c);
	  //3.获取属性ID, String签名别忘了分号;
	  jfieldID nameId = env->GetFieldID(c,"name","Ljava/lang/String;");
	  //4.创建字符串用utf
	  jstring value = env->NewStringUTF("yangkj");
	  //5.设置string类型的属性值
	  env->SetObjectField(person,nameId, value);
	  //6.获取属性id  int类型的属性签名
	  jfieldID ageId = env->GetFieldID(c,"age","I");
	  jint age = 31;
	  //7.设置int类型的属性值
	  env->SetIntField(person,ageId,age);
	  //8.头文件生成的对象统一是jobject。
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
	  //9.获取构造器方法ID:方法名<init> 方法签名 返回值 V
	  jmethodID con = env->GetMethodID(clazz,"<init>","(Ljava/lang/String;I)V");

	  jstring name = env->NewStringUTF("yangfan");
	  jint age = 30;
	  jobject person = env->NewObject(clazz,con,name,age);

	  //10.参数是指向jvalue数组的指针
	  jvalue* p_v = new jvalue[10];
	  p_v[0].l = env->NewStringUTF("yangkunjian");
	  p_v[1].i = 31;
	  jobject person1 = env->NewObjectA(clazz,con,p_v);
	  /*
	  int v = 10;
	  va_list list;//如何初始化
	  va_start(list,v);
	  va_arg(list,int);
	  jobject person2 = env->NewObjectV(clazz,con,list);
	  va_end(list);
	  */
	  //11.创建对象数组
	  jobjectArray result = env->NewObjectArray(2,clazz,NULL);
	  //12.给对象数组赋值
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
	  //13.获取引用类型
	  jobjectRefType type = env->GetObjectRefType(person);
	  cout << "type -> person : " << type << endl;
	  //14.从对象获取类信息
	  jclass clazz = env->GetObjectClass(person);
	  jfieldID nameId = env->GetFieldID(clazz,"name","Ljava/lang/String;");
	  jobject name = env->GetObjectField(person,nameId);
	  cout << "person name -> " << name << endl;

	  jobject newPerson = env->AllocObject(clazz);
	  type = env->GetObjectRefType(newPerson);
	  cout << "type -> newPerson : " << type << endl;
	  //15.判断是否是指定的类实例
	  jboolean isSameType = env->IsInstanceOf(newPerson,clazz);
	  cout << "type is same -> " << isSameType + '0' << endl;// 49 -> 1		true
	  //16.判断释放是同一个对象
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
	  //17.调用的方法返回值是数组类型：需要用强转
	  jbyteArray result = (jbyteArray)env->CallObjectMethod(person,translateId2,name);
	  
	  //18.获取数组长度
	  jsize len = env->GetArrayLength(result);
      cout << "len -> " << len << endl;

	  //19.获取数组元素：返回指向数组头部的指针
	  jbyte* p_byte = env->GetByteArrayElements(result,false);
	  //20.通过指针遍历数组
	  for(jsize i = 0; i<len;i++){
		  cout << i << " -> " << *p_byte << endl;
		  p_byte +=1;
	  }
	  
	  jmethodID programId = env->GetMethodID(clazz,"program","(Lcom/sankuai/jnicase/Computer;J)V");

	  jclass computerClazz = env->FindClass("com/sankuai/jnicase/Computer");
	  jobject computer = env->AllocObject(computerClazz);

	  
	  jclass systemClazz = env->FindClass("java/lang/System");
	  //23.获取静态属性ID
	  jfieldID outId = env->GetStaticFieldID(systemClazz,"out","Ljava/io/PrintStream;");
	  jobject out = env->GetStaticObjectField(systemClazz,outId);
	  jclass outClazz = env->GetObjectClass(out);
	  jmethodID printlnId = env->GetMethodID(outClazz,"println","(Ljava/lang/String;)V");
	  jstring text = env->NewStringUTF("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ");
	  env->CallVoidMethod(out,printlnId,text);
	  
	  //24.获取静态方法ID,注意没有参数的方法()里没有V
	  jmethodID currentId1 = env->GetStaticMethodID(systemClazz,"getSecurityManager","()Ljava/lang/SecurityManager;");
	  
	  jmethodID currentId = env->GetStaticMethodID(systemClazz,"currentTimeMillis","()J");
	  jlong time = env->CallStaticLongMethod(systemClazz,currentId);
	  
	  jvalue* params = new jvalue[2];
	  params[0].l = computer;
	  params[1].j = time;
	  //21.调用A
	  env->CallVoidMethodA(person,programId,params);
	  //22.调用默认方法  time直接传数值 相当于直接取地址
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
	  // 当前没有异常抛出
	  jthrowable exce = env->ExceptionOccurred();
	  if(exce == NULL){
		  cout << "ExceptionOccurred: no exception "<< exce << endl;
	  }else{
		  cout << "ExceptionOccurred: exception "<< exce << endl;
	  }
	  //jint result = env->Throw(exception);
	  jclass clazz = env->FindClass("com/sankuai/jnicase/CustomException");
	  
	  // const char* message 直接赋值
	  const char* info = "new exception ...";
	  jint result = env->ThrowNew(clazz,info);
	  if(result == 0){
		  cout << "exception throw ok " << endl;
	  }else{
		  cout << "exception throw error" << endl;
	  }
	  //当前能检测到异常抛出
	  jthrowable exce1 = env->ExceptionOccurred();
	  if(exce1 == NULL){
		  cout << "ExceptionOccurred: no exception "<< exce1 << endl;
	  }else{
		  cout << "ExceptionOccurred: exception "<< exce1 << endl;
	  }
	  //相当于调用printStackTrace(); 拦截后不会回调到java层
	  //env->ExceptionDescribe();

	  jboolean checkResult1 = env->ExceptionCheck();
	  if(checkResult1){
		  cout << "ExceptionCheck1: has exception "<< endl;
	  }else{
		  cout << "ExceptionCheck1: no exception " << endl;
	  }

	  //清空异常信息
	  env->ExceptionClear();
	  //程序终止
	  /*
	  const char* msg = "programs end";
	  env->FatalError(msg);
	  */
	  //及时清空了异常或拦截补货了 不会检测到异常发生
	  jboolean checkResult2 = env->ExceptionCheck();
	  if(checkResult2){
		  cout << "ExceptionCheck2: has exception "<< endl;
	  }else{
		  cout << "ExceptionCheck2: no exception " << endl;
	  }
}
