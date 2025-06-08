
add_library(IoCCore STATIC
    
  "IFunctor.h"
  "IIoCContainer.h"
  "IoC.cpp" "IoC.h"
  "IoCException.cpp" "IoCException.h"
)

target_include_directories(IoCCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

