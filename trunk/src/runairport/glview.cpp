#include "StdAfx.h"
#include "glview.h"
#include "../libredwg/dwg.h"

class dwgRender
{
public:
	class odObject
	{
	public:
		virtual void gldraw()
		{

		}
	};
	class odLine : public odObject
	{
	public:
		QVector2D p1,p2;
		virtual void gldraw()
		{			
			glBegin(GL_LINES);
			glVertex2d(p1.x(),p1.y());
			glVertex2d(p2.x(),p2.y());
			glEnd();
		}
	};

	virtual ~dwgRender(){ clear(); }

	std::vector<odObject*> vObjectlist;
	QVector2D pMin,pMax;
	void MergePoint(const QVector2D& p)
	{
		pMin.setX( min(p.x(),pMin.x()) );pMin.setY( min(p.y(),pMin.y()) );
		pMax.setX( max(p.x(),pMax.x()) );pMax.setY( max(p.y(),pMax.y()) );
	}

	void clear()
	{
		for(std::vector<odObject*>::iterator itr= vObjectlist.begin();itr!=vObjectlist.end();++itr)
		{
			delete *itr;
		}
		vObjectlist.clear();
	}
	void add_line(double x1,double y1, double x2,double y2)
	{
		odLine* pnewLine = new odLine();
		pnewLine->p1 = QVector2D(x1,y1);
		pnewLine->p2 = QVector2D(x2,y2);
		vObjectlist.push_back(pnewLine);
		MergePoint(pnewLine->p1);
		MergePoint(pnewLine->p2);
	}

	int	load_dwg(char *filename)
	{
		unsigned int i;
		int success;
		Dwg_Data dwg;

		dwg.num_objects = 0;
		success = dwg_read_file(filename, &dwg);
		for (i = 0; i < dwg.num_objects; i++)
		{
			Dwg_Entity_LINE *line;
			Dwg_Entity_CIRCLE *circle;
			Dwg_Entity_TEXT *text;

			switch (dwg.object[i].type)
			{
			case DWG_TYPE_LINE:
				line = dwg.object[i].tio.entity->tio.LINE;
				add_line(line->start.x, line->end.x, line->start.y, line->end.y);
				break;
			case DWG_TYPE_CIRCLE:
				circle = dwg.object[i].tio.entity->tio.CIRCLE;
				//add_circle(circle->center.x, circle->center.y, circle->radius);
				break;
			case DWG_TYPE_TEXT:
				text = dwg.object[i].tio.entity->tio.TEXT;
				//add_text(text->insertion_pt.x, text->insertion_pt.y, text->text_value);
				break;
			default:
				{
					break;
				}
			}
		}
		dwg_free(&dwg);
		return success;
	}


	void draw()
	{
		for(std::vector<odObject*>::iterator itr= vObjectlist.begin();itr!=vObjectlist.end();++itr)
		{
			odObject*pobj= *itr;
			pobj->gldraw();
		}
	}

};

glView::glView(QWidget *parent)
	: QGLWidget(parent)
{
	pdwgdraw = new dwgRender();
	//pdwgdraw->load_dwg("c:\\a.dwg");
	startTimer(1);
}

glView::~glView()
{
	delete pdwgdraw;
	pdwgdraw = NULL;
}


void glView::initializeGL()
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	//glClearDepth( 1.0 );
	//glEnable( GL_DEPTH_TEST );
	//glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void glView::paintGL()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D(-100,100,-100,100);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2d(-50,-50);
	glVertex2d(50,-50);
	glVertex2d(50,50);
	glVertex2d(-50,50);
	glEnd();

	pdwgdraw->draw();


	
}

void glView::resizeGL( int width, int height )
{
	if ( height == 0 )
	{
		height = 1;
	}
	glViewport( 0, 0, (GLint)width, (GLint)height );	
	
}

void glView::keyPressEvent( QKeyEvent *e )
{
	switch ( e->key() )
	{
	case Qt::Key_F2:
		fullscreen = !fullscreen;
		if ( fullscreen )
		{
			showFullScreen();
		}
		else
		{
			showNormal();
			setGeometry( 0, 0, 640, 480 );
		}
		updateGL();
		break;
	case Qt::Key_Escape:
		close();
	}
}



void glView::timerEvent( QTimerEvent* evt )
{
	Q_UNUSED(evt);
	update();
}