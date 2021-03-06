// SceneTerrain.h

#ifndef __SCENETERRAIN_H__
#define __SCENETERRAIN_H__

#include "SceneBase.h"
#include <SigmaUtil/SulCoordUTM.h>

class CSceneTerrain : public CSceneBase
{
public:
	CSceneTerrain( const CSulString& sFile, bool bRenderMe, double offsetX, double offsetY );
	CSceneTerrain( sigma::uint32 gx, sigma::uint32 gy, float cellw, float cellh, sigma::uint32 subx, sigma::uint32 suby, bool bRenderMe, double offsetX, double offsetY );

	virtual void adjustPosition( CSulCoordUTM* pWorldUTM );

private:
	double	m_offsetX;
	double	m_offsetY;
};

#endif // __SCENETERRAIN_H__