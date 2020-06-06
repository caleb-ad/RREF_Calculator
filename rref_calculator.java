import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.lang.*;
import java.io.*;


class size_select extends Container{

    JTextField columns;
    JTextField rows;

    rref_calculator parent;

    size_select(rref_calculator frame){
        parent = frame;
        this.setLocation(600, 600);

        GridBagLayout layout = new GridBagLayout();
        GridBagConstraints cons = new GridBagConstraints();
        cons.gridx = GridBagConstraints.RELATIVE;
        cons.weightx = 1.0;
        cons.fill = GridBagConstraints.BOTH;

        JLabel label = new JLabel("Enter columns and rows: ");
        layout.setConstraints(label, cons);
        this.add(label);

        columns = new JTextField(20);
        layout.setConstraints(columns, cons);
        this.add(columns);

        rows = new JTextField(20);
        layout.setConstraints(rows, cons);
        this.add(rows);

        JButton button = new JButton("Submit");
        cons.gridx = 1;
        cons.gridy = 1;
        cons.anchor = GridBagConstraints.CENTER;
        cons.fill = GridBagConstraints.NONE;
        layout.setConstraints(button, cons);
        button.addActionListener(parent);
        this.add(button);

        this.setLayout(layout);
        this.setVisible(true);
    }
      
}

class rref_calculator extends JFrame implements WindowListener, ActionListener{

    int columns = -1;
    int rows = -1;
    size_select ss;
    ArrayList<JTextField> boxes;
    JButton button;

    rref_calculator(String name){
        super(name);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocation(600, 600);
        this.addWindowListener(this);
        boxes = new ArrayList<JTextField>();
        
        ss = new size_select(this);
        this.getContentPane().add(ss);
        
        this.pack();
        this.setVisible(true);
    }

    private void populate(){
        GridBagLayout layout = new GridBagLayout();
        GridBagConstraints cons = new GridBagConstraints();
        cons.weightx = 1.0;
        cons.weighty = 1.0;
        cons.anchor = GridBagConstraints.NORTH;
        cons.fill = GridBagConstraints.BOTH;

        for(int a=0; a<rows; a++){
            cons.gridy = a;
            for(int b=0; b<columns; b++){
                cons.gridx = b;
                JTextField tfield = new JTextField(20);
                layout.setConstraints(tfield, cons);
                this.getContentPane().add(tfield, a);
                boxes.add(tfield);
                boxes.get(boxes.size()-1).setVisible(true);
            }
        }

        button = new JButton("Submit");
        cons.gridx = (int)columns / 2;
        cons.gridy = rows + 1;
        cons.anchor = GridBagConstraints.CENTER;
        cons.fill = GridBagConstraints.NONE;
        layout.setConstraints(button, cons);
        button.addActionListener(this);
        this.getContentPane().add(button);
        this.getContentPane().setLayout(layout);

        //this.validate();
        this.pack();
        this.setVisible(true);
    }

    public void windowClosing(WindowEvent e) {
        if( e.getSource() == this){
            dispose();
            System.exit(0);
        }   
    }

    public void actionPerformed(ActionEvent e){
        try{
            if(e.getSource() == button){
                String matrix = String.valueOf(rows) + "," + String.valueOf(columns) + ",";
                for(JTextField  tf: boxes){
                    matrix += String.valueOf((Float.valueOf(tf.getText()))) + ",";
                }
                matrix += "\n";
                Runtime r = Runtime.getRuntime();
                Process calc = r.exec("rref_calc.exe");
                OutputStreamWriter wr = new OutputStreamWriter(calc.getOutputStream());
                Scanner sc =  new Scanner(calc.getInputStream());
                wr.write(matrix);
                wr.close();
                sc.useDelimiter(",");
                int idx = 0;
                while(sc.hasNextFloat()){
                    boxes.get(idx).setText(String.valueOf(sc.nextFloat()));;
                    idx += 1;
                }
            }
            else{
                columns = Integer.valueOf(ss.columns.getText());
                rows = Integer.valueOf(ss.rows.getText());
                ss.setVisible(false);
                populate();   
            }
        }catch(Exception exp){
            if(exp instanceof NumberFormatException){
                JOptionPane.showMessageDialog(this, "please enter valid number", "Error", JOptionPane.ERROR_MESSAGE);
            }
            else if(exp instanceof IOException){
                JOptionPane.showMessageDialog(this, "Error running calculation");
            }
        }       
    }

    public void windowOpened(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}

    public static void main(String args[]){
        rref_calculator Calculator = new rref_calculator("RREF calculator");
    }
}