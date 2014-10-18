//
//  main.cpp
//  Practica1
//
//  Created by Victor on 03/10/14.
//  Copyright (c) 2014 Victor. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct indice {
    int size;
    float* data;
};

void seleccionarOperacion(vector<string>, string);
indice create_vector(int n, float* data);
void destroy_vector(indice v);
void print(indice v);
float dot(indice v1, indice v2);
float norm(indice v);
void normalize(indice v);
indice add(indice v1, indice v2);
indice sub(indice v1, indice v2);
void incr(indice* source, indice* other);
void decr(indice* source, indice* other);
float distance(indice v1, indice v2);
void netejar_vector(indice* vector, int mida);


//******************UTILITIES FUNCTIONS***************************

void netejar_vector(indice* vector, int mida) {
    for (int i = 0; i < mida; i++)
        vector->data[i] = 0;
}

vector<string> leerOperaciones(string cadena) {

    vector<string> operations;
    int i, j = 0;
    for (i = 0; i < cadena.length(); i++)
        if (cadena.at(i) == ' ') {
            operations.push_back(cadena.substr(j, i - j));
            j = (i) + 1;
        }

    operations.push_back(cadena.substr(j, i - j));

    return operations;
}

void seleccionarOperacion(vector<string> operacion, indice index[]) {

    string funciones[9] = {"+ ", "- ", "print ", "dot ", "norm ", "normalize ", "incr ", "decr ", "distance "};

    int function = 0, aux = 0, op1 = -1, op2 = -1, index1 = 0, index2 = 0, i, k;

    for (i = 0; i < operacion.size(); i++)
        for (int j = 0; j < operacion[j].length(); j++) {
            if (operacion[i].at(j) == 'v' && aux == 0) {
                index1 = (int) operacion[i].at(j + 1) - 49;
                aux++;
                op1 = i;
            } else if (operacion[i].at(j) == 'v' && aux == 1) {
                index2 = (int) operacion[i].at(j + 1) - 49;
                aux = 0;
                op2 = i;
            }
            function = (op1 == 0) ? 1 : 0;
        }
    cout<< operacion[function] << endl;
    for (k = 0; k < 9; k++) {
        if (strcmp(funciones[k],operacion[function]) == 0){
            cout << "if" << endl;
            switch (k) {
                case 0:
                    cout << "entrando al add";
                    index[index1] = add(index[index1], index[index2]);
                    break;
                case 1:
                    cout << "Entrando al sub";
                    index[index1] = sub(index[index1], index[index2]);
                    break;
                case 2:
                    print(index[index1]);
                    break;
                case 3:
                    cout << "Resultado operacion dot: " << dot(index[index1], index[index2]) << endl;
                    break;
                case 4:
                    cout << "Resultado operacion dot: " << norm(index[index1]) << endl;
                    break;
                case 5:
                    //normalize(index[index1]);
                    break;
                case 6:
                    incr(&index[index1], &index[index2]);
                    break;
                case 7:
                    incr(&index[index1], &index[index2]);
                    break;
                case 8:
                    //cout << "Resultado operacion dot: " << distance(index[index1], index[index2]) << endl;
                    break;
            }
        }
    }
}


//********************BASICS FUNCTIONS*****************************

indice* create_vector(int n) {
    
    char c = ' ', d = ' ';
    float f = 0.0;
    int cont;
    indice* index = (struct indice*) malloc(n * sizeof (struct indice));

    for (int i = 0; i < n; i++) {
        index[i].data = (float*) malloc(sizeof (float));

        scanf("%c", &d);
        cont = 0;
        c = ',';

        while (c == ',') {

            index[i].data = (float*) realloc(index[i].data, sizeof (float));

            scanf("%f%c", &f, &c);

            index[i].data[cont] = f;

            if (c == ',')
                cont++;
        }
        getchar();
        index[i].size = cont + 1;
    }
    return index;
}

void destroy_vector(indice* v) {
    free(v);
}

void print(indice v) {
    
    cout << "[";
    for (int i = 0; i < v.size; i++) {
        if (i != v.size)
            cout << v.data[i] << ", ";
        else
            cout << v.data[i] << "]";
    }
}

//********************INTERMIDIATE FUNCTIONS*****************************

float dot(indice v1, indice v2) {
    
    double product = 0;
    
    for (int i = 0; i < v1.size; i++)
        for (int j = 0; j < v2.size; i++)
            product += (v1.data[i]) * (v2.data[i]);
    
    return product;
}

float norm(indice v) {
    float norma = 0;

    for (int i = 0; i < v.size; i++) {
        //norma += pow(v.data[i]);
    }
    norma = sqrt(norma);

    return norma;
}

void normalize(indice* v) {

}

//********************HARD FUNCTIONS*****************************

/*En les  funcions add i sub reutilitzem les funcions de incr i decr*/

indice add(indice v1, indice v2) {

    indice index;
    int mida = (v1.size > v2.size) ? v1.size : v2.size;

    index.data = (float*) malloc(sizeof (float)*mida);

    netejar_vector(&index, mida); 
    //Netejem el vector per si accedeix a una zona de memoria on hi ha bruticia

    incr(&index, &v1);
    incr(&index, &v2);

    index.size = mida;

    return index;
}

indice sub(indice v1, indice v2) {

    indice index;
    int mida = (v1.size > v2.size) ? v1.size : v2.size;

    index.data = (float*) malloc(sizeof (float)*mida);

    netejar_vector(&index, mida);

    decr(&index, &v1);
    decr(&index, &v2);

    index.size = mida;

    return index;
}

/* En les funcions de incr i decr
 * Agafem el nombre més petit per fer les sumes.
 * Si escribim el petit ja quedarà bé i el gran també
 */

void incr(indice* source, indice* other) {
    int mida = (source->size < other->size) ? source->size : other->size;

    for (int i = 0; i < mida; i++)
        source->data[i] = source->data[i] + other->data[i];
}

void decr(indice* source, indice* other) {
    int mida = (source->size < other->size) ? source->size : other->size;

    for (int i = 0; i < mida; i++)
        source->data[i] = source->data[i] - other->data[i];
}

float distance(indice* v1, indice* v2) {

    return 0.0;
}

int main(int argc, const char * argv[]) {
    struct indice *index = NULL;
    int n = 0;
    string cadena;
    vector<string> operaciones;

    scanf("%d", &n);
    getchar();

    index = create_vector(n);

    for (getline(cin, cadena); cin && cadena != ""; getline(cin, cadena)) {
        //cout << cadena << endl;
        operaciones = leerOperaciones(cadena);


        //cout << operaciones[0] << endl;
        //cout << operaciones[1] << endl;
        //cout << operaciones[2] << endl;
        seleccionarOperacion(operaciones, index);
        operaciones.clear();

    }
    //print(index);

    //destroy_vector(index);

    return 0;
}
