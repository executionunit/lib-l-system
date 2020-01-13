#ifndef EXUNIT_LSYSTEMLIB_LSYSTEMCONFIG_H
#define EXUNIT_LSYSTEMLIB_LSYSTEMCONFIG_H

#ifndef XLSYS_ALLOCATOR
#define XLSYS_ALLOCATOR
#endif

#ifndef XLSYS_ARRAY
#include <array>
#define XLSYS_ARRAY std::array
#endif

#ifndef XLSYS_VECTOR
#include <vector>
#define XLSYS_VECTOR std::vector
#endif

#ifndef XLSYS_STRING
#include <string>
#define XLSYS_STRING std::string
#endif

#ifndef XLSYS_UMAP
#include <unordered_map>
#define  XLSYS_UMAP std::unordered_map
#endif

#ifndef XLSYS_REPORT_ERROR
#define XLSYS_REPORT_ERROR(msg) printf("ERROR: %s\n", msg);
#endif

#endif