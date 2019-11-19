package com.sankuai.jnicase;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class Person implements IWorkable{
    public String name;
    public int age;

    public Person(){
    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }

    @Override
    public char translate(byte code) {
        if(code % 2 == 0){
            return 'N';
        }
        return 'M';
    }

    @Override
    public byte[] translate(String chinese) {
        if(chinese == null){
            return null;
        }
        return chinese.getBytes(StandardCharsets.UTF_8);
    }

    @Override
    public void program(Computer computer, long time) {
        computer.test(time);
    }


}
