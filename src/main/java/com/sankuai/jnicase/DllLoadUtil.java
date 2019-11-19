package com.sankuai.jnicase;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

/**
 * @Author yangkunjian.
 * @Date 2019/9/3 20:35.
 * @Desc
 */

public class DllLoadUtil {
    private static final String TAG = "DllLoadUtil";

    private static final String DLL_PATH = "cjars";

    private static void deleteFileByName(String libName){
        String path = new File(DLL_PATH).getAbsolutePath();
        File file = new File(path);
        if (!file.exists() && !file.isDirectory()) {
            return;
        }

        File[] files = file.listFiles();
        if (files == null){
            return;
        }
        for (File f : files) {
            if(f.getName().endsWith(libName)){
                f.delete();
                return;
            }
        }
    }

    public static String resourceTempPath(String libName) {
        deleteFileByName(libName);
        String path = new File(DLL_PATH).getAbsolutePath();
        File file = new File(path);
        if (!file.exists() && !file.isDirectory()) {
            file.mkdir();
        }
        String tempLibName = System.nanoTime() + "_" + libName;

        File dll = new File(path, tempLibName);
        try {
            InputStream input = DllLoadUtil.class.getClassLoader().getResourceAsStream(libName);
            Files.copy(input, Paths.get(dll.getPath()), StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            System.out.println("resourceTempPath -> " + e + " exception ");
        }
        return dll.getAbsolutePath();
    }

    public static void load(String name) {
        try {
            String path = resourceTempPath(name);
            System.load(path);
        } catch (Exception e) {
            System.out.println("load -> " + e + " exception ");
        }
    }
}
