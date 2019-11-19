package com.sankuai.jnicase;

import java.io.*;

public class CustomClassLoader extends ClassLoader {

    private String mPath;

    public CustomClassLoader(){
        super();
    }

    public CustomClassLoader(String mPath) {
        super();
        this.mPath = mPath;
    }

    public CustomClassLoader(ClassLoader parent, String mPath) {
        super(parent);
        this.mPath = mPath;
    }



    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        byte[] data = readFileToByteArray(name);
        return this.defineClass(name,data,0,data.length);
    }

    public byte[] readFileToByteArray(String name) {

        name = name.replaceAll("\\.","/");
        //拼接
        String filePath = this.mPath + name +".class";
        File file = new File(filePath);
        ByteArrayOutputStream os = null;
        InputStream is = null;
        byte[] rtnData = null;
        try {
            os = new ByteArrayOutputStream();
            is = new FileInputStream(file);
            int tmp = 0;
            while ((tmp = is.read()) != -1){
                os.write(tmp);
            }
            rtnData = os.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if(is != null){
                try {
                    is.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if(os != null){
                try {
                    os.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return rtnData;
    }
}
