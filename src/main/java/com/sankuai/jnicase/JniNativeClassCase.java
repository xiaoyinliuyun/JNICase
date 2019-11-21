package com.sankuai.jnicase;


import java.lang.reflect.Method;
import java.nio.ByteBuffer;

public class JniNativeClassCase {

    static {
        DllLoadUtil.load("JniNative.dll");
    }

    public static void main(String[] args) {
        //testCase();
        testNativeSync();
        //caseDirectByteBuffer();
        //caseJniReflected();
        //caseJVMJNI();
    }

    private static void testCase() {
        createPersonByLoader();
        Person person = caseFindClass();
        System.out.println(person);

        caseInvokeInName(person);

        Person globalRef = caseCreateGlobalRef(person);
        Person localRef = caseCreateLocalRef(person);
        Person weakGlobalRef = caseCreateWeakGlobalRef(person);
        System.gc();
        new Thread() {
            @Override
            public void run() {
                super.run();
                System.out.println("global Ref -> " + globalRef);
                System.out.println("local Ref -> " + localRef);
                System.out.println("weak global Ref -> " + weakGlobalRef);
            }
        }.start();


        Person[] people = caseNewArray();
        for (Person p : people) {
            System.out.println(p);
        }

        Person newPerson = caseConvertPersonToAnother(person);

        System.out.println(newPerson);


        try {
            caseException(new CustomException());
        } catch (Exception e) {
            System.out.println("exception is ok ok ok ok");
        }

        String result = caseJniString();
        System.out.println("你好 -> " + result + "OOO");

        byte[] byteArray = new byte[16];
        int len = caseJniArray(byteArray);
        System.out.println(" result len  -> " + len);
    }

    private static Person person = new Person();

    private static void testNativeSync() {
        JniNativeClassCase mainClass = new JniNativeClassCase();
        for (int i = 0; i < 5; i++) {
            new Thread() {
                @Override
                public void run() {
                    super.run();
                    while (true) {
                        syncTest(mainClass);
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }.start();
        }
    }

    private static void syncTest(JniNativeClassCase mainClass) {
        caseForThreadSync(person);
    }

    private static void createPersonByLoader() {
        CustomClassLoader loader = new CustomClassLoader("E:/meituan/JNICase/build/classes/java/main/");
        byte[] bytes = loader.readFileToByteArray("com.sankuai.jnicase.Person");
        Person person = caseDefineClass(loader, bytes, bytes.length, Person.class);
        System.out.println("by native classloader -> " + person);

        /*
        try {
            // 已经加装过Person 且不能用于下面的转换 除非用新的loader对象
            Class<?> clazzForName = Class.forName("com.sankuai.jnicase.Person", false, loader);
            Person personForName = (Person) clazzForName.newInstance();
            System.out.println("by for name -> " +personForName);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        }
        */

        /*
        try {
              //用新的类加载器可以正常强转，用上面的loader不能正常强转
//            CustomClassLoader loaderNoPath = new CustomClassLoader();

            Class<?> clazz = loader.loadClass("com.sankuai.jnicase.Person");
            Person personByClazz = (Person) clazz.newInstance();
            personByClazz.age = 21;
            personByClazz.name = "yang man";
            System.out.println("by classloader -> " + personByClazz);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        }
        */
    }

    public static native Person caseDefineClass(CustomClassLoader loader, byte[] buf, int len, Class<?> personClazzSource);

    public static native Person caseFindClass();

    public static native Person[] caseNewArray();

    public static native Person caseConvertPersonToAnother(Person person);

    public static native void caseInvokeInName(Person person);

    public static native Person caseCreateGlobalRef(Person person);

    public static native Person caseCreateLocalRef(Person person);

    public static native Person caseCreateWeakGlobalRef(Person person);

    public static native void caseException(CustomException exception);

    public static native String caseJniString();

    public static native int caseJniArray(byte[] data);

    public static native void caseForThreadSync(Person person);

    public static native ByteBuffer caseDirectByteBuffer();

    public static native void caseJniReflected();

    public static native void caseJVMJNI();
}
