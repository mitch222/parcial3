
/*
* Fecha: 21 sept 2022
* Autor: Mitchell Bermin
* Materia: HPC
* Tópico: Implementación de la regresión linear como
* modelo en C++
* Requerimientos:
* - Construir una clase Extraction, que permita
* manipular, extraer y cargar los datos
* - Construir una clase LinearRegression, que permita
* los cálculos de la función de costo, gradiente descendiente
* entre otras.*/

#include <iostream>
#include "ClassExtraction/extractiondata.h"
#include "Regression/linearregression.h"
#include <eigen3/Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <list>
#include <vector>
#include <fstream>

int main(int argc, char* argv[])
{
    /*Se necesitan 3 argumentos de entrada*/
    /* Se crea un objeto del tiop ClasExtraction*/

    ExtractionData ExData(argv[1],argv[2],argv[3]);
    // Se instancia la clase de regresión linear en un objeto
    LinearRegression modeloLR;
    /* Se crea un vector de vectores del tipo string para cargar el objeto ExData lectura*/
    std::vector<std::vector<std::string>> dataframe = ExData.LeerCSV();




    /*Cantidad de filas y columnas*/
    int filas = dataframe.size();
    int columnas = dataframe[0].size();
    /* Se crea una ,atriz Eigen, para ingresar los valores a esa matriz*/
    Eigen::MatrixXd matData = ExData.CSVtoEigen(dataframe, filas, columnas);



    //Eliminacion datos no numericos
    Eigen::MatrixXd m;

    m.conservativeResize(matData.rows(), 4);
    m.col(0) = matData.col(3);
    m.col(1) = matData.col(4);
    m.col(2) = matData.col(9);
    m.col(3) = matData.col(11);

    //Se normaliza la matriz de datos
    Eigen::MatrixXd mat_norm = ExData.Norm(m);
    /* Se dividen en datos de entrenamiento y datos de prueba*/
    Eigen::MatrixXd X_train, y_train, X_test, y_test;
    std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> div_datos = ExData.TrainTestSplit(mat_norm, 0.8);

    // Se descomprime la tupla en cuatro conjuntos
    std::tie(X_train, y_train, X_test, y_test) = div_datos;

    /* Se crean vectores auxiliares pra prueba y entrenamiento inicializados en 1*/
    Eigen::VectorXd V_train = Eigen::VectorXd::Ones(X_train.rows());
    Eigen::VectorXd V_test = Eigen::VectorXd::Ones(X_test.rows());

    /* Se redimensiona la matriz de entrenamiento y prueba para ser ajustadas
     * a los vectores auxiliares anteriores*/

    X_train.conservativeResize(X_train.rows(), X_train.cols()+1);
    X_train.col(X_train.cols()-1) = V_train;
    X_test.conservativeResize(X_test.rows(), X_test.cols()+1);
    X_test.col(X_test.cols()-1) = V_test;

    /* Se crea el vector de coeficientes theta*/
    Eigen::VectorXd theta = Eigen::VectorXd::Zero(X_train.cols());

    /* Se establece que el alpha como ratio de aprendizaje es de tipo flotante*/
    float alpha = .01;
    int num_iter = 1000;

    // Se crea un vector para alamacenar las thetas de salida (parametros m y b)
     Eigen::VectorXd thetas_out;
     // Se crea un vector sencillo (std) de flotantes para alamacenar los valores del costo
     std::vector<float> costo;
     // Se cálcula el gradiente descendiente
     std::tuple<Eigen::VectorXd, std::vector<float>> g_descendiente = modeloLR.GD(X_train,
                                                                                  y_train,
                                                                                  theta,
                                                                                  alpha,
                                                                                  num_iter);

     // Se desempaqueta el gradiente
     std::tie(thetas_out,costo) = g_descendiente;
     // Se almacenan los valores de thetas y costos en un fichero para posteriormente ser visualizados
     //ExData.VectorToFile(costo, "costos.txt");
     //ExData.EigenToFile(thetas_out, "thetas.txt");

     /* Se extrae el promedio de la matriz de entrada*/
     auto prom_data = ExData.Promedio(m);
     // Se extraen los valores de las variables independientes
     auto var_prom_independientes = prom_data(0,3);
     // Se escalan los datos
     auto datos_escalados = m.rowwise()-m.colwise().mean();
     // Se extrae la desviación estándar de los datos escalados
     auto desv_stand = ExData.DevStand(datos_escalados);
     // Se extraen los valores de las variables independientes
     auto var_desv_independientes = desv_stand(0,3);
     // Se crea una matriz para almacenar los valores estimados de entrenamiento

     Eigen::MatrixXd y_train_hat = (X_train * thetas_out * var_desv_independientes).array() + var_prom_independientes;

     // Matriz para los valores reales de y

     Eigen::MatrixXd y = m.col(3).topRows(5907);
     // Se revisa que tan bueno fue el modelo a través de la métrica de rendiemiento
     float metrica_r2 = modeloLR.R2_score(y,y_train_hat);
     std::cout << "Métrica R2 Entrenamiento: " << metrica_r2 << std::endl;

     Eigen::MatrixXd y_test_hat = (X_test * thetas_out * var_desv_independientes).array() + var_prom_independientes;

     y = m.col(3).bottomRows(1477);
     float metrica_r2t = modeloLR.R2_score(y,y_test_hat);

     std::cout << "Métrica R2 Prueba : " << metrica_r2t << std::endl;
     return EXIT_SUCCESS;
}
