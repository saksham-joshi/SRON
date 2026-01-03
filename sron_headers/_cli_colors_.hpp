#ifndef _CLI_COLORS_H
#define _CLI_COLORS_H

// ============================================
// Base Macro
// ============================================
#define DECLARE_TERMINAL_DESIGN(__value) "\033[" #__value "m"

// ============================================
// Text Styles
// ============================================
#define CLI_DESIGN_RESET DECLARE_TERMINAL_DESIGN(0)
#define CLI_DESIGN_BOLD DECLARE_TERMINAL_DESIGN(1)
#define CLI_DESIGN_DIM DECLARE_TERMINAL_DESIGN(2)
#define CLI_DESIGN_ITALIC DECLARE_TERMINAL_DESIGN(3)
#define CLI_DESIGN_UNDERLINE DECLARE_TERMINAL_DESIGN(4)
#define CLI_DESIGN_BLINK DECLARE_TERMINAL_DESIGN(5)
#define CLI_DESIGN_BLINK_FAST DECLARE_TERMINAL_DESIGN(6)
#define CLI_DESIGN_REVERSE DECLARE_TERMINAL_DESIGN(7)
#define CLI_DESIGN_HIDDEN DECLARE_TERMINAL_DESIGN(8)
#define CLI_DESIGN_STRIKE DECLARE_TERMINAL_DESIGN(9)

// Reset specific styles
#define CLI_DESIGN_RESET_BOLD DECLARE_TERMINAL_DESIGN(22)
#define CLI_DESIGN_RESET_ITALIC DECLARE_TERMINAL_DESIGN(23)
#define CLI_DESIGN_RESET_UNDERLINE DECLARE_TERMINAL_DESIGN(24)

// ============================================
// Standard Foreground Colors (30-37)
// ============================================
#define CLI_COLOR_BLACK DECLARE_TERMINAL_DESIGN(30)
#define CLI_COLOR_RED DECLARE_TERMINAL_DESIGN(31)
#define CLI_COLOR_GREEN DECLARE_TERMINAL_DESIGN(32)
#define CLI_COLOR_YELLOW DECLARE_TERMINAL_DESIGN(33)
#define CLI_COLOR_BLUE DECLARE_TERMINAL_DESIGN(34)
#define CLI_COLOR_MAGENTA DECLARE_TERMINAL_DESIGN(35)
#define CLI_COLOR_CYAN DECLARE_TERMINAL_DESIGN(36)
#define CLI_COLOR_WHITE DECLARE_TERMINAL_DESIGN(37)

// Default foreground
#define CLI_COLOR_DEFAULT DECLARE_TERMINAL_DESIGN(39)

// ============================================
// Standard Background Colors (40-47)
// ============================================
#define CLI_DESIGN_BG_BLACK DECLARE_TERMINAL_DESIGN(40)
#define CLI_DESIGN_BG_RED DECLARE_TERMINAL_DESIGN(41)
#define CLI_DESIGN_BG_GREEN DECLARE_TERMINAL_DESIGN(42)
#define CLI_DESIGN_BG_YELLOW DECLARE_TERMINAL_DESIGN(43)
#define CLI_DESIGN_BG_BLUE DECLARE_TERMINAL_DESIGN(44)
#define CLI_DESIGN_BG_MAGENTA DECLARE_TERMINAL_DESIGN(45)
#define CLI_DESIGN_BG_CYAN DECLARE_TERMINAL_DESIGN(46)
#define CLI_DESIGN_BG_WHITE DECLARE_TERMINAL_DESIGN(47)

// Default background
#define CLI_DESIGN_BG_DEFAULT DECLARE_TERMINAL_DESIGN(49)

// ============================================
// Bright Foreground Colors (90-97)
// ============================================
#define CLI_COLOR_BRIGHT_BLACK DECLARE_TERMINAL_DESIGN(90)
#define CLI_COLOR_BRIGHT_RED DECLARE_TERMINAL_DESIGN(91)
#define CLI_COLOR_BRIGHT_GREEN DECLARE_TERMINAL_DESIGN(92)
#define CLI_COLOR_BRIGHT_YELLOW DECLARE_TERMINAL_DESIGN(93)
#define CLI_COLOR_BRIGHT_BLUE DECLARE_TERMINAL_DESIGN(94)
#define CLI_COLOR_BRIGHT_MAGENTA DECLARE_TERMINAL_DESIGN(95)
#define CLI_COLOR_BRIGHT_CYAN DECLARE_TERMINAL_DESIGN(96)
#define CLI_COLOR_BRIGHT_WHITE DECLARE_TERMINAL_DESIGN(97)

// ============================================
// Bright Background Colors (100-107)
// ============================================
#define CLI_DESIGN_BG_BRIGHT_BLACK DECLARE_TERMINAL_DESIGN(100)
#define CLI_DESIGN_BG_BRIGHT_RED DECLARE_TERMINAL_DESIGN(101)
#define CLI_DESIGN_BG_BRIGHT_GREEN DECLARE_TERMINAL_DESIGN(102)
#define CLI_DESIGN_BG_BRIGHT_YELLOW DECLARE_TERMINAL_DESIGN(103)
#define CLI_DESIGN_BG_BRIGHT_BLUE DECLARE_TERMINAL_DESIGN(104)
#define CLI_DESIGN_BG_BRIGHT_MAGENTA DECLARE_TERMINAL_DESIGN(105)
#define CLI_DESIGN_BG_BRIGHT_CYAN DECLARE_TERMINAL_DESIGN(106)
#define CLI_DESIGN_BG_BRIGHT_WHITE DECLARE_TERMINAL_DESIGN(107)

// ============================================
// 256 Color Support (0-255)
// ============================================
// Foreground: ESC[38;5;<n>m
// Background: ESC[48;5;<n>m
#define CLI_COLOR_256(__num) "\033[38;5;" #__num "m"
#define CLI_BG_256(__num) "\033[48;5;" #__num "m"

// ============================================
// True Color / RGB Support (16M colors)
// ============================================
// Foreground: ESC[38;2;<r>;<g>;<b>m
// Background: ESC[48;2;<r>;<g>;<b>m
#define CLI_COLOR_RGB(__r, __g, __b) "\033[38;2;" #__r ";" #__g ";" #__b "m"
#define CLI_BG_RGB(__r, __g, __b) "\033[48;2;" #__r ";" #__g ";" #__b "m"

// ============================================
// Utility Macros
// ============================================
#define COLOR_TEXT(__color, __text) __color __text CLI_DESIGN_RESET

// Combine multiple styles
#define COMBINE_STYLES(__style1, __style2) __style1 __style2

// ============================================
// Common Color Combinations (Convenience)
// ============================================
#define CLI_SUCCESS (CLI_DESIGN_BOLD CLI_COLOR_BRIGHT_GREEN)
#define CLI_ERROR (CLI_DESIGN_BOLD CLI_COLOR_BRIGHT_RED)
#define CLI_WARNING (CLI_DESIGN_BOLD CLI_COLOR_BRIGHT_YELLOW)
#define CLI_INFO (CLI_DESIGN_BOLD CLI_COLOR_BRIGHT_CYAN)
#define CLI_DEBUG (CLI_DESIGN_DIM CLI_COLOR_WHITE)

// ============================================
// C++ Namespace Wrapper
// ============================================
#ifdef __cplusplus

namespace CliColors
{
    #define CREATE_CLI_COLOR(__name) constexpr const char* const __name = CLI_COLOR_##__name
    #define CREATE_CLI_DESIGN(__design) constexpr const char* const __design = CLI_DESIGN_##__design

    // Text styles
    CREATE_CLI_DESIGN(RESET);
    CREATE_CLI_DESIGN(BOLD);
    CREATE_CLI_DESIGN(DIM);
    CREATE_CLI_DESIGN(ITALIC);
    CREATE_CLI_DESIGN(UNDERLINE);
    CREATE_CLI_DESIGN(BLINK);
    CREATE_CLI_DESIGN(REVERSE);
    CREATE_CLI_DESIGN(STRIKE);

    // Standard colors
    CREATE_CLI_COLOR(BLACK);
    CREATE_CLI_COLOR(RED);
    CREATE_CLI_COLOR(GREEN);
    CREATE_CLI_COLOR(YELLOW);
    CREATE_CLI_COLOR(BLUE);
    CREATE_CLI_COLOR(MAGENTA);
    CREATE_CLI_COLOR(CYAN);
    CREATE_CLI_COLOR(WHITE);

    // Standard backgrounds
    CREATE_CLI_DESIGN(BG_BLACK);
    CREATE_CLI_DESIGN(BG_RED);
    CREATE_CLI_DESIGN(BG_GREEN);
    CREATE_CLI_DESIGN(BG_YELLOW);
    CREATE_CLI_DESIGN(BG_BLUE);
    CREATE_CLI_DESIGN(BG_MAGENTA);
    CREATE_CLI_DESIGN(BG_CYAN);
    CREATE_CLI_DESIGN(BG_WHITE);

    // Bright colors
    CREATE_CLI_COLOR(BRIGHT_BLACK);
    CREATE_CLI_COLOR(BRIGHT_RED);
    CREATE_CLI_COLOR(BRIGHT_GREEN);
    CREATE_CLI_COLOR(BRIGHT_YELLOW);
    CREATE_CLI_COLOR(BRIGHT_BLUE);
    CREATE_CLI_COLOR(BRIGHT_MAGENTA);
    CREATE_CLI_COLOR(BRIGHT_CYAN);
    CREATE_CLI_COLOR(BRIGHT_WHITE);

    // Bright backgrounds
    CREATE_CLI_DESIGN(BG_BRIGHT_BLACK);
    CREATE_CLI_DESIGN(BG_BRIGHT_RED);
    CREATE_CLI_DESIGN(BG_BRIGHT_GREEN);
    CREATE_CLI_DESIGN(BG_BRIGHT_YELLOW);
    CREATE_CLI_DESIGN(BG_BRIGHT_BLUE);
    CREATE_CLI_DESIGN(BG_BRIGHT_MAGENTA);
    CREATE_CLI_DESIGN(BG_BRIGHT_CYAN);
    CREATE_CLI_DESIGN(BG_BRIGHT_WHITE);

    // Convenience combinations
    constexpr const char* const SUCCESS_TEXT = CLI_SUCCESS;
    constexpr const char* const ERROR_TEXT = CLI_ERROR;
    constexpr const char* const WARNING_TEXT = CLI_WARNING;
    constexpr const char* const INFO_TEXT = CLI_INFO;
    constexpr const char* const DEBUG_TEXT = CLI_DEBUG;
}

#endif // __cplusplus

#endif // _CLI_COLORS_H