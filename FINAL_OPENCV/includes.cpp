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

//Global Variables
Dim d;
Mat imagen;
string label;
int imagewidth, imageheight, textwidth, textheight;

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
	label= arg++;
	putText(imagen, 
            label,
            Point(0,115), // Coordinates
            cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
            1.0, // Scale. 2.0 = 2x bigger
            Scalar(81, 229, 18), // Color
            1, // Thickness
            CV_AA);
	imwrite( "newImage.jpg", imagen);
	return 1;
}

extern "C"
int writeresize(int resize){
	double num = (abs(resize) * pow(10,-3)) - 0.01;
	double scale = 1* num;
	cout << resize << endl;
	cout << num << endl;
	cout << label << endl;
	putText(imagen,
            label,
            Point(0,115), // Coordinates
            cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
            scale, // Scale. 2.0 = 2x bigger
            Scalar(81, 229, 18), // Color
            1, // Thickness
            CV_AA);
	imwrite( "newImage.jpg", imagen);
	cout << "it was written"<< endl;
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
	/*int baseline = 0;
	double scale = 0;
	//double scale = ((float)(height-3))/20.0;
	Size textSize = getTextSize(arg++, 
	FONT_HERSHEY_COMPLEX_SMALL, scale, 1, &baseline);  //Geting text rect
	dtext.c = textSize.width;
	dtext.r = textSize.height;
	if(dtext.c < d.c or dtext.c == d.c){
		printf("True");		
		return 1;
	}
	return 0;*/

	/*int width = imagen.size().width;
	int height = imagen.size().height;
	int baseline = 0;
	double scale = 0;
	Size textSize = getTextSize(arg++, 
	FONT_HERSHEY_COMPLEX_SMALL, scale, 1, &baseline);  //Geting text rect
	int textwidth = textSize.width;
	int textheight = textSize.height;
	cout << (width)<< endl;
	cout << (textwidth) << endl;
	if(textwidth < width or textwidth == width){	
		return 1;
	}	
	return 0;*/
	label = arg++;
	int baseline = 0;
	Size textSize = getTextSize(arg, 
	FONT_HERSHEY_COMPLEX_SMALL,0.99,2,&baseline);  //Geting text rect

	textwidth = textSize.width;
	textheight = textSize.height;
	imagewidth = imagen.cols;
	imageheight = imagen.rows;
	cout << (arg)<< endl;
	cout << imagewidth << endl;
	cout << textwidth << endl;
	if(imagen.cols - textSize.width < 0 ){	
		return 0;
	}	
	return 1;	
}


extern "C"
int getdifference(){
	int baseline = 0;
	Size textSize = getTextSize(label, 
	FONT_HERSHEY_COMPLEX_SMALL,0.99,2,&baseline);  //Geting text rect
	cout << textwidth << endl;
	cout << imagewidth << endl;
	cout << textwidth - imagewidth << endl;
	int dif[2];
	dif[1] = textwidth;
	dif[0] = imagewidth;
	return  textwidth;	
}



extern "C" 
int getdims(){
	int dims[2];
	dims[1] = d.r;
	dims[0] = d.c;
	return *dims; // Sends to the NASM program a pointer to the dimension array
}

extern "C" 
void pixchange(){
	printf("Mañaaana tiene que calcular el tamaño!!!!!! pinche!");
}