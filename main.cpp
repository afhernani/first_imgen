#include <iostream>
#include "Imagen.h"


using namespace std;

int main()
{
    Imagen i;
    cout <<"abrindo fichero imagen flor.ppm ..."<< endl;
    i.lee("mamita.ppm");
    cout <<"copiando fichero flor2.ppm .." << endl;
    i.save("mamita2.ppm");
    cout << "invertimos imagen flor-invertida.ppm" << endl;
    i.invertir();
    i.save("mamaita-invertida.ppm");
    cout <<"posterizamos la imagen entre 5 valores" << endl;
    cout << "mamita-posterizada.ppm"<< endl;
    i.invertir();
    i.posterizar(5);
    i.save("mamita-posterizada.ppm");
    cout << "end file"<< endl;

    system("pause");
}
