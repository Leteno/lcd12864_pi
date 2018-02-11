import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class Cheese extends Panel {

    private int cheeseSize = 16;

    public Cheese() {
	this.setLayout(new GridLayout(cheeseSize, cheeseSize));
	for (int row = 0; row < cheeseSize; row++) {
	    for (int col = 0; col < cheeseSize; col++) {
		this.add(new B(row, col));
	    }
	}
    }

    public String dump() {

	int gridSize = cheeseSize * cheeseSize;
	boolean[] output = new boolean[gridSize];
	for (int i = 0; i < gridSize; i++) {
	    B b = (B)getComponent(i);
	    output[i] = b.isSelected;
	}
	int left = 0, right = cheeseSize - 1,
	    top = 0, bottom = cheeseSize - 1;
	for (int col = 0; col < cheeseSize; col++) {
	    for (int row = 0; row < cheeseSize; row++) {
		if (output[col + row * cheeseSize]) {
		    right = col;
		    break;
		}
	    }
	}
	for (int col = cheeseSize - 1; col >= 0; col--) {
	    for (int row = 0; row < cheeseSize; row++) {
		if (output[col + row * cheeseSize]) {
		    left = col;
		    break;
		}
	    }
	}
	for (int row = 0; row < cheeseSize; row++) {
	    for (int col = 0; col < cheeseSize; col++) {
		if (output[col + row * cheeseSize]) {
		    bottom = row;
		    break;
		}
	    }
	}
	for (int row = cheeseSize - 1; row >= 0; row--) {
	    for (int col = 0; col < cheeseSize; col++) {
		if (output[col + row * cheeseSize]) {
		    top = row;
		    break;
		}
	    }
	}

	int width = right + 1 - left;
	int height = bottom + 1 - top;
	int resultSize = width * height / 8 + 1;
	int []result = new int[resultSize];
	for (int i = 0; i < resultSize; i++) result[i] = 0;
	int index = 0;
	int counter = 0;
	for (int row = top; row <= bottom; row++) {
	    for (int col = left; col <= right; col++) {
		if (output[row * cheeseSize + col]) {
		    result[index] |= 0x80 >> counter;
		}
		counter++;
		if (counter >= 8) {
		    counter = 0;
		    index++;
		}
	    }
	}
	
	StringBuffer buffer = new StringBuffer();
	buffer.append(String.format("(%d, %d, %d, %d)\n", left, top, right, bottom));
	buffer.append(String.format("(%d, %d)\n", width, height));
	buffer.append("\n{\n");

	index = 0;
	for (int ch : result) {
	    buffer.append(String.format("0x%X,", ch));
	    if (++index % width == 0) {
		index = 0;
		buffer.append("\n");
	    }
	}
	buffer.append("\n}");
	return buffer.toString();
    }

    public static class B extends Panel implements MouseListener {
	private int mRow, mCol;
	public boolean isSelected;
	
	public B(int row, int col) {
	    super();
	    this.mRow = row;
	    this.mCol = col;
	    isSelected = false;
	    addMouseListener(this);
	}

	@Override
	public void paint(Graphics g) {
	    Color color = isSelected ? Color.black :
		(mRow + mCol) % 2 == 0 ? Color.white :
		Color.lightGray;
	    setBackground(color);
	    super.paint(g);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
	    isSelected = !isSelected;
	    repaint();
	}

	public void mouseEntered(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
    }
}