#include "Imagen.h"
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include <cstring>
#include<cmath>

using namespace std;

Imagen::Imagen()
//aqui se llama al contructor de _pixels por defecto
{
    _width = 0;
    _heigh = 0;
    _maxi = 255;
}
Imagen::Imagen(int width, int heigh, int maxi)
:_pixels(width*heigh, maxi)
{
    _width = width;
    _heigh = heigh;
    _maxi = maxi;
}
Imagen::Imagen(int width, int heigh)
:_pixels(width*heigh, 0 )
{
    _width = width;
    _heigh = heigh;
    _maxi = 255;
}
Imagen::Imagen(const Imagen& other)
:_pixels(other._pixels)
{
    _width = other._width;
    _heigh = other._heigh;
    _maxi = other._maxi;
}

int Imagen::Getpixel(int i, int j)const
{
    return _pixels[j*_width +i];
}
void Imagen::Setpixel(int i, int j, int valor){
    _pixels[j*_width + i ] = valor;
}
void Imagen::lee(std::string nombre){
    ifstream f(nombre.c_str());
    if(!f.good()){
        cout <<"no se ha podido habrir el fichero " << nombre << endl;
        return;
    }
    string linea;
    getline(f, linea);
    if(linea != "P2"){
        cout << "formato incorrecto "<<endl;
        return;
    }
    getline(f, linea);
    while(linea[0]=='#'){
        getline(f, linea);
    }

    istringstream S(linea);
    S >>_width >> _heigh;
    f >>_maxi;
    _pixels.resize(_width*_heigh);
    for(int i =0; i<(int)_pixels.size(); i++){
        f>>_pixels[i];
    }
    f.close();
}

void Imagen::save(std::string nombre)const
{
    ofstream f(nombre.c_str());
    if(!f.good()){
        cout << "fichero con algun problema" << endl;
        return;
    }
    f <<"P2" << endl;
    f <<"# escrito por la clase Imagen" << endl;
    f << _width << " " << _heigh << endl;
    f << _maxi << endl;
    for(int i=0; i< (int)_pixels.size(); i++){
        f<< _pixels[i] << ' ';
        if((i%_width) == (_width-1)){
            f << endl;
        }
    }
    f.close();
}

Imagen Imagen::cut(int izq, int arr, int der, int aba) const{
    Imagen T(der-izq, aba-arr);
    for(int i=izq; i< der; i++){
        for(int j = arr; j<aba; j++){
            if((i>=0 && i<_width)&&(j>=0 && j <_heigh)){
            //estamos dentro de la imagen original
                int x = i - izq;
                int y = j - arr;
                T.Setpixel(x,y,Getpixel(i,j));
            }
        }
    }
    return T;
}

//creamos el método pegar en una Imagen
void Imagen::paste( Imagen& I, int izq, int arr){
    if(_maxi<I.maxi()) _maxi=I.maxi();
    //recorremos el bucle de la imagen
    for(int i=0; i<I.width(); i++){
        for(int j=0; j<I.heigh(); j++){
            int x = izq + i;
            int y= arr+j;
            if((x>=0 && x<_width)&&(y>=0 && y <_heigh)){
                Setpixel(x, y, I.Getpixel(i,j));
            }
        }
    }
}

void Imagen::invertir(){
    for(int i =0; i < (int)_pixels.size(); i++){
        _pixels[i]= _maxi - _pixels[i];
    }
}
//esta función redondea el numero.
//double round(double x){return floor(x+0.5);}

void Imagen::posterizar(int niveles){
    for(int i = 0; i< int(_pixels.size()); i++){
        double valor = double(_pixels[i])/double(_maxi)*(niveles-1);
        valor = round(valor);
        _pixels[i]=int(valor*double(_maxi)/(niveles-1));
    }
}
