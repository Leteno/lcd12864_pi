import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class GUI extends Frame {

    private Cheese cheese;
    private TextArea textArea;

    public GUI() {
	setTitle("bit_matrix_generator");
	setSize(750, 600);
	setLayout(new FlowLayout());

	this.addWindowListener(new WindowAdapter() {
		public void windowClosing(WindowEvent we)
		    {
			System.exit(0);
		    }
	    });

	cheese = new Cheese();
	add(cheese);

	Panel downPanel = new Panel();
	downPanel.setLayout(new FlowLayout());
	add(downPanel);

	Panel controller = new Panel();
	controller.setLayout(new GridLayout(6, 1));
	downPanel.add(controller);

	Button btn = new Button("to matrix");
	btn.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    textArea.setText(cheese.dump());
		}
	    });
	controller.add(btn);

	Button btn2 = new Button("recovery");
	btn2.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    try {
			cheese.recovery(textArea.getText());
			JOptionPane.showMessageDialog(null, "done");
		    } catch (Exception exception) {
			exception.printStackTrace();
			JOptionPane.showMessageDialog(null, "An exception has happended");
		    }
		}
	    });
	controller.add(btn2);

	Button btn3 = new Button("Clear");
	btn3.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    cheese.clearContent();
		}
	    });
	controller.add(btn3);

	controller.add(new Label("left, top"));
	controller.add(new Label("width, height"));
	controller.add(new Label("data"));

	textArea = new TextArea();
	textArea.setSize(100, 100);
	downPanel.add(textArea);
    }

    public static void main(String[] args) {
	GUI gui = new GUI();
	gui.setVisible(true);
    }
}