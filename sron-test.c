#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sron_headers/_cli_colors_.hpp"

const char*const GOOD_TESTCASE[][2] = {
    { "add_assign.sron"           ,"sronc add_assign.sron" },
    { "Armstrong_num.sron"        ,"sronc Armstrong_num.sron"},
    { "break_.sron"               ,"sronc break_.sron"},
    { "calculator.sron"           ,"sronc calculator.sron"},
    { "cmd_line_args.sron"        ,"sronc cmd_line_args.sron"},
    { "color_print.sron"          ,"sronc color_print.sron"},
    { "console_.sron"             ,"sronc console_.sron"},
    { "continue_.sron"            ,"sronc continue_.sron"},
    { "deadcode_break.sron"       ,"sronc deadcode_break.sron"},
    { "deadcode.sron"             ,"sronc deadcode.sron"},
    { "exit_.sron"                ,"sronc exit_.sron"},
    { "factorial_recursion.sron"  ,"sronc factorial_recursion.sron"},
    { "factorial.sron"            ,"sronc factorial.sron"},
    { "File_cur_pos.sron"         ,"sronc File_cur_pos.sron"},
    { "FileAppender.sron"         ,"sronc FileAppender.sron"},
    { "FileReader.sron"           ,"sronc FileReader.sron"},
    { "FileWriter.sron"           ,"sronc FileWriter.sron"},
    { "for_.sron"                 ,"sronc for_.sron"},
    { "for_speed.sron"            ,"sronc for_speed.sron"},
    { "Foreach_literalstr.sron"   ,"sronc Foreach_literalstr.sron"},
    { "foreach_speed.sron"        ,"sronc foreach_speed.sron"},
    { "hello.sron"                ,"sronc hello.sron"},
    { "if_.sron"                  ,"sronc if_.sron"},
    { "list_insert.sron"          ,"sronc list_insert.sron"},
    { "list_sort.sron"            ,"sronc list_sort.sron"},
    { "LiteralStr.sron"           ,"sronc LiteralStr.sron"},
    { "math_.sron"                ,"sronc math_.sron"},
    { "max_min_int.sron"          ,"sronc max_min_int.sron"},
    { "negative.sron"             ,"sronc negative.sron"},
    { "num.sron"                  ,"sronc num.sron"},
    { "obuffer.sron"              ,"sronc obuffer.sron"},
    { "odd_even.sron"             ,"sronc odd_even.sron"},
    { "os_.sron"                  ,"sronc os_.sron"},
    { "ownership_.sron"           ,"sronc ownership_.sron"},
    { "pass_file.sron"            ,"sronc pass_file.sron"},
    { "pi.sron"                   ,"sronc pi.sron"},
    { "print_only_even.sron"      ,"sronc print_only_even.sron"},
    { "reassign.sron"             ,"sronc reassign.sron"},
    { "return_.sron"              ,"sronc return_.sron"},
    { "rev_loop.sron"             ,"sronc rev_loop.sron"},
    { "rotate.sron"               ,"sronc rotate.sron"},
    { "sizeof.sron"               ,"sronc sizeof.sron"},
    { "sleep.sron"                ,"sronc sleep.sron"},
    { "speed.sron"                ,"sronc speed.sron"},

    { "sron_cmd_gc_stack_size.sron"             , "sronc sron_cmd_gc_stack_size.sron"},
    { "sron_cmd_is_bytecode_cached.sron"        , "sronc sron_cmd_is_bytecode_cached.sron"},
    { "sron_cmd_is_file_avail.sron"             , "sronc sron_cmd_is_file_avail.sron"},
    { "sron_cmd_no_of_bytecode_cached.sron"     , "sronc sron_cmd_no_of_bytecode_cached.sron"},
    { "sron_cmd_obuffer_clear.sron"             , "sronc sron_cmd_obuffer_clear.sron"},
    { "sron_cmd_obuffer_size.sron"              , "sronc sron_cmd_obuffer_size.sron"},
    
    { "strict_compare.sron"       ,"sronc strict_compare.sron"},
    { "string_.sron"              ,"sronc string_.sron"},
    { "string_to_list.sron"       ,"sronc string_to_list.sron"},
    { "system_cmd.sron"           ,"sronc system_cmd.sron"},
    { "type__.sron"               ,"sronc type__.sron"},
    { "type_attribute.sron"       ,"sronc type_attribute.sron"},
    { "type.sron"                 ,"sronc type.sron"},
    { "unicode_test.sron"         ,"sronc unicode_test.sron"},
    { "variable_.sron"            ,"sronc variable_.sron"},
    { "version.sron"              ,"sronc version.sron"},
    { "while_.sron"               ,"sronc while_.sron"},
    { "while_speed.sron"          ,"sronc while_speed.sron"}
};

const char*const ERROR_TESTCASE[][2] = {
    { "args_.sron"                ,"sronc args_.sron" },
    { "bitwise.sron"              ,"sronc bitwise.sron" },
    { "calc_assign.sron"          ,"sronc calc_assign.sron"},
    { "case1.sron"                ,"sronc case1.sron"},
    { "case2.sron"                ,"sronc case2.sron"},
    { "case3.sron"                ,"sronc case3.sron"},
    { "case4.sron"                ,"sronc case4.sron"},
    { "case5.sron"                ,"sronc case5.sron"},
    { "division_by_zero.sron"     ,"sronc division_by_zero.sron"},
    { "empty_fnc.sron"            ,"sronc empty_fnc.sron"},
    { "excep.sron"                ,"sronc excep.sron"},
    { "fnc_not_exist.sron"        ,"sronc fnc_not_exist.sron"},
    { "Foreach_invalid.sron"      ,"sronc Foreach_invalid.sron"},
    { "function_not_found.sron"   ,"sronc function_not_found.sron"},
    { "invalid-attribute.sron"    ,"sronc invalid-attribute.sron"},
    { "invalid-math.sron"         ,"sronc invalid-math.sron"},
    { "number_overflow.sron"      ,"sronc number_overflow.sron"},
    { "os_attribute.sron"         ,"sronc os_attribute.sron"},
    { "scope_error.sron"          ,"sronc scope_error.sron"},
    { "variable_scope.sron"       ,"sronc variable_scope.sron"}
};

#define ArLen(x)   (sizeof(x)/sizeof(x[0]))
#define CLEAR_INPUT_BUFFER while ((getchar()) != '\n')

// returns true if file cannot be printed otherwise false
inline static bool printFile(const char*const restrict __filename)
{
    FILE* file = fopen(__filename, "r");

    if(file)
    {
        int ch;

        while( (ch = fgetc(file)) != EOF ) putchar(ch);

        fclose(file);
    }
    else
    {
        printf( CLI_DESIGN_BOLD CLI_COLOR_RED "\n | Cannot load the file '%s'" CLI_DESIGN_RESET, __filename);

        return true;
    }

    return false;
}

inline static clock_t getCurTime()
{
    return clock();
}

// returns in milliseconds
inline static unsigned long long getExecTime(const clock_t __finish_time, const clock_t __start_time)
{
    return ((double)(__finish_time - __start_time)/(double)(CLOCKS_PER_SEC)) * 1000;
}

inline static void executeTestcase(const char*const __arr[][2], const unsigned len)
{
    char ch;

    for(unsigned i = 0 ; i < len; ++i)
    {
        if ( printFile(__arr[i][0]) ) break;

        getchar();
        CLEAR_INPUT_BUFFER;

        clock_t start_time = getCurTime();

        int compiler_rc = system(__arr[i][1]);

        if( compiler_rc )
        {
            printf( CLI_COLOR_BRIGHT_CYAN "\n---+++++==++ Report for '%s' ++==+++++---\n"
                                   "|| Compiler:\n\t - Return Code: %d\n\t - Time taken: %llu ms\n" CLI_DESIGN_RESET,
                                   __arr[i][0], compiler_rc, getExecTime(getCurTime(), start_time) - start_time);
        }
        else 
        {
            auto interpreter_start_time = getCurTime();
            auto compile_time = getExecTime(interpreter_start_time, start_time);

            int interpreter_rc = system("sron");

            printf( CLI_COLOR_BRIGHT_CYAN  "\n---+++++==++ Report for '%s' ++==+++++---\n"
                                      "|| Compiler:\n\t - Return Code: %d\n\t - Time taken: %llu ms\n"
                                      "|| Interpreter:\n\t - Return Code: %d\n\t - Time taken: %llu ms\n" CLI_DESIGN_RESET
                  , __arr[i][0], compiler_rc, compile_time, interpreter_rc, getExecTime(getCurTime(), interpreter_start_time));
        }

        printf("\n Shall we continue(Y/R/N) :_");
        ch = getchar();

        // continuing
        if(ch == 'Y' || ch == 'y') { }

        // repeat
        else if(ch == 'R' || ch == 'r') --i;

        // stopping testcase analysis
        else break;

        CLEAR_INPUT_BUFFER;
    }
}

int main(void)
{
    char choice;

    printf("\n ==> Enter 0 for Error-testcases else for Good-testcases :- ");
    scanf("%c", &choice);
    CLEAR_INPUT_BUFFER;

    if(choice == '0') executeTestcase(ERROR_TESTCASE, ArLen(ERROR_TESTCASE));

    else executeTestcase(GOOD_TESTCASE, ArLen(GOOD_TESTCASE));
    
    return 0;
}

#pragma clang diagnostic pop