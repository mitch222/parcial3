=====REQUERIMIENTOS E INSTALACIONES PREVIAS=====
Para el uso correcto del modelo de C++ es necesario tener ciertas herramientas previas,
a continuación se prsentaran los comandos y las configuraciones para el funcionamiento
del modelo.

* Instalación de EIGEN
  sudo apt install libeigen3-dev
  sudo apt update

Creación del enlace simbolico de la biblioteca EIGEN
  ln -sf  /usr/include/eigen3/Eigen Eigen
  ln -sf  /usr/include/eigen3/unsupported unsupported
  sudo apt update

Instalación de BOOST
  sudo apt-get install libboost-all-dev
  sudo apt update
Creación del enlace simbolico de la biblioteca BOOST
  ln -sf /usr/include/boost boost
  sudo apt update

Instalación de CMAKE
  sudo apt install cmake
  sudo apt update
  
=====INSTRUCCIONES=====
Una vez realizado todos lo procedimientos requeridos se podra realizar la instalación 
del modelo.

* Acceder al proyecto
  Primero es necesario tener una terminal que este en la direccion donde 
  se descargo el modelo. Para esto daremos el siguiente comando en una terminal:
    cd [dirección de descarga\Modelo C++]

* Creación de modelo 
  Una vez terminado el paso anterior procederemos a hacer uso del makefile mediante:
    make all
  Se inicializara la creación de los objetos para la el modelo.
  
* Ejecucción del modelo
  Del ultimo paso quedara creado un archivo llamado final, este sera el archivo 
  que ejecutaremos con los paramentros.
  
    ./final [Direccion del data set] [separador] [Header]
   
Cabe aclarar que este modelo solo funciona con el dataset especificado en el repositorio.
   
=====RECOMENDACIONES=====  
* Eliminar el encabezado manualmente del dataset.
* Si se elimino el encabezado, utilizar flase como parametro para header.
  Esto con el fin de tener el mismo resultado que se obtuvo en el desarrollo 
  del modelo.
