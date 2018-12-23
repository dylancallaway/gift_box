#include <SD.h>
#include <SPI.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_HX8357.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>
#include <analogWrite.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; // variable to store the servo position

#define STMPE_CS 32
#define TFT_CS 15
#define TFT_DC 33
#define SD_CS 14
#define TFT_RST -1

#define TS_MINX 150
#define TS_MAXX 3800
#define TS_MINY 130
#define TS_MAXY 4000

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

bool draw_flag = 0;
int test_num = 0;
TS_Point p;
int touch_x_low, touch_x_high, touch_y_low, touch_y_high;

void setup()
{
	Serial.begin(115200);

	tft.begin(HX8357D);

	if (!ts.begin())
	{
		Serial.println("Couldn't start touchscreen controller");
	}
	else
	{
		Serial.println("Touchscreen started");
	}

	tft.setRotation(1);
	tft.fillScreen(HX8357_BLACK);

	Serial.print("Initializing SD card...");
	if (!SD.begin(SD_CS))
	{
		Serial.println("SD Card Initialization Failed!");
	}
	Serial.println("SD Card Initialization OK!");

	myservo.attach(A0); // attaches the servo on pin 9 to the servo object
}

void loop()
{
	while (ts.touched())
	{
		p = ts.getPoint();
	}
	p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
	p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
	Serial.print("X = ");
	Serial.print(p.x);
	Serial.print("\tY = ");
	Serial.println(p.y);
	switch (test_num)
	{
	case 0:
		test_intro();
		break;
	case 1:
		test_1();
		break;
	case 2:
		test_2();
		break;
	case 3:
		test_3();
		break;
	case 4:
		test_4();
		break;
	case 5:
		test_5();
		break;
	case 6:
		test_end();
		break;
	}
}

void test_intro()
{
	touch_x_low = 50;
	touch_x_high = 4430;
	touch_y_low = 50;
	touch_y_high = 270;

	if (draw_flag == 0)
	{
		bmpDraw("/intro.bmp", 0, 0);
		draw_flag = 1;
		myservo.write(110);
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 0;
		test_num = 1;
	}
}

void test_1()
{
	touch_x_low = 70;
	touch_x_high = 380;
	touch_y_low = 150;
	touch_y_high = 270;

	if (draw_flag == 0)
	{
		bmpDraw("/1.bmp", 0, 0);
		draw_flag = 1;
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 0;
		test_num = 2;
	}
}

void test_2()
{
	touch_x_low = 360;
	touch_x_high = 450;
	touch_y_low = 240;
	touch_y_high = 290;

	if (draw_flag == 0)
	{
		bmpDraw("/2.bmp", 0, 0);
		draw_flag = 1;
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 0;
		test_num = 3;
	}
}

void test_3()
{
	touch_x_low = 200;
	touch_x_high = 290;
	touch_y_low = 220;
	touch_y_high = 270;

	if (draw_flag == 0)
	{
		bmpDraw("/3.bmp", 0, 0);
		draw_flag = 1;
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 0;
		test_num = 4;
	}
}

void test_4()
{
	touch_x_low = 300;
	touch_x_high = 390;
	touch_y_low = 150;
	touch_y_high = 210;

	if (draw_flag == 0)
	{
		bmpDraw("/4.bmp", 0, 0);
		draw_flag = 1;
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 0;
		test_num = 5;
	}
}

void test_5()
{
	touch_x_low = 60;
	touch_x_high = 210;
	touch_y_low = 120;
	touch_y_high = 190;

	if (draw_flag == 0)
	{
		bmpDraw("/5.bmp", 0, 0);
		draw_flag = 1;
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 0;
		test_num = 6;
	}
}

void test_end()
{
	touch_x_low = 50;
	touch_x_high = 4430;
	touch_y_low = 50;
	touch_y_high = 270;

	if (draw_flag == 0)
	{
		bmpDraw("/end.bmp", 0, 0);
		draw_flag = 1;
	}
	if (p.x > touch_x_low && p.x < touch_x_high && p.y > touch_y_low && p.y < touch_y_high)
	{
		draw_flag = 1;
		test_num = 6;
		myservo.write(180);
	}
}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint16_t y)
{

	File bmpFile;
	int bmpWidth, bmpHeight;			// W+H in pixels
	uint8_t bmpDepth;					// Bit depth (currently must be 24)
	uint32_t bmpImageoffset;			// Start of image data in file
	uint32_t rowSize;					// Not always = bmpWidth; may have padding
	uint8_t sdbuffer[3 * BUFFPIXEL];	// pixel buffer (R+G+B per pixel)
	uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
	boolean goodBmp = false;			// Set to true on valid header parse
	boolean flip = true;				// BMP is stored bottom-to-top
	int w, h, row, col;
	uint8_t r, g, b;
	uint32_t pos = 0, startTime = millis();

	if ((x >= tft.width()) || (y >= tft.height()))
		return;

	Serial.println();
	Serial.print(F("Loading image '"));
	Serial.print(filename);
	Serial.println('\'');

	// Open requested file on SD card
	if ((bmpFile = SD.open(filename)) == NULL)
	{
		Serial.print(F("File not found"));
		return;
	}

	// Parse BMP header
	if (read16(bmpFile) == 0x4D42)
	{ // BMP signature
		Serial.print(F("File size: "));
		Serial.println(read32(bmpFile));
		(void)read32(bmpFile);			  // Read & ignore creator bytes
		bmpImageoffset = read32(bmpFile); // Start of image data
		Serial.print(F("Image Offset: "));
		Serial.println(bmpImageoffset, DEC);
		// Read DIB header
		Serial.print(F("Header size: "));
		Serial.println(read32(bmpFile));
		bmpWidth = read32(bmpFile);
		bmpHeight = read32(bmpFile);
		if (read16(bmpFile) == 1)
		{								// # planes -- must be '1'
			bmpDepth = read16(bmpFile); // bits per pixel
			Serial.print(F("Bit Depth: "));
			Serial.println(bmpDepth);
			if ((bmpDepth == 24) && (read32(bmpFile) == 0))
			{ // 0 = uncompressed

				goodBmp = true; // Supported BMP format -- proceed!
				Serial.print(F("Image size: "));
				Serial.print(bmpWidth);
				Serial.print('x');
				Serial.println(bmpHeight);

				// BMP rows are padded (if needed) to 4-byte boundary
				rowSize = (bmpWidth * 3 + 3) & ~3;

				// If bmpHeight is negative, image is in top-down order.
				// This is not canon but has been observed in the wild.
				if (bmpHeight < 0)
				{
					bmpHeight = -bmpHeight;
					flip = false;
				}

				// Crop area to be loaded
				w = bmpWidth;
				h = bmpHeight;
				if ((x + w - 1) >= tft.width())
					w = tft.width() - x;
				if ((y + h - 1) >= tft.height())
					h = tft.height() - y;

				// Set TFT address window to clipped image bounds
				tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

				for (row = 0; row < h; row++)
				{ // For each scanline...

					// Seek to start of scan line.  It might seem labor-
					// intensive to be doing this on every line, but this
					// method covers a lot of gritty details like cropping
					// and scanline padding.  Also, the seek only takes
					// place if the file position actually needs to change
					// (avoids a lot of cluster math in SD library).
					if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
						pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
					else // Bitmap is stored top-to-bottom
						pos = bmpImageoffset + row * rowSize;
					if (bmpFile.position() != pos)
					{ // Need seek?
						bmpFile.seek(pos);
						buffidx = sizeof(sdbuffer); // Force buffer reload
					}

					for (col = 0; col < w; col++)
					{ // For each pixel...
						// Time to read more pixel data?
						if (buffidx >= sizeof(sdbuffer))
						{ // Indeed
							bmpFile.read(sdbuffer, sizeof(sdbuffer));
							buffidx = 0; // Set index to beginning
						}

						// Convert pixel from BMP to TFT format, push to display
						b = sdbuffer[buffidx++];
						g = sdbuffer[buffidx++];
						r = sdbuffer[buffidx++];
						tft.pushColor(tft.color565(r, g, b));
					} // end pixel
				}	 // end scanline
				Serial.print(F("Loaded in "));
				Serial.print(millis() - startTime);
				Serial.println(" ms");
			} // end goodBmp
		}
	}

	bmpFile.close();
	if (!goodBmp)
		Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f)
{
	uint16_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read(); // MSB
	return result;
}

uint32_t read32(File &f)
{
	uint32_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read();
	((uint8_t *)&result)[2] = f.read();
	((uint8_t *)&result)[3] = f.read(); // MSB
	return result;
}