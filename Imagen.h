#ifndef IMAGEN_H
#define IMAGEN_H

#include <vector>
#include<string>
#include<cstring>

struct Pixel{
    int _r, _g, _b;
    Pixel(){_r=0;_g=0;_b=0;}
    Pixel(int r, int g, int b){
        _r=r; _g=g; _b=b;
    }
    void invertir(int maxi);
    void posterizar(int maxi, int niveles);
};

class Imagen
{
    std::vector<Pixel> _pixels;
    int _width, _heigh, _maxi;
    public:
        Imagen();
        Imagen(int width, int heigh);
        Imagen(int width, int heigh, int maxi);
        Imagen(const Imagen& other);
        Pixel Getpixel(int i, int j)const;
        void Setpixel(int i, int j, Pixel valor);
        void lee(std::string nombre);
        void save(std::string nombre)const;
        int width(){return _width;} //devuelve el ancho
        int heigh(){ return _heigh;}//devuelve el alto
        int maxi(){return _maxi;} //devuelve el maximo
        Imagen cut(int izq, int arr, int der, int aba) const;
        void paste( Imagen& I, int izq, int arr);
        void invertir();
        void posterizar(int niveles);
};

#endif // IMAGEN_H
