#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <igvCilindro.h>

#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"


// M�todos constructores

/**
 * Constructor por defecto
 */
igvEscena3D::igvEscena3D()
{
    // TODO: Apartado B: Inserta el c�digo para crear un cilindro
    //malla = new igvCilindro(1,1,40,5);

    try {
        modeloImportado = cargarOBJ("../Sniper_Rifle.obj");
        std::cout << "Modelo cargado correctamente." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error al cargar el archivo: " << e.what() << std::endl;
    }
}

/**
 * Destructor
 */
igvEscena3D::~igvEscena3D()
{
    if (malla != nullptr)
    {
        delete malla;
        malla = nullptr;
    }
}


// M�todos p�blicos

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glBegin(GL_LINES);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glBegin(GL_LINES);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

// Dibuja un cilindro (asumiendo que está a lo largo del eje Y después de la transformación).
void dibujaCilindro(float radio, float altura) {
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, radio, radio, altura, 30, 30);
    gluDeleteQuadric(quad);
}

/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar(void)
{
    GLfloat color_malla[] = {0, 0.25,0};
    // crear luces
    GLfloat luz0[4] = {5, 5, 5, 1}; // luz puntual para visualizar el cubo

    glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
    glEnable(GL_LIGHT0);

    // se pintan los ejes
    if (ejes) pintar_ejes();

    // crear el modelo
    glPushMatrix(); // guarda la matriz de modelado

    glTranslatef(0,0,rotX);
    //glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);


    //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena
    glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);


    // Apartado B: la siguiente llamada hay que sustituirla por la llamada al método visualizar de la malla
    /*GLUquadric* cyl = gluNewQuadric();
    gluCylinder(cyl, 1, 1, 1, 20, 5);
    gluDeleteQuadric(cyl);
    cyl=nullptr;*/
    //malla->visualizar();

/*
    //Cabeza
    glPushMatrix();
    glTranslatef(0.0, 1.25, 0.0); // Posiciona la cabeza por encima del cuerpo
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();

    // Manos
    glPushMatrix();
    glTranslatef(0.25, 0.57, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, 0.57, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    // Cuerpo
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0);
    glScalef(0.4, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Brazos
    glPushMatrix();
    glTranslatef(0.25, 1.0, 0.0); // Posición inicial
    glRotatef(90,1,0,0);
    dibujaCilindro(0.05, 0.4); // Radio, Altura
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, 1.0, 0.0); // Posición inicial
    glRotatef(90,1,0,0);
    dibujaCilindro(0.05, 0.4);
    glPopMatrix();


    // Piernas
    glPushMatrix();
    glTranslatef(0.1, 0.03, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    dibujaCilindro(0.06, 0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0.03, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    dibujaCilindro(0.06, 0.28);
    glPopMatrix();

    // Pies
    glPushMatrix();
    glTranslatef(0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25); // Ancho (X), Altura (Y), Largo (Z)
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25); // Ancho (X), Altura (Y), Largo (Z)
    glutSolidCube(1.0);
    glPopMatrix();





    if(modeloImportado!=nullptr) {
        GLfloat color_pieza[] = { 0, 0, 0 };
        glMaterialfv ( GL_FRONT, GL_EMISSION, color_pieza );

        glPushMatrix();
        glTranslatef(0.25,0.25,0);
        glRotatef(90,1,0,0);
        glRotatef(-90,0,1,0);
        glScalef(0.1,0.1,0.1);
        modeloImportado->visualizar();
        glPopMatrix();
    }
*/

    // --- Variables de rotación (Debes definirlas en tu scope, ej. globalmente) ---
      // Rotación adicional del arma en el eje Y
// --------------------------------------------------------------------------

/* FUNCIONAAAAAA
// Cabeza
    glPushMatrix();
    glTranslatef(0.0, 1.25, 0.0);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();

// Cuerpo (sin cambios)
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0);
    glScalef(0.4, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

// --- Brazo Izquierdo (Sin Arma) y Mano Izquierda ---
    glPushMatrix();
// 1. Traslada al hombro izquierdo (punto de pivote del brazo)
    glTranslatef(-0.25, 1.0, 0.0);
// 2. Aplica la rotación del brazo en X
    glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);

    // Brazo Izquierdo (Cilindro)
    glPushMatrix();
    // 3. Traslada al centro del cilindro (o donde sea que empiece a dibujarse)
    glRotatef(90, 1, 0, 0); // Rotación inicial para alineación
    dibujaCilindro(0.05, 0.4);
    glPopMatrix();

    // Mano Izquierda (Esfera)
    glPushMatrix();
    // 4. Traslada desde el hombro hasta el centro de la mano.
    // La mano se mueve con la rotación del padre (el brazo).
    glTranslatef(0.0, -0.4, 0.0); // Mover hacia abajo por la longitud del brazo (0.4)
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    glPopMatrix(); // Restaura la matriz del Brazo Izquierdo

// --- Brazo Derecho (Con Arma) y Mano Derecha ---
    glPushMatrix();
// 1. Traslada al hombro derecho (punto de pivote del brazo)
    glTranslatef(0.25, 1.0, 0.0);
// 2. Aplica la rotación del brazo en X (aplica a brazo, mano y arma)
    glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);

    // Brazo Derecho (Cilindro)
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.05, 0.4);
    glPopMatrix();

    // Mano Derecha (Esfera)
    glPushMatrix();
    // 3. Traslada desde el hombro hasta el centro de la mano.
    glTranslatef(0.0, -0.4, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    // Arma (Modelo Importado)
    if(modeloImportado!=nullptr) {
        GLfloat color_pieza[] = { 0, 0, 0 };
        glMaterialfv ( GL_FRONT, GL_EMISSION, color_pieza );

        glPushMatrix();
        // 4. Posiciona el arma al final de la mano (asumiendo que el brazo mide 0.4)
        glTranslatef(0.0, -0.43, 0.0);

        // 5. APLICA LA ROTACIÓN EXTRA DEL ARMA (Eje X e Y)
        glRotatef(anguloArmaZ, 0.0, 0.0, 1.0);
        glRotatef(anguloArmaX, 1.0, 0.0, 0.0);

        // 6. Rotaciones y escalas específicas del modelo
        glRotatef(90,1,0,0);
        glRotatef(-90,0,1,0);
        glScalef(0.1,0.1,0.1);
        modeloImportado->visualizar();
        glPopMatrix();
    }
    glPopMatrix(); // Restaura la matriz del Brazo Derecho

// --- Resto del cuerpo (sin cambios en la lógica de rotación) ---
    glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
// Piernas (sin cambios)
    glPushMatrix();
    glTranslatef(0.1, 0.03, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    dibujaCilindro(0.06, 0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0.03, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    dibujaCilindro(0.06, 0.28);
    glPopMatrix();

// Pies (sin cambios)
    glPushMatrix();
    glTranslatef(0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix(); // restaura la matriz de modelado

    */



// Cabeza
    glPushMatrix();
    glTranslatef(0.0, 1.25, 0.0);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();

    // Cuerpo (sin cambios)
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0);
    glScalef(0.4, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

// --- Brazo Izquierdo (Sin Arma) y Mano Izquierda ---
    glPushMatrix();
// 1. Traslada al hombro izquierdo (punto de pivote del brazo)
    glTranslatef(-0.25, 1.0, 0.0);
// 2. Aplica la rotación del brazo en X (Hombro)
    glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);

    // --- BRAZO SUPERIOR IZQUIERDO ---
    glPushMatrix();
    glRotatef(90, 1, 0, 0); // Alineación cilindro
    dibujaCilindro(0.05, 0.2); // Longitud reducida a la mitad (0.2)
    glPopMatrix();

    // --- ARTICULACIÓN CODO IZQUIERDO ---
    glTranslatef(0.0, -0.2, 0.0); // Traslada al final del brazo superior

    // Lógica de límite del codo (Vida real: 0 a 130 grados)
    //float codoIzq = anguloCodo;
    //if(codoIzq < 0) codoIzq = 0;
    //if(codoIzq > 130) codoIzq = 130;
    glRotatef(anguloCodo, 1.0, 0.0, 0.0); // Rotación del antebrazo

    // --- ANTEBRAZO IZQUIERDO ---
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.045, 0.2); // Segundo cilindro (un poco más fino)
    glPopMatrix();

    // Mano Izquierda (Esfera)
    glPushMatrix();
    // 4. Traslada desde el codo hasta el final del antebrazo
    glTranslatef(0.0, -0.2, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    glPopMatrix(); // Restaura la matriz del Brazo Izquierdo

// --- Brazo Derecho (Con Arma) y Mano Derecha ---
    glPushMatrix();
// 1. Traslada al hombro derecho
    glTranslatef(0.25, 1.0, 0.0);
// 2. Aplica la rotación del brazo en X (Hombro)
    glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);

    // --- BRAZO SUPERIOR DERECHO ---
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.05, 0.2); // Longitud 0.2
    glPopMatrix();

    // --- ARTICULACIÓN CODO DERECHO ---
    glTranslatef(0.0, -0.2, 0.0); // Traslada al final del brazo superior

    // Lógica de límite del codo
    //float codoDer = anguloCodo;
    //if(codoDer < 0) codoDer = 0;
    //if(codoDer > 130) codoDer = 130;
    glRotatef(anguloCodo, 1.0, 0.0, 0.0); // Rotación del antebrazo

    // --- ANTEBRAZO DERECHO ---
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.045, 0.2); // Longitud 0.2
    glPopMatrix();

    // Mano Derecha (Esfera)
    glPushMatrix();
    // 3. Traslada desde el codo hasta la mano
    glTranslatef(0.0, -0.2, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    // Arma (Modelo Importado)
    if(modeloImportado!=nullptr) {
        GLfloat color_pieza[] = { 0, 0, 0 };
        glMaterialfv ( GL_FRONT, GL_EMISSION, color_pieza );

        glPushMatrix();
        // 4. Posiciona el arma al final de la mano (acumulado: -0.2 brazo -0.2 antebrazo = -0.4 total)
        glTranslatef(0.0, -0.23, 0.0); // -0.2 del codo + -0.03 ajuste mano

        // IMPORTANTE: Como estamos dentro de la matriz del codo, el arma ya sigue al antebrazo.

        // 5. APLICA LA ROTACIÓN EXTRA DEL ARMA (Eje X e Y)
        glRotatef(anguloArmaZ, 0.0, 0.0, 1.0); // Ajusté a Z según tu código anterior, o Y según petición
        glRotatef(anguloArmaX, 1.0, 0.0, 0.0);

        // 6. Rotaciones y escalas específicas del modelo
        glRotatef(90,1,0,0);
        glRotatef(-90,0,1,0);
        glScalef(0.1,0.1,0.1);
        modeloImportado->visualizar();
        glPopMatrix();
    }
    glPopMatrix(); // Restaura la matriz del Brazo Derecho

// --- Resto del cuerpo (sin cambios en la lógica de rotación) ---
    glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
// Piernas (sin cambios)
    glPushMatrix();
    glTranslatef(0.1, 0.03, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    dibujaCilindro(0.06, 0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0.03, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    dibujaCilindro(0.06, 0.28);
    glPopMatrix();

// Pies (sin cambios)
    glPushMatrix();
    glTranslatef(0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix(); // restaura la matriz de modelado


}

/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes()
{
    return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes(bool _ejes)
{
    ejes = _ejes;
}

igvMallaTriangulos* igvEscena3D::cargarOBJ(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo OBJ: " + filename);
    }

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
        else if (prefix == "f") {
            unsigned int v1, v2, v3;
            std::string s1, s2, s3;
            iss >> s1 >> s2 >> s3;

            auto parseIndex = [](const std::string& s) {
                std::stringstream ss(s);
                unsigned int idx;
                ss >> idx;
                return idx - 1; // los OBJ empiezan en 1
            };

            v1 = parseIndex(s1);
            v2 = parseIndex(s2);
            v3 = parseIndex(s3);

            indices.push_back(v1);
            indices.push_back(v2);
            indices.push_back(v3);
        }
    }

    file.close();

    // Crear arrays planos para el constructor
    float* vertexArray = new float[vertices.size()];
    std::copy(vertices.begin(), vertices.end(), vertexArray);

    unsigned int* indexArray = new unsigned int[indices.size()];
    std::copy(indices.begin(), indices.end(), indexArray);

    long int numVertices = vertices.size() / 3;
    long int numTriangulos = indices.size() / 3;

    return new igvMallaTriangulos(numVertices, vertexArray,
                                  numTriangulos, indexArray);
}