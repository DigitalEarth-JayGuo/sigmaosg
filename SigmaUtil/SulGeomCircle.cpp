// SulGeomCircle.cpp

#include "stdafx.h"
#include "SulGeomCircle.h"

CSulGeomCircle::CSulGeomCircle( float radius, const osg::Vec4& color ) :
CSulGeomLineStrip( color ),
m_radius( radius ),
m_color( color )
{
	m_ofs.set(0,0,0);
	m_segments = 32;
	m_width = 2.0f;
	createDrawable();
}

void CSulGeomCircle::createDrawable()
{
	sigma::VEC_VEC3::vector	vecPos;

	for ( sigma::uint32 i=0; i<m_segments; i++ )
	{
		double d = ((2.0*osg::PI)/(m_segments-1)) * (double)i;

		double x = cos( d );
		double y = sin( d );

		osg::Vec3 pos = osg::Vec3( x*m_radius, y*m_radius, 0 )+m_ofs;
		vecPos.push_back( pos );
	}

	setLines( vecPos );
	setWidth ( m_width );

	CSulGeomLineStrip::createDrawable();
}

void CSulGeomCircle::setOffset( const osg::Vec3& ofs )
{
	m_ofs = ofs;
	createDrawable();
}