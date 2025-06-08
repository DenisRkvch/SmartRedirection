set(PLUGIN_NAME time)
# Создаем DLL
add_library(${PLUGIN_NAME} SHARED 
    "${PLUGIN_NAME}.cpp" "${PLUGIN_NAME}.h"
)

# Настройки экспорта
target_compile_definitions(${PLUGIN_NAME} PRIVATE PLUGIN_EXPORTS)
target_compile_definitions(${PLUGIN_NAME} PRIVATE CONNECT_IOC_EXPORTS)
target_include_directories(${PLUGIN_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../web_service")

# Подключаем библиотеку ioc
target_link_directories(${PLUGIN_NAME} PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/../../out/build/x64-debug/web_service/core/IoCContainer/IoCCore"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../out/build/x64-debug/web_service/core/IoCContainer"
)
target_link_libraries(${PLUGIN_NAME} PRIVATE IoCCore)
target_link_libraries(${PLUGIN_NAME} PRIVATE IoC)

# Копирование в каталог основного приложения
if(MAINAPP_PLUGIN_DIR)
    add_custom_command(TARGET ${PLUGIN_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${PLUGIN_NAME}>
            ${MAINAPP_PLUGIN_DIR}
        COMMENT "Copying ${PLUGIN_NAME} to web_service app plugins directory"
    )
else()
    message(WARNING "MAINAPP_PLUGIN_DIR is not set")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

