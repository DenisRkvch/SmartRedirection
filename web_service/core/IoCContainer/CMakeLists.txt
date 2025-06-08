
add_library(IoC STATIC
    
  "IoCConnectContainerCommand.cpp" "IoCConnectContainerCommand.h"
  "IScope.h"
  "Scope.cpp" "Scope.h"
  "ScopeTree.cpp" "ScopeTree.h"
  "Commands/IoCChangeCurrentScopeCommand.cpp" "Commands/IoCChangeCurrentScopeCommand.h"
  "Commands/IoCRegisterCommand.cpp" "Commands/IoCRegisterCommand.h"
  "Commands/IoCScopeDeleteCommand.cpp" "Commands/IoCScopeDeleteCommand.h"
  "Commands/IoCScopeNewCommand.cpp" "Commands/IoCScopeNewCommand.h"
)

add_subdirectory (IoCCore)

target_link_libraries(IoC PRIVATE
	IoCCore
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

