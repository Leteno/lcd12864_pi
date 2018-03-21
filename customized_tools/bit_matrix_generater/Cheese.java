import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import java.util.*;

public class Cheese extends Panel {

    private int cheeseSize = 16;
    private ArrayList<B> list = new ArrayList();

    public Cheese() {
	this.setLayout(new GridLayout(cheeseSize, cheeseSize));
	for (int row = 0; row < cheeseSize; row++) {
	    for (int col = 0; col < cheeseSize; col++) {
		B b = new B(row, col);
		list.add(b);
		this.add(b);
	    }
	}
    }

    public String dump() {

	int gridSize = cheeseSize * cheeseSize;
	boolean[] output = new boolean[gridSize];
	for (int i = 0; i < gridSize; i++) {
	    B b = list.get(i);
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
	buffer.append(String.format("%d, %d\n", left, top, right, bottom));
	buffer.append(String.format("%d, %d\n", width, height));

	index = 0;
	boolean firstTime = true;
	for (int ch : result) {
	    if (!firstTime) buffer.append(", ");
	    buffer.append(String.format("0x%02X", ch));
	    if (++index % width == 0) {
		index = 0;
		buffer.append("\n");
	    }
	    firstTime = false;
	}

	firstTime = true;
	buffer.append("\nreverse: \n");
	for (int ch : result) {
	    ch = ~ch & 0xFF;
	    if (!firstTime) buffer.append(", ");
	    buffer.append(String.format("0x%02X", ch));
	    if (++index % width == 0) {
		index = 0;
		buffer.append("\n");
	    }
	    firstTime = false;
	}
	return buffer.toString();
    }

    public void recovery(String str) {
	Scanner scanner = new Scanner(str);

	String line1 = scanner.nextLine();
	String[] line1S = line1.split(", ");
	int left = Integer.parseInt(line1S[0]);
	int top = Integer.parseInt(line1S[1]);
	System.out.printf("left: %d, top: %d\n", left, top);

	String line2 = scanner.nextLine();
	String[] line2S = line2.split(", ");
	int width = Integer.parseInt(line2S[0]);
	int height = Integer.parseInt(line2S[1]);
	System.out.printf("width: %d, height: %d\n", width, height);

	int[] matrix = new int[width * height / 8 + 1];

	String line3 = scanner.nextLine();
	String[] line3S = line3.split(", ");
	int index = 0;
	for (String hex : line3S) {
	    int i = Integer.decode(hex);
	    matrix[index++] = i;
	    System.out.printf("0x%X\n", i);
	}
	clearContent();

	index = 0;
	int bitIndex = 7;
	for (int j = top; j < top + height; j++) {
	    for (int i = left; i < left + width; i++) {
		B b = list.get(i + j * cheeseSize);
		if (b.mCol != i || b.mRow != j) {
		    System.out.printf("error: B(%d, %d) not (%d, %d)\n", b.mCol, b.mRow, i, j);
		}
		b.isSelected = (matrix[index] & (1 << bitIndex--)) > 0;
		b.repaint();
		if (bitIndex < 0) {
		    index++;
		    bitIndex = 7;
		}
	    }
	}
    }

    public void clearContent() {
	int gridSize = cheeseSize * cheeseSize;
	for (int i = 0; i < gridSize; i++) {
	    B b = list.get(i);
	    b.isSelected = false; // clear all
	    b.repaint();
	}
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