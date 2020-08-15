#ifndef _G_COMMON_H_
#define _G_COMMON_H_

#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
//TRUE FALSE
#ifndef TRUE
#define  TRUE  1
#endif

#ifndef FALSE
#define FALSE				0
#endif
//////////////////////////////////////////////////////////////////////////
//MIN MAX ABS
#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef	ABS
#define	ABS(a)		((a) < 0 ? -(a) : (a))
#endif
//////////////////////////////////////////////////////////////////////////
//NEW  DEL SAFE_DELETE
#ifndef SAFE_DELETE
#define	SAFE_DELETE(p)				if(p!=NULL){delete(p);(p)=NULL;}
#endif // !SAFE_DELETE
#ifndef SAFE_DELETE_ARRAY
#define	SAFE_DELETE_ARRAY(a)		if(a!=NULL){delete[](a);(a)=NULL;}
#endif
#ifndef NEW
#define NEW new
#endif
#ifndef DEL
#define DEL delete
#endif
//////////////////////////////////////////////////////////////////////////
//CONST STATIC INLINE
#ifndef	CONST
#define CONST	const
#endif
#ifndef	STATIC
#define STATIC	static
#endif
#ifndef	INLINE
#define INLINE	inline
#endif

//Const defines
typedef int					BOOL;
typedef char				CHAR;
typedef unsigned char		UCHAR;
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
#if _WIN32
typedef unsigned long		DWORD;
#else
typedef unsigned int		DWORD;
#endif
typedef float				FLOAT;
typedef double				DOUBLE;
typedef signed int			INT;
typedef signed char			INT8;
typedef signed short		INT16;
typedef signed int			INT32;
typedef unsigned int		UINT;
typedef unsigned char		UINT8;
typedef unsigned short		UINT16;
typedef unsigned int		UINT32;
///////////////////////////////////////////////////////////////////////////////
#if	_WIN32_
typedef __int64				INT64;
typedef unsigned __int64    UINT64;
#define	F_NUM_64			"I64"
#else
#include <limits.h>
typedef signed long long	INT64;
typedef unsigned long long  UINT64;
#define	F_NUM_64			"ll"
#endif	//_WIN32_
//////////////////////////////////////////////////////////////////////////
#ifdef	_ASSERT_
#define	ASSERT(c)															\
if(!c)																		\
{																			\
	char s[256];															\
	s[255] = 0;																\
	snprintf(s,255,"Assert: %s, %d, %s\r\n",__FILE__,__LINE__,#c);			\
	ZObject::Assert(s);														\
}
#define	ASSERT_VOLID_OBJECT(p)												\
if(ZObject::IsValidObject(p)>0)												\
{																			\
	char s[256];															\
	s[255] = 0;																\
	snprintf(s,255,"Assert: %s, %d, 0x%08X\r\n",__FILE__,__LINE__,(int)p);	\
	ZObject::Assert(s);														\
}
#else
#define	ASSERT(c)
#define	ASSERT_VOLID_OBJECT(p)
#endif	//_ASSERT_
//////////////////////////////////////////////////////////////////////////
/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else  /* __cplusplus */
#define NULL    ((void *)0)
#endif  /* __cplusplus */
#endif  /* NULL */
//////////////////////////////////////////////////////////////////////////
#endif//_G_COMMON_H_