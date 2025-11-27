#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "igvInterfaz.h"

// Aplicación del patrón de diseño Singleton
igvInterfaz* igvInterfaz::_instancia = nullptr;

// Métodos públicos ----------------------------------------

igvInterfaz& igvInterfaz::getInstancia()
{
    if (!_instancia)
    {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

void igvInterfaz::crear_mundo()
{
    _instancia->camara.set(IGV_PARALELA, {3, 2, 4}, {0, 0, 0}
            , {0, 1.0, 0}, -1 * 1.5, 1 * 1.5, -1 * 1.5, 1 * 1.5
            , -1 * 3, 200);
}

void igvInterfaz::configura_entorno(int argc, char** argv, int _ancho_ventana
        , int _alto_ventana, int _pos_X, int _pos_Y
        , std::string _titulo)
{
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    crear_mundo();
}

void igvInterfaz::inicia_bucle_visualizacion()
{
    glutMainLoop();
}

bool c_activo=false;
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x':
            _instancia->escena.incrX();
            break;
        case 'X':
            _instancia->escena.decrX();
            break;
        case 'y':
            _instancia->escena.incrY();
            break;
        case 'Y':
            _instancia->escena.decrY();
            break;
        case 'z':
            _instancia->escena.incrZ();
            break;
        case 'Z':
            _instancia->escena.decrZ();
            break;
        case 'n':
        case 'N':
            if(_instancia->escena.getMalla())
                _instancia->escena.getMalla()->cambiarnormales();
            break;
        case 'g':
        case 'G':
            if(_instancia->escena.getMalla())
                _instancia->escena.getMalla()->cambiarvis();
            break;
        case 'q':
            _instancia->escena.setAnguloBrazoX(_instancia->escena.getAnguloBrazoX()-5);
            break;
        case 'Q':
            _instancia->escena.setAnguloBrazoX(_instancia->escena.getAnguloBrazoX()+5);
            break;
        case 't':
            _instancia->escena.setAnguloArmaX(_instancia->escena.getAnguloArmaX()+5);
            break;
        case 'T':
            _instancia->escena.setAnguloArmaX(_instancia->escena.getAnguloArmaX()-5);
            break;
        case 'r':
            _instancia->escena.setAnguloArmaZ(_instancia->escena.getAnguloArmaZ()+5);
            break;
        case 'R':
            _instancia->escena.setAnguloArmaZ(_instancia->escena.getAnguloArmaZ()-5);
            break;
        case 'E':
            _instancia->escena.setAnguloCodo(_instancia->escena.getAnguloCodo()+5);
            break;
        case 'e':
            _instancia->escena.setAnguloCodo(_instancia->escena.getAnguloCodo()-5);
            break;

        case 'c':
            c_activo=true;
            break;

        case 'C':
            c_activo=false;
            break;

        case 'a':
            if(c_activo) {
                _instancia->camara.orbitar(0, 0.05);
                _instancia->camara.aplicar();
            }
            break;

        case 'd':
            if(c_activo) {
                _instancia->camara.orbitar(0, -0.05);
                _instancia->camara.aplicar();
            }
            break;

        case 'w':
            if(c_activo) {
                _instancia->camara.orbitar(0.05, 0);
                _instancia->camara.aplicar();
            }
            break;

        case 's':
            if(c_activo) {
                _instancia->camara.orbitar(-0.05, 0);
                _instancia->camara.aplicar();
            }
            break;

        case '4':
            _instancia->cambioVentana = !_instancia->cambioVentana;
            _instancia->actualizar_vista_camara(0);
            break;

        case 'u':
            _instancia->escena.movimientoAutomatico();
            break;

        case 27: // ESC
            exit(1);
            break;
    }
    glutPostRedisplay();
}

void igvInterfaz::actualizar_vista_camara(int pos) {
    switch (pos + 1) {
        case 1:
            _instancia->camara.set(p0, r, V); //Básico
            break;
        case 2:
            _instancia->camara.set(igvPunto3D(0, 5, 0), igvPunto3D(0, 0, 0), igvPunto3D(1, 0, 0)); //Planta
            break;
        case 3:
            _instancia->camara.set(igvPunto3D(5, 0, 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1, 0)); //Alzado
            break;
        case 4:
            _instancia->camara.set(igvPunto3D(0, 0, 5), igvPunto3D(0, 0, 0), igvPunto3D(0, 1, 0)); //Perfil
            break;
    }

    _instancia->camara.aplicar();
}

/**
 * Callback para eventos de clic del ratón
 * @param button Botón del ratón presionado (GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, etc.)
 * @param state Estado del botón (GLUT_DOWN o GLUT_UP)
 * @param x Coordenada X del cursor en píxeles
 * @param y Coordenada Y del cursor en píxeles
 */
void igvInterfaz::mouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // Realizar picking para seleccionar la parte del cuerpo
            PartesCuerpo parte = _instancia->escena.seleccionarParte(x, y);

            if (parte != NINGUNA)
            {
                // Mostrar en consola qué parte se ha seleccionado
                std::cout << "Parte seleccionada: ";
                switch(parte) {
                    case BRAZO_SUP_IZQ:
                        std::cout << "Brazo Superior Izquierdo";
                        break;
                    case BRAZO_INF_IZQ:
                        std::cout << "Brazo Inferior Izquierdo (Antebrazo)";
                        break;
                    case BRAZO_SUP_DER:
                        std::cout << "Brazo Superior Derecho";
                        break;
                    case BRAZO_INF_DER:
                        std::cout << "Brazo Inferior Derecho (Antebrazo)";
                        break;
                    case ARMA:
                        std::cout << "Arma";
                        break;
                    default:
                        break;
                }
                std::cout << std::endl;

                // Iniciar el modo de rotación con el ratón
                _instancia->escena.iniciarRotacion(x, y);
            }
            else
            {
                std::cout << "No se seleccionó ninguna parte" << std::endl;
            }

            // Redibujar la escena
            glutPostRedisplay();
        }
        else if (state == GLUT_UP)
        {
            // Finalizar la rotación cuando se suelta el botón
            if (_instancia->escena.estaRotando())
            {
                _instancia->escena.finalizarRotacion();
                std::cout << "Rotación finalizada" << std::endl;
            }
        }
    }
}

/**
 * Callback para movimiento del ratón con botón presionado (arrastrar)
 * @param x Coordenada X actual del cursor en píxeles
 * @param y Coordenada Y actual del cursor en píxeles
 */
void igvInterfaz::motionFunc(int x, int y)
{
    // Solo procesar movimiento si hay una parte seleccionada
    if (_instancia->escena.estaRotando())
    {
        // Actualizar la rotación de la parte seleccionada
        _instancia->escena.actualizarRotacion(x, y);

        // Redibujar la escena con la nueva rotación
        glutPostRedisplay();
    }
}

void igvInterfaz::reshapeFunc(int w, int h)
{
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);
    _instancia->camara.aplicar();
}

void igvInterfaz::displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*
    glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());

    _instancia->camara.aplicar();

    _instancia->escena.visualizar();
    */
    if (!_instancia->cambioVentana) {
        glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());
        //visualiza la escena
        _instancia->escena.visualizar();
    } else {
        glViewport(0, _instancia->get_alto_ventana() / 2, _instancia->get_ancho_ventana() / 2,
                   _instancia->get_alto_ventana() / 2);
        _instancia->actualizar_vista_camara(0);
        _instancia->escena.visualizar();
        glViewport(_instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2,
                   _instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2);
        _instancia->actualizar_vista_camara(1);
        _instancia->escena.visualizar();
        glViewport(0, 0, _instancia->get_ancho_ventana() / 2, _instancia->get_alto_ventana() / 2);
        _instancia->actualizar_vista_camara(2);
        _instancia->escena.visualizar();
        glViewport(_instancia->get_ancho_ventana() / 2, 0, _instancia->get_ancho_ventana() / 2,
                   _instancia->get_alto_ventana() / 2);
        _instancia->actualizar_vista_camara(3);
        _instancia->escena.visualizar();
    }

    glutSwapBuffers();
}

void igvInterfaz::inicializa_callbacks()
{
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseFunc);        // Nuevo: callback para clics
    glutMotionFunc(motionFunc);      // Nuevo: callback para movimiento con botón presionado
}

int igvInterfaz::get_ancho_ventana()
{
    return ancho_ventana;
}

int igvInterfaz::get_alto_ventana()
{
    return alto_ventana;
}

void igvInterfaz::set_ancho_ventana(int _ancho_ventana)
{
    ancho_ventana = _ancho_ventana;
}

void igvInterfaz::set_alto_ventana(int _alto_ventana)
{
    alto_ventana = _alto_ventana;
}