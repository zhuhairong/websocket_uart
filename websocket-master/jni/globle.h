#ifndef _GLOBLE_H__
#define _GLOBLE_H__




//#define ZZZD 
#ifdef ZZZD
#define DPRINTF(fmt, argv...)\
{\
	printf("----Debug-----[%s %d]"fmt,__FUNCTION__, __LINE__, ##argv);}
#else
#define DPRINTF(fmt, argv...)
#endif

#define ZZZE
#ifdef ZZZE
#define EPRINTF(fmt, argv...)\
{\
	printf("----Error-----[%s %d]" fmt,__FUNCTION__, __LINE__, ##argv);}
#else
#define EPRINTF(fmt, argv...)
#endif

#define ZZZI
#ifdef ZZZI
#define IPRINTF(fmt, argv...)\
{\
	printf("----Info-----[%s %d]" fmt,__FUNCTION__, __LINE__, ##argv);}
#else
#define EPRINTF(fmt, argv...)
#endif


#define CMD(n) IPRINTF(""#n"")


#endif
