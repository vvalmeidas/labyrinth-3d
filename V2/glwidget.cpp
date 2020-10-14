//INCLUDES --------------------
#include "windows.h" //biblioteca do windows...
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include <QApplication>

//DEFINES--------------------------------------------

#define TAM_BLOCO 100
#define PASSO 10

#define NORTE 0
#define LESTE 1
#define SUL 2
#define OESTE 3

/* ESTRUTURAS------------ */

typedef struct _esf
{
  GLint x_pos, z_pos;
  GLint dir;

} ESFERA;

//GLOBALS--------------------------------------------

GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {50.0};
GLfloat mat_amarelo[] = {0.8, 0.8, 0.1, 1.0};
GLfloat mat_verde[] = {0.1, 0.6, 0.1, 1.0};
GLfloat mat_vermelho[] = {0.7, 0.1, 0.1, 1.0};
GLfloat light_position[] = {0.0, 500.0, 0.0, 1.0};
GLfloat luz_branca[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lmodel_ambient[] = {0.6, 0.6, 0.6, 1.0};

GLfloat jog_x = TAM_BLOCO, jog_z = TAM_BLOCO;
GLfloat mov_x = PASSO, mov_z = 0;
GLint angulo = 0;
GLint wire = 0;

ESFERA g_esfera;

/*labirinto */
GLint mapa[15][15] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                      1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                      1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1,
                      1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1,
                      1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
                      1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
                      1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
                      1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
                      1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
                      1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
                      1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
                      1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1,
                      1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1,
                      1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//FUNCOES--------------------------------------------
int canMove(float pos_x, float pos_z, float vet_x, float vet_z)
{
  float mundo_x = pos_x + vet_x;
  float mundo_z = pos_z + vet_z;

  int ind_x = (int)((mundo_x + TAM_BLOCO / 2) / TAM_BLOCO);
  int ind_z = (int)((mundo_z + TAM_BLOCO / 2) / TAM_BLOCO);

  if (mapa[ind_x][ind_z])
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void display()
{
  int x, z;
  int x_mun, z_mun;

  //limpa todos os pixels
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(jog_x, 25, jog_z, jog_x + mov_x, 25, jog_z + mov_z, 0, 1, 0);

  glPushMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_verde);

  glBegin(GL_QUADS);

  glVertex3f(-10000, -TAM_BLOCO / 2, -10000);
  glVertex3f(-10000, -TAM_BLOCO / 2, 10000);
  glVertex3f(10000, -TAM_BLOCO / 2, 10000);
  glVertex3f(10000, -TAM_BLOCO / 2, -10000);

  glEnd();

  glPopMatrix();

  //desenha esfera
  glPushMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_vermelho);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glTranslatef(g_esfera.x_pos, 5, g_esfera.z_pos);

  glutSolidSphere(20, 20, 16);

  glPopMatrix();

  for (x = 0; x < 15; x++)
  {
    for (z = 0; z < 15; z++)
    {
      if (mapa[x][z]) //tem um bloco
      {
        x_mun = x * TAM_BLOCO;
        z_mun = z * TAM_BLOCO;

        //cubo grande
        glPushMatrix();

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amarelo);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glTranslatef(x_mun, 5, z_mun);

        if (wire)
          glutWireCube(TAM_BLOCO);
        else
          glutSolidCube(TAM_BLOCO);

        glPopMatrix();

      } //if(mapa[x][z])
    }   //for
  }     //for

  glutSwapBuffers();
}

//-----------------------------------------------------------------

void control(unsigned char key, int x, int y){
  switch (key){
    case 27:
      exit(0);
      break; //ESC -> encerra aplicativo...
    case 'w':
    case 'W':
      wire = !wire;
      glutPostRedisplay();
      break;
  }
}

//-----------------------------------------------------------------

void updatePos(int key, int x, int y){
 float rad;

 switch (key){
  case GLUT_KEY_DOWN:

    if(pode_mover(jog_x, jog_z, - mov_x, -mov_z))
    {
      jog_x -= mov_x;
      jog_z -= mov_z;
    }
    break;


  case GLUT_KEY_UP:

      if(pode_mover(jog_x, jog_z,  mov_x, mov_z))
      {
       jog_x += mov_x;
       jog_z += mov_z;
      }
      break;

  case GLUT_KEY_LEFT:

    angulo -= 10;

     if(angulo < 0) angulo +=360;


    rad =  (float) (3.14159 * angulo / 180.0f);

    mov_x =  cos(rad) * PASSO;
    mov_z =  sin(rad) * PASSO;
    break;


  case GLUT_KEY_RIGHT:

      angulo += 10;

    if(angulo >= 360) angulo -=360;

     rad =  (float) (3.14159 * angulo / 180.0f);

    mov_x = cos(rad) * PASSO;
    mov_z = sin(rad) * PASSO;

    break;

 }//fim do switch

}

//-----------------------------------------------------------------
void movePerson()
{
    GLint mapa_x, mapa_z;

    GLint frente, esquerda, direita;
    GLint num_rnd, dir_tmp;

    DWORD inicio_clock ;

    inicio_clock = GetTickCount() ;


    switch(g_esfera.dir)
    {
        case NORTE : g_esfera.z_pos -= PASSO; break;
        case LESTE : g_esfera.x_pos += PASSO; break;
        case SUL   : g_esfera.z_pos += PASSO; break;
        case OESTE : g_esfera.x_pos -= PASSO; break;
    }


    if( (g_esfera.x_pos % TAM_BLOCO == 0) &&
        (g_esfera.z_pos % TAM_BLOCO == 0) )
    {
        frente = 0;
        esquerda = 0;
        direita = 0;

        mapa_x = (int) ((g_esfera.x_pos + TAM_BLOCO/2) / TAM_BLOCO);
        mapa_z = (int) ((g_esfera.z_pos + TAM_BLOCO/2) / TAM_BLOCO);

        switch(g_esfera.dir )
            {
                case NORTE :  if(mapa[mapa_x][mapa_z - 1] == 0)
                              {
                                  frente = 1;
                              }
                              if(mapa[mapa_x + 1][mapa_z] == 0)
                              {
                                  direita = 1;
                              }
                              if(mapa[mapa_x - 1][mapa_z] == 0)
                              {
                                  esquerda = 1;
                              }

                              break;

                case LESTE :  if(mapa[mapa_x + 1][mapa_z] == 0)
                              {
                                  frente = 1;
                              }
                              if(mapa[mapa_x][mapa_z + 1] == 0)
                              {
                                  direita = 1;
                              }
                              if(mapa[mapa_x][mapa_z - 1] == 0)
                              {
                                  esquerda = 1;
                              }
                              break;

                case SUL   :  if(mapa[mapa_x][mapa_z + 1] == 0)
                              {
                                  frente = 1;
                              }
                              if(mapa[mapa_x - 1][mapa_z] == 0)
                              {
                                  direita = 1;
                              }
                              if(mapa[mapa_x + 1][mapa_z] == 0)
                              {
                                  esquerda = 1;
                              }

                              break;

                case OESTE :  if(mapa[mapa_x - 1][mapa_z] == 0)
                              {
                                  frente = 1;
                              }
                              if(mapa[mapa_x][mapa_z - 1] == 0)
                              {
                                  direita = 1;
                              }
                              if(mapa[mapa_x][mapa_z + 1] == 0)
                              {
                                  esquerda = 1;
                              }
                              break;
            }


        dir_tmp = g_esfera.dir;


        if(frente)
        {
            if(esquerda && direita)
            {
                num_rnd = rand() % 10;

                if(num_rnd < 4) g_esfera.dir = dir_tmp;
                else if(num_rnd > 6) g_esfera.dir = (dir_tmp + 1) & 3;
                else g_esfera.dir = (dir_tmp - 1) & 3;
            }
            else
            if(esquerda)
            {
                if(!(rand()%2)) g_esfera.dir = dir_tmp ;
                else g_esfera.dir = (dir_tmp - 1) & 3;
            }
            else
            if(direita)
            {
                if(!(rand()%2)) g_esfera.dir = dir_tmp ;
                else g_esfera.dir = (dir_tmp + 1) & 3;
            }
            else  g_esfera.dir = dir_tmp ;
        }
        else
        {
            if(esquerda && direita)
            {
                if(!(rand()%2)) g_esfera.dir = (dir_tmp + 1) & 3;
                else g_esfera.dir = (dir_tmp - 1) & 3;
            }
            else
            if(esquerda)
            {
                g_esfera.dir = (dir_tmp - 1) & 3;
            }
            else
            if(direita)
            {
                g_esfera.dir = (dir_tmp + 1) & 3;
            }
            else  g_esfera.dir = (dir_tmp + 2) & 3 ;
        }

    }


    //esperar um pouco nos computadores mais rapidos
    while( (GetTickCount() - inicio_clock) < 25) ;

 glutPostRedisplay();
}