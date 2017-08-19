#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//----------------
// abrir simples ficheros
//----------------

//#include <iostream>
//#include <fstream>
//using namespace std;

int main_entrada_salida() {
   char cadena[128];
   // Crea un fichero de salida
   ofstream fs("nombre.txt");

   // Enviamos una cadena al fichero de salida:
   fs << "Hola, mundo" << endl;
   // Cerrar el fichero,
   // para luego poder abrirlo para lectura:
   fs.close();

   // Abre un fichero de entrada
   ifstream fe("nombre.txt");

   // Leeremos mediante getline, si lo hiciéramos
   // mediante el operador << sólo leeríamos
   // parte de la cadena:
   fe.getline(cadena, 128);

   cout << cadena << endl;

   return 0;
}
//----------------
// lectura simple de fichero
//----------------

//#include <iostream>
//#include <fstream>
//using namespace std;

int main_lee_fichero() {
   char cadena[128];
   ifstream fe("streams.cpp");

   while(!fe.eof()) {
      fe >> cadena;
      cout << cadena << endl;
   }
   fe.close();

   return 0;
}

//----------------
// ficheros binarios
//----------------
//#include <iostream>
//#include <fstream>
//#include <cstring>

//using namespace std;


struct tipoRegistro {
   char nombre[32];
   int edad;
   float altura;
};

int main_file() {
   tipoRegistro pepe;
   tipoRegistro pepe2;
   ofstream fsalida("prueba.dat",
      ios::out | ios::binary);

   strcpy(pepe.nombre, "Jose Luis");
   pepe.edad = 32;
   pepe.altura = 1.78;

   fsalida.write(reinterpret_cast<char *>(&pepe),
      sizeof(tipoRegistro));
   fsalida.close();

   ifstream fentrada("prueba.dat",
      ios::in | ios::binary);

   fentrada.read(reinterpret_cast<char *>(&pepe2),
      sizeof(tipoRegistro));
   cout << pepe2.nombre << endl;
   cout << pepe2.edad << endl;
   cout << pepe2.altura << endl;
   fentrada.close();

   return 0;
}


/*
fichero de acceso aleatorio
*/
//#include <fstream>
//using namespace std;

int main_ale() {
   int i;
   char mes[][20] = {"Enero", "Febrero", "Marzo",
      "Abril", "Mayo", "Junio", "Julio", "Agosto",
      "Septiembre", "Octubre", "Noviembre",
      "Diciembre"};
   char cad[20];

   ofstream fsalida("meses.dat",
      ios::out | ios::binary);

   // Crear fichero con los nombres de los meses:
   cout << "Crear archivo de nombres de meses:" << endl;
   for(i = 0; i < 12; i++)
      fsalida.write(mes[i], 20);
   fsalida.close();

   ifstream fentrada("meses.dat", ios::in | ios::binary);

   // Acceso secuencial:
   cout << "\nAcceso secuencial:" << endl;
   fentrada.read(cad, 20);
   do {
      cout << cad << endl;
      fentrada.read(cad, 20);
   } while(!fentrada.eof());

   fentrada.clear();
   // Acceso aleatorio:
   cout << "\nAcceso aleatorio:" << endl;
   for(i = 11; i >= 0; i--) {
      fentrada.seekg(20*i, ios::beg);
      fentrada.read(cad, 20);
      cout << cad << endl;
   }

   // Calcular el número de elementos
   // almacenados en un fichero:
   // ir al final del fichero
   fentrada.seekg(0, ios::end);
   // leer la posición actual
   int pos;
   pos = fentrada.tellg();
   // El número de registros es el tamaño en
   // bytes dividido entre el tamaño del registro:
   cout << "\nNúmero de registros: " << pos/20 << endl;
   fentrada.close();

   return 0;
}

//--------------------
//fichero simultaneo de entrada y salida
//--------------------
//#include <fstream>
//using namespace std;

int main_simultaneo() {
   char l;
   long i, lon;
   fstream fich("prueba.dat", ios::in |
      ios::out | ios::trunc | ios::binary);

   fich << "abracadabra" << flush;

   fich.seekg(0L, ios::end);
   lon = fich.tellg();
   for(i = 0L; i < lon; i++) {
      fich.seekg(i, ios::beg);
      fich.get(l);
      if(l == 'a') {
         fich.seekp(i, ios::beg);
         fich << 'e';
      }
   }
   cout << "Salida:" << endl;
   fich.seekg(0L, ios::beg);
   for(i = 0L; i < lon; i++) {
      fich.get(l);
      cout << l;
   }
   cout << endl;
   fich.close();

   return 0;
}

// -------------------------
// sobrecarga de operadores
//--------------------------
//#include <iostream>
#include <cstring>
using namespace std;

class Registro {
  public:
   Registro(char *, int, char *);
   const char* LeeNombre() const {return nombre;}
   int LeeEdad() const {return edad;}
   const char* LeeTelefono() const {return telefono;}

  private:
   char nombre[64];
   int edad;
   char telefono[10];
};

Registro::Registro(char *n, int e, char *t) : edad(e) {
   strcpy(nombre, n);
   strcpy(telefono, t);
}

ostream& operator<<(ostream &os, Registro& reg) {
   os << "Nombre: " << reg.LeeNombre() << "\nEdad: " <<
      reg.LeeEdad() << "\nTelefono: " << reg.LeeTelefono();

   return os;
}

int main_sobrecarga() {
   Registro Pepe((char*)"José", 32, (char*)"61545552");

   cout << Pepe << endl;

   return 0;
}

//-----------------------
/*
Comprobar estado de un stream
^
Hay varios flags de estado que podemos usar para comprobar el estado
en que se encuentra un stream.
Concretamente nos puede interesar si hemos alcanzado el fin de fichero,
o si el stream con el que estamos trabajando está en un estado de error.
La función principal para esto es good(), de la clase ios.
Después de ciertas operaciones con streams, a menudo no es mala idea
comprobar el estado en que ha quedado el stream. Hay que tener en cuenta
que ciertos estados de error impiden que se puedan seguir realizando
operaciones de entrada y salida.
Otras funciones útiles son fail(), eof(), bad(), rdstate() o clear().
En el ejemplo de archivos de acceso aleatorio hemos usado clear() para
eliminar el bit de estado eofbit del fichero de entrada, si no hacemos eso,
las siguientes operaciones de lectura fallarían.
Otra condición que conviene verificar es la existencia de un fichero.
En los ejemplos anteriores no ha sido necesario, aunque hubiera sido
conveniente, verificar la existencia, ya que el propio ejemplo crea el
fichero que después lee.
Cuando vayamos a leer un fichero que no podamos estar seguros de que
existe, o que aunque exista pueda estar abierto por otro programa,
debemos asegurarnos de que nuestro programa tiene acceso al stream.
Por ejemplo:
*/
//#include <fstream>
//using namespace std;
//--------------------

int main_previos_opne() {
   char mes[20];
   ifstream fich("meses1.dat", ios::in | ios::binary);

   // El fichero meses1.dat no existe, este programa es
   // una prueba de los bits de estado.

   if(fich.good()) {
      fich.read(mes, 20);
      cout << mes << endl;
   }
   else {
      cout << "Fichero no disponible" << endl;
      if(fich.fail()) cout << "Bit fail activo" << endl;
      if(fich.eof())  cout << "Bit eof activo" << endl;
      if(fich.bad())  cout << "Bit bad activo" << endl;
   }
   fich.close();

   return 0;
}

//----------

//#include <fstream>
//using namespace std;

int main_previos() {
   char mes[20];
   ofstream fich1("meses.dat", ios::out | ios::binary);
   ifstream fich("meses.dat", ios::in | ios::binary);

   // El fichero meses.dat existe, pero este programa
   // intenta abrir dos streams al mismo fichero, uno en
   // escritura y otro en lectura. Eso no es posible, se
   // trata de una prueba de los bits de estado.

   fich.read(mes, 20);
   if(fich.good())
      cout << mes << endl;
   else {
      cout << "Error al leer de Fichero" << endl;
      if(fich.fail()) cout << "Bit fail activo" << endl;
      if(fich.eof())  cout << "Bit eof activo" << endl;
      if(fich.bad())  cout << "Bit bad activo" << endl;
   }
   fich.close();
   fich1.close();

   return 0;
}
