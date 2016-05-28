#include<cmath>
#include "BMPImg.h"

using namespace std;

bool BMPImg::gammaCorrection(double gamma){
    for(int y = 0; y != header.Height; y++){
            for(int x = 0; x != header.Width; x++){
                unsigned char B=data[y][x].B,G=data[y][x].G,R=data[y][x].R;
                B=(int)(255*pow((double)B/255.0,1/gamma));
                G=(int)(255*pow((double)G/255.0,1/gamma));
                R=(int)(255*pow((double)R/255.0,1/gamma));
                data[y][x].B = B;
                data[y][x].G = G;
                data[y][x].R = R;
            }

   }
}
bool BMPImg::sobelEdge(){
    double **gray = new double *[getHeight()];
    for(int i= 0; i<getHeight(); i++){
        gray[i]= new double [getWidth()];
    }
    for( int i=0; i<getHeight(); i++){
		for(int j=0; j<getWidth(); j++ ){
            unsigned char B=data[i][j].B;
			unsigned char G=data[i][j].G;
			unsigned char R=data[i][j].R;
			gray[i][j]= 0.229*(double)R+ 0.587*(double)G+ 0.114*(double)B;
		}
	}
	double **gray_x= new double *[getHeight()];
    for(int i= 0; i<getHeight(); i++){
        gray_x[i]= new double [getWidth()];
    }
    double **gray_y= new double *[getHeight()];
    for(int i= 0; i<getHeight(); i++){
        gray_y[i]= new double [getWidth()];
    }
    for(int i= 1; i<getHeight()-1; i++){
        for(int j= 1; j<getWidth()-1;j++){

            gray_x[i][j]= -gray[i-1][j-1]-2*gray[i-1][j]-gray[i-1][j+1]
                          +gray[i+1][j-1]+2*gray[i+1][j]+gray[i+1][j+1];
            gray_y[i][j]= -gray[i-1][j-1]-2*gray[i][j-1]-gray[i+1][j-1]
                          +gray[i-1][j+1]+2*gray[i][j+1]+gray[i+1][j+1];
            double edge= sqrt(gray_x[i][j]*gray_x[i][j]+gray_y[i][j]*gray_y[i][j]);
            data[i][j].R=(int)edge;
            data[i][j].G=(int)edge;
            data[i][j].B=(int)edge;
        }
    }
}




