# Определение версии Windows API
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)  # Windows 10
    # Другие варианты:
    # 0x0601 - Windows 7
    # 0x0602 - Windows 8
    # 0x0A00 - Windows 10
endif()
find_package(Boost REQUIRED COMPONENTS beast)


add_subdirectory(core/IoCContainer)

add_executable(WebService 
    "main.cpp" 

    "core/ICommand.h"
    "core/ICondition.h" 
    "core/IPlugin.h" 
    "core/UsingPluginsDecorator.h" "core/UsingPluginsDecorator.cpp" 
    "core/UsingThreadScopeDecorator.h" "core/UsingThreadScopeDecorator.cpp"
    "core/Exceptions/ConditionException.h" "core/Exceptions/ConditionException.cpp"
    "core/Exceptions/CommandException.h" "core/Exceptions/CommandException.cpp"
    "core/Exceptions/PluginException.h" "core/Exceptions/CommandException.cpp"
    "core/Commands/InitIoCContainerCommand.h" "core/Commands/InitIoCContainerCommand.cpp" 
    "core/Commands/RegisterConditionsCommand.h" "core/Commands/RegisterConditionsCommand.cpp" 
    "core/Commands/RegisterRuleEngineCommand.h" "core/Commands/RegisterRuleEngineCommand.cpp"
    "core/Conditions/PathNameEqCondition.h" "core/Conditions/PathNameEqCondition.cpp"

    "http/HttpServer.h" "http/HttpServer.cpp" 
    "http/IRequestHandler.h" 
    "http/RedirectorRequestHandler.h" "http/RedirectorRequestHandler.cpp" 
 
    "plugins/connect_ioc_api_dll.h" 
    "plugins/plugin_api_dll.h"
    "plugins/IPluginManager.h" 
    "plugins/IoCPluginManager.cpp" "plugins/IoCPluginManager.h"   

    "rules_engine/IRuleEngine.h"
    "rules_engine/IRuleProvider.h" 
    "rules_engine/RuleAstBuilder.h" "rules_engine/RuleAstBuilder.cpp" 
    "rules_engine/RuleInterpreter.h" "rules_engine/RuleInterpreter.cpp" 

    "rules_engine/RuleExpressions/IRuleExpression.h"
    "rules_engine/RuleExpressions/SingleRule.h" "rules_engine/RuleExpressions/SingleRule.cpp"
    "rules_engine/RuleExpressions/RuleCondition.h" "rules_engine/RuleExpressions/RuleCondition.cpp"
    "rules_engine/RuleExpressions/RuleInterpreterException.h" "rules_engine/RuleExpressions/RuleInterpreterException.cpp"  
    "rules_engine/RuleExpressions/CheckFailException.h" "rules_engine/RuleExpressions/CheckFailException.cpp"
    "rules_engine/RuleExpressions/RuleSet.h" "rules_engine/RuleExpressions/RuleSet.cpp"
    "rules_engine/RuleExpressions/StringTarget.h" "rules_engine/RuleExpressions/StringTarget.cpp"
    "rules_engine/RuleExpressions/NestedTarget.h" "rules_engine/RuleExpressions/NestedTarget.cpp"

    "utils/IJsonProvider.h" 
    "utils/JsonFileLoader.h" "utils/JsonFileLoader.cpp"
      "core/Commands/RegisterLoggerCommand.h" "core/Commands/RegisterLoggerCommand.cpp")

target_include_directories(WebService PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json.hpp)

add_subdirectory(logger)

target_link_libraries(WebService
    PRIVATE 
        Boost::beast
        IoC
        Logger

)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/rules_config.json
    ${CMAKE_CURRENT_BINARY_DIR}/rules_config.json
    COPYONLY
)

# Настройка стандарта C++
set_target_properties(WebService PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)