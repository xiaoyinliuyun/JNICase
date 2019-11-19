package com.sankuai.jnicase;

import javax.swing.*;

public class GUI extends JFrame {

    private JTextField className = new JTextField();
    private JTextField path = new JTextField();

    public GUI(){

        add(className);
        add(path);

        this.setVisible(true);
    }

}
