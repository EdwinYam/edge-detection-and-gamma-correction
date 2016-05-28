#ifndef __BMPIMG_H__
#define __BMPIMG_H__
#include <vector>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

static const int headerNum = 15;       //15 elements for header
static const int headerSize[headerNum] = {2,4,4,4,4,4,4,2,2,4,4,4,4,4,4};     //the number of bytes for each element of information
static const string headerInfo[headerNum]
    = {"Identifier","FileSize","Reserved","BitmapDataOffset",
       "BitmapHeaderSize","Width","Height","Planes",
       "BitsPerPixel","Compression","BitmapDataSize","H_Resolution",
       "V_Resolution","UsedColors","ImportantColors"};

class BMPHead{
private:
    char Identifier[2];
    unsigned int    FileSize;
    unsigned int    Reserved;
    unsigned int    BitmapDataOffset;

    unsigned int    BitmapHeaderSize;
    unsigned int    Width;
    unsigned int    Height;
    unsigned short  Planes;
    unsigned short  BitsPerPixel;
    unsigned int    Compression;
    unsigned int    BitmapDataSize;
    unsigned int    H_Resolution;
    unsigned int    V_Resolution;
    unsigned int    UsedColors;
    unsigned int    ImportantColors;
public:
    friend class BMPImg;
    void* pFlag(const int i)const{  //return pointers of flags according to its order(int)
        switch(i){
        default:
        case  0:    return (void*)Identifier;//void* ¬°µL¯S©w«¬ºAªº«ü¼Ð
        case  1:    return (void*)&FileSize;
        case  2:    return (void*)&Reserved;
        case  3:    return (void*)&BitmapDataOffset;
        case  4:    return (void*)&BitmapHeaderSize;
        case  5:    return (void*)&Width;
        case  6:    return (void*)&Height;
        case  7:    return (void*)&Planes;
        case  8:    return (void*)&BitsPerPixel;
        case  9:    return (void*)&Compression;
        case 10:    return (void*)&BitmapDataSize;
        case 11:    return (void*)&H_Resolution;
        case 12:    return (void*)&V_Resolution;
        case 13:    return (void*)&UsedColors;
        case 14:    return (void*)&ImportantColors;
        }
    }
};
class BMPImg{
private:
    BMPHead header;
public:

    struct color{
        char B,G,R;
    };
    color** data;
    int getWidth()const{return header.Width;}
    int getHeight()const{return header.Height;}
    int getPxlNum()const{return header.Width * header.Height;}
    int getBytesPerPixel()const{return header.BitsPerPixel/8;}

    BMPImg(){}
    BMPImg(const string& picPath){loadPic(picPath);}
    ~BMPImg(){delete [] data;}

    bool loadPic(const string& picPath){
        ifstream file( picPath.c_str(), ios::in|ios::binary);
        if(!file){
            cout<<"Failure to open bitmap file.\n";
            return true;
        }
        for(int i=0;i<15;i++){
            file.read((char*)header.pFlag(i),headerSize[i]);
        }
        const int sizey = header.Height;
        const int sizex = header.Width;
        color **arr = new color*[sizey];
        for(int i=0;i<sizey;i++){
            arr[i] = new color[sizex];
        }
        for(int y = 0; y < sizey; y++){
            for(int x = 0; x < sizex; x++){
                char chR,chG,chB;
                file.get(chB).get(chG).get(chR);
                arr[y][x].B = chB;
                arr[y][x].G = chG;
                arr[y][x].R = chR;
            }
        }
        data=arr;
        file.close();
    }
    void printHeader()const{
        for(int i=0;i<headerNum;++i){
            cout<< headerInfo[i]+":";

            if(i==0){
                cout<< header.Identifier[0] << header.Identifier[1];
            }else{
                if(headerSize[i]==4)
                    cout<< *(  (unsigned int*)(header.pFlag(i))  );
                else
                    cout<< *(  (unsigned short*)(header.pFlag(i))  );
            }
            cout<< endl;
        }
    }
    bool gammaCorrection(double gamma);
    bool sobelEdge();
    bool storePic(const string& outPath){
        ofstream file(outPath.c_str(), ios::out|ios::binary);
        for(int i=0;i<15;i++){
            file.write((char*)header.pFlag(i),headerSize[i]);
        }
        const int sizey = header.Height;
        const int sizex = header.Width;
        for(int y = 0; y < sizey; y++){
            for(int x = 0; x < sizex; x++){
                char chR,chG,chB;
                chB = data[y][x].B;
                chG = data[y][x].G;
                chR = data[y][x].R;
                file.put(chB).put(chG).put(chR);
            }
        }
        file.close();
    }

};

#endif // __BMPIMG_H__
