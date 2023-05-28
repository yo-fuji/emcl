#ifndef EMCL__VISIBILITY_CONTROL_H_
#define EMCL__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define EMCL_EXPORT __attribute__((dllexport))
#define EMCL_IMPORT __attribute__((dllimport))
#else
#define EMCL_EXPORT __declspec(dllexport)
#define EMCL_IMPORT __declspec(dllimport)
#endif
#ifdef EMCL_BUILDING_LIBRARY
#define EMCL_PUBLIC EMCL_EXPORT
#else
#define EMCL_PUBLIC EMCL_IMPORT
#endif
#define EMCL_PUBLIC_TYPE EMCL_PUBLIC
#define EMCL_LOCAL
#else
#define EMCL_EXPORT __attribute__((visibility("default")))
#define EMCL_IMPORT
#if __GNUC__ >= 4
#define EMCL_PUBLIC __attribute__((visibility("default")))
#define EMCL_LOCAL __attribute__((visibility("hidden")))
#else
#define EMCL_PUBLIC
#define EMCL_LOCAL
#endif
#define EMCL_PUBLIC_TYPE
#endif

#endif // EMCL__VISIBILITY_CONTROL_H_
