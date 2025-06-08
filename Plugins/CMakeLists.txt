cmake_minimum_required(VERSION 3.15)
project(Plugins)

# определение директории плагинов основного прилодения, в которую будут копироваться плагины полученные в этом проекте
set(MAINAPP_PLUGIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../out/build/${CMAKE_GENERATOR}/web_service/plugins" CACHE PATH "Directory for web_service app plugins")
file(MAKE_DIRECTORY "${MAINAPP_PLUGIN_DIR}")  # Создаем каталог если не существует

# плагины

add_subdirectory(time)
add_subdirectory(browser)
add_subdirectory(lang)