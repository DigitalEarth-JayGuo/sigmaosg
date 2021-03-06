// SulGuiManager.h

#ifndef __SULGUIMANAGER_H__
#define __SULGUIMANAGER_H__

#include "SulString.h"
#include "SulGuiEventHandler.h"
#include "SulExport.h"
#include <osg/group>
#include <osg/projection>
#include <osg/matrixtransform>
#include <osgViewer/Viewer>

class SUL_EXPORT CSulGuiManager : public osg::Projection, public sigma::has_slots<>
{
public:
						CSulGuiManager( osgViewer::View* pViewer, bool bFlipTopBottom=false, osg::Vec2 fixedDimensions=osg::Vec2(-1,-1) );

	void				noResize();

	bool				load( const CSulString& sFileXml, osg::Group* pParent=0, CSulString sFileThemeXml="" );

	void				show( bool bShow );
	bool				isVisible();

	void				setEditMode( bool bEdit );

	class CSulGuiComp*	get( const CSulString& id );

	float				getViewW();
	float				getViewH();

	// convience methods
	class CSulGuiTextBox*		getTextBox( const CSulString& id );
	class CSulGuiCanvas*		getCanvas( const CSulString& id );
	class CSulGuiListBox*		getListBox( const CSulString& id );
	class CSulGuiButton*		getButton( const CSulString& id );
	class CSulGuiEditBox*		getEditBox( const CSulString& id );
	class CSulGuiRadioButton*	getRadioButton( const CSulString& id );
	class CSulGuiComboBox*		getComboBox( const CSulString& id );
	class CSulGuiCheckBox*		getCheckBox( const CSulString& id );
	class CSulGuiDial*			getDial( const CSulString& id );
	class CSulGuiProfiler*		getProfiler( const CSulString& id );
	class CSulGuiAlign*			getAlign( const CSulString& id );
	class CSulGuiText*			getText( const CSulString& id );
	class CSulGuiSliderH*		getSliderH( const CSulString& id );
	class CSulGuiTable*			getTable( const CSulString& id );
	class CSulGuiListView*		getListView( const CSulString& id );

	sigma::signal1<bool> signalShow;

private:
	void	onViewResize( float w, float h );

private:
	osg::ref_ptr<osg::MatrixTransform>	m_rMT;
	osg::ref_ptr<osgViewer::View>		m_rViewer;
	osg::ref_ptr<CSulGuiEventHandler>	m_rEventHandler;
	float m_viewW;
	float m_viewH;
	osg::Group* m_pParent;
	bool		m_bFlipTopBottom;
	bool		m_noResize;
};

#endif // __SULGUIMANAGER_H__