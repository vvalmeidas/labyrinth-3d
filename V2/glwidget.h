#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget();
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent *event);
    int canMove(float pos_x, float pos_z, float vet_x, float vet_z);
    void display();
    void control(unsigned char key, int x, int y);
    void updatePos(int key, int x, int y);
    void movePerson(QEvent *event);
};

#endif // GLWIDGET_H
