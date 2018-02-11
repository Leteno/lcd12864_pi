import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class GUI extends Frame implements ActionListener {

    private Cheese cheese;
    private TextArea textArea;

    public GUI() {
	setTitle("bit_matrix_generator");
	setSize(550, 400);
	setLayout(new FlowLayout());

	cheese = new Cheese();
	add(cheese);

	Panel controller = new Panel();
	controller.setLayout(new FlowLayout());
	Button btn = new Button("don't press me");
	btn.addActionListener(this);
	controller.add(btn);
	controller.add(new Label("ABC"));
	textArea = new TextArea();
	textArea.setSize(100, 100);
	controller.add(textArea);
	add(controller);

	this.addWindowListener(new WindowAdapter() {
		public void windowClosing(WindowEvent we)
		    {
			System.exit(0);
		    }
	    });
    }

    public void actionPerformed(ActionEvent e) {
	textArea.setText(cheese.dump());
    }

    public static void main(String[] args) {
	GUI gui = new GUI();
	gui.setVisible(true);
    }
}