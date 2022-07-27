#ifndef TBS_TYPES_H
#define TBS_TYPES_H

#include "arch.h"

/* unsigned integers */
#ifndef TBS_NO_UINTS
	typedef unsigned char		u8;
	typedef unsigned short		u16;
	typedef unsigned int		u32;

# if(TBS_WORDSIZE == 64)
	#define TBS_LARGE_UINT_SIZE 128
	#define TBS_HAS_64
	typedef unsigned long		u64;
	typedef unsigned __int128	u128;	/* todo: make sure target can support u128 before typedefing */
/* # else */
/* 	#define TBS_LARGE_UINT_SIZE 96 */
/* 	typedef unsigned __int128	u96; */
# endif
#endif

#ifndef TBS_NO_INTS
	typedef signed char			i8;
	typedef signed short		i16;
	typedef signed int			i32;

# if(TBS_WORDSIZE == 64)
	#define TBS_LARGE_SINT_SIZE 128
	#define TBS_HAS_64
	typedef signed long			i64;
	typedef signed __int128		i128;
/* # else */
/* 	#define TBS_LARGE_SINT_SIZE 96 */
/* 	typedef signed __int128	i96; */
# endif
#endif

#ifndef TBS_NO_FLOATS
	typedef float				f32;
	typedef double				f64;

# if(TBS_WORDSIZE == 64)
	#define TBS_LARGE_FLOAT_SIZE 128
	#define TBS_HAS_128
	typedef long double			f128;
# else
	#define TBS_LARGE_FLOAT_SIZE 96
	typedef long double			f96;
# endif

	typedef long double			f64plus; /* "float 64+" */

#endif



#endif /* tbs/types.h */
