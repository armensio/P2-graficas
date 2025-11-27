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

// Constructor por defecto
igvEscena3D::igvEscena3D()
{
    try {
        modeloImportado = cargarOBJ("../Sniper_Rifle.obj");
        std::cout << "Modelo cargado correctamente." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error al cargar el archivo: " << e.what() << std::endl;
    }
}

// Destructor
igvEscena3D::~igvEscena3D()
{
    if (malla != nullptr) {
        delete malla;
        malla = nullptr;
    }
}

// Método para pintar los ejes coordenados
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

// Dibuja un cilindro
void dibujaCilindro(float radio, float altura) {
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, radio, radio, altura, 30, 30);
    gluDeleteQuadric(quad);
}

// Convierte un ID de parte a un color RGB único
void idAColor(PartesCuerpo id) {
    unsigned char r = ((id >> 0) & 0xFF);
    unsigned char g = ((id >> 8) & 0xFF);
    unsigned char b = ((id >> 16) & 0xFF);
    glColor3ub(r, g, b);
}

// Dibuja el cuerpo completo (versión normal para visualización)
void igvEscena3D::dibujarCuerpoCompleto()
{
    GLfloat color_malla[] = {0, 0.25, 0};
    glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);

    // Cabeza
    glPushMatrix();
    glTranslatef(0.0, 1.25, 0.0);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();

    // Cuerpo
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0);
    glScalef(0.4, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // --- Brazo Izquierdo ---
    glPushMatrix();
    glTranslatef(-0.25, 1.0, 0.0);
    glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);

    // Brazo Superior Izquierdo
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.05, 0.2);
    glPopMatrix();

    // Articulación Codo Izquierdo
    glTranslatef(0.0, -0.2, 0.0);
    glRotatef(anguloCodo, 1.0, 0.0, 0.0);

    // Antebrazo Izquierdo
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.045, 0.2);
    glPopMatrix();

    // Mano Izquierda
    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    glPopMatrix(); // Fin Brazo Izquierdo

    // --- Brazo Derecho ---
    glPushMatrix();
    glTranslatef(0.25, 1.0, 0.0);
    glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);

    // Brazo Superior Derecho
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.05, 0.2);
    glPopMatrix();

    // Articulación Codo Derecho
    glTranslatef(0.0, -0.2, 0.0);
    glRotatef(anguloCodo, 1.0, 0.0, 0.0);

    // Antebrazo Derecho
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    dibujaCilindro(0.045, 0.2);
    glPopMatrix();

    // Mano Derecha
    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    glutSolidSphere(0.05, 30, 30);
    glPopMatrix();

    // Arma
    if(modeloImportado != nullptr) {
        GLfloat color_pieza[] = {0, 0, 0};
        glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

        glPushMatrix();
        glTranslatef(0.0, -0.23, 0.0);
        glRotatef(anguloArmaZ, 0.0, 0.0, 1.0);
        glRotatef(anguloArmaX, 1.0, 0.0, 0.0);
        glRotatef(90, 1, 0, 0);
        glRotatef(-90, 0, 1, 0);
        glScalef(0.1, 0.1, 0.1);
        modeloImportado->visualizar();
        glPopMatrix();
    }

    glPopMatrix(); // Fin Brazo Derecho

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
    glScalef(0.1, 0.05, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0.1);
    glScalef(0.1, 0.05, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Dibuja una parte específica con su color de picking
void igvEscena3D::dibujarParteConColor(PartesCuerpo parte)
{
    // Desactivar iluminación para modo picking
    glDisable(GL_LIGHTING);
    idAColor(parte);

    switch(parte) {
        case BRAZO_SUP_IZQ:
            glPushMatrix();
            glTranslatef(-0.25, 1.0, 0.0);
            glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);
            glRotatef(90, 1, 0, 0);
            dibujaCilindro(0.05, 0.2);
            glPopMatrix();
            break;

        case BRAZO_INF_IZQ:
            glPushMatrix();
            glTranslatef(-0.25, 1.0, 0.0);
            glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);
            glTranslatef(0.0, -0.2, 0.0);
            glRotatef(anguloCodo, 1.0, 0.0, 0.0);
            glRotatef(90, 1, 0, 0);
            dibujaCilindro(0.045, 0.2);
            glPopMatrix();
            break;

        case BRAZO_SUP_DER:
            glPushMatrix();
            glTranslatef(0.25, 1.0, 0.0);
            glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);
            glRotatef(90, 1, 0, 0);
            dibujaCilindro(0.05, 0.2);
            glPopMatrix();
            break;

        case BRAZO_INF_DER:
            glPushMatrix();
            glTranslatef(0.25, 1.0, 0.0);
            glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);
            glTranslatef(0.0, -0.2, 0.0);
            glRotatef(anguloCodo, 1.0, 0.0, 0.0);
            glRotatef(90, 1, 0, 0);
            dibujaCilindro(0.045, 0.2);
            glPopMatrix();
            break;

        case ARMA:
            if(modeloImportado != nullptr) {
                glPushMatrix();
                glTranslatef(0.25, 1.0, 0.0);
                glRotatef(anguloBrazoX, 1.0, 0.0, 0.0);
                glTranslatef(0.0, -0.2, 0.0);
                glRotatef(anguloCodo, 1.0, 0.0, 0.0);
                glTranslatef(0.0, -0.23, 0.0);
                glRotatef(anguloArmaZ, 0.0, 0.0, 1.0);
                glRotatef(anguloArmaX, 1.0, 0.0, 0.0);
                glRotatef(90, 1, 0, 0);
                glRotatef(-90, 0, 1, 0);
                glScalef(0.1, 0.1, 0.1);
                modeloImportado->visualizar();
                glPopMatrix();
            }
            break;

        default:
            break;
    }

    glEnable(GL_LIGHTING);
}

// Visualización para picking (con colores únicos)
void igvEscena3D::visualizarParaPicking()
{
    glPushMatrix();
    glTranslatef(despX,0,0);
    glTranslatef(0, 0, despZ);
    glRotatef(rotY, 0, 1, 0);

    // Dibujar cada parte seleccionable con su color único
    dibujarParteConColor(BRAZO_SUP_IZQ);
    dibujarParteConColor(BRAZO_INF_IZQ);
    dibujarParteConColor(BRAZO_SUP_DER);
    dibujarParteConColor(BRAZO_INF_DER);
    dibujarParteConColor(ARMA);

    glPopMatrix();
}

// Método con las llamadas OpenGL para visualizar la escena
void igvEscena3D::visualizar(void)
{
    GLfloat luz0[4] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, luz0);
    glEnable(GL_LIGHT0);

    if (ejes) pintar_ejes();

    glPushMatrix();
    glTranslatef(despX,0,0);
    glTranslatef(0, 0, despZ);
    glRotatef(rotY, 0, 1, 0);

    dibujarCuerpoCompleto();

    glPopMatrix();
}

bool igvEscena3D::get_ejes()
{
    return ejes;
}

void igvEscena3D::set_ejes(bool _ejes)
{
    ejes = _ejes;
}

// Seleccionar parte mediante picking
PartesCuerpo igvEscena3D::seleccionarParte(int x, int y)
{
    // Buffer para leer el color
    unsigned char pixel[3];

    // Renderizar la escena en modo picking
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    visualizarParaPicking();

    glFlush();
    glFinish();

    // Leer el pixel en la posición del ratón (invertir Y)
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    // Convertir el color a ID
    PartesCuerpo id = (PartesCuerpo)(pixel[0] + (pixel[1] << 8) + (pixel[2] << 16));

    // Restaurar color de fondo
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Guardar la parte seleccionada
    parteSeleccionada = id;

    return id;
}

void igvEscena3D::iniciarRotacion(int x, int y)
{
    rotandoConRaton = true;
    ultimoMouseX = x;
    ultimoMouseY = y;
}

void igvEscena3D::actualizarRotacion(int x, int y)
{
    if (!rotandoConRaton) return;

    int deltaX = x - ultimoMouseX;
    int deltaY = y - ultimoMouseY;

    //float sensibilidad = 0.5f;

    switch(parteSeleccionada) {
        case BRAZO_SUP_IZQ:
        case BRAZO_SUP_DER:
            //setAnguloBrazoX(anguloBrazoX + deltaY * sensibilidad);
            setAnguloBrazoX(anguloBrazoX + deltaY);
            break;

        case BRAZO_INF_IZQ:
        case BRAZO_INF_DER:
            setAnguloCodo(anguloCodo + deltaY); //* sensibilidad);
            break;

        case ARMA:
            setAnguloArmaX(anguloArmaX + deltaY); //* sensibilidad);
            setAnguloArmaZ(anguloArmaZ + deltaX); //* sensibilidad);
            break;

        default:
            break;
    }

    ultimoMouseX = x;
    ultimoMouseY = y;
}

void igvEscena3D::finalizarRotacion()
{
    rotandoConRaton = false;
    parteSeleccionada = NINGUNA;
}

void igvEscena3D::movimentoAutomatico() {

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
                return idx - 1;
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

    float* vertexArray = new float[vertices.size()];
    std::copy(vertices.begin(), vertices.end(), vertexArray);

    unsigned int* indexArray = new unsigned int[indices.size()];
    std::copy(indices.begin(), indices.end(), indexArray);

    long int numVertices = vertices.size() / 3;
    long int numTriangulos = indices.size() / 3;

    return new igvMallaTriangulos(numVertices, vertexArray,
                                  numTriangulos, indexArray);
}