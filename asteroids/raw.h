// raw.h -- defines a RAWIMG struct,
// and the loadRawImage() & loadRawImageInv functions

#include <stdio.h>

struct RAWIMG {    // a simple structure for storing an rgb image in memory
	RAWIMG() {data=NULL;} // default constructor
	//~RAWIMG() { if (data != NULL) delete [] data; } // destructor
	GLuint   w;    // Image's Width
	GLuint   h;    // Image's Height
	GLubyte* data; // Image's Data (Pixels)
}; 

bool loadRawImage(const char* file_name, int w, int h, RAWIMG & img)
{   // loads a RAW RGB file into img & returns whether successful
	GLuint   sz;    // size in bytes for given width & height
	FILE*    fp;    // file pointer
	long     fsize; // file size in bytes

	// Update The Image's Fields
	img.w = (GLuint) w;
	img.h = (GLuint) h;
	sz = img.w*img.h*3;      // 3 bytes per pixel (24 bit)
    if (img.data) delete [] img.data;
	img.data = NULL;
	
	// Open the file and check its size
	fp = fopen(file_name , "rb");
	if (!fp) {
		fclose(fp);
		return false;        // couldn't open file
	}
	fseek(fp, 0L, SEEK_END); // go to last byte of file
	fsize = ftell(fp);       // get position in file in bytes
	if (fsize != (long)sz) {
		fclose(fp);
		return false;        // file was incomplete or given w,h wrong
	}

	// Allocate memory for the pixels
	img.data = new GLubyte [img.w * img.h * 3];
	if (img.data == NULL) {
		fclose(fp);
		return false;  // couldn't allocate memory
	}

	fseek(fp, 0L, SEEK_SET); // go back to beginning of file
	fread(img.data, sz, 1, fp); // read 1 block of sz bytes
	fclose(fp);
	return true; // success
}
	
bool loadRawImageInv(const char* file_name, int w, int h, RAWIMG & img)
{   // loads a RAW RGB file into img & returns whether successful
	GLuint   sz;    // size in bytes for given width & height
	FILE*    fp;    // file pointer
	long     fsize; // file size in bytes

	// Update The Image's Fields
	img.w = (GLuint) w;
	img.h = (GLuint) h;
	sz = img.w*img.h*3;             // 3 bytes per pixel (24 bit)
    if (img.data) delete [] img.data;
	img.data = NULL;
	
	// Open the file and check its size
	fp = fopen(file_name , "rb");
	if (!fp) {
		fclose(fp);
		return false;        // couldn't open file
	}
	fseek(fp, 0L, SEEK_END); // go to last byte of file
	fsize = ftell(fp);       // get position in file in bytes
	if (fsize != (long)sz) {
		fclose(fp);
		return false;        // file was incomplete or given w,h wrong
	}

	// Allocate memory for the pixels
	img.data = new GLubyte [img.w * img.h * 3];
	if (img.data == NULL) {
		fclose(fp);
		return false;  // couldn't allocate memory
	}

	fseek(fp, 0L, SEEK_SET); // go back to beginning of file
	for (GLuint i=1; i <= img.h; i++) {
		int loc = (img.h - i) * img.w * 3;  // location for i'th row
		fread(&img.data[loc],img.w*3,1,fp); // read one row into that spot
	}		
	fclose(fp);
	return true; // success
}
	
