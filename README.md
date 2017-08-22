# first_imgen

trabajando con imagen formato .pgm y .ppm con c++

Esta aplicación es para trabajar con imagenes de formato Netpbm.
portable pixmap format (ppm), the portable gray map format (pgm)
trabajando con ellos como un fichero plano ascii de texto.
consultar en wikii para este tipo de formato.

se hace uso de Gim para transformar una imagen a este tipo de 
formato ppm, guardándolo como texto ascii.

Se desarrolla la Clase Imagen con varias funciones para trabajar
con este tipo de fichero. cargarla, guardarla, clonar, copiar, pegar
porciones, invertir valores de colores y posterizar imagen en niveles.
La clase pixel complementa a la clase imagen, siendo una estructura
que guarda los valores de cada pixel en una matriz unidireccional dentro
de la clase Imagen.

Se ha desarrollado una biblioteca cout, para facilitar la lectura de 
los datos extraídos de fichero, con objeto de simplificar los metodos
de lectura. Aunque no hace falta otra para guardar datos a ficheros, pues
el método es más simple.

Se ha extraído esto, de los ejemplos: "clase Imagen 1 (constructores getpixel
setpixel).flv " de youtube. Todo esto en cuanto a la funcionalidad de la
clase Imagen.