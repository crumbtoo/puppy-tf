#ifndef TBS_ARCH_H
#define TBS_ARCH_H

/* https://stackoverflow.com/users/14804593/freakanon */
#if defined(__x86_64__) || defined(_M_X64)
	#define TBS_ARCH x86_64
	#define TBS_WORDSIZE 64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
	#define TBS_ARCH x86_32
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_2__)
	#define TBS_ARCH ARM2
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
	#define TBS_ARCH ARM3
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
	#define TBS_ARCH ARM4T
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
	#define TBS_ARCH ARM5
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
	#define TBS_ARCH ARM6T2
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
	#define TBS_ARCH ARM6
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
	#define TBS_ARCH ARM7
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
	#define TBS_ARCH ARM7A
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
	#define TBS_ARCH ARM7R
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_7M__)
	#define TBS_ARCH ARM7M
	#define TBS_WORDSIZE 32
#elif defined(__ARM_ARCH_7S__)
	#define TBS_ARCH ARM7S
	#define TBS_WORDSIZE 32
#elif defined(__aarch64__) || defined(_M_ARM64)
	#define TBS_ARCH ARM64
	#define TBS_WORDSIZE 64
#elif defined(mips) || defined(__mips__) || defined(__mips)
	#define TBS_ARCH MIPS
	#define TBS_WORDSIZE 64
#elif defined(__sh__)
	#define TBS_ARCH SUPERH
	#define TBS_WORDSIZE 32
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
	#define TBS_ARCH POWERPC
	#define TBS_WORDSIZE 32
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
	#define TBS_ARCH POWERPC64
	#define TBS_WORDSIZE 64
#elif defined(__sparc__) || defined(__sparc)
	#define TBS_ARCH SPARC
	#define TBS_WORDSIZE 64
#elif defined(__m68k__)
	#define TBS_ARCH M68K
	#define TBS_WORDSIZE 32
#else
	#define TBS_ARCH UNKNOWN
	#define TBS_WORDSIZE 8
#endif

#endif
