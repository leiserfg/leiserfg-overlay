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
typedef struct LongString_0_sysvq0asl LongString_0_sysvq0asl;
typedef NU8 FileMode_0_syn1lfpjv;

#define fmRead_0_syn1lfpjv ((NU8)IL64(0))
#define fmWrite_0_syn1lfpjv ((NU8)IL64(1))
#define fmReadWrite_0_syn1lfpjv ((NU8)IL64(2))
#define fmReadWriteExisting_0_syn1lfpjv ((NU8)IL64(3))
#define fmAppend_0_syn1lfpjv ((NU8)IL64(4))
typedef NU8 FileSeekPos_0_syn1lfpjv;

#define fspSet_0_syn1lfpjv ((NU8)IL64(0))
#define fspCur_0_syn1lfpjv ((NU8)IL64(1))
#define fspEnd_0_syn1lfpjv ((NU8)IL64(2))
typedef NU8 FilePermission_0_syn1lfpjv;

#define fpUserExec_0_syn1lfpjv ((NU8)IL64(0))
#define fpUserWrite_0_syn1lfpjv ((NU8)IL64(1))
#define fpUserRead_0_syn1lfpjv ((NU8)IL64(2))
#define fpGroupExec_0_syn1lfpjv ((NU8)IL64(3))
#define fpGroupWrite_0_syn1lfpjv ((NU8)IL64(4))
#define fpGroupRead_0_syn1lfpjv ((NU8)IL64(5))
#define fpOthersExec_0_syn1lfpjv ((NU8)IL64(6))
#define fpOthersWrite_0_syn1lfpjv ((NU8)IL64(7))
#define fpOthersRead_0_syn1lfpjv ((NU8)IL64(8))
typedef NU8 FileFlag_0_syn1lfpjv;

#define ffReadable_0_syn1lfpjv ((NU8)IL64(0))
#define ffWritable_0_syn1lfpjv ((NU8)IL64(1))
#define ffEof_0_syn1lfpjv ((NU8)IL64(2))
#define ffError_0_syn1lfpjv ((NU8)IL64(3))
#define ffUnbuf_0_syn1lfpjv ((NU8)IL64(4))
typedef struct seq_0_I7epg22_syn1lfpjv{
  NI64 len_0;
  NC8* data_0;}
seq_0_I7epg22_syn1lfpjv;
typedef struct FileObj_0_syn1lfpjv{
  int fd_0;
  NU8 flags_0;
  seq_0_I7epg22_syn1lfpjv wbuf_0;
  seq_0_I7epg22_syn1lfpjv rbuf_0;
  NI64 rpos_0;}
FileObj_0_syn1lfpjv;
typedef struct X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv{
  NI r_00;
  FileObj_0_syn1lfpjv d_00;}
X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv;
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
typedef struct string_0_sysvq0asl{
  NU64 bytes_0;
  LongString_0_sysvq0asl* more_0;}
string_0_sysvq0asl;
typedef struct X60Qt_0_IAtupleSX45rrorX43ode0sysvq0aslSstring0R20_syn1lfpjv{
  ErrorCode_0_sysvq0asl fld_0;
  string_0_sysvq0asl fld_1;}
X60Qt_0_IAtupleSX45rrorX43ode0sysvq0aslSstring0R20_syn1lfpjv;
typedef struct X60Qt_0_IAtupleSX45rrorX43ode0sysvq0aslAiS64_syn1lfpjv{
  ErrorCode_0_sysvq0asl fld_0;
  NI64 fld_1;}
X60Qt_0_IAtupleSX45rrorX43ode0sysvq0aslAiS64_syn1lfpjv;
typedef struct LongString_0_sysvq0asl{
  NI64 fullLen_0;
  NI64 rc_0;
  NI64 capImpl_0;
  NC8 data_0[];}
LongString_0_sysvq0asl;
typedef N_NIMCALL_PTR(void,  X60Qt_0_IAiS64ZSEAnimcallZAfalseZAR17_sysvq0asl)(NI64);
typedef N_NIMCALL_PTR(void,  X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl)(void);
NI64 sysWrite_0_syn1lfpjv(int fd_0, void* buf_0, NU64 n_0) __asm__(NIM_ASM_PREFIX "write");
static inline NI64 len_3_Irwqcn4_syn1lfpjv(seq_0_I7epg22_syn1lfpjv s_8);
static inline NC8* getQ_7_Iqupddu1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv s_9, NI64 i_1);
void setLen_0_Ifg83xa1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv* s_10, NI64 newLen_1);
NB8 resize_0_Irimnxi1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv* dest_2, NI64 addedElements_1);
extern void* allocFixed_0_sysvq0asl(NI64 size_31);
extern N_NOINLINE void __attribute__((noreturn)) panic_0_sysvq0asl(string_0_sysvq0asl s_74);
extern X60Qt_0_IAiS64ZSEAnimcallZAfalseZAR17_sysvq0asl oomHandler_0_sysvq0asl;
extern NI64 allocatedSize_0_sysvq0asl(void* p_27);
static inline NI64 recalcCap_0_sysvq0asl(NI64 oldCap_0, NI64 addedElements_0);
extern void* realloc_1_sysvq0asl(void* p_25, NI64 size_30);
extern void X60Qini_0_sysvq0asl(void);
extern void X60Qini_0_for2ybv4p1(void);
static inline void setExitFlush_0_sysvq0asl(X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl p_0);
extern X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl gExitFlush_0_sysvq0asl;
LongString_0_sysvq0asl const strlit_0_I7655461567997625268_syn1lfpjv = {
  .fullLen_0 = IL64(139), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../../../../../nix/store/k6w9mr6jan950vv5lxkfzgh0pw94jgjv-nimony-0.6.0/lib/std/system/seqimpl.nim(167, 41): i < s.len [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I3542881952749030761_syn1lfpjv = {
  .fullLen_0 = IL64(136), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../../../../../nix/store/k6w9mr6jan950vv5lxkfzgh0pw94jgjv-nimony-0.6.0/lib/std/system/seqimpl.nim(167, 41): 0 <= i [AssertionDefect]\012"}
;
X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* stdin_0_syn1lfpjv;
X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* stdout_0_syn1lfpjv;
X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* stderr_0_syn1lfpjv;
NB8 X60QiniGuard_0_syn1lfpjv;
X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* newFile_0_syn1lfpjv(int fd_4, NU8 flags_1){
  X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* result_4;
  void* X60Qx_3 = allocFixed_0_sysvq0asl(sizeof(X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv));
  X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* X60Qtmp_0 = ((X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv*)X60Qx_3);
  seq_0_I7epg22_syn1lfpjv X60Qx_4;
  {
    {
      X60Qx_4 = (seq_0_I7epg22_syn1lfpjv){
        .len_0 = IL64(0), .data_0 = NIM_NIL}
      ;
      returnLabel_0h6: ;}}
  seq_0_I7epg22_syn1lfpjv X60Qx_5;
  {
    {
      X60Qx_5 = (seq_0_I7epg22_syn1lfpjv){
        .len_0 = IL64(0), .data_0 = NIM_NIL}
      ;
      returnLabel_0h16: ;}}
  (*X60Qtmp_0) = (X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv){
    .r_00 = IL64(0), .d_00 = (FileObj_0_syn1lfpjv){
      .fd_0 = fd_4, .flags_0 = flags_1, .wbuf_0 = X60Qx_4, .rbuf_0 = X60Qx_5, .rpos_0 = ((NI64)IL64(0))}}
  ;
  result_4 = X60Qtmp_0;
  return result_4;}
NB8 rawWriteAll_0_syn1lfpjv(int fd_5, void* p_0, NI64 n_2){
  NB8 result_6;
  NI64 off_0 = IL64(0);
  {
    while (off_0 < n_2){
      NI64 k_0 = sysWrite_0_syn1lfpjv(fd_5, ((void*)((NI64)(((NI64)p_0) + off_0))), ((NU64)((NI64)(n_2 - off_0))));
      if (k_0 <= IL64(0)){
        return NIM_FALSE;}
      {
        {
          (*(&off_0)) = ((NI64)((*(&off_0)) + k_0));
          returnLabel_0h23: ;}}}}
  whileStmtLabel_0: ;
  result_6 = NIM_TRUE;
  return result_6;}
void flushImpl_0_syn1lfpjv(X60Qt_0_IArefSX46ileX4fbj0syn1lfpjv_syn1lfpjv* f_1){
  NI64 X60Qx_6 = len_3_Irwqcn4_syn1lfpjv((*f_1).d_00.wbuf_0);
  if (IL64(0) < X60Qx_6){
    NC8* X60Qx_7 = getQ_7_Iqupddu1_syn1lfpjv((*f_1).d_00.wbuf_0, IL64(0));
    NI64 X60Qx_8 = len_3_Irwqcn4_syn1lfpjv((*f_1).d_00.wbuf_0);
    NB8 X60Qx_9 = rawWriteAll_0_syn1lfpjv((*f_1).d_00.fd_0, ((void*)(&(*X60Qx_7))), X60Qx_8);
    if ((!X60Qx_9)){
      NU8* X60Qdesugar_0 = (&(*f_1).d_00.flags_0);
      FileFlag_0_syn1lfpjv X60Qdesugar_1 = IL64(3);
      (*X60Qdesugar_0) = ((NU8)((*X60Qdesugar_0) | ((NU8)(((NU8)IL64(1)) << ((NU)(X60Qdesugar_1 & IL64(7)))))));}
    setLen_0_Ifg83xa1_syn1lfpjv((&(*f_1).d_00.wbuf_0), IL64(0));}}
N_NIMCALL(void, flushStdStreams_0_syn1lfpjv)(void){
  flushImpl_0_syn1lfpjv(stdout_0_syn1lfpjv);
  flushImpl_0_syn1lfpjv(stderr_0_syn1lfpjv);}
static inline NI64 len_3_Irwqcn4_syn1lfpjv(seq_0_I7epg22_syn1lfpjv s_8){
  NI64 result_25;
  result_25 = s_8.len_0;
  return result_25;}
static inline NC8* getQ_7_Iqupddu1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv s_9, NI64 i_1){
  if ((!(i_1 < s_9.len_0))){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 3327929425545015038ull, .more_0 = (&strlit_0_I7655461567997625268_syn1lfpjv)}
    );}
  if ((!(IL64(0) <= i_1))){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 3327929425545015038ull, .more_0 = (&strlit_0_I3542881952749030761_syn1lfpjv)}
    );}
  NC8* result_26;
  result_26 = (&s_9.data_0[i_1]);
  return result_26;}
void setLen_0_Ifg83xa1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv* s_10, NI64 newLen_1){
  NB8 LENGC_OVF_ = NIM_FALSE;
  if (newLen_1 < (*s_10).len_0){
    {
      {
        NI64 i_0h471 = ((NI64)((*s_10).len_0 - IL64(1)));
        {
          while (newLen_1 <= i_0h471){
            {
              {
                (*(&i_0h471)) = ((NI64)((*(&i_0h471)) - ((NI64)IL64(1))));
                returnLabel_0h475: ;}}}}
        whileStmtLabel_0h472: ;
        (*s_10).len_0 = newLen_1;
        returnLabel_0h473: ;}}}
  else {
    NI64 i_2 = (*s_10).len_0;
    {
      {
        NI64 X60QconstRefTemp_0h478;
        if (__builtin_smulll_overflow(newLen_1, sizeof(NC8), (long long int*)(&X60QconstRefTemp_0h478))){
          LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
        NI64 newSize_0h479 = X60QconstRefTemp_0h478;
        if (LENGC_OVF_){
          oomHandler_0_sysvq0asl(((NI64)IL64(9223372036854775807)));
          goto returnLabel_0h482;}
        NI64 X60Qx_0h480;
        {
          {
            if ((!((*s_10).data_0 == NIM_NIL))){
              NI64 X60Qx_0h486 = allocatedSize_0_sysvq0asl(((void*)((void*)(*s_10).data_0)));
              X60Qx_0h480 = X60Qx_0h486;}
            else {
              X60Qx_0h480 = IL64(0);}
            returnLabel_0h487: ;}}
        if (X60Qx_0h480 < newSize_0h479){
          NB8 X60Qx_0h481 = resize_0_Irimnxi1_syn1lfpjv(s_10, ((NI64)(newLen_1 - (*s_10).len_0)));
          if ((!X60Qx_0h481)){
            goto returnLabel_0h482;}}
        (*s_10).len_0 = newLen_1;
        returnLabel_0h482: ;}}
    if ((*s_10).data_0 == NIM_NIL){
      return;}
    {
      while (i_2 < newLen_1){
        (*s_10).data_0[i_2] = (NC8)'\000';
        {
          {
            (*(&i_2)) = ((NI64)((*(&i_2)) + ((NI64)IL64(1))));
            returnLabel_0h489: ;}}}}
    whileStmtLabel_0: ;}}
static inline NI64 memSizeInBytes_0_Iigtmlk1_syn1lfpjv(NI64 size_5){
  NB8 LENGC_OVF_ = NIM_FALSE;
  NI64 result_27;
  NI64 X60QconstRefTemp_0;
  if (__builtin_smulll_overflow(size_5, sizeof(NC8), (long long int*)(&X60QconstRefTemp_0))){
    LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
  result_27 = X60QconstRefTemp_0;
  if (LENGC_OVF_){
    result_27 = ((NI64)IL64(9223372036854775807));}
  return result_27;}
static inline NI64 capInBytes_0_Isccluk1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv s_16){
  NI64 result_28;
  NI64 X60Qx_2;
  if ((!(s_16.data_0 == NIM_NIL))){
    NI64 X60Qx_50 = allocatedSize_0_sysvq0asl(((void*)((void*)s_16.data_0)));
    X60Qx_2 = X60Qx_50;}
  else {
    X60Qx_2 = IL64(0);}
  result_28 = X60Qx_2;
  return result_28;}
NB8 resize_0_Irimnxi1_syn1lfpjv(seq_0_I7epg22_syn1lfpjv* dest_2, NI64 addedElements_1){
  NB8 result_29;
  NI64 X60Qx_51 = capInBytes_0_Isccluk1_syn1lfpjv((*dest_2));
  NI64 oldCap_0 = ((NI64)(X60Qx_51 / sizeof(NC8)));
  NI64 newCap_0 = recalcCap_0_sysvq0asl(oldCap_0, addedElements_1);
  NI64 memSize_1 = memSizeInBytes_0_Iigtmlk1_syn1lfpjv(newCap_0);
  void* X60Qx_52 = realloc_1_sysvq0asl(((void*)((void*)(*dest_2).data_0)), memSize_1);
  (*dest_2).data_0 = ((NC8*)X60Qx_52);
  if ((*dest_2).data_0 == NIM_NIL){
    (*dest_2).len_0 = IL64(0);
    oomHandler_0_sysvq0asl(memSize_1);
    result_29 = NIM_FALSE;}
  else {
    result_29 = NIM_TRUE;}
  return result_29;}
void X60Qini_0_syn1lfpjv(void){
  if (X60QiniGuard_0_syn1lfpjv){
    return;}
  X60QiniGuard_0_syn1lfpjv = NIM_TRUE;
  X60Qini_0_sysvq0asl();
  X60Qini_0_for2ybv4p1();
  stdin_0_syn1lfpjv = newFile_0_syn1lfpjv(((int)IL64(0)), ((NU8)1ull));
  stdout_0_syn1lfpjv = newFile_0_syn1lfpjv(((int)IL64(1)), ((NU8)2ull));
  stderr_0_syn1lfpjv = newFile_0_syn1lfpjv(((int)IL64(2)), ((NU8)18ull));
  setExitFlush_0_sysvq0asl(flushStdStreams_0_syn1lfpjv);}
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
static inline void setExitFlush_0_sysvq0asl(X60Qt_0_ISEAnimcallZAfalseZAR11_sysvq0asl p_0){
  gExitFlush_0_sysvq0asl = p_0;}
