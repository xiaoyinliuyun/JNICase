package com.sankuai.jnicase;

public interface IWorkable {

    char translate(byte code);

    byte[] translate(String chinese);

    void program(Computer computer, long time);



}
