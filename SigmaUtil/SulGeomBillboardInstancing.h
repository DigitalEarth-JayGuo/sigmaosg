// SulGeomBillboardInstancing.h

#ifndef __SULGEOMBILLBOARDINSTANCING_H__
#define __SULGEOMBILLBOARDINSTANCING_H__

#include "SulGeom.h"
#include "SulTypes.h"
#include <osg/geode>

class CSulGeomBillboardInstancing :  public osg::Geode
{
public:
					CSulGeomBillboardInstancing( sigma::uint32 numInstances, bool bUseZDirectionNormal=false, float sizeMultiplier=1.0f );

private:
	void			createDrawable();

private:
	sigma::uint32	m_numInstances;
	float			m_sizeMultiplier;
	bool			m_bUseZDirectionNormal;
};

#endif // __SULGEOMBILLBOARDINSTANCING_H__