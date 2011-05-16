// MultiSampling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
 
osg::Node* CreateScene()
{
    osg::Geode* pGeode = new osg::Geode();

    pGeode->addDrawable( new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(-2.0f,0.0f,-2.0f),1.5f,2.0f) ) );
	pGeode->addDrawable( new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(2.0f,0.0f,-2.0f),1.5f,2.0f) ) );
	pGeode->addDrawable( new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(2.0f,0.0f,2.0f),1.5f,2.0f) ) );
	pGeode->addDrawable( new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(-2.0f,0.0f,2.0f),1.5f,2.0f) ) );

    return pGeode;
}

int _tmain(int argc, _TCHAR* argv[])
{
    // construct the viewer
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	// full screen antialiasing (if supported)
	osg::DisplaySettings::instance()->setNumMultiSamples( 4 );

    // make the viewer create a 512x512 window and position it at 32, 32
    viewer->setUpViewInWindow( 32, 32, 512, 512 );

    // set the scene-graph data the viewer will render
    viewer->setSceneData( CreateScene() );

    // execute main loop
    return viewer->run();
}