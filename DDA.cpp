#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>


double X1, Y1, X2, Y2, m;

float round_value(float v) { return floor(v + 0.5); }

void drawAxes(void) {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(-m, m / 2);
  glVertex2f(m, m / 2);
  glVertex2f(m / 2, -m);
  glVertex2f(m / 2, m);
  glEnd();
  glFlush();
}


void drawLine(void) {
  glColor3f(0.0, 0.0, 1.0);
  double dx = (X2 - X1);
  double dy = (Y2 - Y1);
  double steps;
  float xInc, yInc, x = X1, y = Y1;
  steps = (fabs(dx) > fabs(dy)) ? (fabs(dx)) : (fabs(dy));
  xInc = dx / (float)steps;
  yInc = dy / (float)steps;

  glBegin(GL_POINTS);
  glVertex2d((m / 2) + x, (m / 2) + y);
  int k;
  /* For every step, find an intermediate vertex */
  for (k = 0; k < steps; k++) {
    x += xInc;
    y += yInc;
    glVertex2d((m / 2) + round_value(x), (m / 2) + round_value(y));
  }
  glEnd();
  glFlush();
}
void init(void) {
  glEnable(GL_POINT_SMOOTH);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, m, 0.0, m);
}
void setupDraw(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  drawAxes();
  drawLine();
}
int main(int argc, char **argv) {
  printf("Enter Size:\n");
  scanf("%lf", &m);
  printf("Enter two end points of the line to be drawn:\n");
  printf("\nEnter first point (x1 y1):\n");
  scanf("%lf %lf", &X1, &Y1);
  printf("\nEnter second point (x2 y2):\n");
  scanf("%lf %lf", &X2, &Y2);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(m, m);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("DDA Line");
  glutDisplayFunc(setupDraw);
  init();

  glutMainLoop();
  return EXIT_SUCCESS;
}