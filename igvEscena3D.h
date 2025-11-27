#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif // defined(__APPLE__) && defined(__MACH__)

#include "igvMallaTriangulos.h"

// Identificadores de las partes del cuerpo para picking
enum PartesCuerpo {
    NINGUNA= 0,
    BRAZO_SUP_IZQ = 1,
    BRAZO_INF_IZQ = 2,
    BRAZO_SUP_DER = 3,
    BRAZO_INF_DER = 4,
    ARMA = 5
};

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D
{
private:
    // Atributos
    bool ejes = true; ///< Indica si hay que dibujar los ejes coordenados o no
    double despX, rotY, despZ;
    igvMallaTriangulos* malla = nullptr; ///< Malla de triángulos asociada a la escena
    igvMallaTriangulos* modeloImportado = nullptr;

    float anguloBrazoX = 0; // Rotación de ambos brazos en el eje X
    float anguloArmaX = 0;  // Rotación adicional del arma en el eje X
    float anguloArmaZ = 0;
    float anguloCodo = 0;

    // Variables para picking y rotación con ratón
    PartesCuerpo parteSeleccionada = NINGUNA;
    bool rotandoConRaton = false;
    int ultimoMouseX = 0;
    int ultimoMouseY = 0;

public:
    // Constructores por defecto y destructor
    igvEscena3D();
    ~igvEscena3D();

    // Métodos
    void visualizar();
    void visualizarParaPicking(); // Nueva función para dibujar con colores de picking

    bool get_ejes();
    void set_ejes(bool _ejes);

    igvMallaTriangulos* getMalla() const { return malla; }

    // Métodos para incrementar los ángulos (teclado)
    void incrX() { despX += 0.10; }
    void incrY() { rotY += 10; }
    void incrZ() { despZ += 0.10; }
    void decrX() { despX -= 0.10; }
    void decrY() { rotY -= 10; }
    void decrZ() { despZ -= 0.10; }

    // Getters y setters para ángulos
    float getAnguloBrazoX() const { return anguloBrazoX; }
    void setAnguloBrazoX(float anguloBrazoX) {
        if(anguloBrazoX <= 0 && anguloBrazoX >= -180) {
            this->anguloBrazoX = anguloBrazoX;
        }
    }

    float getAnguloArmaX() const { return anguloArmaX; }
    void setAnguloArmaX(float anguloArmaX) {
        if(anguloArmaX >= -20 && anguloArmaX <= 20) {
            this->anguloArmaX = anguloArmaX;
        }
    }

    float getAnguloArmaZ() const { return anguloArmaZ; }
    void setAnguloArmaZ(float anguloArmaZ) {
        if(anguloArmaZ >= -20 && anguloArmaZ <= 20) {
            this->anguloArmaZ = anguloArmaZ;
        }
    }

    float getAnguloCodo() const { return anguloCodo; }
    void setAnguloCodo(float anguloCodo) {
        if(anguloCodo <= 0 && anguloCodo >= -120) {
            this->anguloCodo = anguloCodo;
        }
    }

    // Métodos para picking con ratón
    PartesCuerpo seleccionarParte(int x, int y);
    void iniciarRotacion(int x, int y);
    void actualizarRotacion(int x, int y);
    void finalizarRotacion();
    bool estaRotando() const { return rotandoConRaton; }

    void movimentoAutomatico();

private:
    void pintar_ejes();
    igvMallaTriangulos* cargarOBJ(const std::string& filename);
    void dibujarCuerpoCompleto();
    void dibujarParteConColor(PartesCuerpo parte);
};

#endif // __IGVESCENA3D