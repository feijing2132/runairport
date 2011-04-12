#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>

class dwgRender;
class glView : public QGLWidget
{
	Q_OBJECT

public:
	glView(QWidget *parent);
	~glView();
	bool event( QEvent * e );
	void timerEvent( QTimerEvent* evt );

private:
	void initializeGL();
	void paintGL();
	void resizeGL( int width, int height );

	void keyPressEvent( QKeyEvent *e );
	bool fullscreen;

	dwgRender* pdwgdraw;


};

#endif // GLVIEW_H
