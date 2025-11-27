#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif // defined(__APPLE__) && defined(__MACH__)

#include <string>
#include "igvEscena3D.h"
#include "igvCamara.h"

/**
 * Clase que gestiona la interfaz de usuario de la aplicación
 */
class igvInterfaz
{
private:
    // Atributos
    static igvInterfaz* _instancia; ///< Instancia única de la clase (patrón Singleton)

    int ancho_ventana = 500; ///< Ancho de la ventana de visualización
    int alto_ventana = 500;  ///< Alto de la ventana de visualización
    bool cambioVentana=false;

    igvEscena3D escena; ///< Escena 3D a visualizar
    igvCamara camara;   ///< Cámara de visualización

    igvPunto3D p0 = { 3, 2, 4 } ///< Posici�n de la c�mara
    , r = { 0, 0, 0 } ///< Punto de referencia para las vistas
    , V = { 0, 1.0, 0 } ///< Vector que indica la vertical en la vista
    ;

    // Constructor y destructor privados (patrón Singleton)
    igvInterfaz() = default;
    ~igvInterfaz() = default;

    // Métodos privados
    static void crear_mundo();

public:
    // Métodos públicos
    static igvInterfaz& getInstancia();

    void configura_entorno(int argc, char** argv, int _ancho_ventana
            , int _alto_ventana, int _pos_X, int _pos_Y
            , std::string _titulo);

    void inicia_bucle_visualizacion();

    void inicializa_callbacks();

    int get_ancho_ventana();
    int get_alto_ventana();
    void set_ancho_ventana(int _ancho_ventana);
    void set_alto_ventana(int _alto_ventana);

    void actualizar_vista_camara(int pos);

    // Callbacks estáticas
    static void keyboardFunc(unsigned char key, int x, int y);
    static void reshapeFunc(int w, int h);
    static void displayFunc();
    static void mouseFunc(int button, int state, int x, int y);      // Nuevo
    static void motionFunc(int x, int y);                            // Nuevo
};

#endif // __IGVINTERFAZ