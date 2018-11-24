cmake_minimum_required(VERSION 3.10)
project(linter)

set(CMAKE_CXX_STANDARD 14)

include_directories(header)

# string helpers
add_library(strings src/strings.c header/strings.h)

# coding norms
add_library(coding_norms header/coding_norms.h src/coding_norms.c tests/tests_strings.c)

# coding rules
add_library(coding_rules header/coding_rules.h src/coding_rules.c)

# rule list
add_library(rule_list header/rule_list.h src/rule_list.c)

# file list
add_library(file_list header/file_list.h src/file_list.c)

# config
add_library(config header/config.h src/config.c)
target_link_libraries(config rule_list file_list)

# error
add_library(error header/error.h src/error.c)

# lconf
add_library(lconf header/lconf.h src/lconf.c)
target_link_libraries(lconf config rule_list file_list)

# rules
add_library(rules header/rules.h src/rules.c)
target_link_libraries(rules coding_norms strings)

# variable rules
add_library(variable_rules header/variable_rules.h src/variable_rules.c)

# variables
add_library(variables header/variables.h src/variables.c)

# file helpers
add_library(file_helpers src/file_helper.c header/file_helper.h)
target_link_libraries(file_helpers strings)


add_executable(linter src/main.c header/struct.h)
target_link_libraries(
        linter
        lconf
        config
        coding_norms
        rules
)

add_executable(tests_strings tests/tests_strings.c)
target_link_libraries(tests_strings strings file_helpers)
