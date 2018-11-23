cmake_minimum_required(VERSION 3.10)
project(linter)

set(CMAKE_CXX_STANDARD 14)

include_directories(header)

add_library(coding_norms header/coding_norms.h src/coding_norms.c)
add_library(coding_rules header/coding_rules.h src/coding_rules.c)
add_library(config header/config.h src/config.c)
add_library(error header/error.h src/error.c)
add_library(file_list header/file_list.h src/file_list.c)
add_library(lconf header/lconf.h src/lconf.c)
add_library(rules header/rules.h src/rules.c)
add_library(rule_list header/rule_list.h src/rule_list.c)
add_library(variable_rules header/variable_rules.h src/variable_rules.c)
add_library(variables header/variables.h src/variables.c)


target_link_libraries(rules coding_norms)

add_executable(linter src/main.c header/struct.h)
target_link_libraries(
        linter
        coding_norms
        coding_rules
        config
        error
        file_list
        lconf
        rules
        rule_list
        variable_rules
        variables
)
