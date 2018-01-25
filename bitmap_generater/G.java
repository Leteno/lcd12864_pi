import java.awt.image.BufferedImage;
import java.io.PrintWriter;
import java.io.File;
import javax.imageio.ImageIO;

public class G {

    private static void usage() {
	System.out.println("usage: java G <image-file>");
    }

    public static void main(String[] args) throws Exception{
	if (args.length <= 0) {
	    usage();
	    return;
	}
	BufferedImage image = ImageIO.read(new File(args[0]));
	int byteSize = 8;
	int resultSize = (image.getWidth() * image.getHeight() + byteSize - 1) / byteSize;
	byte[] result = new byte[resultSize];
	for (int i = 0; i < resultSize; i++) {
	    result[i] = 0x0;
	}
	int index = 0;
	int bitIndex = 0; // from left
	for (int xPixel = 0, i = 0; xPixel < image.getWidth(); xPixel++) {
	    for (int yPixel = 0; yPixel < image.getHeight(); yPixel++) {
		if (bitIndex >= byteSize) {
		    bitIndex %= byteSize;
		    index++;
		}
		int color = image.getRGB(xPixel, yPixel);
		System.out.println("color: " + color);
		int red = (color & 0xFF0000) >> 4;
		int green = (color & 0xFF00) >> 2;
		int blue = color & 0xFF;
		if (red + green + blue < 255 * 3 / 2) { // white 255 * 3 black 0 * 3
		    result[index] |= 0x1 << (byteSize - 1 - bitIndex);
		}
		bitIndex++;
	    }
	}
	PrintWriter out = new PrintWriter("result.out");
	int feet = image.getWidth() / byteSize;
	out.print("{");
	for (int m = 0; m < resultSize; m++) {
	    if (m % feet == 0) out.print("\n");
	    out.printf("0x%X,", result[m]);
	}
	out.printf("\n} (%d, %d)", image.getWidth(), image.getHeight());
	out.flush();
    }
}