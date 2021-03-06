// SulString.cpp

#include "stdafx.h"
#include "SulString.h"
#include <iomanip>
#include <sstream>
#include <iostream>

CSulString::CSulString() :
std::string()
{
}

CSulString::CSulString( sigma::uint32 i ) :
std::string()
{
	char buf[16];
	itoa( i, buf, 10 );
	assign( buf );
}

CSulString::CSulString( sigma::int32 i ) :
std::string()
{
	char buf[16];
	itoa( i, buf, 10 );
	assign( buf );
}

CSulString::CSulString( const sigma::int8* pszText ) :
std::string( pszText )
{
}

CSulString::CSulString( const CSulString& s ) :
std::string( s )
{
}

CSulString::CSulString( const std::string& s ) :
std::string( s )
{
}

CSulString::CSulString( sigma::uint8 c )
{
	CSulString s;
	s.Format( "%c", c );
	assign( s.c_str() );
}

CSulString::CSulString( sigma::int64 c )
{
	// FIXME: very microsofty
	char buf[1024];
	_i64toa_s( c, buf, 1024, 10 );
	CSulString s = buf;
	assign( s.c_str() );
} 

CSulString::CSulString( const osg::Vec3 v, sigma::uint32 decimalCount )
{
	CSulString s;
	CSulString fmt = 
		"%."+CSulString(decimalCount)+"f, " +
		"%."+CSulString(decimalCount)+"f, " +
		"%."+CSulString(decimalCount)+"f";
	s.Format( fmt.c_str(), v.x(), v.y(), v.z() );
	assign( s.c_str() );
}

CSulString::CSulString( const osg::Vec4 v, sigma::uint32 decimalCount )
{
	CSulString s;
	CSulString fmt = 
		"%."+CSulString(decimalCount)+"f, " +
		"%."+CSulString(decimalCount)+"f, " +
		"%."+CSulString(decimalCount)+"f, " +
		"%."+CSulString(decimalCount)+"f";
	s.Format( fmt.c_str(), v.r(), v.g(), v.b(), v.a() );
	assign( s.c_str() );
}

CSulString::CSulString( const osg::Vec4s v )
{
	CSulString s;
	CSulString fmt = "%i, %i, %i, %i";
	s.Format( fmt.c_str(), v.r(), v.g(), v.b(), v.a() );
	assign( s.c_str() );
}

CSulString::CSulString( float f, sigma::uint32 decimalCount )
{
	CSulString s;
	CSulString fmt = "%."+CSulString(decimalCount)+"f";
	s.Format( fmt.c_str(), f );
	assign( s.c_str() );
}

CSulString::CSulString( double d, sigma::uint32 decimalCount )
{
	// FIXME: not a double, can't find a good metod to convert to a double text
	CSulString s;
	CSulString fmt = "%."+CSulString(decimalCount)+"f";
	s.Format( fmt.c_str(), (float)d );
	assign( s.c_str() );

	/*
	std::ostringstream oss;
	oss << std::setprecision( decimalCount ) << d;
	assign( oss.str() );
	*/
}

void CSulString::Format( const char* Format, ... )
{
#ifdef WIN32
	// FIXME: this is NOT good at all... crash if we exceed!
	char szTmp[32000];

	va_list ArgList;
	va_start( ArgList, Format );
	//vsprintf_s( szTmp, sizeof(szTmp), Format, ArgList );
	VSPRINTF( szTmp, sizeof(szTmp), Format, ArgList );
	va_end( ArgList );
	//SetText( szTmp );

	assign( szTmp );
#else
	assert( 0 ); // FIXME: needs implementation for other platforms
#endif
}

void CSulString::makeLower()
{
	std::transform( begin(), end(), begin(), tolower );
}

void CSulString::Trim()
{
	//@TKG Test to make sure that we don't have a "" string with only white space
	if ( size()==0 )
	{
		return;
	}

	char* ws = " \t\n\r";
	std::string s(*this);
	std::string::size_type i = s.find_first_not_of(ws);
	std::string::size_type j = s.find_last_not_of(ws);
	
	// @TKG Test to make sure that if we only have white space that we dont do some nasty stuff
	if ( i==j )
	{
		return;
	}

	s = s.substr(i, j-i+1);
	assign(s);
}

float CSulString::asFloat() const
{
	return (float)atof( c_str() );
}

double CSulString::asDouble() const
{
	return (float)strtod( c_str(), 0 );
}

sigma::uint32 CSulString::asUint32() const
{
	return (sigma::uint32)atoi( c_str() );
}

sigma::int32 CSulString::asInt32() const
{
	return (sigma::int32)atoi( c_str() );
}

sigma::int64 CSulString::asInt64() const
{
	// FIXME: very microsofty
	return (sigma::int64)_strtoi64( c_str(), 0, 10 );
}

CSulString CSulString::GetStartWord( char c ) 
{
	std::string::size_type i = find_first_of( c, 0 )+1;
	return substr( 0, i );
}

bool CSulString::asBool() const
{
	if ( empty() )
	{
		return false;
	}

	CSulString tmp = *this;
	tmp.makeLower();

	if ( tmp=="1" ) return true;
	if ( tmp=="true" ) return true;
	if ( tmp=="yes" ) return true;

	return false;
}

osg::Vec3 CSulString::asVec3() const
{
	if ( !empty() )
	{
		float r, g, b;
		sscanf( c_str(), "%f,%f,%f,%f", &r, &g, &b ); 
		return osg::Vec3( r, g, b );
	}

	return osg::Vec3( 1, 1, 1 );
}

osg::Vec4 CSulString::asVec4() const
{
	if ( !empty() )
	{
		float r, g, b, a;
		sscanf( c_str(), "%f,%f,%f,%f", &r, &g, &b, &a ); 
		return osg::Vec4( r, g, b, a );
	}

	return osg::Vec4( 1, 1, 1, 1 );
}

osg::Vec4s CSulString::asVec4s() const
{
	if ( !empty() )
	{
		int r, g, b, a;
		sscanf( c_str(), "%i,%i,%i,%i", &r, &g, &b, &a ); 
		return osg::Vec4s( r, g, b, a );
	}

	return osg::Vec4s( 1, 1, 1, 1 );
}

void CSulString::replaceAll( const std::string& searchFor, const std::string& changeTo ) 
{
	basic_string <char>::size_type x;

	while ( x=find(searchFor), x!=std::string::npos ) 
	{
		erase(x, searchFor.length());
		insert(x, changeTo);
	}
}

// "http://whatever.com?id=1&what=2

void CSulString::urlSetHost( const CSulString& host )
{
	basic_string <char>::size_type i;

	i = find( '?' );
	if ( i!=npos )
	{
		assign( host+substr( i ) );
		return;
	}

	// two possibilities
	// 1. there is only a host string
	// 2. there is only the url part 

	// '=' does not exist in the host string
	if ( find( '=' )==npos )
	{
		assign( host );
		return;
	}

	assign( host + "?" + c_str() );
}

CSulString CSulString::urlGetHost()
{
	basic_string <char>::size_type i;
	
	i = find( '?' );
	if ( i==npos )
	{
		if ( find( '=' )==npos )
			return *this;

		return "";
	}

	return substr( 0, i );
}

CSulString CSulString::urlGetParameterStringOnly()
{
	basic_string <char>::size_type i;
	
	i = find( '?' );
	if ( i==npos )
	{
		if ( find( '=' )==npos )
			return "";

		return *this;
	}

	return substr( i );
}

CSulString CSulString::urlGetParameter( const CSulString& name )
{
	CSulString s = urlGetParameterStringOnly();
	CSulString sParam;

	basic_string <char>::size_type is, ie;
	
	is = s.find( name+"=" );
	if ( is==npos )
		return "";

	is += name.length()+1;

	ie = s.find( '&', is );
	if ( ie!=npos )
	{
		sParam = s.substr( is, ie-is );
	}
	else
	{
		sParam = s.substr( is );
	}

	return sParam.urlGetDecode();
}

void CSulString::urlAddParameter( const CSulString& name, const CSulString& value )
{
	CSulString v = value.urlGetEncode();

	if ( empty() )
	{
		assign( name+"="+v );
		return;
	}

	// ok, the string is not empty. Now we check to see if the "?" exists
	if ( find( '?' )==npos )
	{
		if ( find( '=' )==npos )
		{
			append( "?"+name+"="+v );
			return;
		}
	}

	append( "&"+name+"="+v );
}

CSulString CSulString::urlGetDecode() const
{
	CSulString s = *this;
	s.replaceAll( "%20", " " );
	return s;
}

CSulString CSulString::urlGetEncode() const
{
	CSulString escaped="";
    int max = length();
    for(int i=0; i<max; i++)
    {
        if ( (48 <= c_str()[i] && c_str()[i] <= 57) ||//0-9
             (65 <= c_str()[i] && c_str()[i] <= 90) ||//abc...xyz
             (97 <= c_str()[i] && c_str()[i] <= 122) || //ABC...XYZ
             (c_str()[i]=='~' || c_str()[i]=='!' || c_str()[i]=='*' || c_str()[i]=='(' || c_str()[i]==')' || c_str()[i]=='\'')
        )
        {
            escaped.append( &c_str()[i], 1);
        }
        else
        {
            escaped.append("%");
            escaped.append( char2hex(c_str()[i]) );//converts char 255 to string "ff"
        }
    }

    return escaped;
}

CSulString CSulString::char2hex( char dec ) const
{
    char dig1 = (dec&0xF0)>>4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
    if (10<= dig1 && dig1<=15) dig1+=97-10; //a,97inascii
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=97-10;

    CSulString r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

CSulString CSulString::getExtension()
{
	return substr(find_last_of( "." ) + 1);
}
