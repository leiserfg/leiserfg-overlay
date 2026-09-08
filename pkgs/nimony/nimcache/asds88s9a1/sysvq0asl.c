#define NIM_INTBITS 64
/* GENERATED CODE. DO NOT EDIT. */

#ifdef __cplusplus
#  if __cplusplus >= 201103L
#    /* nullptr is more type safe (less implicit conversions than 0) */
#    define NIM_NIL nullptr
#  else
#    // both `((void*)0)` and `NULL` would cause codegen to emit
#    // error: assigning to 'Foo *' from incompatible type 'void *'
#    // but codegen could be fixed if need. See also potential caveat regarding
#    // NULL.
#    // However, `0` causes other issues, see #13798
#    define NIM_NIL 0
#  endif
#else
#  include <stdbool.h>
#  define NIM_NIL NULL
#endif

#ifdef __cplusplus
#define NB8 bool
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901)
// see #13798: to avoid conflicts for code emitting `#include <stdbool.h>`
#define NB8 _Bool
#else
typedef unsigned char NB8; // best effort
#endif

/* Assembler-name prefix for `__asm__` symbol labels: Mach-O prepends an
   underscore to C identifiers, ELF/PE(x64) do not. Used via string-literal
   concatenation: __asm__(NIM_ASM_PREFIX "write"). */
#ifdef __APPLE__
#define NIM_ASM_PREFIX "_"
#else
#define NIM_ASM_PREFIX ""
#endif

/* The spin-wait hint behind `std/atomics`'s `cpuRelax` (the `CpuRelax`
   intrinsic row). A macro rather than a builtin named on the Nimony side,
   because WHICH instruction it is depends on the target the C compiler is
   configured for, which Nimony does not know: `__builtin_ia32_pause` does not
   exist off x86 and there is no ARM builtin portable across GCC and clang to
   name instead. Every arm is a hint and nothing more, so a target with no
   spelling for it gets an empty statement — the loop still spins correctly,
   it just does not tell the core it is waiting. */
#if defined(__GNUC__) || defined(__clang__)
#  if defined(__i386__) || defined(__x86_64__)
#    define NIM_CPU_RELAX() __builtin_ia32_pause()
#  elif defined(__aarch64__) || defined(__arm__)
#    define NIM_CPU_RELAX() __asm__ __volatile__("yield" ::: "memory")
#  else
#    define NIM_CPU_RELAX() ((void)0)
#  endif
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
#  include <intrin.h>
#  define NIM_CPU_RELAX() _mm_pause()
#else
#  define NIM_CPU_RELAX() ((void)0)
#endif

typedef unsigned char NC8;

typedef float NF32;
typedef double NF64;
#if defined(__BORLANDC__) || defined(_MSC_VER)
typedef signed char NI8;
typedef signed short int NI16;
typedef signed int NI32;
typedef __int64 NI64;
/* XXX: Float128? */
typedef unsigned char NU8;
typedef unsigned short int NU16;
typedef unsigned int NU32;
typedef unsigned __int64 NU64;
#elif defined(HAVE_STDINT_H)
#ifndef USE_NIM_NAMESPACE
#  include <stdint.h>
#endif
typedef int8_t NI8;
typedef int16_t NI16;
typedef int32_t NI32;
typedef int64_t NI64;
typedef uint8_t NU8;
typedef uint16_t NU16;
typedef uint32_t NU32;
typedef uint64_t NU64;
#elif defined(HAVE_CSTDINT)
#ifndef USE_NIM_NAMESPACE
#  include <cstdint>
#endif
typedef std::int8_t NI8;
typedef std::int16_t NI16;
typedef std::int32_t NI32;
typedef std::int64_t NI64;
typedef std::uint8_t NU8;
typedef std::uint16_t NU16;
typedef std::uint32_t NU32;
typedef std::uint64_t NU64;
#else
/* Unknown compiler/version, do our best */
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ NI8;
#else
typedef signed char NI8;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ NI16;
#else
typedef signed short int NI16;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ NI32;
#else
typedef signed int NI32;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ NI64;
#else
typedef long long int NI64;
#endif
/* XXX: Float128? */
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ NU8;
#else
typedef unsigned char NU8;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ NU16;
#else
typedef unsigned short int NU16;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ NU32;
#else
typedef unsigned int NU32;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ NU64;
#else
typedef unsigned long long int NU64;
#endif
#endif

#ifdef NIM_INTBITS
#  if NIM_INTBITS == 64
typedef NI64 NI;
typedef NU64 NU;
#  elif NIM_INTBITS == 32
typedef NI32 NI;
typedef NU32 NU;
#  elif NIM_INTBITS == 16
typedef NI16 NI;
typedef NU16 NU;
#  elif NIM_INTBITS == 8
typedef NI8 NI;
typedef NU8 NU;
#  else
#    error "invalid bit width for int"
#  endif
#endif

#define NIM_TRUE true
#define NIM_FALSE false

#define _GNU_SOURCE

// Include math.h to use `NAN` that should be defined in C compilers supports C99.
#include <math.h>

// Define NAN in case math.h doesn't define it.
// NAN definition copied from math.h included in the Windows SDK version 10.0.14393.0
#ifndef NAN
#  ifndef _HUGE_ENUF
#    define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#  endif
#  define NAN_INFINITY ((float)(_HUGE_ENUF * _HUGE_ENUF))
#  define NAN ((float)(NAN_INFINITY * 0.0F))
#endif

#ifndef INF
#  ifdef INFINITY
#    define INF INFINITY
#  elif defined(HUGE_VAL)
#    define INF  HUGE_VAL
#  elif defined(_MSC_VER)
#    include <float.h>
#    define INF (DBL_MAX+DBL_MAX)
#  else
#    define INF (1.0 / 0.0)
#  endif
#endif

#if defined(__GNUC__) || defined(_MSC_VER)
#  define IL64(x) x##LL
#else /* works only without LL */
#  define IL64(x) ((NI64)x)
#endif


/* ------------ ignore typical warnings in Nim-generated files ------------- */
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic ignored "-Wswitch-bool"
#  pragma GCC diagnostic ignored "-Wformat"
#  pragma GCC diagnostic ignored "-Wpointer-sign"
#  if defined(__clang__)
#    pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
#  else
#    pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#  endif
#endif



/* ------------------------------------------------------------------- */
#ifdef  __cplusplus
#  define NIM_EXTERNC extern "C"
#else
#  define NIM_EXTERNC
#endif

#if defined(WIN32) || defined(_WIN32) /* only Windows has this mess... */
#  define N_LIB_PRIVATE
#  define N_CDECL(rettype, name) rettype __cdecl name
#  define N_STDCALL(rettype, name) rettype __stdcall name
#  define N_SYSCALL(rettype, name) rettype __syscall name
#  define N_FASTCALL(rettype, name) rettype __fastcall name
#  define N_THISCALL(rettype, name) rettype __thiscall name
#  define N_SAFECALL(rettype, name) rettype __stdcall name
/* function pointers with calling convention: */
#  define N_CDECL_PTR(rettype, name) rettype (__cdecl *name)
#  define N_STDCALL_PTR(rettype, name) rettype (__stdcall *name)
#  define N_SYSCALL_PTR(rettype, name) rettype (__syscall *name)
#  define N_FASTCALL_PTR(rettype, name) rettype (__fastcall *name)
#  define N_THISCALL_PTR(rettype, name) rettype (__thiscall *name)
#  define N_SAFECALL_PTR(rettype, name) rettype (__stdcall *name)

#  ifdef __EMSCRIPTEN__
#    define N_LIB_EXPORT  NIM_EXTERNC __declspec(dllexport) __attribute__((used))
#    define N_LIB_EXPORT_VAR  __declspec(dllexport) __attribute__((used))
#  else
#    define N_LIB_EXPORT  NIM_EXTERNC __declspec(dllexport)
#    define N_LIB_EXPORT_VAR  __declspec(dllexport)
#  endif
#  define N_LIB_IMPORT  extern __declspec(dllimport)
#else
#  define N_LIB_PRIVATE __attribute__((visibility("hidden")))
#  if defined(__GNUC__)
#    define N_CDECL(rettype, name) rettype name
#    define N_STDCALL(rettype, name) rettype name
#    define N_SYSCALL(rettype, name) rettype name
#    define N_FASTCALL(rettype, name) __attribute__((fastcall)) rettype name
#    define N_SAFECALL(rettype, name) rettype name
/*   function pointers with calling convention: */
#    define N_CDECL_PTR(rettype, name) rettype (*name)
#    define N_STDCALL_PTR(rettype, name) rettype (*name)
#    define N_SYSCALL_PTR(rettype, name) rettype (*name)
#    define N_FASTCALL_PTR(rettype, name) __attribute__((fastcall)) rettype (*name)
#    define N_SAFECALL_PTR(rettype, name) rettype (*name)
#  else
#    define N_CDECL(rettype, name) rettype name
#    define N_STDCALL(rettype, name) rettype name
#    define N_SYSCALL(rettype, name) rettype name
#    define N_FASTCALL(rettype, name) rettype name
#    define N_SAFECALL(rettype, name) rettype name
/*   function pointers with calling convention: */
#    define N_CDECL_PTR(rettype, name) rettype (*name)
#    define N_STDCALL_PTR(rettype, name) rettype (*name)
#    define N_SYSCALL_PTR(rettype, name) rettype (*name)
#    define N_FASTCALL_PTR(rettype, name) rettype (*name)
#    define N_SAFECALL_PTR(rettype, name) rettype (*name)
#  endif
#  ifdef __EMSCRIPTEN__
#    define N_LIB_EXPORT NIM_EXTERNC __attribute__((visibility("default"), used))
#    define N_LIB_EXPORT_VAR  __attribute__((visibility("default"), used))
#  else
#    define N_LIB_EXPORT NIM_EXTERNC __attribute__((visibility("default")))
#    define N_LIB_EXPORT_VAR  __attribute__((visibility("default")))
#  endif
#  define N_LIB_IMPORT  extern
#endif

#if defined(__BORLANDC__) || defined(_MSC_VER) || defined(WIN32) || defined(_WIN32)
/* these compilers have a fastcall so use it: */
#  define N_NIMCALL(rettype, name) rettype __fastcall name
#  define N_NIMCALL_PTR(rettype, name) rettype (__fastcall *name)
#else
#  define N_NIMCALL(rettype, name) rettype name /* no modifier */
#  define N_NIMCALL_PTR(rettype, name) rettype (*name)
#endif

#define N_NOCONV(rettype, name) rettype name
/* specify no calling convention */
#define N_NOCONV_PTR(rettype, name) rettype (*name)

/* calling convention mess ----------------------------------------------- */
#if defined(__GNUC__) || defined(__TINYC__)
  /* these should support C99's inline */
#  define N_INLINE(rettype, name) inline rettype name
#elif defined(__BORLANDC__) || defined(_MSC_VER)
/* Borland's compiler is really STRANGE here; note that the __fastcall
   keyword cannot be before the return type, but __inline cannot be after
   the return type, so we do not handle this mess in the code generator
   but rather here. */
#  define N_INLINE(rettype, name) __inline rettype name
#else /* others are less picky: */
#  define N_INLINE(rettype, name) rettype __inline name
#endif

#define N_INLINE_PTR(rettype, name) rettype (*name)

#if defined(__GNUC__) || defined(__ICC__)
#  define N_NOINLINE __attribute__((__noinline__))
#elif defined(_MSC_VER)
#  define N_NOINLINE __declspec(noinline)
#else
#  define N_NOINLINE
#endif

#define N_NOINLINE_PTR(rettype, name) rettype (*name)

#if defined(_MSC_VER)
#  define NIM_ALIGN(x)  __declspec(align(x))
#  define NIM_ALIGNOF(x) __alignof(x)
#else
#  define NIM_ALIGN(x)  __attribute__((aligned(x)))
#  define NIM_ALIGNOF(x) __alignof__(x)
#endif

#include <stddef.h>


/*
  NIM_THREADVAR declaration based on
  https://stackoverflow.com/questions/18298280/how-to-declare-a-variable-as-thread-local-portably
*/
#if defined _WIN32
#  if defined _MSC_VER || defined __BORLANDC__
#    define NIM_THREADVAR __declspec(thread)
#  else
#    define NIM_THREADVAR __thread
#  endif
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112 && !defined __STDC_NO_THREADS__
#  define NIM_THREADVAR _Thread_local
#elif defined _WIN32 && ( \
       defined _MSC_VER || \
       defined __ICL || \
       defined __BORLANDC__ )
#  define NIM_THREADVAR __declspec(thread)
#elif defined(__TINYC__) || defined(__GENODE__)
#  define NIM_THREADVAR
/* note that ICC (linux) and Clang are covered by __GNUC__ */
#elif defined __GNUC__ || \
       defined __SUNPRO_C || \
       defined __xlC__
#  define NIM_THREADVAR __thread
#else
#  error "Cannot define NIM_THREADVAR"
#endif

/* define NIM_STATIC_ASSERT */
#if defined(__cplusplus)
#define NIM_STATIC_ASSERT(x, msg) static_assert((x), msg)
#else
#define NIM_STATIC_ASSERT(x, msg) _Static_assert((x), msg)
#endif

// Test to see if Nim and the C compiler agree on the size of a pointer.
NIM_STATIC_ASSERT(sizeof(NI) == sizeof(void*) && NIM_INTBITS == sizeof(NI)*8, "Pointer size mismatch between Nim and C/C++ backend. You probably need to setup the backend compiler for target CPU.");

N_INLINE(NB8, _Qlengc_div_sll_overflow)(long long int a, long long int b, long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long long int)(((unsigned long long int)1) << (sizeof(long long int) * 8 - 1)) && b == -1) {
    *res = a;
    return NIM_TRUE;
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_div_sl_overflow)(long int a, long int b, long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long int)(((unsigned long int)1) << (sizeof(long int) * 8 - 1)) && b == -1) {
    *res = a;
    return NIM_TRUE;
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_div_ull_overflow)(unsigned long long int a, unsigned long long int b, unsigned long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE; /* Overflow: division by zero */
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_div_ul_overflow)(unsigned long int a, unsigned long int b, unsigned long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_sll_overflow)(long long int a, long long int b, long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long long int)(((unsigned long long int)1) << (sizeof(long long int) * 8 - 1)) && b == -1) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_sl_overflow)(long int a, long int b, long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long int)(((unsigned long int)1) << (sizeof(long int) * 8 - 1)) && b == -1) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_ull_overflow)(unsigned long long int a, unsigned long long int b, unsigned long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_ul_overflow)(unsigned long int a, unsigned long int b, unsigned long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}
#include <string.h>
typedef struct LongString_0_sysvq0asl LongString_0_sysvq0asl;
typedef struct Rtti_0_sysvq0asl Rtti_0_sysvq0asl;
typedef struct Trunk_0_sysvq0asl Trunk_0_sysvq0asl;
typedef struct LLChunk_0_sysvq0asl LLChunk_0_sysvq0asl;
typedef struct AvlNode_0_sysvq0asl AvlNode_0_sysvq0asl;
typedef struct FreeCell_0_sysvq0asl FreeCell_0_sysvq0asl;
typedef struct MemRegion_0_sysvq0asl MemRegion_0_sysvq0asl;
typedef struct SmallChunk_0_sysvq0asl SmallChunk_0_sysvq0asl;
typedef struct BigChunk_0_sysvq0asl BigChunk_0_sysvq0asl;
typedef struct HeapLinks_0_sysvq0asl HeapLinks_0_sysvq0asl;
typedef struct CoroutineBase_0_sysvq0asl CoroutineBase_0_sysvq0asl;
typedef struct Continuation_0_sysvq0asl Continuation_0_sysvq0asl;
typedef struct Exception_0_sysvq0asl Exception_0_sysvq0asl;
typedef struct LongString_0_sysvq0asl{
  NI64 fullLen_0;
  NI64 rc_0;
  NI64 capImpl_0;
  NC8 data_0[];}
LongString_0_sysvq0asl;
typedef struct string_0_sysvq0asl{
  NU64 bytes_0;
  LongString_0_sysvq0asl* more_0;}
string_0_sysvq0asl;
typedef struct RootObj_0_sysvq0asl{
  Rtti_0_sysvq0asl* vt_00;}
RootObj_0_sysvq0asl;
typedef struct X60Qt_0_IAarrayAuS64ZS8_sysvq0asl{
  NU64 a[IL64(8)];}
X60Qt_0_IAarrayAuS64ZS8_sysvq0asl;
typedef struct Trunk_0_sysvq0asl{
  Trunk_0_sysvq0asl* next_0;
  NI64 key_0;
  X60Qt_0_IAarrayAuS64ZS8_sysvq0asl bits_0;}
Trunk_0_sysvq0asl;
typedef struct X60Qt_0_IAarrayAptrSX54runk0sysvq0aslZS256_sysvq0asl{
  Trunk_0_sysvq0asl* a[IL64(256)];}
X60Qt_0_IAarrayAptrSX54runk0sysvq0aslZS256_sysvq0asl;
typedef struct IntSet_0_sysvq0asl{
  X60Qt_0_IAarrayAptrSX54runk0sysvq0aslZS256_sysvq0asl data_0;}
IntSet_0_sysvq0asl;
typedef struct LLChunk_0_sysvq0asl{
  NI64 size_0;
  NI64 acc_0;
  LLChunk_0_sysvq0asl* next_0;}
LLChunk_0_sysvq0asl;
typedef struct X60Qt_0_IAarrayAptrSX41vlX4eode0sysvq0aslZS2_sysvq0asl{
  AvlNode_0_sysvq0asl* a[IL64(2)];}
X60Qt_0_IAarrayAptrSX41vlX4eode0sysvq0aslZS2_sysvq0asl;
typedef struct AvlNode_0_sysvq0asl{
  X60Qt_0_IAarrayAptrSX41vlX4eode0sysvq0aslZS2_sysvq0asl link_0;
  NI64 key_0;
  NI64 upperBound_0;
  NI64 level_0;}
AvlNode_0_sysvq0asl;
typedef struct FreeCell_0_sysvq0asl{
  FreeCell_0_sysvq0asl* next_0;
  NI64 alignment_0;}
FreeCell_0_sysvq0asl;
typedef struct BaseChunk_0_sysvq0asl{
  NI64 prevSize_0;
  NI64 size_0;
  MemRegion_0_sysvq0asl* owner_0;}
BaseChunk_0_sysvq0asl;
typedef struct SmallChunk_0_sysvq0asl{
  BaseChunk_0_sysvq0asl Q;
  SmallChunk_0_sysvq0asl* next_0;
  SmallChunk_0_sysvq0asl* prev_0;
  FreeCell_0_sysvq0asl* freeList_0;
  NI32 free_0;
  NU32 acc_0;
  NI32 foreignCells_0;
  NI32 chunkAlignOff_0;
   NIM_ALIGN(16)NU8 data_0[];}
SmallChunk_0_sysvq0asl;
typedef struct BigChunk_0_sysvq0asl{
  BaseChunk_0_sysvq0asl Q;
  BigChunk_0_sysvq0asl* next_0;
  BigChunk_0_sysvq0asl* prev_0;
   NIM_ALIGN(16)NU8 data_0[];}
BigChunk_0_sysvq0asl;
typedef struct X60Qt_0_IAtupleAptrSX42igX43hunk0sysvq0aslZAiS64_sysvq0asl{
  BigChunk_0_sysvq0asl* fld_0;
  NI64 fld_1;}
X60Qt_0_IAtupleAptrSX42igX43hunk0sysvq0aslZAiS64_sysvq0asl;
typedef struct X60Qt_0_IAarrayAtupleAptrSX42igX43hunk0sysvq0aslZAiS64ZZS30_sysvq0asl{
  X60Qt_0_IAtupleAptrSX42igX43hunk0sysvq0aslZAiS64_sysvq0asl a[IL64(30)];}
X60Qt_0_IAarrayAtupleAptrSX42igX43hunk0sysvq0aslZAiS64ZZS30_sysvq0asl;
typedef struct HeapLinks_0_sysvq0asl{
  NI64 count_0;
  X60Qt_0_IAarrayAtupleAptrSX42igX43hunk0sysvq0aslZAiS64ZZS30_sysvq0asl chunks_0;
  HeapLinks_0_sysvq0asl* next_0;}
HeapLinks_0_sysvq0asl;
typedef struct X60Qt_0_IAarrayAptrSX53mallX43hunk0sysvq0aslZS256_sysvq0asl{
  SmallChunk_0_sysvq0asl* a[IL64(256)];}
X60Qt_0_IAarrayAptrSX53mallX43hunk0sysvq0aslZS256_sysvq0asl;
typedef struct X60Qt_0_IAarrayAptrSX46reeX43ell0sysvq0aslZS256_sysvq0asl{
  FreeCell_0_sysvq0asl* a[IL64(256)];}
X60Qt_0_IAarrayAptrSX46reeX43ell0sysvq0aslZS256_sysvq0asl;
typedef struct X60Qt_0_IAarrayAuS32ZS24_sysvq0asl{
  NU32 a[IL64(24)];}
X60Qt_0_IAarrayAuS32ZS24_sysvq0asl;
typedef struct X60Qt_0_IAarrayAptrSX42igX43hunk0sysvq0aslZS32_sysvq0asl{
  BigChunk_0_sysvq0asl* a[IL64(32)];}
X60Qt_0_IAarrayAptrSX42igX43hunk0sysvq0aslZS32_sysvq0asl;
typedef struct X60Qt_0_IAarrayAR0AptrSX42igX43hunk0sysvq0aslZS32ZS24_sysvq0asl{
  X60Qt_0_IAarrayAptrSX42igX43hunk0sysvq0aslZS32_sysvq0asl a[IL64(24)];}
X60Qt_0_IAarrayAR0AptrSX42igX43hunk0sysvq0aslZS32ZS24_sysvq0asl;
typedef struct MemRegion_0_sysvq0asl{
  X60Qt_0_IAarrayAptrSX53mallX43hunk0sysvq0aslZS256_sysvq0asl freeSmallChunks_0;
  X60Qt_0_IAarrayAptrSX46reeX43ell0sysvq0aslZS256_sysvq0asl sharedFreeLists_0;
  NU32 flBitmap_0;
  X60Qt_0_IAarrayAuS32ZS24_sysvq0asl slBitmap_0;
  X60Qt_0_IAarrayAR0AptrSX42igX43hunk0sysvq0aslZS32ZS24_sysvq0asl matrix_0;
  LLChunk_0_sysvq0asl* llmem_0;
  NI64 currMem_0;
  NI64 maxMem_0;
  NI64 freeMem_0;
  NI64 occ_0;
  NI64 lastSize_0;
  BigChunk_0_sysvq0asl* sharedFreeListBigChunks_0;
  IntSet_0_sysvq0asl chunkStarts_0;
  NB8 lockActive_0;
  NB8 locked_0;
  NB8 blockChunkSizeIncrease_0;
  NI64 nextChunkSize_0;
  HeapLinks_0_sysvq0asl heapLinks_0;}
MemRegion_0_sysvq0asl;
typedef struct Rtti_0_sysvq0asl{
  NI64 dl_0;
  NU32* dy_0;
  void* mt_0[];}
Rtti_0_sysvq0asl;
typedef struct Single_0_sysvq0asl{
  NU32 bits_0;}
Single_0_sysvq0asl;
typedef struct FloatingDecimal32_0_sysvq0asl{
  NU32 digits_0;
  NI64 exponent_0;}
FloatingDecimal32_0_sysvq0asl;
typedef struct Double_0_sysvq0asl{
  NU64 bits_0;}
Double_0_sysvq0asl;
typedef struct uint64x2_0_sysvq0asl{
  NU64 hi_0;
  NU64 lo_0;}
uint64x2_0_sysvq0asl;
typedef struct MulCmp_0_sysvq0asl{
  NU64 mul_0;
  NU64 cmp_0;}
MulCmp_0_sysvq0asl;
typedef struct FloatingDecimal64_0_sysvq0asl{
  NU64 significand_0;
  NI64 exponent_0;}
FloatingDecimal64_0_sysvq0asl;
typedef NU8 ErrorCode_0_sysvq0asl;

#define Success_0_sysvq0asl ((NU8)IL64(0))
#define OverflowError_0_sysvq0asl ((NU8)IL64(1))
#define Failure_0_sysvq0asl ((NU8)IL64(2))
#define BugError_0_sysvq0asl ((NU8)IL64(3))
#define IndexError_0_sysvq0asl ((NU8)IL64(4))
#define RangeError_0_sysvq0asl ((NU8)IL64(5))
#define OverlapError_0_sysvq0asl ((NU8)IL64(6))
#define SyntaxError_0_sysvq0asl ((NU8)IL64(7))
#define OutOfMemError_0_sysvq0asl ((NU8)IL64(8))
#define DiskFullError_0_sysvq0asl ((NU8)IL64(9))
#define StackOverflow_0_sysvq0asl ((NU8)IL64(10))
#define IOError_0_sysvq0asl ((NU8)IL64(11))
#define ValueError_0_sysvq0asl ((NU8)IL64(12))
#define KeyError_0_sysvq0asl ((NU8)IL64(13))
#define EndOfStreamError_0_sysvq0asl ((NU8)IL64(14))
#define SkipError_0_sysvq0asl ((NU8)IL64(15))
#define FullError_0_sysvq0asl ((NU8)IL64(16))
#define EmptyError_0_sysvq0asl ((NU8)IL64(17))
#define BusyError_0_sysvq0asl ((NU8)IL64(18))
#define DeadResource_0_sysvq0asl ((NU8)IL64(19))
#define ResourceExhaustedError_0_sysvq0asl ((NU8)IL64(20))
#define DescriptorExhaustedError_0_sysvq0asl ((NU8)IL64(21))
#define PermissionDenied_0_sysvq0asl ((NU8)IL64(22))
#define RetryError_0_sysvq0asl ((NU8)IL64(23))
#define TimeoutError_0_sysvq0asl ((NU8)IL64(24))
#define InterruptedError_0_sysvq0asl ((NU8)IL64(25))
#define DeadlockError_0_sysvq0asl ((NU8)IL64(26))
#define LockedError_0_sysvq0asl ((NU8)IL64(27))
#define FormatMismatch_0_sysvq0asl ((NU8)IL64(28))
#define AlreadyConnected_0_sysvq0asl ((NU8)IL64(29))
#define AddressNotAvailable_0_sysvq0asl ((NU8)IL64(30))
#define AddressFamilyUnsupported_0_sysvq0asl ((NU8)IL64(31))
#define BadOperation_0_sysvq0asl ((NU8)IL64(32))
#define AbortedOperation_0_sysvq0asl ((NU8)IL64(33))
#define UnimplementedOperation_0_sysvq0asl ((NU8)IL64(34))
#define AlreadyInProgress_0_sysvq0asl ((NU8)IL64(35))
#define NameTooLong_0_sysvq0asl ((NU8)IL64(36))
#define NameExists_0_sysvq0asl ((NU8)IL64(37))
#define NameNotFound_0_sysvq0asl ((NU8)IL64(38))
#define ContentTooLong_0_sysvq0asl ((NU8)IL64(39))
#define BadDescriptor_0_sysvq0asl ((NU8)IL64(40))
#define BadExecutable_0_sysvq0asl ((NU8)IL64(41))
#define BadLink_0_sysvq0asl ((NU8)IL64(42))
#define BadProtocol_0_sysvq0asl ((NU8)IL64(43))
#define ProtocolError_0_sysvq0asl ((NU8)IL64(44))
#define ReadonlyProtection_0_sysvq0asl ((NU8)IL64(45))
#define SegFault_0_sysvq0asl ((NU8)IL64(46))
#define DiskCorruption_0_sysvq0asl ((NU8)IL64(47))
#define Disconnected_0_sysvq0asl ((NU8)IL64(48))
#define RefusedConnection_0_sysvq0asl ((NU8)IL64(49))
#define UnreachableHost_0_sysvq0asl ((NU8)IL64(50))
#define UnrecoverableState_0_sysvq0asl ((NU8)IL64(51))
#define AuthenticationRequired_0_sysvq0asl ((NU8)IL64(52))
#define RedirectError_0_sysvq0asl ((NU8)IL64(53))
#define Reserved1_0_sysvq0asl ((NU8)IL64(54))
#define Reserved2_0_sysvq0asl ((NU8)IL64(55))
#define Reserved3_0_sysvq0asl ((NU8)IL64(56))
#define Reserved4_0_sysvq0asl ((NU8)IL64(57))
#define Reserved5_0_sysvq0asl ((NU8)IL64(58))
#define Reserved6_0_sysvq0asl ((NU8)IL64(59))
#define Reserved7_0_sysvq0asl ((NU8)IL64(60))
#define Reserved8_0_sysvq0asl ((NU8)IL64(61))
#define Reserved9_0_sysvq0asl ((NU8)IL64(62))
typedef N_NIMCALL_PTR(Continuation_0_sysvq0asl,  X60Qt_0_IAptrSX43oroutineX42ase0sysvq0aslZSX43ontinuation0R22AnimcallZAfalseZAR61_sysvq0asl)(CoroutineBase_0_sysvq0asl*);
typedef struct Continuation_0_sysvq0asl{
  X60Qt_0_IAptrSX43oroutineX42ase0sysvq0aslZSX43ontinuation0R22AnimcallZAfalseZAR61_sysvq0asl fn_0;
  CoroutineBase_0_sysvq0asl* env_0;}
Continuation_0_sysvq0asl;
typedef struct CoroutineBase_0_sysvq0asl{
  RootObj_0_sysvq0asl Q;
  Continuation_0_sysvq0asl caller_0;
  CoroutineBase_0_sysvq0asl* callee_0;}
CoroutineBase_0_sysvq0asl;
typedef NU8 TypeOfMode_0_sysvq0asl;

#define typeOfProc_0_sysvq0asl ((NU8)IL64(0))
#define typeOfIter_0_sysvq0asl ((NU8)IL64(1))
typedef struct Exception_0_sysvq0asl{
  RootObj_0_sysvq0asl Q;
  string_0_sysvq0asl msg_0;}
Exception_0_sysvq0asl;
typedef struct openArray_0_Ijk0jkw1_sysvq0asl{
  NC8* a_0;
  NI64 len_0;}
openArray_0_Ijk0jkw1_sysvq0asl;
typedef struct HSlice_0_I6e0t4q1_sysvq0asl{
  NI64 a_0;
  NI64 b_0;}
HSlice_0_I6e0t4q1_sysvq0asl;
typedef struct HSlice_0_Ii5kgy01_sysvq0asl{
  NI64 a_0;
  NI64 b_0;}
HSlice_0_Ii5kgy01_sysvq0asl;
typedef struct X60Qt_0_IAarrayAuS8ZS32_sysvq0asl{
  NU8 a[IL64(32)];}
X60Qt_0_IAarrayAuS8ZS32_sysvq0asl;
typedef struct X60Qt_0_IArefSX52ootX4fbj0sysvq0asl_sysvq0asl{
  NI r_00;
  RootObj_0_sysvq0asl d_00;}
X60Qt_0_IArefSX52ootX4fbj0sysvq0asl_sysvq0asl;
typedef struct X60Qt_0_IAarraySstring0sysvq0aslS10_sysvq0asl{
  string_0_sysvq0asl a[IL64(10)];}
X60Qt_0_IAarraySstring0sysvq0aslS10_sysvq0asl;
typedef N_NIMCALL_PTR(void,  X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl)(void);
typedef struct X60Qt_0_IAarrayAuS8ZS256_sysvq0asl{
  NU8 a[IL64(256)];}
X60Qt_0_IAarrayAuS8ZS256_sysvq0asl;
typedef struct X60Qt_0_IAarrayAiS8ZS256_sysvq0asl{
  NI8 a[IL64(256)];}
X60Qt_0_IAarrayAiS8ZS256_sysvq0asl;
typedef struct X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl{
  NI64 fld_0;
  NI64 fld_1;}
X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl;
typedef N_NIMCALL_PTR(void,  X60Qt_0_IAiS64ZSEAnimcallZAfalseZAR17_sysvq0asl)(NI64);
typedef struct X60Qt_0_IAarrayAiS8ZS100_sysvq0asl{
  NI8 a[IL64(100)];}
X60Qt_0_IAarrayAiS8ZS100_sysvq0asl;
typedef struct X60Qt_0_IAarrayAcS8ZS200_sysvq0asl{
  NC8 a[IL64(200)];}
X60Qt_0_IAarrayAcS8ZS200_sysvq0asl;
typedef struct X60Qt_0_IAarrayAuS64ZS77_sysvq0asl{
  NU64 a[IL64(77)];}
X60Qt_0_IAarrayAuS64ZS77_sysvq0asl;
typedef struct X60Qt_0_IAarraySuint64x20sysvq0aslS619_sysvq0asl{
  uint64x2_0_sysvq0asl a[IL64(619)];}
X60Qt_0_IAarraySuint64x20sysvq0aslS619_sysvq0asl;
typedef struct X60Qt_0_IAarraySX4dulX43mp0sysvq0aslS25_sysvq0asl{
  MulCmp_0_sysvq0asl a[IL64(25)];}
X60Qt_0_IAarraySX4dulX43mp0sysvq0aslS25_sysvq0asl;
typedef struct X60Qt_0_IAarrayAcS8ZS16_sysvq0asl{
  NC8 a[IL64(16)];}
X60Qt_0_IAarrayAcS8ZS16_sysvq0asl;
typedef struct X60Qt_0_IAarrayAcS8ZS65_sysvq0asl{
  NC8 a[IL64(65)];}
X60Qt_0_IAarrayAcS8ZS65_sysvq0asl;
typedef N_NIMCALL_PTR(Continuation_0_sysvq0asl,  X60Qt_0_ISX43ontinuation0sysvq0aslSR0AnimcallZAfalseZAR37_sysvq0asl)(Continuation_0_sysvq0asl);
typedef N_NIMCALL_PTR(void,  X60Qt_0_IAptrSX43oroutineX42ase0sysvq0aslZSEAnimcallZAfalseZAR44_sysvq0asl)(CoroutineBase_0_sysvq0asl*);
typedef struct X60Qt_0_IArefSX45xception0sysvq0asl_sysvq0asl{
  NI r_00;
  Exception_0_sysvq0asl d_00;}
X60Qt_0_IArefSX45xception0sysvq0asl_sysvq0asl;
typedef N_NIMCALL_PTR(void,  X60Qt_0_ISX45xception0sysvq0aslSEAnimcallZAfalseZAR33_sysvq0asl)(Exception_0_sysvq0asl*);
int cKill_0_sysvq0asl(int pid_0, int sig_0) __asm__(NIM_ASM_PREFIX "kill");
int cGetpid_0_sysvq0asl(void) __asm__(NIM_ASM_PREFIX "getpid");
void __attribute__((noreturn)) cExitSys_0_sysvq0asl(int code_0) __asm__(NIM_ASM_PREFIX "_exit");
void* mmap_0_sysvq0asl(void* adr_0, size_t len_2, int prot_0, int flags_0, int fildes_0, NI64 off_0) __asm__(NIM_ASM_PREFIX "mmap");
NI64 len_4_sysvq0asl(string_0_sysvq0asl s_34);
static inline void nimStrWasMoved(string_0_sysvq0asl* s_43);
void nimStrDestroy(string_0_sysvq0asl s_44);
static inline string_0_sysvq0asl nimStrDup(string_0_sysvq0asl s_45);
void add_1_sysvq0asl(string_0_sysvq0asl* s_52, NC8 c_14);
NC8 getQ_9_sysvq0asl(string_0_sysvq0asl s_57, NI64 i_14);
static inline void putQ_9_sysvq0asl(string_0_sysvq0asl* s_58, NI64 i_15, NC8 c_15);
string_0_sysvq0asl substr_0_sysvq0asl(string_0_sysvq0asl s_59, NI64 first_0, NI64 last_0);
string_0_sysvq0asl ampQ_0_sysvq0asl(string_0_sysvq0asl a_58, string_0_sysvq0asl b_20);
static inline void arcInc_0_sysvq0asl(NI64* memLoc_0);
static inline NB8 arcDec_0_sysvq0asl(NI64* memLoc_1);
static inline NB8 arcIsUnique_0_sysvq0asl(NI64* memLoc_2);
NI64 cWriteErr_0_sysvq0asl(int fd_0, void* buf_0, NU64 n_8) __asm__(NIM_ASM_PREFIX "write");
N_NOINLINE void __attribute__((noreturn)) panic_0_sysvq0asl(string_0_sysvq0asl s_74);
static inline NI64 nimIcheckB(NI64 i_19, NI64 b_25);
static inline NU64 nimUcheckB(NU64 i_21, NU64 b_27);
void* dlopen_0_sysvq0asl(NC8* path_1, int mode_0) __asm__(NIM_ASM_PREFIX "dlopen");
void* dlsym_0_sysvq0asl(void* lib_1, NC8* name_2) __asm__(NIM_ASM_PREFIX "dlsym");
static inline void inc_0_Iwdk9lf_sysvq0asl(NI64* x_390, NI64 y_217);
static inline void dec_0_Iw9ew8i1_sysvq0asl(NI64* x_392, NI64 y_219);
static inline void listAdd_0_Ik4wxhz_sysvq0asl(SmallChunk_0_sysvq0asl** head_5, SmallChunk_0_sysvq0asl* c_42);
static inline void listRemove_0_Ibzev091_sysvq0asl(SmallChunk_0_sysvq0asl** head_6, SmallChunk_0_sysvq0asl* c_43);
N_NOINLINE void raiseIndexError3_0_Ice8haj1_sysvq0asl(NI64 i_77, NI64 a_89, NI64 b_41);
N_NOINLINE void raiseIndexError3_0_Ils6gq61_sysvq0asl(NU64 i_78, NU64 a_90, NU64 b_42);
static inline void inc_1_Irn1g7r1_mat7cnfv21(NI64* x_154);
LongString_0_sysvq0asl const strlit_0_I17787898778150197797_sysvq0asl = {
  .fullLen_0 = IL64(143), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../../../../../nix/store/k6w9mr6jan950vv5lxkfzgh0pw94jgjv-nimony-0.6.0/lib/std/system/stringimpl.nim(596, 37): i < len(s) [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I8081769352426431819_sysvq0asl = {
  .fullLen_0 = IL64(139), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../../../../../nix/store/k6w9mr6jan950vv5lxkfzgh0pw94jgjv-nimony-0.6.0/lib/std/system/stringimpl.nim(596, 37): 0 <= i [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I6290767771972150606_sysvq0asl = {
  .fullLen_0 = IL64(143), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../../../../../nix/store/k6w9mr6jan950vv5lxkfzgh0pw94jgjv-nimony-0.6.0/lib/std/system/stringimpl.nim(600, 45): i < len(s) [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I3404901998373565316_sysvq0asl = {
  .fullLen_0 = IL64(139), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../../../../../nix/store/k6w9mr6jan950vv5lxkfzgh0pw94jgjv-nimony-0.6.0/lib/std/system/stringimpl.nim(600, 45): 0 <= i [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I15539159382304113184_sysvq0asl = {
  .fullLen_0 = IL64(27), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "invalid object conversion: "}
;
LongString_0_sysvq0asl const strlit_0_I14281474217946372742_sysvq0asl = {
  .fullLen_0 = IL64(35), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "cannot dispatch; dispatcher is nil\012"}
;
LongString_0_sysvq0asl const strlit_0_I16690852185662743073_sysvq0asl = {
  .fullLen_0 = IL64(16), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "could not load: "}
;
LongString_0_sysvq0asl const strlit_0_I10604297744791418982_sysvq0asl = {
  .fullLen_0 = IL64(18), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "could not import: "}
;
LongString_0_sysvq0asl const strlit_0_I11614695157650328859_sysvq0asl = {
  .fullLen_0 = IL64(21), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "index out of bounds: "}
;
X60Qt_0_IAarraySstring0sysvq0aslS10_sysvq0asl const NegTen_0_sysvq0asl = {
  .a = {
    {
      .bytes_0 = 3157250ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3222786ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3288322ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3353858ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3419394ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3484930ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3550466ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3616002ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3681538ull, .more_0 = NIM_NIL}
    , {
      .bytes_0 = 3747074ull, .more_0 = NIM_NIL}}}
;
X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl gExitFlush_0_sysvq0asl;
X60Qt_0_IAarrayAiS8ZS256_sysvq0asl const fsLookupTable_0_sysvq0asl = {
  .a = {
    ((NI8)IL64(-1)), ((NI8)IL64(0)), ((NI8)IL64(1)), ((NI8)IL64(1)), ((NI8)IL64(2)), ((NI8)IL64(2)), ((NI8)IL64(2)), ((NI8)IL64(2)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(3)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(4)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(5)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(6)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7)), ((NI8)IL64(7))}}
;
__thread MemRegion_0_sysvq0asl allocator_0_sysvq0asl;
__thread NI64 missingBytes_0_sysvq0asl;
X60Qt_0_IAiS64ZSEAnimcallZAfalseZAR17_sysvq0asl oomHandler_0_sysvq0asl;
__thread X60Qt_0_IArefSX45xception0sysvq0asl_sysvq0asl* exc_0_sysvq0asl;
NB8 X60QiniGuard_0_sysvq0asl;
static inline NI64 min_3_sysvq0asl(NI64 x_205, NI64 y_162){
  NI64 result_6;
  NI64 X60Qx_3;
  if (x_205 <= y_162){
    X60Qx_3 = x_205;}
  else {
    X60Qx_3 = y_162;}
  result_6 = X60Qx_3;
  return result_6;}
static inline NI64 max_3_sysvq0asl(NI64 x_212, NI64 y_169){
  NI64 result_13;
  NI64 X60Qx_9;
  if (y_169 <= x_212){
    X60Qx_9 = x_212;}
  else {
    X60Qx_9 = y_169;}
  result_13 = X60Qx_9;
  return result_13;}
string_0_sysvq0asl dollarQ_0_sysvq0asl(NU64 x_226){
  string_0_sysvq0asl result_19;
  result_19 = (string_0_sysvq0asl){
    .bytes_0 = 0ull, .more_0 = NIM_NIL}
  ;
  if (x_226 < ((NU64)IL64(10))){
    nimStrDestroy(result_19);
    NI64 X60Qx_90 = nimIcheckB(((NI64)x_226), IL64(9));
    string_0_sysvq0asl X60Qx_91 = substr_0_sysvq0asl(NegTen_0_sysvq0asl.a[X60Qx_90], IL64(1), IL64(1));
    result_19 = X60Qx_91;}
  else {
    NU64 y_210 = x_226;
    {
      while (NIM_TRUE){
        add_1_sysvq0asl((&result_19), ((NC8)((NU64)(((NU64)(y_210 % 10ull)) + ((NU64)(NC8)'0')))));
        y_210 = ((NU64)(y_210 / 10ull));
        if (y_210 == 0ull){
          goto whileStmtLabel_0;}}}
    whileStmtLabel_0: ;
    NI64 X60Qx_92 = len_4_sysvq0asl(result_19);
    NI64 last_3 = ((NI64)(X60Qx_92 - IL64(1)));
    NI64 i_25 = IL64(0);
    NI64 X60Qx_93 = len_4_sysvq0asl(result_19);
    NI64 b_32 = ((NI64)(X60Qx_93 / IL64(2)));
    {
      while (i_25 < b_32){
        NC8 ch_1 = getQ_9_sysvq0asl(result_19, i_25);
        NC8 X60Qx_94 = getQ_9_sysvq0asl(result_19, ((NI64)(last_3 - i_25)));
        putQ_9_sysvq0asl((&result_19), i_25, X60Qx_94);
        putQ_9_sysvq0asl((&result_19), ((NI64)(last_3 - i_25)), ch_1);
        inc_1_Irn1g7r1_mat7cnfv21((&i_25));}}
    whileStmtLabel_1: ;}
  return result_19;}
string_0_sysvq0asl dollarQ_1_sysvq0asl(NI64 x_227){
  string_0_sysvq0asl result_20;
  nimStrWasMoved((&result_20));
  if (x_227 < IL64(0)){
    if (IL64(-10) < x_227){
      nimStrDestroy(result_20);
      NI64 X60Qx_95 = nimIcheckB(((NI64)((NI64)-x_227)), IL64(9));
      string_0_sysvq0asl X60Qx_96 = nimStrDup(NegTen_0_sysvq0asl.a[X60Qx_95]);
      result_20 = X60Qx_96;}
    else {
      if (x_227 == ((NI64)(IL64(-9223372036854775807) - IL64(1)))){
        string_0_sysvq0asl X60Qtmp_0 = dollarQ_0_sysvq0asl(((NU64)x_227));
        nimStrDestroy(result_20);
        string_0_sysvq0asl X60Qx_97 = ampQ_0_sysvq0asl((string_0_sysvq0asl){
          .bytes_0 = 11521ull, .more_0 = NIM_NIL}
        , X60Qtmp_0);
        result_20 = X60Qx_97;
        nimStrDestroy(X60Qtmp_0);}
      else {
        string_0_sysvq0asl X60Qtmp_1 = dollarQ_1_sysvq0asl(((NI64)(IL64(0) - x_227)));
        nimStrDestroy(result_20);
        string_0_sysvq0asl X60Qx_98 = ampQ_0_sysvq0asl((string_0_sysvq0asl){
          .bytes_0 = 11521ull, .more_0 = NIM_NIL}
        , X60Qtmp_1);
        result_20 = X60Qx_98;
        nimStrDestroy(X60Qtmp_1);}}}
  else {
    if (x_227 < IL64(10)){
      nimStrDestroy(result_20);
      result_20 = (string_0_sysvq0asl){
        .bytes_0 = 0ull, .more_0 = NIM_NIL}
      ;
      add_1_sysvq0asl((&result_20), ((NC8)((NI64)(x_227 + ((NI64)(NC8)'0')))));}
    else {
      nimStrDestroy(result_20);
      string_0_sysvq0asl X60Qx_99 = dollarQ_0_sysvq0asl(((NU64)x_227));
      result_20 = X60Qx_99;}}
  return result_20;}
N_NIMCALL(void, nimNoopFlush_0_sysvq0asl)(void){
  }
static inline void setExitFlush_0_sysvq0asl(X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl p_0){
  gExitFlush_0_sysvq0asl = p_0;}
void nimFlushStdStreams(void){
  gExitFlush_0_sysvq0asl();}
void __attribute__((noreturn)) cAbort_0_sysvq0asl(void){
  gExitFlush_0_sysvq0asl();
  int X60Qx_104 = cGetpid_0_sysvq0asl();
  int X60Qx_105 = cKill_0_sysvq0asl(X60Qx_104, ((NI32)IL64(6)));
  cExitSys_0_sysvq0asl(((NI32)IL64(127)));}
static inline void copyMem_0_sysvq0asl(void* dest_4, void* src_3, NI64 size_3){
  memcpy(dest_4, src_3, ((size_t)size_3));}
static inline void zeroMem_0_sysvq0asl(void* dest_6, NI64 size_6){
  memset(dest_6, ((int)IL64(0)), ((size_t)size_6));}
N_NOINLINE void __attribute__((noreturn)) raiseOutOfMem_0_sysvq0asl(void){
  cAbort_0_sysvq0asl();}
static inline NI64 roundup_0_sysvq0asl(NI64 x_299, NI64 v_0){
  NI64 result_31;
  result_31 = ((NI64)(((NI64)(x_299 + ((NI64)(v_0 - IL64(1))))) & ((NI64) ~ ((NI64)(v_0 - IL64(1))))));
  return result_31;}
static inline void* osAllocPages_0_sysvq0asl(NI64 size_7){
  void* result_32;
  void* X60Qx_111 = mmap_0_sysvq0asl(NIM_NIL, ((size_t)size_7), ((int)((NI64)(((NI64)IL64(1)) | ((NI64)IL64(2))))), ((int)((NI64)(((NI64)(((NI64)IL64(32)) | ((NI64)IL64(2)))) | ((NI64)IL64(0))))), ((int)IL64(-1)), IL64(0));
  result_32 = X60Qx_111;
  {
    if (result_32 == NIM_NIL){
      goto X60QL_14;}
    {
      if ((!(result_32 == ((void*)IL64(-1))))){
        goto X60QL_13;}}
    X60QL_14: ;
    raiseOutOfMem_0_sysvq0asl();}
  X60QL_13: ;
  return result_32;}
static inline NI64 msbit_0_sysvq0asl(NU32 x_304){
  NI64 result_35;
  NI64 X60Qx_15;
  if (x_304 <= ((NU32)65535ull)){
    NI64 X60Qx_16;
    if (x_304 <= ((NU32)IL64(255))){
      X60Qx_16 = IL64(0);}
    else {
      X60Qx_16 = IL64(8);}
    X60Qx_15 = X60Qx_16;}
  else {
    NI64 X60Qx_17;
    if (x_304 <= ((NU32)16777215ull)){
      X60Qx_17 = IL64(16);}
    else {
      X60Qx_17 = IL64(24);}
    X60Qx_15 = X60Qx_17;}
  NI64 a_79 = X60Qx_15;
  NU64 X60Qx_113 = nimUcheckB(((NU8)((NU32)(x_304 >> a_79))), IL64(255));
  result_35 = ((NI64)(((NI64)fsLookupTable_0_sysvq0asl.a[X60Qx_113]) + a_79));
  return result_35;}
static inline NI64 lsbit_0_sysvq0asl(NU32 x_305){
  NI64 result_36;
  NI64 X60Qx_114 = msbit_0_sysvq0asl(((NU32)(x_305 & ((NU32)(((NU32) ~ x_305) + ((NU32)IL64(1)))))));
  result_36 = X60Qx_114;
  return result_36;}
static inline void setBit_0_sysvq0asl(NI64 nr_0, NU32* dest_7){
  (*dest_7) = ((NU32)((*dest_7) | ((NU32)(((NU32)1ull) << ((NI64)(nr_0 & IL64(31)))))));}
static inline void clearBit_0_sysvq0asl(NI64 nr_1, NU32* dest_8){
  (*dest_8) = ((NU32)((*dest_8) & ((NU32) ~ ((NU32)(((NU32)1ull) << ((NI64)(nr_1 & IL64(31))))))));}
static inline void mappingSearch_0_sysvq0asl(NI64* r_0, NI64* fl_0, NI64* sl_0){
  NI64 X60Qx_115 = msbit_0_sysvq0asl(((NU32)(*r_0)));
  NI64 X60Qx_116 = roundup_0_sysvq0asl(((NI64)(IL64(1) << ((NI64)(X60Qx_115 - ((NI64)IL64(5)))))), ((NI64)IL64(4096)));
  NI64 t_3 = ((NI64)(X60Qx_116 - IL64(1)));
  (*r_0) = ((NI64)((*r_0) + t_3));
  (*r_0) = ((NI64)((*r_0) & ((NI64) ~ t_3)));
  NI64 X60Qx_117 = min_3_sysvq0asl((*r_0), ((NI64)IL64(1056964608)));
  (*r_0) = ((NI64)X60Qx_117);
  NI64 X60Qx_118 = msbit_0_sysvq0asl(((NU32)(*r_0)));
  (*fl_0) = X60Qx_118;
  (*sl_0) = ((NI64)(((NI64)(((NI64)(*r_0)) >> ((NU64)((NI64)((*fl_0) - ((NI64)IL64(5))))))) - ((NI64)IL64(32))));
  dec_0_Iw9ew8i1_sysvq0asl(fl_0, ((NI64)IL64(6)));}
static inline X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl mappingInsert_0_sysvq0asl(NI64 r_1){
  X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl result_37;
  NI64 fl_4 = msbit_0_sysvq0asl(((NU32)r_1));
  NI64 sl_6 = ((NI64)(((NI64)(((NI64)r_1) >> ((NU64)((NI64)(fl_4 - ((NI64)IL64(5))))))) - ((NI64)IL64(32))));
  fl_4 = ((NI64)(fl_4 - ((NI64)IL64(6))));
  result_37 = (X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl){
    .fld_0 = fl_4, .fld_1 = sl_6}
  ;
  return result_37;}
static inline BigChunk_0_sysvq0asl* findSuitableBlock_0_sysvq0asl(MemRegion_0_sysvq0asl* a_8, NI64* fl_1, NI64* sl_1){
  BigChunk_0_sysvq0asl* result_38;
  NI64 X60Qx_119 = nimIcheckB((*fl_1), IL64(23));
  NU32 tmp_2 = ((NU32)((*a_8).slBitmap_0.a[X60Qx_119] & ((NU32)(((NU32) ~ ((NU32)0ull)) << (*sl_1)))));
  result_38 = NIM_NIL;
  if ((!(tmp_2 == ((NU32)IL64(0))))){
    NI64 X60Qx_120 = lsbit_0_sysvq0asl(tmp_2);
    (*sl_1) = X60Qx_120;
    NI64 X60Qx_121 = nimIcheckB((*fl_1), IL64(23));
    NI64 X60Qx_122 = nimIcheckB((*sl_1), IL64(31));
    result_38 = (*a_8).matrix_0.a[X60Qx_121].a[X60Qx_122];}
  else {
    NI64 X60Qx_123 = lsbit_0_sysvq0asl(((NU32)((*a_8).flBitmap_0 & ((NU32)(((NU32) ~ ((NU32)0ull)) << ((NI64)((*fl_1) + IL64(1))))))));
    (*fl_1) = X60Qx_123;
    if (IL64(0) < (*fl_1)){
      NI64 X60Qx_124 = nimIcheckB((*fl_1), IL64(23));
      NI64 X60Qx_125 = lsbit_0_sysvq0asl((*a_8).slBitmap_0.a[X60Qx_124]);
      (*sl_1) = X60Qx_125;
      NI64 X60Qx_126 = nimIcheckB((*fl_1), IL64(23));
      NI64 X60Qx_127 = nimIcheckB((*sl_1), IL64(31));
      result_38 = (*a_8).matrix_0.a[X60Qx_126].a[X60Qx_127];}}
  return result_38;}
void removeChunkFromMatrix_0_sysvq0asl(MemRegion_0_sysvq0asl* a_9, BigChunk_0_sysvq0asl* b_9){
  X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl X60Qtmptup_0 = mappingInsert_0_sysvq0asl((*b_9).Q.size_0);
  NI64 fl_5 = X60Qtmptup_0.fld_0;
  NI64 sl_7 = X60Qtmptup_0.fld_1;
  if ((!((*b_9).next_0 == NIM_NIL))){
    (*(*b_9).next_0).prev_0 = (*b_9).prev_0;}
  if ((!((*b_9).prev_0 == NIM_NIL))){
    (*(*b_9).prev_0).next_0 = (*b_9).next_0;}
  NI64 X60Qx_128 = nimIcheckB(fl_5, IL64(23));
  NI64 X60Qx_129 = nimIcheckB(sl_7, IL64(31));
  if ((*a_9).matrix_0.a[X60Qx_128].a[X60Qx_129] == b_9){
    NI64 X60Qx_130 = nimIcheckB(fl_5, IL64(23));
    NI64 X60Qx_131 = nimIcheckB(sl_7, IL64(31));
    (*a_9).matrix_0.a[X60Qx_130].a[X60Qx_131] = (*b_9).next_0;
    NI64 X60Qx_132 = nimIcheckB(fl_5, IL64(23));
    NI64 X60Qx_133 = nimIcheckB(sl_7, IL64(31));
    if ((*a_9).matrix_0.a[X60Qx_132].a[X60Qx_133] == NIM_NIL){
      NI64 X60Qx_134 = nimIcheckB(fl_5, IL64(23));
      clearBit_0_sysvq0asl(sl_7, (&(*a_9).slBitmap_0.a[X60Qx_134]));
      NI64 X60Qx_135 = nimIcheckB(fl_5, IL64(23));
      if ((*a_9).slBitmap_0.a[X60Qx_135] == ((NU32)0ull)){
        clearBit_0_sysvq0asl(fl_5, (&(*a_9).flBitmap_0));}}}
  (*b_9).prev_0 = NIM_NIL;
  (*b_9).next_0 = NIM_NIL;}
void removeChunkFromMatrix2_0_sysvq0asl(MemRegion_0_sysvq0asl* a_10, BigChunk_0_sysvq0asl* b_10, NI64 fl_3, NI64 sl_3){
  NI64 X60Qx_136 = nimIcheckB(fl_3, IL64(23));
  NI64 X60Qx_137 = nimIcheckB(sl_3, IL64(31));
  (*a_10).matrix_0.a[X60Qx_136].a[X60Qx_137] = (*b_10).next_0;
  NI64 X60Qx_138 = nimIcheckB(fl_3, IL64(23));
  NI64 X60Qx_139 = nimIcheckB(sl_3, IL64(31));
  if ((!((*a_10).matrix_0.a[X60Qx_138].a[X60Qx_139] == NIM_NIL))){
    NI64 X60Qx_140 = nimIcheckB(fl_3, IL64(23));
    NI64 X60Qx_141 = nimIcheckB(sl_3, IL64(31));
    (*(*a_10).matrix_0.a[X60Qx_140].a[X60Qx_141]).prev_0 = NIM_NIL;}
  else {
    NI64 X60Qx_142 = nimIcheckB(fl_3, IL64(23));
    clearBit_0_sysvq0asl(sl_3, (&(*a_10).slBitmap_0.a[X60Qx_142]));
    NI64 X60Qx_143 = nimIcheckB(fl_3, IL64(23));
    if ((*a_10).slBitmap_0.a[X60Qx_143] == ((NU32)0ull)){
      clearBit_0_sysvq0asl(fl_3, (&(*a_10).flBitmap_0));}}
  (*b_10).prev_0 = NIM_NIL;
  (*b_10).next_0 = NIM_NIL;}
void addChunkToMatrix_0_sysvq0asl(MemRegion_0_sysvq0asl* a_11, BigChunk_0_sysvq0asl* b_11){
  X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl X60Qtmptup_1 = mappingInsert_0_sysvq0asl((*b_11).Q.size_0);
  NI64 fl_6 = X60Qtmptup_1.fld_0;
  NI64 sl_8 = X60Qtmptup_1.fld_1;
  (*b_11).prev_0 = NIM_NIL;
  NI64 X60Qx_144 = nimIcheckB(fl_6, IL64(23));
  NI64 X60Qx_145 = nimIcheckB(sl_8, IL64(31));
  (*b_11).next_0 = (*a_11).matrix_0.a[X60Qx_144].a[X60Qx_145];
  NI64 X60Qx_146 = nimIcheckB(fl_6, IL64(23));
  NI64 X60Qx_147 = nimIcheckB(sl_8, IL64(31));
  if ((!((*a_11).matrix_0.a[X60Qx_146].a[X60Qx_147] == NIM_NIL))){
    NI64 X60Qx_148 = nimIcheckB(fl_6, IL64(23));
    NI64 X60Qx_149 = nimIcheckB(sl_8, IL64(31));
    (*(*a_11).matrix_0.a[X60Qx_148].a[X60Qx_149]).prev_0 = b_11;}
  NI64 X60Qx_150 = nimIcheckB(fl_6, IL64(23));
  NI64 X60Qx_151 = nimIcheckB(sl_8, IL64(31));
  (*a_11).matrix_0.a[X60Qx_150].a[X60Qx_151] = b_11;
  NI64 X60Qx_152 = nimIcheckB(fl_6, IL64(23));
  setBit_0_sysvq0asl(sl_8, (&(*a_11).slBitmap_0.a[X60Qx_152]));
  setBit_0_sysvq0asl(fl_6, (&(*a_11).flBitmap_0));}
static inline void incCurrMem_0_sysvq0asl(MemRegion_0_sysvq0asl* a_12, NI64 bytes_0){
  {
    NI64* x_0h63 = (&(*a_12).currMem_0);
    {
      (*x_0h63) = ((NI64)((*x_0h63) + bytes_0));
      returnLabel_0h65: ;}}}
void* allocPages_0_sysvq0asl(MemRegion_0_sysvq0asl* a_15, NI64 size_15){
  void* result_40;
  void* X60Qx_155;
  {
    {
      void* X60Qx_0h81 = mmap_0_sysvq0asl(NIM_NIL, ((size_t)size_15), ((int)((NI64)(((NI64)IL64(1)) | ((NI64)IL64(2))))), ((int)((NI64)(((NI64)(((NI64)IL64(32)) | ((NI64)IL64(2)))) | ((NI64)IL64(0))))), ((int)IL64(-1)), IL64(0));
      X60Qx_155 = X60Qx_0h81;
      {
        if (X60Qx_155 == NIM_NIL){
          goto X60QL_0h82;}
        {
          if ((!(X60Qx_155 == ((void*)IL64(-1))))){
            goto X60QL_0h83;}}
        X60QL_0h82: ;
        raiseOutOfMem_0_sysvq0asl();}
      X60QL_0h83: ;
      returnLabel_0h84: ;}}
  result_40 = X60Qx_155;
  return result_40;}
void* tryAllocPages_0_sysvq0asl(MemRegion_0_sysvq0asl* a_16, NI64 size_16){
  void* result_41;
  void* X60Qx_156;
  {
    {
      void* X60Qx_0h87 = mmap_0_sysvq0asl(NIM_NIL, ((size_t)size_16), ((int)((NI64)(((NI64)IL64(1)) | ((NI64)IL64(2))))), ((int)((NI64)(((NI64)(((NI64)IL64(32)) | ((NI64)IL64(2)))) | ((NI64)IL64(0))))), ((int)IL64(-1)), IL64(0));
      X60Qx_156 = X60Qx_0h87;
      if (X60Qx_156 == ((void*)IL64(-1))){
        X60Qx_156 = NIM_NIL;}
      returnLabel_0h88: ;}}
  result_41 = X60Qx_156;
  return result_41;}
void* llAlloc_0_sysvq0asl(MemRegion_0_sysvq0asl* a_17, NI64 size_17){
  void* result_42;
  if ((((*a_17).llmem_0 == NIM_NIL) || ((*(*a_17).llmem_0).size_0 < size_17))){
    LLChunk_0_sysvq0asl* old_1 = (*a_17).llmem_0;
    void* X60Qx_157 = allocPages_0_sysvq0asl(a_17, ((NI64)IL64(4096)));
    (*a_17).llmem_0 = ((LLChunk_0_sysvq0asl*)X60Qx_157);
    incCurrMem_0_sysvq0asl(a_17, ((NI64)IL64(4096)));
    (*(*a_17).llmem_0).size_0 = ((NI64)(((NI64)IL64(4096)) - sizeof(LLChunk_0_sysvq0asl)));
    (*(*a_17).llmem_0).acc_0 = sizeof(LLChunk_0_sysvq0asl);
    (*(*a_17).llmem_0).next_0 = old_1;}
  result_42 = ((void*)((NI64)(((NI64)(*a_17).llmem_0) + (*(*a_17).llmem_0).acc_0)));
  dec_0_Iw9ew8i1_sysvq0asl((&(*(*a_17).llmem_0).size_0), size_17);
  inc_0_Iwdk9lf_sysvq0asl((&(*(*a_17).llmem_0).acc_0), size_17);
  zeroMem_0_sysvq0asl(result_42, size_17);
  return result_42;}
HeapLinks_0_sysvq0asl* addHeapLink_0_sysvq0asl(MemRegion_0_sysvq0asl* a_18, BigChunk_0_sysvq0asl* p_16, NI64 size_18){
  HeapLinks_0_sysvq0asl* result_43;
  HeapLinks_0_sysvq0asl* it_0 = (&(*a_18).heapLinks_0);
  {
    while (NIM_TRUE){
      if (((!(it_0 == NIM_NIL)) && (((NI64)(((NI64)(((NI64)((NI64)IL64(29))) - ((NI64)((NI64)IL64(0))))) + IL64(1))) <= (*it_0).count_0))){
        it_0 = (*it_0).next_0;}
      else {
        break;}}}
  whileStmtLabel_0: ;
  if (it_0 == NIM_NIL){
    void* X60Qx_158 = llAlloc_0_sysvq0asl(a_18, sizeof(HeapLinks_0_sysvq0asl));
    HeapLinks_0_sysvq0asl* n_11 = ((HeapLinks_0_sysvq0asl*)X60Qx_158);
    (*n_11).next_0 = (*a_18).heapLinks_0.next_0;
    (*a_18).heapLinks_0.next_0 = n_11;
    NI64 X60Qx_159 = nimIcheckB(IL64(0), IL64(29));
    (*n_11).chunks_0.a[X60Qx_159] = (X60Qt_0_IAtupleAptrSX42igX43hunk0sysvq0aslZAiS64_sysvq0asl){
      .fld_0 = p_16, .fld_1 = size_18}
    ;
    (*n_11).count_0 = IL64(1);
    result_43 = n_11;}
  else {
    NI64 L_0 = (*it_0).count_0;
    NI64 X60Qx_160 = nimIcheckB(L_0, IL64(29));
    (*it_0).chunks_0.a[X60Qx_160] = (X60Qt_0_IAtupleAptrSX42igX43hunk0sysvq0aslZAiS64_sysvq0asl){
      .fld_0 = p_16, .fld_1 = size_18}
    ;
    inc_1_Irn1g7r1_mat7cnfv21((&(*it_0).count_0));
    result_43 = it_0;}
  return result_43;}
Trunk_0_sysvq0asl* intSetGet_0_sysvq0asl(IntSet_0_sysvq0asl* t_0, NI64 key_0){
  Trunk_0_sysvq0asl* result_44;
  NI64 X60Qx_161;
  {
    NI64 i_0h92 = ((NI64)(key_0 & ((NI64)IL64(255))));
    {
      if (((IL64(0) <= i_0h92) && (i_0h92 <= IL64(255)))){
        X60Qx_161 = i_0h92;}
      else {
        X60Qx_161 = IL64(0);
        raiseIndexError3_0_Ice8haj1_sysvq0asl(i_0h92, IL64(0), IL64(255));}
      returnLabel_0h95: ;}}
  Trunk_0_sysvq0asl* it_2 = (*t_0).data_0.a[X60Qx_161];
  {
    while ((!(it_2 == NIM_NIL))){
      if ((*it_2).key_0 == key_0){
        return it_2;}
      it_2 = (*it_2).next_0;}}
  whileStmtLabel_0: ;
  result_44 = NIM_NIL;
  return result_44;}
Trunk_0_sysvq0asl* intSetPut_0_sysvq0asl(MemRegion_0_sysvq0asl* a_20, NI64 key_1){
  Trunk_0_sysvq0asl* result_45;
  Trunk_0_sysvq0asl* X60Qx_162 = intSetGet_0_sysvq0asl((&(*a_20).chunkStarts_0), key_1);
  result_45 = X60Qx_162;
  if (result_45 == NIM_NIL){
    void* X60Qx_163 = llAlloc_0_sysvq0asl(a_20, sizeof(Trunk_0_sysvq0asl));
    result_45 = ((Trunk_0_sysvq0asl*)X60Qx_163);
    NI64 X60Qx_164 = nimIcheckB(((NI64)(key_1 & ((NI64)IL64(255)))), IL64(255));
    (*result_45).next_0 = (*a_20).chunkStarts_0.data_0.a[X60Qx_164];
    NI64 X60Qx_165 = nimIcheckB(((NI64)(key_1 & ((NI64)IL64(255)))), IL64(255));
    (*a_20).chunkStarts_0.data_0.a[X60Qx_165] = result_45;
    (*result_45).key_0 = key_1;}
  return result_45;}
NB8 contains_1_sysvq0asl(IntSet_0_sysvq0asl* s_4, NI64 key_2){
  NB8 result_46;
  Trunk_0_sysvq0asl* t_4 = intSetGet_0_sysvq0asl((&(*s_4)), ((NI64)(((NI64)key_2) >> ((NU64)((NI64)IL64(9))))));
  if ((!(t_4 == NIM_NIL))){
    NI64 u_2 = ((NI64)(key_2 & ((NI64)IL64(511))));
    NI64 X60Qx_166 = nimIcheckB(((NI64)(((NI64)u_2) >> ((NU64)((NI64)IL64(6))))), IL64(7));
    result_46 = (!(((NU64)((*t_4).bits_0.a[X60Qx_166] & ((NU64)(((NU64)IL64(1)) << ((NI64)(u_2 & ((NI64)IL64(63)))))))) == ((NU64)IL64(0))));}
  else {
    result_46 = NIM_FALSE;}
  return result_46;}
void incl_2_sysvq0asl(MemRegion_0_sysvq0asl* a_21, NI64 key_3){
  Trunk_0_sysvq0asl* t_5 = intSetPut_0_sysvq0asl(a_21, ((NI64)(((NI64)key_3) >> ((NU64)((NI64)IL64(9))))));
  NI64 u_3 = ((NI64)(key_3 & ((NI64)IL64(511))));
  NI64 X60Qx_167 = nimIcheckB(((NI64)(((NI64)u_3) >> ((NU64)((NI64)IL64(6))))), IL64(7));
  NI64 X60Qx_168 = nimIcheckB(((NI64)(((NI64)u_3) >> ((NU64)((NI64)IL64(6))))), IL64(7));
  (*t_5).bits_0.a[X60Qx_167] = ((NU64)((*t_5).bits_0.a[X60Qx_168] | ((NU64)(((NU64)IL64(1)) << ((NI64)(u_3 & ((NI64)IL64(63))))))));}
void excl_2_sysvq0asl(IntSet_0_sysvq0asl* s_5, NI64 key_4){
  Trunk_0_sysvq0asl* t_6 = intSetGet_0_sysvq0asl((&(*s_5)), ((NI64)(((NI64)key_4) >> ((NU64)((NI64)IL64(9))))));
  if ((!(t_6 == NIM_NIL))){
    NI64 u_4 = ((NI64)(key_4 & ((NI64)IL64(511))));
    NI64 X60Qx_169 = nimIcheckB(((NI64)(((NI64)u_4) >> ((NU64)((NI64)IL64(6))))), IL64(7));
    NI64 X60Qx_170 = nimIcheckB(((NI64)(((NI64)u_4) >> ((NU64)((NI64)IL64(6))))), IL64(7));
    (*t_6).bits_0.a[X60Qx_169] = ((NU64)((*t_6).bits_0.a[X60Qx_170] & ((NU64) ~ ((NU64)(((NU64)IL64(1)) << ((NI64)(u_4 & ((NI64)IL64(63)))))))));}}
static inline NB8 isSmallChunk_0_sysvq0asl(BaseChunk_0_sysvq0asl* c_0){
  NB8 result_47;
  result_47 = ((*c_0).size_0 <= ((NI64)(((NI64)IL64(4096)) - sizeof(SmallChunk_0_sysvq0asl))));
  return result_47;}
static inline NB8 chunkUnused_0_sysvq0asl(BaseChunk_0_sysvq0asl* c_1){
  NB8 result_48;
  result_48 = (((NI64)((*c_1).prevSize_0 & IL64(1))) == IL64(0));
  return result_48;}
static inline NI64 pageIndex_0_sysvq0asl(BaseChunk_0_sysvq0asl* c_2){
  NI64 result_49;
  result_49 = ((NI64)(((NI64)((NI64)c_2)) >> ((NU64)((NI64)IL64(12)))));
  return result_49;}
static inline BaseChunk_0_sysvq0asl* pageAddr_0_sysvq0asl(void* p_18){
  BaseChunk_0_sysvq0asl* result_51;
  result_51 = ((BaseChunk_0_sysvq0asl*)((NI64)(((NI64)p_18) & ((NI64) ~ ((NI64)IL64(4095))))));
  return result_51;}
BigChunk_0_sysvq0asl* requestOsChunks_0_sysvq0asl(MemRegion_0_sysvq0asl* a_22, NI64 size_19){
  BigChunk_0_sysvq0asl* result_52;
  if ((!(*a_22).blockChunkSizeIncrease_0)){
    NI64 usedMem_0 = (*a_22).occ_0;
    if (usedMem_0 < ((NI64)(IL64(64) * IL64(1024)))){
      (*a_22).nextChunkSize_0 = ((NI64)(((NI64)IL64(4096)) * IL64(4)));}
    else {
      NI64 X60Qx_171 = roundup_0_sysvq0asl(((NI64)(((NI64)usedMem_0) >> ((NU64)IL64(2)))), ((NI64)IL64(4096)));
      NI64 X60Qx_172 = min_3_sysvq0asl(X60Qx_171, ((NI64)((*a_22).nextChunkSize_0 * IL64(2))));
      (*a_22).nextChunkSize_0 = X60Qx_172;
      NI64 X60Qx_173 = min_3_sysvq0asl((*a_22).nextChunkSize_0, ((NI64)IL64(1056964608)));
      (*a_22).nextChunkSize_0 = ((NI64)X60Qx_173);}}
  NI64 size_39 = size_19;
  if ((*a_22).nextChunkSize_0 < size_39){
    void* X60Qx_174 = allocPages_0_sysvq0asl(a_22, size_39);
    result_52 = ((BigChunk_0_sysvq0asl*)X60Qx_174);}
  else {
    void* X60Qx_175 = tryAllocPages_0_sysvq0asl(a_22, (*a_22).nextChunkSize_0);
    result_52 = ((BigChunk_0_sysvq0asl*)X60Qx_175);
    if (result_52 == NIM_NIL){
      void* X60Qx_176 = allocPages_0_sysvq0asl(a_22, size_39);
      result_52 = ((BigChunk_0_sysvq0asl*)X60Qx_176);
      (*a_22).blockChunkSizeIncrease_0 = NIM_TRUE;}
    else {
      size_39 = (*a_22).nextChunkSize_0;}}
  incCurrMem_0_sysvq0asl(a_22, size_39);
  inc_0_Iwdk9lf_sysvq0asl((&(*a_22).freeMem_0), size_39);
  HeapLinks_0_sysvq0asl* heapLink_0 = addHeapLink_0_sysvq0asl(a_22, result_52, size_39);
  (*result_52).next_0 = NIM_NIL;
  (*result_52).prev_0 = NIM_NIL;
  (*result_52).Q.size_0 = size_39;
  NI64 nxt_0 = ((NI64)((NU64)(((NU64)((NI64)result_52)) + ((NU64)size_39))));
  BaseChunk_0_sysvq0asl* next_1 = ((BaseChunk_0_sysvq0asl*)nxt_0);
  NI64 X60Qx_177 = pageIndex_0_sysvq0asl(next_1);
  NB8 X60Qx_178 = contains_1_sysvq0asl((&(*a_22).chunkStarts_0), X60Qx_177);
  if (X60Qx_178){
    (*next_1).prevSize_0 = ((NI64)(size_39 | ((NI64)((*next_1).prevSize_0 & IL64(1)))));}
  NI64 X60Qx_18;
  if ((!((*a_22).lastSize_0 == IL64(0)))){
    X60Qx_18 = (*a_22).lastSize_0;}
  else {
    X60Qx_18 = ((NI64)IL64(4096));}
  NI64 lastSize_0 = X60Qx_18;
  NI64 prv_0 = ((NI64)((NU64)(((NU64)((NI64)result_52)) - ((NU64)lastSize_0))));
  BaseChunk_0_sysvq0asl* prev_1 = ((BaseChunk_0_sysvq0asl*)prv_0);
  {
    NI64 X60Qx_179 = pageIndex_0_sysvq0asl(prev_1);
    NB8 X60Qx_180 = contains_1_sysvq0asl((&(*a_22).chunkStarts_0), X60Qx_179);
    if ((!X60Qx_180)){
      goto X60QL_20;}
    if ((!((*prev_1).size_0 == lastSize_0))){
      goto X60QL_20;}
    (*result_52).Q.prevSize_0 = ((NI64)(lastSize_0 | ((NI64)((*result_52).Q.prevSize_0 & IL64(1)))));}
  goto X60QL_19;
  X60QL_20: ;
  {
    (*result_52).Q.prevSize_0 = ((NI64)(IL64(0) | ((NI64)((*result_52).Q.prevSize_0 & IL64(1)))));}
  X60QL_19: ;
  (*a_22).lastSize_0 = size_39;
  return result_52;}
static inline NB8 isAccessible_0_sysvq0asl(MemRegion_0_sysvq0asl* a_23, void* p_19){
  NB8 result_53;
  NI64 X60Qx_181;
  {
    {
      X60Qx_181 = ((NI64)(((NI64)((NI64)p_19)) >> ((NU64)((NI64)IL64(12)))));
      returnLabel_0h98: ;}}
  NB8 X60Qx_182 = contains_1_sysvq0asl((&(*a_23).chunkStarts_0), X60Qx_181);
  result_53 = X60Qx_182;
  return result_53;}
static inline void updatePrevSize_0_sysvq0asl(MemRegion_0_sysvq0asl* a_24, BigChunk_0_sysvq0asl* c_5, NI64 prevSize_0){
  BaseChunk_0_sysvq0asl* ri_0 = ((BaseChunk_0_sysvq0asl*)((NI64)((NU64)(((NU64)((NI64)c_5)) + ((NU64)(*c_5).Q.size_0)))));
  NB8 X60Qx_183;
  {
    MemRegion_0_sysvq0asl* a_0h99 = (&(*a_24));
    void* p_0h100 = ((void*)ri_0);
    {
      NI64 X60Qx_0h102;
      {
        {
          X60Qx_0h102 = ((NI64)(((NI64)((NI64)p_0h100)) >> ((NU64)((NI64)IL64(12)))));
          returnLabel_0h107: ;}}
      X60Qx_183 = contains_1_sysvq0asl((&(*a_0h99).chunkStarts_0), X60Qx_0h102);
      returnLabel_0h104: ;}}
  if (X60Qx_183){
    (*ri_0).prevSize_0 = ((NI64)(prevSize_0 | ((NI64)((*ri_0).prevSize_0 & IL64(1)))));}}
BigChunk_0_sysvq0asl* splitChunk2_0_sysvq0asl(MemRegion_0_sysvq0asl* a_25, BigChunk_0_sysvq0asl* c_6, NI64 size_20){
  BigChunk_0_sysvq0asl* result_54;
  result_54 = ((BigChunk_0_sysvq0asl*)((NI64)((NU64)(((NU64)((NI64)c_6)) + ((NU64)size_20)))));
  (*result_54).Q.size_0 = ((NI64)((*c_6).Q.size_0 - size_20));
  (*result_54).next_0 = NIM_NIL;
  (*result_54).prev_0 = NIM_NIL;
  (*result_54).Q.prevSize_0 = size_20;
  (*result_54).Q.owner_0 = (&(*a_25));
  updatePrevSize_0_sysvq0asl(a_25, c_6, (*result_54).Q.size_0);
  (*c_6).Q.size_0 = size_20;
  NI64 X60Qx_184 = pageIndex_0_sysvq0asl(((BaseChunk_0_sysvq0asl*)result_54));
  incl_2_sysvq0asl(a_25, X60Qx_184);
  return result_54;}
void splitChunk_0_sysvq0asl(MemRegion_0_sysvq0asl* a_26, BigChunk_0_sysvq0asl* c_7, NI64 size_21){
  BigChunk_0_sysvq0asl* rest_0 = splitChunk2_0_sysvq0asl(a_26, c_7, size_21);
  {
    {
      X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl X60Qtmptup_0h110;
      {
        NI64 r_0h123 = (*rest_0).Q.size_0;
        {
          NI64 fl_0h125 = msbit_0_sysvq0asl(((NU32)r_0h123));
          NI64 sl_0h126 = ((NI64)(((NI64)(((NI64)r_0h123) >> ((NU64)((NI64)(fl_0h125 - ((NI64)IL64(5))))))) - ((NI64)IL64(32))));
          fl_0h125 = ((NI64)(fl_0h125 - ((NI64)IL64(6))));
          X60Qtmptup_0h110 = (X60Qt_0_IAtupleAiS64ZAiS64_sysvq0asl){
            .fld_0 = fl_0h125, .fld_1 = sl_0h126}
          ;
          returnLabel_0h127: ;}}
      NI64 fl_0h111 = X60Qtmptup_0h110.fld_0;
      NI64 sl_0h112 = X60Qtmptup_0h110.fld_1;
      (*rest_0).prev_0 = NIM_NIL;
      NI64 X60Qx_0h113;
      {
        {
          if (((IL64(0) <= fl_0h111) && (fl_0h111 <= IL64(23)))){
            X60Qx_0h113 = fl_0h111;}
          else {
            X60Qx_0h113 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(fl_0h111, IL64(0), IL64(23));}
          returnLabel_0h131: ;}}
      NI64 X60Qx_0h114;
      {
        {
          if (((IL64(0) <= sl_0h112) && (sl_0h112 <= IL64(31)))){
            X60Qx_0h114 = sl_0h112;}
          else {
            X60Qx_0h114 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(sl_0h112, IL64(0), IL64(31));}
          returnLabel_0h135: ;}}
      (*rest_0).next_0 = (*a_26).matrix_0.a[X60Qx_0h113].a[X60Qx_0h114];
      NI64 X60Qx_0h115;
      {
        {
          if (((IL64(0) <= fl_0h111) && (fl_0h111 <= IL64(23)))){
            X60Qx_0h115 = fl_0h111;}
          else {
            X60Qx_0h115 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(fl_0h111, IL64(0), IL64(23));}
          returnLabel_0h139: ;}}
      NI64 X60Qx_0h116;
      {
        {
          if (((IL64(0) <= sl_0h112) && (sl_0h112 <= IL64(31)))){
            X60Qx_0h116 = sl_0h112;}
          else {
            X60Qx_0h116 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(sl_0h112, IL64(0), IL64(31));}
          returnLabel_0h143: ;}}
      if ((!((*a_26).matrix_0.a[X60Qx_0h115].a[X60Qx_0h116] == NIM_NIL))){
        NI64 X60Qx_0h117;
        {
          {
            if (((IL64(0) <= fl_0h111) && (fl_0h111 <= IL64(23)))){
              X60Qx_0h117 = fl_0h111;}
            else {
              X60Qx_0h117 = IL64(0);
              raiseIndexError3_0_Ice8haj1_sysvq0asl(fl_0h111, IL64(0), IL64(23));}
            returnLabel_0h147: ;}}
        NI64 X60Qx_0h118;
        {
          {
            if (((IL64(0) <= sl_0h112) && (sl_0h112 <= IL64(31)))){
              X60Qx_0h118 = sl_0h112;}
            else {
              X60Qx_0h118 = IL64(0);
              raiseIndexError3_0_Ice8haj1_sysvq0asl(sl_0h112, IL64(0), IL64(31));}
            returnLabel_0h151: ;}}
        (*(*a_26).matrix_0.a[X60Qx_0h117].a[X60Qx_0h118]).prev_0 = rest_0;}
      NI64 X60Qx_0h119;
      {
        {
          if (((IL64(0) <= fl_0h111) && (fl_0h111 <= IL64(23)))){
            X60Qx_0h119 = fl_0h111;}
          else {
            X60Qx_0h119 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(fl_0h111, IL64(0), IL64(23));}
          returnLabel_0h155: ;}}
      NI64 X60Qx_0h120;
      {
        {
          if (((IL64(0) <= sl_0h112) && (sl_0h112 <= IL64(31)))){
            X60Qx_0h120 = sl_0h112;}
          else {
            X60Qx_0h120 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(sl_0h112, IL64(0), IL64(31));}
          returnLabel_0h159: ;}}
      (*a_26).matrix_0.a[X60Qx_0h119].a[X60Qx_0h120] = rest_0;
      NI64 X60Qx_0h121;
      {
        {
          if (((IL64(0) <= fl_0h111) && (fl_0h111 <= IL64(23)))){
            X60Qx_0h121 = fl_0h111;}
          else {
            X60Qx_0h121 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(fl_0h111, IL64(0), IL64(23));}
          returnLabel_0h163: ;}}
      {
        NU32* dest_0h165 = (&(*a_26).slBitmap_0.a[X60Qx_0h121]);
        {
          (*dest_0h165) = ((NU32)((*dest_0h165) | ((NU32)(((NU32)1ull) << ((NI64)(sl_0h112 & IL64(31)))))));
          returnLabel_0h166: ;}}
      {
        NU32* dest_0h168 = (&(*a_26).flBitmap_0);
        {
          (*dest_0h168) = ((NU32)((*dest_0h168) | ((NU32)(((NU32)1ull) << ((NI64)(fl_0h111 & IL64(31)))))));
          returnLabel_0h169: ;}}
      returnLabel_0h122: ;}}}
void freeBigChunk_0_sysvq0asl(MemRegion_0_sysvq0asl* a_27, BigChunk_0_sysvq0asl* c_8){
  BigChunk_0_sysvq0asl* c_28 = c_8;
  inc_0_Iwdk9lf_sysvq0asl((&(*a_27).freeMem_0), (*c_28).Q.size_0);
  (*c_28).Q.prevSize_0 = ((NI64)((*c_28).Q.prevSize_0 & ((NI64) ~ IL64(1))));
  NI64 prevSize_1 = (*c_28).Q.prevSize_0;
  if ((!(prevSize_1 == IL64(0)))){
    BaseChunk_0_sysvq0asl* le_0 = ((BaseChunk_0_sysvq0asl*)((NI64)((NU64)(((NU64)((NI64)c_28)) - ((NU64)prevSize_1)))));
    {
      NB8 X60Qx_185 = isAccessible_0_sysvq0asl((&(*a_27)), ((void*)le_0));
      if ((!X60Qx_185)){
        goto X60QL_21;}
      {
        NB8 X60Qx_186 = chunkUnused_0_sysvq0asl(le_0);
        if ((!X60Qx_186)){
          goto X60QL_21;}}
      {
        NB8 X60Qx_187 = isSmallChunk_0_sysvq0asl(le_0);
        if (X60Qx_187){
          goto X60QL_22;}
        if ((!((*le_0).size_0 < ((NI64)IL64(1056964608))))){
          goto X60QL_22;}
        removeChunkFromMatrix_0_sysvq0asl(a_27, ((BigChunk_0_sysvq0asl*)le_0));
        inc_0_Iwdk9lf_sysvq0asl((&(*le_0).size_0), (*c_28).Q.size_0);
        NI64 X60Qx_188 = pageIndex_0_sysvq0asl(((BaseChunk_0_sysvq0asl*)c_28));
        excl_2_sysvq0asl((&(*a_27).chunkStarts_0), X60Qx_188);
        c_28 = ((BigChunk_0_sysvq0asl*)le_0);
        if (((NI64)IL64(1056964608)) < (*c_28).Q.size_0){
          BigChunk_0_sysvq0asl* rest_1 = splitChunk2_0_sysvq0asl(a_27, c_28, ((NI64)IL64(1056964608)));
          addChunkToMatrix_0_sysvq0asl(a_27, c_28);
          c_28 = rest_1;}}
      X60QL_22: ;}
    X60QL_21: ;}
  BaseChunk_0_sysvq0asl* ri_1 = ((BaseChunk_0_sysvq0asl*)((NI64)((NU64)(((NU64)((NI64)c_28)) + ((NU64)(*c_28).Q.size_0)))));
  {
    NB8 X60Qx_189 = isAccessible_0_sysvq0asl((&(*a_27)), ((void*)ri_1));
    if ((!X60Qx_189)){
      goto X60QL_23;}
    {
      NB8 X60Qx_190 = chunkUnused_0_sysvq0asl(ri_1);
      if ((!X60Qx_190)){
        goto X60QL_23;}}
    {
      NB8 X60Qx_191 = isSmallChunk_0_sysvq0asl(ri_1);
      if (X60Qx_191){
        goto X60QL_24;}
      if ((!((*c_28).Q.size_0 < ((NI64)IL64(1056964608))))){
        goto X60QL_24;}
      removeChunkFromMatrix_0_sysvq0asl(a_27, ((BigChunk_0_sysvq0asl*)ri_1));
      inc_0_Iwdk9lf_sysvq0asl((&(*c_28).Q.size_0), (*ri_1).size_0);
      NI64 X60Qx_192 = pageIndex_0_sysvq0asl(ri_1);
      excl_2_sysvq0asl((&(*a_27).chunkStarts_0), X60Qx_192);
      if (((NI64)IL64(1056964608)) < (*c_28).Q.size_0){
        BigChunk_0_sysvq0asl* rest_2 = splitChunk2_0_sysvq0asl(a_27, c_28, ((NI64)IL64(1056964608)));
        addChunkToMatrix_0_sysvq0asl(a_27, rest_2);}}
    X60QL_24: ;}
  X60QL_23: ;
  addChunkToMatrix_0_sysvq0asl(a_27, c_28);}
BigChunk_0_sysvq0asl* getBigChunk_0_sysvq0asl(MemRegion_0_sysvq0asl* a_28, NI64 size_22){
  BigChunk_0_sysvq0asl* result_55;
  NI64 size_40 = size_22;
  NI64 fl_7 = IL64(0);
  NI64 sl_9 = IL64(0);
  mappingSearch_0_sysvq0asl((&size_40), (&fl_7), (&sl_9));
  BigChunk_0_sysvq0asl* X60Qx_193 = findSuitableBlock_0_sysvq0asl((&(*a_28)), (&fl_7), (&sl_9));
  result_55 = X60Qx_193;
  if (result_55 == NIM_NIL){
    if (size_40 < ((NI64)(((NI64)IL64(128)) * ((NI64)IL64(4096))))){
      BigChunk_0_sysvq0asl* X60Qx_194 = requestOsChunks_0_sysvq0asl(a_28, ((NI64)(((NI64)IL64(128)) * ((NI64)IL64(4096)))));
      result_55 = X60Qx_194;
      splitChunk_0_sysvq0asl(a_28, result_55, size_40);}
    else {
      BigChunk_0_sysvq0asl* X60Qx_195 = requestOsChunks_0_sysvq0asl(a_28, size_40);
      result_55 = X60Qx_195;
      if (size_40 < (*result_55).Q.size_0){
        splitChunk_0_sysvq0asl(a_28, result_55, size_40);}}
    (*result_55).Q.owner_0 = (&(*a_28));}
  else {
    removeChunkFromMatrix2_0_sysvq0asl(a_28, result_55, fl_7, sl_9);
    if (((NI64)(size_40 + ((NI64)IL64(4096)))) <= (*result_55).Q.size_0){
      splitChunk_0_sysvq0asl(a_28, result_55, size_40);}}
  (*result_55).Q.prevSize_0 = IL64(1);
  NI64 X60Qx_196 = pageIndex_0_sysvq0asl(((BaseChunk_0_sysvq0asl*)result_55));
  incl_2_sysvq0asl(a_28, X60Qx_196);
  dec_0_Iw9ew8i1_sysvq0asl((&(*a_28).freeMem_0), size_40);
  return result_55;}
BigChunk_0_sysvq0asl* getHugeChunk_0_sysvq0asl(MemRegion_0_sysvq0asl* a_29, NI64 size_23){
  BigChunk_0_sysvq0asl* result_56;
  void* X60Qx_197;
  {
    {
      X60Qx_197 = osAllocPages_0_sysvq0asl(size_23);
      returnLabel_0h174: ;}}
  result_56 = ((BigChunk_0_sysvq0asl*)X60Qx_197);
  {
    {
      {
        NI64* x_0h178 = (&(*a_29).currMem_0);
        {
          (*x_0h178) = ((NI64)((*x_0h178) + size_23));
          returnLabel_0h180: ;}}
      returnLabel_0h177: ;}}
  (*result_56).next_0 = NIM_NIL;
  (*result_56).prev_0 = NIM_NIL;
  (*result_56).Q.size_0 = size_23;
  (*result_56).Q.prevSize_0 = IL64(1);
  (*result_56).Q.owner_0 = (&(*a_29));
  NI64 X60Qx_198;
  {
    BaseChunk_0_sysvq0asl* c_0h181 = ((BaseChunk_0_sysvq0asl*)result_56);
    {
      X60Qx_198 = ((NI64)(((NI64)((NI64)c_0h181)) >> ((NU64)((NI64)IL64(12)))));
      returnLabel_0h183: ;}}
  incl_2_sysvq0asl(a_29, X60Qx_198);
  return result_56;}
SmallChunk_0_sysvq0asl* getSmallChunk_0_sysvq0asl(MemRegion_0_sysvq0asl* a_31){
  SmallChunk_0_sysvq0asl* result_57;
  BigChunk_0_sysvq0asl* res_2 = getBigChunk_0_sysvq0asl(a_31, ((NI64)IL64(4096)));
  result_57 = ((SmallChunk_0_sysvq0asl*)res_2);
  return result_57;}
void deallocBigChunk_0_sysvq0asl(MemRegion_0_sysvq0asl* a_33, BigChunk_0_sysvq0asl* c_10){
  {
    NI64* x_0h202 = (&(*a_33).occ_0);
    NI64 y_0h203 = (*c_10).Q.size_0;
    {
      (*x_0h202) = ((NI64)((*x_0h202) - y_0h203));
      returnLabel_0h204: ;}}
  (*c_10).prev_0 = NIM_NIL;
  if (((NI64)IL64(1056964609)) <= (*c_10).Q.size_0){
    {
      {
        NI64 size_0h207 = (*c_10).Q.size_0;
        NI64 X60Qx_0h208;
        {
          BaseChunk_0_sysvq0asl* c_0h210 = ((BaseChunk_0_sysvq0asl*)c_10);
          {
            X60Qx_0h208 = ((NI64)(((NI64)((NI64)c_0h210)) >> ((NU64)((NI64)IL64(12)))));
            returnLabel_0h212: ;}}
        excl_2_sysvq0asl((&(*a_33).chunkStarts_0), X60Qx_0h208);
        {
          {
            NI64 X60Qx_0h215;
            {
              NI64 x_0h217 = (*a_33).maxMem_0;
              NI64 y_0h218 = (*a_33).currMem_0;
              {
                if (y_0h218 <= x_0h217){
                  X60Qx_0h215 = x_0h217;}
                else {
                  X60Qx_0h215 = y_0h218;}
                returnLabel_0h221: ;}}
            (*a_33).maxMem_0 = X60Qx_0h215;
            {
              NI64* x_0h222 = (&(*a_33).currMem_0);
              {
                (*x_0h222) = ((NI64)((*x_0h222) - size_0h207));
                returnLabel_0h224: ;}}
            returnLabel_0h216: ;}}
        {
          void* p_0h225 = ((void*)c_10);
          {
            returnLabel_0h227: ;}}
        returnLabel_0h209: ;}}}
  else {
    freeBigChunk_0_sysvq0asl(a_33, c_10);}}
static inline void addToSharedFreeListBigChunks_0_sysvq0asl(MemRegion_0_sysvq0asl* a_34, BigChunk_0_sysvq0asl* c_11){
  {
    while (NIM_TRUE){
      BigChunk_0_sysvq0asl* X60Qx_200 = __atomic_load_n((&(*a_34).sharedFreeListBigChunks_0), __ATOMIC_RELAXED);
      __atomic_store_n((&(*c_11).next_0), X60Qx_200, __ATOMIC_RELAXED);
      NB8 X60Qx_201 = __atomic_compare_exchange_n((&(*a_34).sharedFreeListBigChunks_0), (&(*c_11).next_0), c_11, NIM_TRUE, __ATOMIC_RELEASE, __ATOMIC_RELAXED);
      if (X60Qx_201){
        goto whileStmtLabel_0;}}}
  whileStmtLabel_0: ;}
static inline BigChunk_0_sysvq0asl* takeFromSharedFreeListBigChunks_0_sysvq0asl(MemRegion_0_sysvq0asl* a_35){
  BigChunk_0_sysvq0asl* result_58;
  {
    while (NIM_TRUE){
      BigChunk_0_sysvq0asl* X60Qx_202 = __atomic_load_n((&(*a_35).sharedFreeListBigChunks_0), __ATOMIC_ACQUIRE);
      result_58 = X60Qx_202;
      if (result_58 == NIM_NIL){
        goto whileStmtLabel_0;}
      BigChunk_0_sysvq0asl* next_2 = __atomic_load_n((&(*result_58).next_0), __ATOMIC_RELAXED);
      BigChunk_0_sysvq0asl* expected_2 = result_58;
      NB8 X60Qx_203 = __atomic_compare_exchange_n((&(*a_35).sharedFreeListBigChunks_0), (&expected_2), next_2, NIM_TRUE, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
      if (X60Qx_203){
        __atomic_store_n((&(*result_58).next_0), NIM_NIL, __ATOMIC_RELAXED);
        goto whileStmtLabel_0;}}}
  whileStmtLabel_0: ;
  return result_58;}
static inline void addToSharedFreeList_0_sysvq0asl(SmallChunk_0_sysvq0asl* c_12, FreeCell_0_sysvq0asl* f_1, NI64 size_24){
  {
    while (NIM_TRUE){
      NI64 X60Qx_204;
      {
        {
          if (((IL64(0) <= size_24) && (size_24 <= IL64(255)))){
            X60Qx_204 = size_24;}
          else {
            X60Qx_204 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(size_24, IL64(0), IL64(255));}
          returnLabel_0h231: ;}}
      FreeCell_0_sysvq0asl* X60Qx_205 = __atomic_load_n((&(*(*c_12).Q.owner_0).sharedFreeLists_0.a[X60Qx_204]), __ATOMIC_RELAXED);
      __atomic_store_n((&(*f_1).next_0), X60Qx_205, __ATOMIC_RELAXED);
      NI64 X60Qx_206;
      {
        {
          if (((IL64(0) <= size_24) && (size_24 <= IL64(255)))){
            X60Qx_206 = size_24;}
          else {
            X60Qx_206 = IL64(0);
            raiseIndexError3_0_Ice8haj1_sysvq0asl(size_24, IL64(0), IL64(255));}
          returnLabel_0h235: ;}}
      NB8 X60Qx_207 = __atomic_compare_exchange_n((&(*(*c_12).Q.owner_0).sharedFreeLists_0.a[X60Qx_206]), (&(*f_1).next_0), f_1, NIM_TRUE, __ATOMIC_RELEASE, __ATOMIC_RELAXED);
      if (X60Qx_207){
        goto whileStmtLabel_0;}}}
  whileStmtLabel_0: ;}
void compensateCounters_0_sysvq0asl(MemRegion_0_sysvq0asl* a_36, SmallChunk_0_sysvq0asl* c_13, NI64 size_25){
  FreeCell_0_sysvq0asl* it_3 = (*c_13).freeList_0;
  NI64 total_0 = IL64(0);
  {
    while ((!(it_3 == NIM_NIL))){
      inc_0_Iwdk9lf_sysvq0asl((&total_0), size_25);
      BaseChunk_0_sysvq0asl* X60Qx_208 = pageAddr_0_sysvq0asl(((void*)it_3));
      SmallChunk_0_sysvq0asl* chunk_0 = ((SmallChunk_0_sysvq0asl*)X60Qx_208);
      if ((!(c_13 == chunk_0))){
        (*c_13).foreignCells_0 = ((NI32)((*c_13).foreignCells_0 + ((NI32)IL64(1))));}
      it_3 = (*it_3).next_0;}}
  whileStmtLabel_0: ;
  (*c_13).free_0 = ((NI32)((*c_13).free_0 + ((NI32)total_0)));
  dec_0_Iw9ew8i1_sysvq0asl((&(*a_36).occ_0), total_0);}
void freeDeferredObjects_0_sysvq0asl(MemRegion_0_sysvq0asl* a_37){
  {
    NI64 X60Qlf_0 = IL64(0);
    NI64 X60Qlf_1 = ((NI64)IL64(20));
    NI64 X60Qlf_2 = X60Qlf_0;
    {
      while (X60Qlf_2 <= X60Qlf_1){
        {
          BigChunk_0_sysvq0asl* X60Qii_2 = takeFromSharedFreeListBigChunks_0_sysvq0asl(a_37);
          if (X60Qii_2 == NIM_NIL){
            goto forStmtLabel_0;}
          {
            {
              {
                NI64* x_0h239 = (&(*a_37).occ_0);
                NI64 y_0h240 = (*X60Qii_2).Q.size_0;
                {
                  (*x_0h239) = ((NI64)((*x_0h239) - y_0h240));
                  returnLabel_0h241: ;}}
              (*X60Qii_2).prev_0 = NIM_NIL;
              if (((NI64)IL64(1056964609)) <= (*X60Qii_2).Q.size_0){
                {
                  {
                    NI64 size_0h244 = (*X60Qii_2).Q.size_0;
                    NI64 X60Qx_0h245;
                    {
                      BaseChunk_0_sysvq0asl* c_0h247 = ((BaseChunk_0_sysvq0asl*)X60Qii_2);
                      {
                        X60Qx_0h245 = ((NI64)(((NI64)((NI64)c_0h247)) >> ((NU64)((NI64)IL64(12)))));
                        returnLabel_0h249: ;}}
                    excl_2_sysvq0asl((&(*a_37).chunkStarts_0), X60Qx_0h245);
                    {
                      {
                        NI64 X60Qx_0h252;
                        {
                          NI64 x_0h254 = (*a_37).maxMem_0;
                          NI64 y_0h255 = (*a_37).currMem_0;
                          {
                            if (y_0h255 <= x_0h254){
                              X60Qx_0h252 = x_0h254;}
                            else {
                              X60Qx_0h252 = y_0h255;}
                            returnLabel_0h258: ;}}
                        (*a_37).maxMem_0 = X60Qx_0h252;
                        {
                          NI64* x_0h259 = (&(*a_37).currMem_0);
                          {
                            (*x_0h259) = ((NI64)((*x_0h259) - size_0h244));
                            returnLabel_0h261: ;}}
                        returnLabel_0h253: ;}}
                    {
                      void* p_0h262 = ((void*)X60Qii_2);
                      {
                        returnLabel_0h264: ;}}
                    returnLabel_0h246: ;}}}
              else {
                freeBigChunk_0_sysvq0asl(a_37, X60Qii_2);}
              returnLabel_0h238: ;}}}
        {
          {
            (*(&X60Qlf_2)) = ((NI64)((*(&X60Qlf_2)) + ((NI64)IL64(1))));
            returnLabel_0h266: ;}}}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;}
static inline NI64 smallChunkAlignOffset_0_sysvq0asl(NI64 alignment_1){
  NI64 result_59;
  if (alignment_1 <= ((NI64)IL64(16))){
    result_59 = IL64(0);}
  else {
    NI64 X60Qx_209;
    {
      NI64 address_0h267 = ((NI64)(sizeof(SmallChunk_0_sysvq0asl) + sizeof(FreeCell_0_sysvq0asl)));
      {
        X60Qx_209 = ((NI64)(((NI64)(address_0h267 + ((NI64)(alignment_1 - IL64(1))))) & ((NI64) ~ ((NI64)(alignment_1 - IL64(1))))));
        returnLabel_0h270: ;}}
    result_59 = ((NI64)(((NI64)(X60Qx_209 - sizeof(SmallChunk_0_sysvq0asl))) - sizeof(FreeCell_0_sysvq0asl)));}
  return result_59;}
static inline NI64 bigChunkAlignOffset_0_sysvq0asl(NI64 alignment_2){
  NI64 result_60;
  if (alignment_2 == IL64(0)){
    result_60 = IL64(0);}
  else {
    NI64 X60Qx_210;
    {
      NI64 address_0h271 = ((NI64)(sizeof(BigChunk_0_sysvq0asl) + sizeof(FreeCell_0_sysvq0asl)));
      {
        X60Qx_210 = ((NI64)(((NI64)(address_0h271 + ((NI64)(alignment_2 - IL64(1))))) & ((NI64) ~ ((NI64)(alignment_2 - IL64(1))))));
        returnLabel_0h274: ;}}
    result_60 = ((NI64)(((NI64)(X60Qx_210 - sizeof(BigChunk_0_sysvq0asl))) - sizeof(FreeCell_0_sysvq0asl)));}
  return result_60;}
void* rawAlloc_0_sysvq0asl(MemRegion_0_sysvq0asl* a_38, NI64 requestedSize_0, NI64 alignment_3){
  void* result_61;
  NI64 X60Qx_211 = max_3_sysvq0asl(((NI64)IL64(16)), alignment_3);
  NI64 size_42 = roundup_0_sysvq0asl(requestedSize_0, X60Qx_211);
  NI64 alignOff_0 = smallChunkAlignOffset_0_sysvq0asl(alignment_3);
  if (((NI64)(size_42 + alignOff_0)) <= ((NI64)(((NI64)IL64(4096)) - sizeof(SmallChunk_0_sysvq0asl)))){
    NI64 s_87 = ((NI64)(((NI64)size_42) >> ((NU64)((NI64)IL64(4)))));
    NI64 X60Qx_212 = nimIcheckB(s_87, IL64(255));
    SmallChunk_0_sysvq0asl* c_29 = (*a_38).freeSmallChunks_0.a[X60Qx_212];
    if (((!(c_29 == NIM_NIL)) && (!((*c_29).chunkAlignOff_0 == ((NI32)alignOff_0))))){
      c_29 = NIM_NIL;}
    if (c_29 == NIM_NIL){
      SmallChunk_0_sysvq0asl* X60Qx_213 = getSmallChunk_0_sysvq0asl(a_38);
      c_29 = X60Qx_213;
      (*c_29).freeList_0 = NIM_NIL;
      (*c_29).foreignCells_0 = ((NI32)IL64(0));
      (*c_29).chunkAlignOff_0 = ((NI32)alignOff_0);
      (*c_29).Q.size_0 = size_42;
      (*c_29).acc_0 = ((NU32)((NI64)(alignOff_0 + size_42)));
      (*c_29).free_0 = ((NI32)((NI64)(((NI64)(((NI64)(((NI64)IL64(4096)) - sizeof(SmallChunk_0_sysvq0asl))) - alignOff_0)) - size_42)));
      (*c_29).next_0 = NIM_NIL;
      (*c_29).prev_0 = NIM_NIL;
      if ((*c_29).freeList_0 == NIM_NIL){
        NI64 X60Qx_214 = nimIcheckB(s_87, IL64(255));
        FreeCell_0_sysvq0asl* X60Qx_215 = __atomic_exchange_n((&(*a_38).sharedFreeLists_0.a[X60Qx_214]), NIM_NIL, __ATOMIC_RELAXED);
        (*c_29).freeList_0 = X60Qx_215;
        compensateCounters_0_sysvq0asl(a_38, c_29, size_42);}
      if (size_42 <= ((NI64)(*c_29).free_0)){
        NI64 X60Qx_216 = nimIcheckB(s_87, IL64(255));
        listAdd_0_Ik4wxhz_sysvq0asl((&(*a_38).freeSmallChunks_0.a[X60Qx_216]), c_29);}
      result_61 = ((void*)((NI64)(((NI64)((void*)((void*)(&(*c_29).data_0)))) + alignOff_0)));}
    else {
      if ((*c_29).freeList_0 == NIM_NIL){
        result_61 = ((void*)((NI64)((NU64)(((NU64)((NI64)(&(*c_29).data_0))) + ((NU64)((NI64)(*c_29).acc_0))))));
        (*c_29).acc_0 = ((NU32)((*c_29).acc_0 + ((NU32)size_42)));}
      else {
        result_61 = ((void*)(*c_29).freeList_0);
        (*c_29).freeList_0 = (*(*c_29).freeList_0).next_0;
        BaseChunk_0_sysvq0asl* X60Qx_217 = pageAddr_0_sysvq0asl(result_61);
        if ((!(((SmallChunk_0_sysvq0asl*)X60Qx_217) == c_29))){
          (*c_29).foreignCells_0 = ((NI32)((*c_29).foreignCells_0 - ((NI32)IL64(1))));}
        else {
          }}
      (*c_29).free_0 = ((NI32)((*c_29).free_0 - ((NI32)size_42)));
      if ((*c_29).freeList_0 == NIM_NIL){
        NI64 X60Qx_218 = nimIcheckB(s_87, IL64(255));
        FreeCell_0_sysvq0asl* X60Qx_219 = __atomic_exchange_n((&(*a_38).sharedFreeLists_0.a[X60Qx_218]), NIM_NIL, __ATOMIC_RELAXED);
        (*c_29).freeList_0 = X60Qx_219;
        compensateCounters_0_sysvq0asl(a_38, c_29, size_42);}
      if (((NI64)(*c_29).free_0) < size_42){
        NI64 X60Qx_220 = nimIcheckB(s_87, IL64(255));
        listRemove_0_Ibzev091_sysvq0asl((&(*a_38).freeSmallChunks_0.a[X60Qx_220]), c_29);}}
    inc_0_Iwdk9lf_sysvq0asl((&(*a_38).occ_0), size_42);}
  else {
    freeDeferredObjects_0_sysvq0asl(a_38);
    NI64 alignPad_0 = bigChunkAlignOffset_0_sysvq0asl(alignment_3);
    size_42 = ((NI64)(((NI64)(requestedSize_0 + sizeof(BigChunk_0_sysvq0asl))) + alignPad_0));
    BigChunk_0_sysvq0asl* X60Qx_25;
    if (((NI64)IL64(1056964609)) <= size_42){
      BigChunk_0_sysvq0asl* X60Qx_221 = getHugeChunk_0_sysvq0asl(a_38, size_42);
      X60Qx_25 = X60Qx_221;}
    else {
      BigChunk_0_sysvq0asl* X60Qx_222 = getBigChunk_0_sysvq0asl(a_38, size_42);
      X60Qx_25 = X60Qx_222;}
    BigChunk_0_sysvq0asl* c_32 = X60Qx_25;
    result_61 = ((void*)((NI64)(((NI64)((void*)((void*)(&(*c_32).data_0)))) + alignPad_0)));
    (*c_32).prev_0 = ((BigChunk_0_sysvq0asl*)result_61);
    inc_0_Iwdk9lf_sysvq0asl((&(*a_38).occ_0), (*c_32).Q.size_0);}
  return result_61;}
void rawDealloc_0_sysvq0asl(MemRegion_0_sysvq0asl* a_40, void* p_20){
  BaseChunk_0_sysvq0asl* c_33 = pageAddr_0_sysvq0asl(p_20);
  NB8 X60Qx_224 = isSmallChunk_0_sysvq0asl(c_33);
  if (X60Qx_224){
    SmallChunk_0_sysvq0asl* c_34 = ((SmallChunk_0_sysvq0asl*)c_33);
    NI64 s_88 = (*c_34).Q.size_0;
    FreeCell_0_sysvq0asl* f_2 = ((FreeCell_0_sysvq0asl*)p_20);
    if ((*c_34).Q.owner_0 == (&(*a_40))){
      dec_0_Iw9ew8i1_sysvq0asl((&(*a_40).occ_0), s_88);
      NI64 X60Qx_225 = nimIcheckB(((NI64)(((NI64)s_88) >> ((NU64)((NI64)IL64(4))))), IL64(255));
      SmallChunk_0_sysvq0asl* activeChunk_0 = (*a_40).freeSmallChunks_0.a[X60Qx_225];
      if ((((!(activeChunk_0 == NIM_NIL)) && (!(c_34 == activeChunk_0))) && ((*activeChunk_0).chunkAlignOff_0 == (*c_34).chunkAlignOff_0))){
        (*f_2).next_0 = (*activeChunk_0).freeList_0;
        (*activeChunk_0).freeList_0 = f_2;
        (*activeChunk_0).free_0 = ((NI32)((*activeChunk_0).free_0 + ((NI32)s_88)));
        (*activeChunk_0).foreignCells_0 = ((NI32)((*activeChunk_0).foreignCells_0 + ((NI32)IL64(1))));}
      else {
        (*f_2).next_0 = (*c_34).freeList_0;
        (*c_34).freeList_0 = f_2;
        if (((NI64)(*c_34).free_0) < s_88){
          NI64 X60Qx_226 = nimIcheckB(((NI64)(((NI64)s_88) >> ((NU64)((NI64)IL64(4))))), IL64(255));
          listAdd_0_Ik4wxhz_sysvq0asl((&(*a_40).freeSmallChunks_0.a[X60Qx_226]), c_34);
          (*c_34).free_0 = ((NI32)((*c_34).free_0 + ((NI32)s_88)));}
        else {
          (*c_34).free_0 = ((NI32)((*c_34).free_0 + ((NI32)s_88)));}}}
    else {
      addToSharedFreeList_0_sysvq0asl(c_34, f_2, ((NI64)(((NI64)s_88) >> ((NU64)((NI64)IL64(4))))));}}
  else {
    if ((*c_33).owner_0 == (&(*a_40))){
      deallocBigChunk_0_sysvq0asl(a_40, ((BigChunk_0_sysvq0asl*)c_33));}
    else {
      addToSharedFreeListBigChunks_0_sysvq0asl((*c_33).owner_0, ((BigChunk_0_sysvq0asl*)c_33));}}}
void* alloc_1_sysvq0asl(NI64 size_28){
  void* result_71;
  void* X60Qx_235;
  {
    {
      void* X60Qx_0h496 = rawAlloc_0_sysvq0asl((&allocator_0_sysvq0asl), size_28, IL64(0));
      X60Qx_235 = X60Qx_0h496;
      returnLabel_0h497: ;}}
  result_71 = X60Qx_235;
  return result_71;}
void* realloc_1_sysvq0asl(void* p_25, NI64 size_30){
  void* result_73;
  void* X60Qx_237;
  {
    {
      X60Qx_237 = NIM_NIL;
      if (IL64(0) < size_30){
        void* X60Qx_0h515;
        {
          {
            void* X60Qx_0h522 = rawAlloc_0_sysvq0asl((&allocator_0_sysvq0asl), size_30, IL64(0));
            X60Qx_0h515 = X60Qx_0h522;
            returnLabel_0h523: ;}}
        X60Qx_237 = X60Qx_0h515;
        if ((!(p_25 == NIM_NIL))){
          NI64 X60Qx_0h516;
          {
            {
              BaseChunk_0_sysvq0asl* c_0h526;
              {
                {
                  c_0h526 = ((BaseChunk_0_sysvq0asl*)((NI64)(((NI64)p_25) & ((NI64) ~ ((NI64)IL64(4095))))));
                  returnLabel_0h531: ;}}
              X60Qx_0h516 = (*c_0h526).size_0;
              if ((!((*c_0h526).size_0 <= ((NI64)(((NI64)IL64(4096)) - sizeof(SmallChunk_0_sysvq0asl)))))){
                {
                  NI64 y_0h534 = sizeof(BigChunk_0_sysvq0asl);
                  {
                    (*(&X60Qx_0h516)) = ((NI64)((*(&X60Qx_0h516)) - y_0h534));
                    returnLabel_0h535: ;}}}
              returnLabel_0h528: ;}}
          NI64 X60Qx_0h517;
          {
            {
              if (X60Qx_0h516 <= size_30){
                X60Qx_0h517 = X60Qx_0h516;}
              else {
                X60Qx_0h517 = size_30;}
              returnLabel_0h540: ;}}
          {
            {
              memcpy(X60Qx_237, p_25, ((size_t)X60Qx_0h517));
              returnLabel_0h544: ;}}
          {
            {
              rawDealloc_0_sysvq0asl((&allocator_0_sysvq0asl), p_25);
              returnLabel_0h547: ;}}}}
      else {
        if ((!(p_25 == NIM_NIL))){
          {
            {
              rawDealloc_0_sysvq0asl((&allocator_0_sysvq0asl), p_25);
              returnLabel_0h550: ;}}}}
      returnLabel_0h518: ;}}
  result_73 = X60Qx_237;
  return result_73;}
void dealloc_1_sysvq0asl(void* p_26){
  {
    {
      rawDealloc_0_sysvq0asl((&allocator_0_sysvq0asl), p_26);
      returnLabel_0h553: ;}}}
NI64 allocatedSize_0_sysvq0asl(void* p_27){
  NI64 result_74;
  NI64 X60Qx_238;
  {
    {
      BaseChunk_0_sysvq0asl* c_0h556;
      {
        {
          c_0h556 = ((BaseChunk_0_sysvq0asl*)((NI64)(((NI64)p_27) & ((NI64) ~ ((NI64)IL64(4095))))));
          returnLabel_0h561: ;}}
      X60Qx_238 = (*c_0h556).size_0;
      if ((!((*c_0h556).size_0 <= ((NI64)(((NI64)IL64(4096)) - sizeof(SmallChunk_0_sysvq0asl)))))){
        {
          NI64 y_0h564 = sizeof(BigChunk_0_sysvq0asl);
          {
            (*(&X60Qx_238)) = ((NI64)((*(&X60Qx_238)) - y_0h564));
            returnLabel_0h565: ;}}}
      returnLabel_0h558: ;}}
  result_74 = X60Qx_238;
  return result_74;}
void* allocFixed_0_sysvq0asl(NI64 size_31){
  void* result_78;
  void* X60Qx_242;
  {
    {
      void* X60Qx_0h577;
      {
        {
          void* X60Qx_0h582 = rawAlloc_0_sysvq0asl((&allocator_0_sysvq0asl), size_31, IL64(0));
          X60Qx_0h577 = X60Qx_0h582;
          returnLabel_0h583: ;}}
      X60Qx_242 = X60Qx_0h577;
      returnLabel_0h578: ;}}
  result_78 = X60Qx_242;
  return result_78;}
N_NIMCALL(void, continueAfterOutOfMem_0_sysvq0asl)(NI64 size_32){
  if (missingBytes_0_sysvq0asl < ((NI64)(((NI64)IL64(9223372036854775807)) - size_32))){
    missingBytes_0_sysvq0asl = ((NI64)(missingBytes_0_sysvq0asl + size_32));}
  else {
    missingBytes_0_sysvq0asl = ((NI64)IL64(9223372036854775807));}}
static inline NI64 recalcCap_0_sysvq0asl(NI64 oldCap_0, NI64 addedElements_0){
  NB8 LENGC_OVF_ = NIM_FALSE;
  NI64 result_87;
  NI64 X60QconstRefTemp_0;
  if (__builtin_saddll_overflow(oldCap_0, addedElements_0, (long long int*)(&X60QconstRefTemp_0))){
    LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
  NI64 requiredLen_0 = X60QconstRefTemp_0;
  if (LENGC_OVF_){
    result_87 = ((NI64)IL64(9223372036854775807));}
  else {
    NI64 X60QconstRefTemp_1;
    if (__builtin_saddll_overflow(oldCap_0, ((NI64)(((NI64)oldCap_0) >> ((NU64)IL64(1)))), (long long int*)(&X60QconstRefTemp_1))){
      LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
    result_87 = X60QconstRefTemp_1;
    if (LENGC_OVF_){
      result_87 = requiredLen_0;}
    else {
      NI64 X60Qx_243;
      {
        {
          if (requiredLen_0 <= result_87){
            X60Qx_243 = result_87;}
          else {
            X60Qx_243 = requiredLen_0;}
          returnLabel_0h593: ;}}
      result_87 = X60Qx_243;}}
  return result_87;}
static inline NI64 ssLenOf_0_sysvq0asl(NU64 bytes_2){
  NI64 result_97;
  result_97 = ((NI64)((NU64)(bytes_2 & 255ull)));
  return result_97;}
static inline NC8* rawData_1_sysvq0asl(string_0_sysvq0asl* s_33){
  NC8* result_98;
  NI64 X60Qx_244;
  {
    NU64 bytes_0h594 = (*s_33).bytes_0;
    {
      X60Qx_244 = ((NI64)((NU64)(bytes_0h594 & 255ull)));
      returnLabel_0h596: ;}}
  if (((NI64)IL64(14)) < X60Qx_244){
    result_98 = ((NC8*)(&(*(*s_33).more_0).data_0[IL64(0)]));}
  else {
    result_98 = ((NC8*)((NU64)(((NU64)(&(*s_33).bytes_0)) + 1ull)));}
  return result_98;}
NI64 len_4_sysvq0asl(string_0_sysvq0asl s_34){
  NI64 result_100;
  NI64 X60Qx_245;
  {
    NU64 bytes_0h597 = s_34.bytes_0;
    {
      X60Qx_245 = ((NI64)((NU64)(bytes_0h597 & 255ull)));
      returnLabel_0h599: ;}}
  result_100 = X60Qx_245;
  if (((NI64)IL64(14)) < result_100){
    result_100 = (*s_34.more_0).fullLen_0;}
  return result_100;}
static inline void nimStrWasMoved(string_0_sysvq0asl* s_43){
  (*s_43).bytes_0 = ((NU64)IL64(0));}
N_NOINLINE void destroyHeapStr_0_sysvq0asl(LongString_0_sysvq0asl* more_1){
  NB8 X60Qx_249 = arcDec_0_sysvq0asl((&(*more_1).rc_0));
  if (X60Qx_249){
    dealloc_1_sysvq0asl(((void*)more_1));}}
void nimStrDestroy(string_0_sysvq0asl s_44){
  NI64 X60Qx_250;
  {
    NU64 bytes_0h616 = s_44.bytes_0;
    {
      X60Qx_250 = ((NI64)((NU64)(bytes_0h616 & 255ull)));
      returnLabel_0h618: ;}}
  if (X60Qx_250 == ((NI64)IL64(255))){
    destroyHeapStr_0_sysvq0asl(s_44.more_0);}}
void nimStrCopy(string_0_sysvq0asl* dest_11, string_0_sysvq0asl src_6){
  NI64 ssrc_0 = ssLenOf_0_sysvq0asl(src_6.bytes_0);
  if (ssrc_0 <= ((NI64)IL64(14))){
    NI64 sdest_0 = ssLenOf_0_sysvq0asl((*dest_11).bytes_0);
    if (sdest_0 == ((NI64)IL64(255))){
      NB8 X60Qx_251 = arcDec_0_sysvq0asl((&(*(*dest_11).more_0).rc_0));
      if (X60Qx_251){
        dealloc_1_sysvq0asl(((void*)(*dest_11).more_0));}}
    copyMem_0_sysvq0asl(((void*)(&(*dest_11).bytes_0)), ((void*)(&src_6.bytes_0)), sizeof(string_0_sysvq0asl));}
  else {
    if ((&(*dest_11)) == (&src_6)){
      return;}
    NI64 sdest_1 = ssLenOf_0_sysvq0asl((*dest_11).bytes_0);
    if (sdest_1 == ((NI64)IL64(255))){
      NB8 X60Qx_252 = arcDec_0_sysvq0asl((&(*(*dest_11).more_0).rc_0));
      if (X60Qx_252){
        dealloc_1_sysvq0asl(((void*)(*dest_11).more_0));}}
    if (ssrc_0 == ((NI64)IL64(255))){
      arcInc_0_sysvq0asl((&(*src_6.more_0).rc_0));}
    copyMem_0_sysvq0asl(((void*)(&(*dest_11).bytes_0)), ((void*)(&src_6.bytes_0)), sizeof(string_0_sysvq0asl));}}
static inline string_0_sysvq0asl nimStrDup(string_0_sysvq0asl s_45){
  string_0_sysvq0asl result_108;
  NI64 X60Qx_253;
  {
    NU64 bytes_0h619 = s_45.bytes_0;
    {
      X60Qx_253 = ((NI64)((NU64)(bytes_0h619 & 255ull)));
      returnLabel_0h621: ;}}
  if (X60Qx_253 == ((NI64)IL64(255))){
    {
      NI64* memLoc_0h622 = (&(*s_45.more_0).rc_0);
      {
        NI64 X60Qx_0h623 = __atomic_add_fetch((&(*memLoc_0h622)), IL64(1), __ATOMIC_SEQ_CST);
        returnLabel_0h624: ;}}}
  result_108 = (string_0_sysvq0asl){
    .bytes_0 = s_45.bytes_0, .more_0 = s_45.more_0}
  ;
  return result_108;}
static inline NI64 ssResize_0_sysvq0asl(NI64 old_0){
  NI64 result_111;
  NI64 X60Qx_28;
  if (old_0 <= IL64(0)){
    X60Qx_28 = IL64(4);}
  else {
    if (old_0 <= IL64(32767)){
      X60Qx_28 = ((NI64)(old_0 * IL64(2)));}
    else {
      X60Qx_28 = ((NI64)(((NI64)(old_0 / IL64(2))) + old_0));}}
  result_111 = X60Qx_28;
  return result_111;}
void ensureUniqueLong_0_sysvq0asl(string_0_sysvq0asl* s_46, NI64 oldLen_0, NI64 newLen_5){
  NI64 sl_12 = ssLenOf_0_sysvq0asl((*s_46).bytes_0);
  NB8 isHeap_0 = (sl_12 == ((NI64)IL64(255)));
  NI64 X60Qx_29;
  if (isHeap_0){
    X60Qx_29 = (*(*s_46).more_0).capImpl_0;}
  else {
    X60Qx_29 = IL64(0);}
  NI64 cap_1 = X60Qx_29;
  {
    if ((!isHeap_0)){
      goto X60QL_31;}
    {
      NB8 X60Qx_255 = arcIsUnique_0_sysvq0asl((&(*(*s_46).more_0).rc_0));
      if ((!X60Qx_255)){
        goto X60QL_31;}}
    if ((!(newLen_5 <= cap_1))){
      goto X60QL_31;}
    (*(*s_46).more_0).fullLen_0 = newLen_5;
    if (oldLen_0 < ((NI64)IL64(7))){
      copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&(*s_46).bytes_0)) + 1ull)))), ((void*)(&(*(*s_46).more_0).data_0[IL64(0)])), oldLen_0);}}
  goto X60QL_30;
  X60QL_31: ;
  {
    NI64 X60Qx_32;
    if (cap_1 < newLen_5){
      NI64 X60Qx_256 = ssResize_0_sysvq0asl(cap_1);
      NI64 X60Qx_257 = max_3_sysvq0asl(newLen_5, X60Qx_256);
      X60Qx_32 = X60Qx_257;}
    else {
      X60Qx_32 = cap_1;}
    NI64 newCap_2 = X60Qx_32;
    void* X60Qx_258 = alloc_1_sysvq0asl(((NI64)(((NI64)IL64(24)) + newCap_2)));
    LongString_0_sysvq0asl* p_43 = ((LongString_0_sysvq0asl*)X60Qx_258);
    if ((!(p_43 == NIM_NIL))){
      (*p_43).rc_0 = IL64(0);
      (*p_43).fullLen_0 = newLen_5;
      (*p_43).capImpl_0 = newCap_2;
      if (isHeap_0){
        LongString_0_sysvq0asl* old_2 = (*s_46).more_0;
        NI64 X60Qx_259 = min_3_sysvq0asl(oldLen_0, newCap_2);
        copyMem_0_sysvq0asl(((void*)(&(*p_43).data_0[IL64(0)])), ((void*)(&(*old_2).data_0[IL64(0)])), X60Qx_259);
        NB8 X60Qx_260 = arcDec_0_sysvq0asl((&(*old_2).rc_0));
        if (X60Qx_260){
          dealloc_1_sysvq0asl(((void*)old_2));}}
      else {
        NI64 X60Qx_261 = min_3_sysvq0asl(oldLen_0, newCap_2);
        copyMem_0_sysvq0asl(((void*)(&(*p_43).data_0[IL64(0)])), ((void*)(&(*(*s_46).more_0).data_0[IL64(0)])), X60Qx_261);}
      (*s_46).more_0 = p_43;
      (*((NU8*)(&(*s_46).bytes_0))) = ((NU8)((NI64)IL64(255)));
      NI64 X60Qx_262 = min_3_sysvq0asl(oldLen_0, ((NI64)IL64(7)));
      copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&(*s_46).bytes_0)) + 1ull)))), ((void*)(&(*p_43).data_0[IL64(0)])), X60Qx_262);}
    else {
      oomHandler_0_sysvq0asl(((NI64)(((NI64)IL64(24)) + newCap_2)));
      (*s_46).bytes_0 = ((NU64)21760775509248519ull);
      (*s_46).more_0 = NIM_NIL;}}
  X60QL_30: ;}
void transitionToLong_0_sysvq0asl(string_0_sysvq0asl* s_47, NI64 sl_5, NI64 newLen_6){
  NI64 X60Qx_263 = ssResize_0_sysvq0asl(newLen_6);
  NI64 newCap_3 = max_3_sysvq0asl(newLen_6, X60Qx_263);
  void* X60Qx_264 = alloc_1_sysvq0asl(((NI64)(((NI64)IL64(24)) + newCap_3)));
  LongString_0_sysvq0asl* p_44 = ((LongString_0_sysvq0asl*)X60Qx_264);
  if ((!(p_44 == NIM_NIL))){
    (*p_44).rc_0 = IL64(0);
    (*p_44).fullLen_0 = newLen_6;
    (*p_44).capImpl_0 = newCap_3;
    copyMem_0_sysvq0asl(((void*)(&(*p_44).data_0[IL64(0)])), ((void*)((NC8*)((NU64)(((NU64)(&(*s_47).bytes_0)) + 1ull)))), sl_5);
    (*s_47).more_0 = p_44;
    (*((NU8*)(&(*s_47).bytes_0))) = ((NU8)((NI64)IL64(255)));
    NI64 X60Qx_265 = min_3_sysvq0asl(sl_5, ((NI64)IL64(7)));
    copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&(*s_47).bytes_0)) + 1ull)))), ((void*)(&(*p_44).data_0[IL64(0)])), X60Qx_265);}
  else {
    oomHandler_0_sysvq0asl(((NI64)(((NI64)IL64(24)) + newCap_3)));
    (*s_47).bytes_0 = ((NU64)21760775509248519ull);
    (*s_47).more_0 = NIM_NIL;}}
void prepareMutation_0_sysvq0asl(string_0_sysvq0asl* s_49){
  NI64 sl_14 = ssLenOf_0_sysvq0asl((*s_49).bytes_0);
  {
    if (sl_14 == ((NI64)IL64(254))){
      goto X60QL_34;}
    if ((!(sl_14 == ((NI64)IL64(255))))){
      goto X60QL_33;}
    {
      NB8 X60Qx_267 = arcIsUnique_0_sysvq0asl((&(*(*s_49).more_0).rc_0));
      if (X60Qx_267){
        goto X60QL_33;}}
    X60QL_34: ;
    if (sl_14 == ((NI64)IL64(255))){
      NB8 X60Qx_268 = arcDec_0_sysvq0asl((&(*(*s_49).more_0).rc_0));}
    LongString_0_sysvq0asl* old_3 = (*s_49).more_0;
    NI64 oldLen_1 = (*old_3).fullLen_0;
    void* X60Qx_269 = alloc_1_sysvq0asl(((NI64)(((NI64)IL64(24)) + oldLen_1)));
    LongString_0_sysvq0asl* p_45 = ((LongString_0_sysvq0asl*)X60Qx_269);
    if ((!(p_45 == NIM_NIL))){
      (*p_45).rc_0 = IL64(0);
      (*p_45).fullLen_0 = oldLen_1;
      (*p_45).capImpl_0 = oldLen_1;
      copyMem_0_sysvq0asl(((void*)(&(*p_45).data_0[IL64(0)])), ((void*)(&(*old_3).data_0[IL64(0)])), oldLen_1);
      (*s_49).more_0 = p_45;
      (*((NU8*)(&(*s_49).bytes_0))) = ((NU8)((NI64)IL64(255)));}
    else {
      oomHandler_0_sysvq0asl(((NI64)(((NI64)IL64(24)) + oldLen_1)));
      (*s_49).bytes_0 = ((NU64)21760775509248519ull);
      (*s_49).more_0 = NIM_NIL;}}
  X60QL_33: ;}
void add_1_sysvq0asl(string_0_sysvq0asl* s_52, NC8 c_14){
  NI64 sl_16 = ssLenOf_0_sysvq0asl((*s_52).bytes_0);
  if (sl_16 < ((NI64)IL64(14))){
    NI64 newLen_14 = ((NI64)(sl_16 + IL64(1)));
    ((NC8*)((NU64)(((NU64)(&(*s_52).bytes_0)) + 1ull)))[sl_16] = c_14;
    (*((NU8*)(&(*s_52).bytes_0))) = ((NU8)newLen_14);}
  else {
    if (((NI64)IL64(14)) < sl_16){
      NI64 l_1 = (*(*s_52).more_0).fullLen_0;
      {
        if ((!(sl_16 == ((NI64)IL64(255))))){
          goto X60QL_37;}
        {
          NB8 X60Qx_271 = arcIsUnique_0_sysvq0asl((&(*(*s_52).more_0).rc_0));
          if ((!X60Qx_271)){
            goto X60QL_37;}}
        if ((!(l_1 < (*(*s_52).more_0).capImpl_0))){
          goto X60QL_37;}
        (*(*s_52).more_0).data_0[l_1] = c_14;
        (*(*s_52).more_0).fullLen_0 = ((NI64)(l_1 + IL64(1)));
        if (l_1 < ((NI64)IL64(7))){
          ((NC8*)((NU64)(((NU64)(&(*s_52).bytes_0)) + 1ull)))[l_1] = c_14;}}
      goto X60QL_36;
      X60QL_37: ;
      {
        NI64 oldLen_2 = (*(*s_52).more_0).fullLen_0;
        ensureUniqueLong_0_sysvq0asl(s_52, oldLen_2, ((NI64)(oldLen_2 + IL64(1))));
        NI64 X60Qx_272 = ssLenOf_0_sysvq0asl((*s_52).bytes_0);
        if (X60Qx_272 == ((NI64)IL64(255))){
          (*(*s_52).more_0).data_0[oldLen_2] = c_14;
          if (oldLen_2 < ((NI64)IL64(7))){
            ((NC8*)((NU64)(((NU64)(&(*s_52).bytes_0)) + 1ull)))[oldLen_2] = c_14;}}}
      X60QL_36: ;}
    else {
      transitionToLong_0_sysvq0asl(s_52, sl_16, ((NI64)(sl_16 + IL64(1))));
      NI64 X60Qx_273 = ssLenOf_0_sysvq0asl((*s_52).bytes_0);
      if (X60Qx_273 == ((NI64)IL64(255))){
        (*(*s_52).more_0).data_0[sl_16] = c_14;}}}}
NC8 getQ_9_sysvq0asl(string_0_sysvq0asl s_57, NI64 i_14){
  NI64 X60Qx_284;
  {
    {
      NI64 X60Qx_0h700;
      {
        NU64 bytes_0h702 = s_57.bytes_0;
        {
          X60Qx_0h700 = ((NI64)((NU64)(bytes_0h702 & 255ull)));
          returnLabel_0h704: ;}}
      X60Qx_284 = X60Qx_0h700;
      if (((NI64)IL64(14)) < X60Qx_284){
        X60Qx_284 = (*s_57.more_0).fullLen_0;}
      returnLabel_0h701: ;}}
  if ((!(i_14 < X60Qx_284))){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 3327929425545015038ull, .more_0 = (&strlit_0_I17787898778150197797_sysvq0asl)}
    );}
  if ((!(IL64(0) <= i_14))){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 3327929425545015038ull, .more_0 = (&strlit_0_I8081769352426431819_sysvq0asl)}
    );}
  NC8 result_117;
  NC8 X60Qx_40;
  NI64 X60Qx_285;
  {
    NU64 bytes_0h705 = s_57.bytes_0;
    {
      X60Qx_285 = ((NI64)((NU64)(bytes_0h705 & 255ull)));
      returnLabel_0h707: ;}}
  if (((NI64)IL64(14)) < X60Qx_285){
    X60Qx_40 = (*s_57.more_0).data_0[i_14];}
  else {
    X60Qx_40 = ((NC8*)((NU64)(((NU64)(&s_57.bytes_0)) + 1ull)))[i_14];}
  result_117 = X60Qx_40;
  return result_117;}
static inline void putQ_9_sysvq0asl(string_0_sysvq0asl* s_58, NI64 i_15, NC8 c_15){
  NI64 X60Qx_286 = len_4_sysvq0asl((*s_58));
  if ((!(i_15 < X60Qx_286))){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 3327929425545015038ull, .more_0 = (&strlit_0_I6290767771972150606_sysvq0asl)}
    );}
  if ((!(IL64(0) <= i_15))){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 3327929425545015038ull, .more_0 = (&strlit_0_I3404901998373565316_sysvq0asl)}
    );}
  prepareMutation_0_sysvq0asl(s_58);
  NI64 X60Qx_287 = ssLenOf_0_sysvq0asl((*s_58).bytes_0);
  if (((NI64)IL64(14)) < X60Qx_287){
    (*(*s_58).more_0).data_0[i_15] = c_15;
    if (i_15 < ((NI64)IL64(7))){
      ((NC8*)((NU64)(((NU64)(&(*s_58).bytes_0)) + 1ull)))[i_15] = c_15;}}
  else {
    ((NC8*)((NU64)(((NU64)(&(*s_58).bytes_0)) + 1ull)))[i_15] = c_15;}}
string_0_sysvq0asl substr_0_sysvq0asl(string_0_sysvq0asl s_59, NI64 first_0, NI64 last_0){
  string_0_sysvq0asl result_118;
  result_118 = (string_0_sysvq0asl){
    .bytes_0 = 0ull, .more_0 = NIM_NIL}
  ;
  NI64 sLen_2 = len_4_sysvq0asl(s_59);
  NI64 f_3 = max_3_sysvq0asl(first_0, IL64(0));
  NI64 X60Qx_288 = min_3_sysvq0asl(last_0, ((NI64)(sLen_2 - IL64(1))));
  NI64 l_2 = ((NI64)(X60Qx_288 + IL64(1)));
  if (l_2 <= f_3){
    return result_118;}
  NI64 newLen_17 = ((NI64)(l_2 - f_3));
  NC8* src_7 = rawData_1_sysvq0asl((&s_59));
  if (newLen_17 <= ((NI64)IL64(14))){
    (*((NU8*)(&result_118.bytes_0))) = ((NU8)newLen_17);
    copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&result_118.bytes_0)) + 1ull)))), ((void*)((NU64)(((NU64)src_7) + ((NU64)f_3)))), newLen_17);}
  else {
    void* X60Qx_289 = alloc_1_sysvq0asl(((NI64)(((NI64)IL64(24)) + newLen_17)));
    LongString_0_sysvq0asl* p_46 = ((LongString_0_sysvq0asl*)X60Qx_289);
    if ((!(p_46 == NIM_NIL))){
      (*p_46).rc_0 = IL64(0);
      (*p_46).fullLen_0 = newLen_17;
      (*p_46).capImpl_0 = newLen_17;
      copyMem_0_sysvq0asl(((void*)(&(*p_46).data_0[IL64(0)])), ((void*)((NU64)(((NU64)src_7) + ((NU64)f_3)))), newLen_17);
      result_118.more_0 = p_46;
      (*((NU8*)(&result_118.bytes_0))) = ((NU8)((NI64)IL64(255)));
      copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&result_118.bytes_0)) + 1ull)))), ((void*)(&(*p_46).data_0[IL64(0)])), ((NI64)IL64(7)));}
    else {
      oomHandler_0_sysvq0asl(((NI64)(((NI64)IL64(24)) + newLen_17)));
      result_118.bytes_0 = ((NU64)21760775509248519ull);
      result_118.more_0 = NIM_NIL;}}
  return result_118;}
string_0_sysvq0asl ampQ_0_sysvq0asl(string_0_sysvq0asl a_58, string_0_sysvq0asl b_20){
  string_0_sysvq0asl result_143;
  result_143 = (string_0_sysvq0asl){
    .bytes_0 = 0ull, .more_0 = NIM_NIL}
  ;
  NI64 X60Qx_319 = len_4_sysvq0asl(a_58);
  NI64 X60Qx_320 = len_4_sysvq0asl(b_20);
  NI64 rlen_0 = ((NI64)(X60Qx_319 + X60Qx_320));
  if (rlen_0 == IL64(0)){
    return result_143;}
  if (rlen_0 <= ((NI64)IL64(14))){
    NI64 al_0 = len_4_sysvq0asl(a_58);
    (*((NU8*)(&result_143.bytes_0))) = ((NU8)rlen_0);
    if (IL64(0) < al_0){
      NC8* X60Qx_321 = rawData_1_sysvq0asl((&a_58));
      copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&result_143.bytes_0)) + 1ull)))), ((void*)X60Qx_321), al_0);}
    NI64 X60Qx_322 = len_4_sysvq0asl(b_20);
    if (IL64(0) < X60Qx_322){
      NC8* X60Qx_323 = rawData_1_sysvq0asl((&b_20));
      NI64 X60Qx_324 = len_4_sysvq0asl(b_20);
      copyMem_0_sysvq0asl(((void*)((NU64)(((NU64)(((NU64)(&result_143.bytes_0)) + 1ull)) + ((NU64)al_0)))), ((void*)X60Qx_323), X60Qx_324);}}
  else {
    void* X60Qx_325 = alloc_1_sysvq0asl(((NI64)(((NI64)IL64(24)) + rlen_0)));
    LongString_0_sysvq0asl* p_49 = ((LongString_0_sysvq0asl*)X60Qx_325);
    if ((!(p_49 == NIM_NIL))){
      (*p_49).rc_0 = IL64(0);
      (*p_49).fullLen_0 = rlen_0;
      (*p_49).capImpl_0 = rlen_0;
      NI64 al_1 = len_4_sysvq0asl(a_58);
      if (IL64(0) < al_1){
        NC8* X60Qx_326 = rawData_1_sysvq0asl((&a_58));
        copyMem_0_sysvq0asl(((void*)(&(*p_49).data_0[IL64(0)])), ((void*)X60Qx_326), al_1);}
      NI64 X60Qx_327 = len_4_sysvq0asl(b_20);
      if (IL64(0) < X60Qx_327){
        NC8* X60Qx_328 = rawData_1_sysvq0asl((&b_20));
        NI64 X60Qx_329 = len_4_sysvq0asl(b_20);
        copyMem_0_sysvq0asl(((void*)((NU64)(((NU64)(&(*p_49).data_0[IL64(0)])) + ((NU64)al_1)))), ((void*)X60Qx_328), X60Qx_329);}
      result_143.more_0 = p_49;
      (*((NU8*)(&result_143.bytes_0))) = ((NU8)((NI64)IL64(255)));
      copyMem_0_sysvq0asl(((void*)((NC8*)((NU64)(((NU64)(&result_143.bytes_0)) + 1ull)))), ((void*)(&(*p_49).data_0[IL64(0)])), ((NI64)IL64(7)));}
    else {
      oomHandler_0_sysvq0asl(((NI64)(((NI64)IL64(24)) + rlen_0)));
      result_143.bytes_0 = ((NU64)21760775509248519ull);
      result_143.more_0 = NIM_NIL;}}
  return result_143;}
string_0_sysvq0asl nimBorrowCStringUnsafe(NC8* s_65){
  string_0_sysvq0asl result_149;
  NI64 X60Qx_335;
  {
    {
      if (((void*)s_65) == NIM_NIL){
        X60Qx_335 = IL64(0);}
      else {
        size_t X60Qx_0h1098;
        {
          {
            NI64 i_0h1102 = IL64(0);
            {
              while ((!(s_65[i_0h1102] == (NC8)'\000'))){
                {
                  {
                    (*(&i_0h1102)) = ((NI64)((*(&i_0h1102)) + ((NI64)IL64(1))));
                    returnLabel_0h1106: ;}}}}
            whileStmtLabel_0h1103: ;
            X60Qx_0h1098 = ((size_t)i_0h1102);
            returnLabel_0h1104: ;}}
        X60Qx_335 = ((NI64)X60Qx_0h1098);}
      returnLabel_0h1099: ;}}
  string_0_sysvq0asl X60Qx_336;
  {
    {
      X60Qx_336 = (string_0_sysvq0asl){
        .bytes_0 = 0ull, .more_0 = NIM_NIL}
      ;
      if (X60Qx_335 <= IL64(0)){
        goto returnLabel_0h1112;}
      if (X60Qx_335 <= ((NI64)IL64(14))){
        (*((NU8*)(&X60Qx_336.bytes_0))) = ((NU8)X60Qx_335);
        {
          void* dest_0h1113 = ((void*)((NC8*)((NU64)(((NU64)(&X60Qx_336.bytes_0)) + 1ull))));
          void* src_0h1114 = ((void*)s_65);
          {
            memcpy(dest_0h1113, src_0h1114, ((size_t)X60Qx_335));
            returnLabel_0h1116: ;}}}
      else {
        void* X60Qx_0h1110;
        {
          NI64 size_0h1117 = ((NI64)(((NI64)IL64(24)) + X60Qx_335));
          {
            void* X60Qx_0h1119;
            {
              {
                void* X60Qx_0h1124 = rawAlloc_0_sysvq0asl((&allocator_0_sysvq0asl), size_0h1117, IL64(0));
                X60Qx_0h1119 = X60Qx_0h1124;
                returnLabel_0h1125: ;}}
            X60Qx_0h1110 = X60Qx_0h1119;
            returnLabel_0h1120: ;}}
        LongString_0_sysvq0asl* p_0h1111 = ((LongString_0_sysvq0asl*)X60Qx_0h1110);
        if ((!(p_0h1111 == NIM_NIL))){
          (*p_0h1111).rc_0 = IL64(0);
          (*p_0h1111).fullLen_0 = X60Qx_335;
          (*p_0h1111).capImpl_0 = X60Qx_335;
          {
            void* dest_0h1126 = ((void*)(&(*p_0h1111).data_0[IL64(0)]));
            void* src_0h1127 = ((void*)s_65);
            {
              memcpy(dest_0h1126, src_0h1127, ((size_t)X60Qx_335));
              returnLabel_0h1129: ;}}
          X60Qx_336.more_0 = p_0h1111;
          (*((NU8*)(&X60Qx_336.bytes_0))) = ((NU8)((NI64)IL64(255)));
          {
            void* dest_0h1130 = ((void*)((NC8*)((NU64)(((NU64)(&X60Qx_336.bytes_0)) + 1ull))));
            void* src_0h1131 = ((void*)(&(*p_0h1111).data_0[IL64(0)]));
            NI64 size_0h1132 = ((NI64)IL64(7));
            {
              memcpy(dest_0h1130, src_0h1131, ((size_t)size_0h1132));
              returnLabel_0h1133: ;}}}
        else {
          oomHandler_0_sysvq0asl(((NI64)(((NI64)IL64(24)) + X60Qx_335)));
          X60Qx_336.bytes_0 = ((NU64)21760775509248519ull);
          X60Qx_336.more_0 = NIM_NIL;}}
      returnLabel_0h1112: ;}}
  result_149 = X60Qx_336;
  return result_149;}
static inline void arcInc_0_sysvq0asl(NI64* memLoc_0){
  NI64 X60Qx_358 = __atomic_add_fetch((&(*memLoc_0)), IL64(1), __ATOMIC_SEQ_CST);}
static inline NB8 arcDec_0_sysvq0asl(NI64* memLoc_1){
  NB8 result_184;
  NI64 X60Qx_359 = __atomic_load_n((&(*memLoc_1)), __ATOMIC_ACQUIRE);
  if (X60Qx_359 == IL64(0)){
    result_184 = NIM_TRUE;}
  else {
    NI64 X60Qx_360 = __atomic_sub_fetch((&(*memLoc_1)), IL64(1), __ATOMIC_SEQ_CST);
    result_184 = (X60Qx_360 < IL64(0));}
  return result_184;}
static inline NB8 arcIsUnique_0_sysvq0asl(NI64* memLoc_2){
  NB8 result_185;
  NI64 X60Qx_361 = __atomic_load_n((&(*memLoc_2)), __ATOMIC_ACQUIRE);
  result_185 = (X60Qx_361 == IL64(0));
  return result_185;}
void writeErr_0_sysvq0asl(string_0_sysvq0asl s_72){
  NC8* X60Qx_362;
  {
    {
      NI64 X60Qx_0h1307;
      {
        NU64 bytes_0h1309 = (*(&s_72)).bytes_0;
        {
          X60Qx_0h1307 = ((NI64)((NU64)(bytes_0h1309 & 255ull)));
          returnLabel_0h1311: ;}}
      if (((NI64)IL64(14)) < X60Qx_0h1307){
        X60Qx_362 = ((NC8*)((NU64)(((NU64)(&(*(*(&s_72)).more_0).data_0[IL64(0)])) + ((NU64)IL64(0)))));}
      else {
        X60Qx_362 = ((NC8*)((NU64)(((NU64)((NC8*)((NU64)(((NU64)(&(*(&s_72)).bytes_0)) + 1ull)))) + ((NU64)IL64(0)))));}
      returnLabel_0h1308: ;}}
  NI64 X60Qx_363;
  {
    {
      NI64 X60Qx_0h1314;
      {
        NU64 bytes_0h1316 = s_72.bytes_0;
        {
          X60Qx_0h1314 = ((NI64)((NU64)(bytes_0h1316 & 255ull)));
          returnLabel_0h1318: ;}}
      X60Qx_363 = X60Qx_0h1314;
      if (((NI64)IL64(14)) < X60Qx_363){
        X60Qx_363 = (*s_72.more_0).fullLen_0;}
      returnLabel_0h1315: ;}}
  NI64 X60Qx_364 = cWriteErr_0_sysvq0asl(((NI32)IL64(2)), ((void*)X60Qx_362), ((NU64)X60Qx_363));}
void writeErr_2_sysvq0asl(NI64 x_344){
  string_0_sysvq0asl X60Qtmp_6 = dollarQ_1_sysvq0asl(x_344);
  {
    string_0_sysvq0asl s_0h1321 = X60Qtmp_6;
    {
      NC8* X60Qx_0h1322;
      {
        {
          NI64 X60Qx_0h1329;
          {
            NU64 bytes_0h1331 = (*(&s_0h1321)).bytes_0;
            {
              X60Qx_0h1329 = ((NI64)((NU64)(bytes_0h1331 & 255ull)));
              returnLabel_0h1333: ;}}
          if (((NI64)IL64(14)) < X60Qx_0h1329){
            X60Qx_0h1322 = ((NC8*)((NU64)(((NU64)(&(*(*(&s_0h1321)).more_0).data_0[IL64(0)])) + ((NU64)IL64(0)))));}
          else {
            X60Qx_0h1322 = ((NC8*)((NU64)(((NU64)((NC8*)((NU64)(((NU64)(&(*(&s_0h1321)).bytes_0)) + 1ull)))) + ((NU64)IL64(0)))));}
          returnLabel_0h1330: ;}}
      NI64 X60Qx_0h1323;
      {
        {
          NI64 X60Qx_0h1336;
          {
            NU64 bytes_0h1338 = s_0h1321.bytes_0;
            {
              X60Qx_0h1336 = ((NI64)((NU64)(bytes_0h1338 & 255ull)));
              returnLabel_0h1340: ;}}
          X60Qx_0h1323 = X60Qx_0h1336;
          if (((NI64)IL64(14)) < X60Qx_0h1323){
            X60Qx_0h1323 = (*s_0h1321.more_0).fullLen_0;}
          returnLabel_0h1337: ;}}
      NI64 X60Qx_0h1324 = cWriteErr_0_sysvq0asl(((NI32)IL64(2)), ((void*)X60Qx_0h1322), ((NU64)X60Qx_0h1323));
      returnLabel_0h1325: ;}}
  {
    {
      NI64 X60Qx_0h1342;
      {
        NU64 bytes_0h1344 = X60Qtmp_6.bytes_0;
        {
          X60Qx_0h1342 = ((NI64)((NU64)(bytes_0h1344 & 255ull)));
          returnLabel_0h1346: ;}}
      if (X60Qx_0h1342 == ((NI64)IL64(255))){
        destroyHeapStr_0_sysvq0asl(X60Qtmp_6.more_0);}
      returnLabel_0h1343: ;}}}
void writeErr_3_sysvq0asl(NU64 x_345){
  string_0_sysvq0asl X60Qtmp_7 = dollarQ_0_sysvq0asl(x_345);
  {
    string_0_sysvq0asl s_0h1347 = X60Qtmp_7;
    {
      NC8* X60Qx_0h1348;
      {
        {
          NI64 X60Qx_0h1355;
          {
            NU64 bytes_0h1357 = (*(&s_0h1347)).bytes_0;
            {
              X60Qx_0h1355 = ((NI64)((NU64)(bytes_0h1357 & 255ull)));
              returnLabel_0h1359: ;}}
          if (((NI64)IL64(14)) < X60Qx_0h1355){
            X60Qx_0h1348 = ((NC8*)((NU64)(((NU64)(&(*(*(&s_0h1347)).more_0).data_0[IL64(0)])) + ((NU64)IL64(0)))));}
          else {
            X60Qx_0h1348 = ((NC8*)((NU64)(((NU64)((NC8*)((NU64)(((NU64)(&(*(&s_0h1347)).bytes_0)) + 1ull)))) + ((NU64)IL64(0)))));}
          returnLabel_0h1356: ;}}
      NI64 X60Qx_0h1349;
      {
        {
          NI64 X60Qx_0h1362;
          {
            NU64 bytes_0h1364 = s_0h1347.bytes_0;
            {
              X60Qx_0h1362 = ((NI64)((NU64)(bytes_0h1364 & 255ull)));
              returnLabel_0h1366: ;}}
          X60Qx_0h1349 = X60Qx_0h1362;
          if (((NI64)IL64(14)) < X60Qx_0h1349){
            X60Qx_0h1349 = (*s_0h1347.more_0).fullLen_0;}
          returnLabel_0h1363: ;}}
      NI64 X60Qx_0h1350 = cWriteErr_0_sysvq0asl(((NI32)IL64(2)), ((void*)X60Qx_0h1348), ((NU64)X60Qx_0h1349));
      returnLabel_0h1351: ;}}
  {
    {
      NI64 X60Qx_0h1368;
      {
        NU64 bytes_0h1370 = X60Qtmp_7.bytes_0;
        {
          X60Qx_0h1368 = ((NI64)((NU64)(bytes_0h1370 & 255ull)));
          returnLabel_0h1372: ;}}
      if (X60Qx_0h1368 == ((NI64)IL64(255))){
        destroyHeapStr_0_sysvq0asl(X60Qtmp_7.more_0);}
      returnLabel_0h1369: ;}}}
void __attribute__((noreturn)) die_0_sysvq0asl(NI32 value_0){
  {
    NI64 code_0h1373 = ((NI64)value_0);
    {
      gExitFlush_0_sysvq0asl();
      cExitSys_0_sysvq0asl(((NI32)code_0h1373));
      returnLabel_0h1374: ;}}}
N_NOINLINE void __attribute__((noreturn)) panic_0_sysvq0asl(string_0_sysvq0asl s_74){
  writeErr_0_sysvq0asl(s_74);
  die_0_sysvq0asl(((NI32)IL64(1)));}
static inline NI64 nimIcheckAB(NI64 i_18, NI64 a_73, NI64 b_24){
  NI64 result_186;
  if (((a_73 <= i_18) && (i_18 <= b_24))){
    result_186 = ((NI64)(i_18 - a_73));}
  else {
    result_186 = IL64(0);
    raiseIndexError3_0_Ice8haj1_sysvq0asl(i_18, a_73, b_24);}
  return result_186;}
static inline NI64 nimIcheckB(NI64 i_19, NI64 b_25){
  NI64 result_187;
  if (((IL64(0) <= i_19) && (i_19 <= b_25))){
    result_187 = i_19;}
  else {
    result_187 = IL64(0);
    raiseIndexError3_0_Ice8haj1_sysvq0asl(i_19, IL64(0), b_25);}
  return result_187;}
static inline NU64 nimUcheckAB(NU64 i_20, NU64 a_74, NU64 b_26){
  NU64 result_188;
  result_188 = ((NU64)(i_20 - a_74));
  if (b_26 < result_188){
    raiseIndexError3_0_Ils6gq61_sysvq0asl(i_20, a_74, b_26);}
  return result_188;}
static inline NU64 nimUcheckB(NU64 i_21, NU64 b_27){
  NU64 result_189;
  result_189 = i_21;
  if (b_27 < result_189){
    raiseIndexError3_0_Ils6gq61_sysvq0asl(i_21, ((NU64)IL64(0)), b_27);}
  return result_189;}
static inline void nimInvalidObjConv(string_0_sysvq0asl name_0){
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 7235433442201987582ull, .more_0 = (&strlit_0_I15539159382304113184_sysvq0asl)}
  );
  {
    string_0_sysvq0asl s_0h1375 = name_0;
    {
      NC8* X60Qx_0h1376;
      {
        {
          NI64 X60Qx_0h1383;
          {
            NU64 bytes_0h1385 = (*(&s_0h1375)).bytes_0;
            {
              X60Qx_0h1383 = ((NI64)((NU64)(bytes_0h1385 & 255ull)));
              returnLabel_0h1387: ;}}
          if (((NI64)IL64(14)) < X60Qx_0h1383){
            X60Qx_0h1376 = ((NC8*)((NU64)(((NU64)(&(*(*(&s_0h1375)).more_0).data_0[IL64(0)])) + ((NU64)IL64(0)))));}
          else {
            X60Qx_0h1376 = ((NC8*)((NU64)(((NU64)((NC8*)((NU64)(((NU64)(&(*(&s_0h1375)).bytes_0)) + 1ull)))) + ((NU64)IL64(0)))));}
          returnLabel_0h1384: ;}}
      NI64 X60Qx_0h1377;
      {
        {
          NI64 X60Qx_0h1390;
          {
            NU64 bytes_0h1392 = s_0h1375.bytes_0;
            {
              X60Qx_0h1390 = ((NI64)((NU64)(bytes_0h1392 & 255ull)));
              returnLabel_0h1394: ;}}
          X60Qx_0h1377 = X60Qx_0h1390;
          if (((NI64)IL64(14)) < X60Qx_0h1377){
            X60Qx_0h1377 = (*s_0h1375.more_0).fullLen_0;}
          returnLabel_0h1391: ;}}
      NI64 X60Qx_0h1378 = cWriteErr_0_sysvq0asl(((NI32)IL64(2)), ((void*)X60Qx_0h1376), ((NU64)X60Qx_0h1377));
      returnLabel_0h1379: ;}}
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 2561ull, .more_0 = NIM_NIL}
  );
  {
    NI32 value_0h1395 = ((NI32)IL64(1));
    {
      {
        NI64 code_0h1397 = ((NI64)value_0h1395);
        {
          gExitFlush_0_sysvq0asl();
          cExitSys_0_sysvq0asl(((NI32)code_0h1397));
          returnLabel_0h1398: ;}}
      returnLabel_0h1396: ;}}}
static inline void nimChckNilDisp(void* p_31){
  if (p_31 == NIM_NIL){
    writeErr_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 2338616626601092094ull, .more_0 = (&strlit_0_I14281474217946372742_sysvq0asl)}
    );
    {
      NI32 value_0h1399 = ((NI32)IL64(1));
      {
        {
          NI64 code_0h1401 = ((NI64)value_0h1399);
          {
            gExitFlush_0_sysvq0asl();
            cExitSys_0_sysvq0asl(((NI32)code_0h1401));
            returnLabel_0h1402: ;}}
        returnLabel_0h1400: ;}}}}
void* nimLoadLibrary(NC8* path_2){
  void* result_190;
  int flags_1 = ((NI32)IL64(2));
  void* X60Qx_366 = dlopen_0_sysvq0asl(path_2, flags_1);
  result_190 = X60Qx_366;
  return result_190;}
void* nimGetProcAddr(void* lib_3, NC8* name_3){
  void* result_191;
  void* X60Qx_367 = dlsym_0_sysvq0asl(lib_3, name_3);
  result_191 = X60Qx_367;
  if (result_191 == NIM_NIL){
    {
      {
        writeErr_0_sysvq0asl((string_0_sysvq0asl){
          .bytes_0 = 7935452960416293886ull, .more_0 = (&strlit_0_I10604297744791418982_sysvq0asl)}
        );
        {
          {
            NI64 n_0h1462 = IL64(0);
            NC8* p_0h1463 = ((NC8*)name_3);
            {
              while ((!(p_0h1463[n_0h1462] == (NC8)'\000'))){
                {
                  {
                    (*(&n_0h1462)) = ((NI64)((*(&n_0h1462)) + ((NI64)IL64(1))));
                    returnLabel_0h1468: ;}}}}
            whileStmtLabel_0h1464: ;
            NI64 X60Qx_0h1465 = cWriteErr_0_sysvq0asl(((NI32)IL64(2)), ((void*)p_0h1463), ((NU64)n_0h1462));
            returnLabel_0h1466: ;}}
        writeErr_0_sysvq0asl((string_0_sysvq0asl){
          .bytes_0 = 2561ull, .more_0 = NIM_NIL}
        );
        {
          NI32 value_0h1469 = ((NI32)IL64(1));
          {
            {
              NI64 code_0h1471 = ((NI64)value_0h1469);
              {
                gExitFlush_0_sysvq0asl();
                cExitSys_0_sysvq0asl(((NI32)code_0h1471));
                returnLabel_0h1472: ;}}
            returnLabel_0h1470: ;}}
        returnLabel_0h1460: ;}}}
  return result_191;}
void* nimDynlibLoadStep(void* prev_0, NC8* cand_0){
  void* result_192;
  if ((!(prev_0 == NIM_NIL))){
    result_192 = prev_0;}
  else {
    void* X60Qx_368;
    {
      {
        int flags_0h1475 = ((NI32)IL64(2));
        X60Qx_368 = dlopen_0_sysvq0asl(cand_0, flags_0h1475);
        returnLabel_0h1477: ;}}
    result_192 = X60Qx_368;}
  return result_192;}
void* nimDynlibCheck(void* lib_4, NC8* path_3){
  void* result_193;
  if (lib_4 == NIM_NIL){
    writeErr_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7935452960416293886ull, .more_0 = (&strlit_0_I16690852185662743073_sysvq0asl)}
    );
    {
      {
        NI64 n_0h1479 = IL64(0);
        NC8* p_0h1480 = ((NC8*)path_3);
        {
          while ((!(p_0h1480[n_0h1479] == (NC8)'\000'))){
            {
              {
                (*(&n_0h1479)) = ((NI64)((*(&n_0h1479)) + ((NI64)IL64(1))));
                returnLabel_0h1485: ;}}}}
        whileStmtLabel_0h1481: ;
        NI64 X60Qx_0h1482 = cWriteErr_0_sysvq0asl(((NI32)IL64(2)), ((void*)p_0h1480), ((NU64)n_0h1479));
        returnLabel_0h1483: ;}}
    writeErr_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 2561ull, .more_0 = NIM_NIL}
    );
    {
      NI32 value_0h1486 = ((NI32)IL64(1));
      {
        {
          NI64 code_0h1488 = ((NI64)value_0h1486);
          {
            gExitFlush_0_sysvq0asl();
            cExitSys_0_sysvq0asl(((NI32)code_0h1488));
            returnLabel_0h1489: ;}}
        returnLabel_0h1487: ;}}}
  result_193 = lib_4;
  return result_193;}
static inline void inc_0_Iwdk9lf_sysvq0asl(NI64* x_390, NI64 y_217){
  (*x_390) = ((NI64)((*x_390) + y_217));}
static inline void dec_0_Iw9ew8i1_sysvq0asl(NI64* x_392, NI64 y_219){
  (*x_392) = ((NI64)((*x_392) - y_219));}
static inline void listAdd_0_Ik4wxhz_sysvq0asl(SmallChunk_0_sysvq0asl** head_5, SmallChunk_0_sysvq0asl* c_42){
  (*c_42).next_0 = (*head_5);
  if ((!((*head_5) == NIM_NIL))){
    (*(*head_5)).prev_0 = c_42;}
  (*head_5) = c_42;}
static inline void listRemove_0_Ibzev091_sysvq0asl(SmallChunk_0_sysvq0asl** head_6, SmallChunk_0_sysvq0asl* c_43){
  if (c_43 == (*head_6)){
    (*head_6) = (*c_43).next_0;
    if ((!((*head_6) == NIM_NIL))){
      (*(*head_6)).prev_0 = NIM_NIL;}}
  else {
    (*(*c_43).prev_0).next_0 = (*c_43).next_0;
    if ((!((*c_43).next_0 == NIM_NIL))){
      (*(*c_43).next_0).prev_0 = (*c_43).prev_0;}}
  (*c_43).next_0 = NIM_NIL;
  (*c_43).prev_0 = NIM_NIL;}
N_NOINLINE void raiseIndexError3_0_Ice8haj1_sysvq0asl(NI64 i_77, NI64 a_89, NI64 b_41){
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 8007532514336729598ull, .more_0 = (&strlit_0_I11614695157650328859_sysvq0asl)}
  );
  writeErr_2_sysvq0asl(i_77);
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 2336921205458477063ull, .more_0 = NIM_NIL}
  );
  writeErr_2_sysvq0asl(a_89);
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 3026434ull, .more_0 = NIM_NIL}
  );
  writeErr_2_sysvq0asl(b_41);
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 2561ull, .more_0 = NIM_NIL}
  );
  die_0_sysvq0asl(((NI32)IL64(1)));}
N_NOINLINE void raiseIndexError3_0_Ils6gq61_sysvq0asl(NU64 i_78, NU64 a_90, NU64 b_42){
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 8007532514336729598ull, .more_0 = (&strlit_0_I11614695157650328859_sysvq0asl)}
  );
  writeErr_3_sysvq0asl(i_78);
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 2336921205458477063ull, .more_0 = NIM_NIL}
  );
  writeErr_3_sysvq0asl(a_90);
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 3026434ull, .more_0 = NIM_NIL}
  );
  writeErr_3_sysvq0asl(b_42);
  writeErr_0_sysvq0asl((string_0_sysvq0asl){
    .bytes_0 = 2561ull, .more_0 = NIM_NIL}
  );
  die_0_sysvq0asl(((NI32)IL64(1)));}
void X60Qini_0_sysvq0asl(void){
  if (X60QiniGuard_0_sysvq0asl){
    return;}
  X60QiniGuard_0_sysvq0asl = NIM_TRUE;
  {
    {
      (*(&exc_0_sysvq0asl)) = NIM_NIL;
      returnLabel_0h2092: ;}}}
static inline void inc_1_Irn1g7r1_mat7cnfv21(NI64* x_154){
  (*x_154) = ((NI64)((*x_154) + ((NI64)IL64(1))));}
static void __attribute__((constructor)) init(void) {gExitFlush_0_sysvq0asl = nimNoopFlush_0_sysvq0asl;
oomHandler_0_sysvq0asl = continueAfterOutOfMem_0_sysvq0asl;
}

