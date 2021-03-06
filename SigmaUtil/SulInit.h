// SulInit.h

#ifndef __SULINIT_H__
#define __SULINIT_H__

#include "SulProfiler.h"
#include <osgViewer/Viewer>
#include "SulExport.h"

class SUL_EXPORT CSulInit
{
public:
	static void init( osg::Camera* pCam );

	static CSulProfiler* Instance();

	static osg::ref_ptr<CSulProfiler>	profiler;
};

#endif // __SULINIT_H__