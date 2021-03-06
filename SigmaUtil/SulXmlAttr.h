// SulXmlAttr.h

#ifndef __SULXMLATTR_H__
#define __SULXMLATTR_H__

#include "SulExport.h"
#include "SulString.h"
#include <osg/Referenced>
#include <map>
#include <string>
#include <vector>

class SUL_EXPORT CSulXmlAttr : public osg::Referenced
{
public:
	struct SINFO
	{
		CSulString	strName;
		CSulString	strValue;
	};

	typedef std::vector<SINFO*> VECTOR_ATTR_PTR;

public:
					CSulXmlAttr();
					~CSulXmlAttr();

	// copy constructor
					CSulXmlAttr( const CSulXmlAttr& other );

	void			free();
	void			reset();

	sigma::uint32	getCount();

	void			add( const CSulString& sName, bool bVal );
	void			add( const CSulString& sName, const char* pszAttr );
	void			add( const CSulString& sName, sigma::int32 dwValue );
	void			add( const CSulString& sName, sigma::uint32 dwValue );
	void			add( const CSulString& sName, float fValue );
	void			add( const CSulString& sName, const osg::Vec4& value );
	void			add( const CSulString& sName, const CSulString& value );

	CSulString&		get( const CSulString& sName );
	bool			get( const CSulString& sName, float& f );
	bool			get( const CSulString& sName, bool& b );
	bool			get( const CSulString& sName, sigma::int8& c );
	bool			get( const CSulString& sName, sigma::uint32& i );
	bool			get( const CSulString& sName, CSulString& s );

	float			getFloat( const CSulString& sName, float defaultValue );
	sigma::uint32	getUint32( const CSulString& sName, sigma::uint32 defaultValue );
	sigma::int32	getInt32( const CSulString& sName, sigma::int32 defaultValue );
	bool			getBool( const CSulString& sName, bool defaultValue );
	CSulString		getString( const CSulString& sName, CSulString defaultValue );
	osg::Vec3		getVec3( const CSulString& sName, osg::Vec3 defaultValue );
	osg::Vec4		getVec4( const CSulString& sName, osg::Vec4 defaultValue );
	double			getDouble( const CSulString& sName, double defaultValue );

	bool			exist( const CSulString& sName );

	CSulXmlAttr&	operator=( const CSulXmlAttr& other );

private:
	SINFO*			getInfo();	

private:
	sigma::uint32	m_dwCount;			// number of actual used sinfo
	CSulString		m_strEmpty;

public:
	VECTOR_ATTR_PTR	m_rVectorAttrPtr;	// attributes
};

#endif // __SULXMLATTR_H__
