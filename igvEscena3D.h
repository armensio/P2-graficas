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

/**
 * Los objetos de esta clase representan escenas 3D para su visualizaci�n
 */
class igvEscena3D
{
private:
    // Atributos
    bool ejes = true; ///< Indica si hay que dibujar los _ejes coordenados o no

    // TODO: Apartado A: A�adir aqu� los atributos con los �ngulos de rotaci�n en X, Y y Z.
    double rotX, rotY, rotZ;
    igvMallaTriangulos* malla = nullptr; ///< Malla de tri�ngulos asociada a la escena
    igvMallaTriangulos* modeloImportado=nullptr;

    float anguloBrazoX = 0; // Rotación de ambos brazos en el eje X
    float anguloArmaX = 0;  // Rotación adicional del arma en el eje X
    float anguloArmaZ = 0;

    float anguloCodo=0;

public:
        // Constructores por defecto y destructor
    igvEscena3D();
    ~igvEscena3D();

    // M�todos
    // m�todo con las llamadas OpenGL para visualizar la escena
    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    igvMallaTriangulos* getMalla() const
    {
        return malla;
    }

    // Apartado A: métodos para incrementar los ángulos
    void incrX() {
        rotX += 0.10;
    }

    void incrY() {
        rotY += 10;
    }

    void incrZ() {
        rotZ += 10;
    }

    void decrX() {
        rotX -= 0.10;
    }

    void decrY() {
        rotY -= 10;
    }

    void decrZ() {
        rotZ -= 10;
    }

    float getAnguloBrazoX() const {
        return anguloBrazoX;
    }

    void setAnguloBrazoX(float anguloBrazoX) {
        if(anguloBrazoX<=0 && anguloBrazoX>=-180) {
            igvEscena3D::anguloBrazoX = anguloBrazoX;
        }
    }

    float getAnguloArmaX() const {
        return anguloArmaX;
    }

    void setAnguloArmaX(float anguloArmaX) {
        if(anguloArmaX>=-20 && anguloArmaX<=20) {
            igvEscena3D::anguloArmaX = anguloArmaX;
        }
    }

    float getAnguloArmaZ() const {
        return anguloArmaZ;
    }

    void setAnguloArmaZ(float anguloArmaZ) {
        if(anguloArmaZ>=-20 && anguloArmaZ<=20) {
            igvEscena3D::anguloArmaZ = anguloArmaZ;
        }
    }

    float getAnguloCodo() const{
        return anguloCodo;
    }

    void setAnguloCodo(float anguloCodo) {
        if(anguloCodo<=0 && anguloCodo>=-120) {
            igvEscena3D::anguloCodo = anguloCodo;
        }
    }

private:
    void pintar_ejes();
    igvMallaTriangulos* cargarOBJ(const std::string& filename);
};

#endif   // __IGVESCENA3D
