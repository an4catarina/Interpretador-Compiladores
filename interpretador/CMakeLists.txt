cmake_minimum_required(VERSION 3.31)

project(interpretador VERSION 0.1 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(LEXER_OUT "${BUILD_DIR}/lexer.c")
set(PARSER_OUT "${BUILD_DIR}/parser.c")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

flex_target(LEXER "lexer/lexer.l" "${LEXER_OUT}" DEFINES_FILE "${BUILD_DIR}/lexer.h")
bison_target(PARSER "parser/parser.y" "${PARSER_OUT}" DEFINES_FILE "${BUILD_DIR}/parser.tab.h")

set(LIBRARY
  ast.c
  ast_nodes.c
  ast_rules.c
  error.c
  func.c
  meta.c
  scope.c
  utils.c
  var.c
)

list(TRANSFORM LIBRARY PREPEND lib/)

add_executable(interpretador
  ${LEXER_OUT}
  ${PARSER_OUT}
  ${LIBRARY}
)

target_include_directories(interpretador PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  include
)
