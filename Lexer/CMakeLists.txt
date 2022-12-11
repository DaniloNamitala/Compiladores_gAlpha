# -*- mode:cmake -*-
set(ANTLR_SRC ${PROJECT_SOURCE_DIR}/lib/*.cpp)

foreach(src_file ${ANTLR_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          GENERATED TRUE
          )
endforeach(src_file ${ANTLR_SRC})

add_custom_target(GenerateParser DEPENDS ${ANTLR_SRC})
add_custom_command(OUTPUT ${ANTLR_SRC}
   COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/lib/
   COMMAND "antlr4" -Dlanguage=Cpp -o ${PROJECT_SOURCE_DIR}/lib/ ${PROJECT_SOURCE_DIR}/DeskLang.g4
   WORKING_DIRECTORY "${CMAKE_BINARY_DIR}" DEPENDS ${PROJECT_SOURCE_DIR}/DeskLang.g4
)

include_directories("/usr/include/antlr4-runtime/")

#file(GLOB antlr4-demo_SRC "${PROJECT_SOURCE_DIR}/demo/generated/*")
set(antlr4-demo_SRC 
  ${PROJECT_SOURCE_DIR}/demo/Linux/main.cpp
  ${ANTLR_SRC}
  )

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set (flags_1 "-Wno-overloaded-virtual")
else()
  set (flags_1 "-MP /wd4251")
endif()

foreach(src_file ${antlr4-demo_SRC})
      set_source_files_properties(
          ${src_file}
          PROPERTIES
          COMPILE_FLAGS "${COMPILE_FLAGS} ${flags_1}"
          )
endforeach(src_file ${antlr4-demo_SRC})

add_executable(antlr4-demo
  ${antlr4-demo_SRC}
  )
#add_precompiled_header(antlr4-demo ${PROJECT_SOURCE_DIR}/runtime/src/antlrcpp-Prefix.h)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(antlr4-demo PRIVATE "/MT$<$<CONFIG:Debug>:d>")
endif()

add_dependencies(antlr4-demo GenerateParser)

target_link_libraries(antlr4-demo antlr4_static)

install(TARGETS antlr4-demo 
        DESTINATION "share" 
        COMPONENT dev 
        )
