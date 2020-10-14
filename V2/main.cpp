/*
 * This code was created by Jeff Molofee 1999
 * And ported to C++/Qt4 by Wesley Stessens 2009
 *
 * Contact Jeff through his website: http://nehe.gamedev.net/
 * Contact Wesley for port-specific comments: wesley@ubuntu.com
 */

#include <QApplication>
#include "glwidget.h"

void Inicializa(void){

    glShadeModel(GL_SMOOTH);

    glClearColor(0.3, 0.6, 0.8, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_branca);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_branca);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Especifica sistema de coordenadas de projecao
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    //Especifica a projecao perspectiva
    gluPerspective(90, 1, 0.1, 3000);

    //Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

    // Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    // inicializa numeros aleatorios
    srand(GetTickCount());

    //posicao inicial da esfera
    g_esfera.x_pos = 3 * TAM_BLOCO;
    g_esfera.z_pos = TAM_BLOCO;
    g_esfera.dir = LESTE;
}

//--------------------------------------------------------------

void main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Labirinto 3D");
    glutFullScreen();

    Inicializa();

    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard_Function);
    glutSpecialFunc(Special_Function);
    glutIdleFunc(Move_Esfera);

    glutMainLoop();
}
