
add_library(LoggerIoCCore STATIC
    
  "IFunctor.h"
  "IIoCContainer.h"
  "IoC.cpp" "IoC.h"
  "IoCException.cpp" "IoCException.h"
)

target_include_directories(LoggerIoCCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

