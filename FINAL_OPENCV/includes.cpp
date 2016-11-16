#include <iostream>
#include <stdio.h>
#include <vector>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

uchar* datas;
struct Dim{
	int r;
	int c;
	int f;
};

Dim d;
Dim dtext;
Mat imagen;


extern "C" 
int loadimg(char* arg){	
	imagen = imread(arg, 1);	
	if(!imagen.data){
		return 0; // Reading failure
	}
	d.r = imagen.rows;
	d.c = imagen.cols;
	// col * fil * 3 its a grid of col * fil pixels
	// where each one has 3 colors/channels, R, G, B

	// unsigned char is used because it ranges between 0 and 255, just enough
	// ..to store each color value. if it were a .png file, there would be an A,
	// ..for alpha, or transparency
	datas = (uchar*) malloc(d.r * d.c * 3 * sizeof(uchar));
	int z;
	for(z = 0; z < d.f * d.c * 3; z++){
		datas[z] = imagen.data[z];	
	}
	return 1; // Reading success
}

extern "C"
int writeimage(char* arg){
	string label= arg++;
	putText(imagen, 
            label,
            Point(115,115), // Coordinates
            cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
            1.0, // Scale. 2.0 = 2x bigger
            Scalar(81, 229, 18), // Color
            1, // Thickness
            CV_AA);
	imwrite( "newImage.jpg", imagen);
	return 1;
}

extern "C" 
int saveimg(char* arg){
	// 8 = 8 bits of depth
	// UC = unsigned char = 0-255
	// 3 = 3 channels
	Mat imagen = Mat(d.f, d.c, CV_8UC3, datas);
	vector <int> param;
	param.push_back(CV_IMWRITE_JPEG_QUALITY);
	param.push_back(100); // Max quality possible
	// There's no loss, but no compression either
	try{
		if(!imwrite(arg, imagen, param)){
			free(datas);
			// Image was not written but there was no exception
			// ..maybe it tried writting in protected storage, it
			// ..could be avoided by running with sudo
			return 2; // Special message value returned to the NASM program
		}
	} catch (exception& e){
		free(datas);
		printf("%s", e.what());
		// exception: problem with the file format
		// ..or simply the filename given is invalid
		return 0;
	}
	free(datas);
	// Success in the file writting
	return 1;
}

extern "C"
int gettextdims(char* arg){
	double scale = ((float)(height-3))/20.0;
	Size textSize = getTextSize(arg++, 
	FONT_HERSHEY_COMPLEX_SMALL, scale, 1, &bottom);  //Geting text rect
	dtext.c = textSize.width;
	dtext.r = textSize.height;
	int dimstext[2];
	dimstext[1] = dtext.r;
	dimstext[0] = dtext.c;
	return *dimstext;
}

extern "C" 
int getdims(){
	int dims[2];
	dims[1] = d.r;
	dims[0] = d.c;
	return *dims; // Sends to the NASM program a pointer to the dimension array
}

extern "C" 
void pixchange(int p1, int p2){
	datas[p1] = datas[p2]; // Swaps a couple of channels between pixels
}