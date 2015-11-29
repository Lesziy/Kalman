#include "GraphicsContext.h"


/**
	Takes canvas that will be drawed on
*/
GraphicsContext::GraphicsContext(wxGLCanvas *canvas): wxGLContext(canvas)
{
	SetCurrent(*canvas);
	glEnable(GL_DEPTH_TEST);
	//sets up our point of view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 10.0f);

}

void GraphicsContext::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(-0.2f, -0.2f, 0.0f);
		glVertex3f(-0.2f, 0.2f, 0.0f);
	glEnd();
	glFlush();
}
