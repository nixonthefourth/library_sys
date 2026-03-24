//
// Created by Mykyta Khomiakov, 28941190 on 23/03/2026.
//

#ifndef LIBRARY_SYS_DISPLAY_H
#define LIBRARY_SYS_DISPLAY_H

#include <string>

/**
 * @brief Static helper class for all terminal rendering.
 *
 * Owns ANSI colour codes, box-drawing characters, and every print
 * routine used by the REPL. Nothing in here touches library data –
 * it is purely presentational.
 */
class Display {
public:

    // ANSI colour / style escape codes

    static constexpr const char* RESET = "\033[0m";
    static constexpr const char* BOLD = "\033[1m";
    static constexpr const char* DIM = "\033[2m";

    static constexpr const char* WHITE = "\033[97m";
    static constexpr const char* CYAN = "\033[96m";
    static constexpr const char* GREEN = "\033[92m";
    static constexpr const char* YELLOW = "\033[93m";
    static constexpr const char* RED = "\033[91m";
    static constexpr const char* GREY = "\033[90m";

    // Core effects

    /**
     * @brief Prints a string one character at a time, mimicking a typewriter.
     *
     * Direct C++ port of the C# DisplayMessage effect.  Each character is
     * flushed immediately so the terminal shows it before the delay fires.
     *
     * @param text The string to print.
     * @param delayMs Milliseconds between characters (default 18 ms).
     */
    static void typewrite(const std::string& text, int delayMs = 18);

    /**
     * @brief Prints a full line with the typewriter effect, then adds a newline.
     *
     * @param text The string to print.
     * @param delayMs Milliseconds between characters (default 18 ms).
     */
    static void typewriteLine(const std::string& text, int delayMs = 18);

    // Structural chrome

    /**
     * @brief Clears the terminal screen using an ANSI escape sequence.
     */
    static void clearScreen();

    /**
     * @brief Prints a full-width horizontal rule using box-drawing glyphs.
     *
     * @param colour  ANSI code to apply to the rule (defaults to DIM grey).
     */
    static void rule(const char* colour = GREY);

    /**
     * @brief Prints the application splash banner on startup.
     *
     * Uses the typewriter effect so the title animates in character by character.
     */
    static void banner();

    // Menus

    /**
     * @brief Renders the main navigation menu.
     *
     * Each option is printed with its shortcut key highlighted in cyan.
     * Includes all extended feature options (search and activity log).
     */
    static void menu();

    /**
     * @brief Asks the user to choose sort order (ascending / descending)
     *        and sort field (title / author).
     *
     * Prompts are printed inline; reads two single-character choices from
     * stdin and returns them via output parameters.
     *
     * @param outOrder Set to 'a' (ascending) or 'd' (descending).
     * @param outField Set to 't' (title) or 'a' (author).
     */
    static void sortMenu(char& outOrder, char& outField);

    /**
     * @brief Asks whether the user report should be saved to a file.
     *
     * @return true if the user answered yes.
     */
    static bool saveReportPrompt();

    // Prompts & feedback

    /**
     * @brief Prints a styled prompt and reads an integer from stdin.
     *
     * @param label The prompt label shown to the user.
     * @return The integer the user entered.
     */
    static int promptInt(const std::string& label);

    /**
     * @brief Prints a styled prompt and reads a string from stdin.
     *
     * @param label The prompt label shown to the user.
     * @return The string the user entered.
     */
    static std::string promptStr(const std::string& label);

    /**
     * @brief Prints a success message in green.
     *
     * @param text  Message body.
     */
    static void success(const std::string& text);

    /**
     * @brief Prints an error message in red.
     *
     * @param text Message body.
     */
    static void error(const std::string& text);

    /**
     * @brief Prints a section heading in bold cyan, flanked by rules.
     *
     * @param heading The heading text.
     */
    static void heading(const std::string& heading);

    /**
     * @brief Prints a single data row: an ID badge followed by a label.
     *
     * @param id Short identifier string (e.g. "B3").
     * @param label Human-readable label.
     */
    static void row(const std::string& id, const std::string& label);

    /**
     * @brief Prints a loan row: resource title + borrower name on one line.
     *
     * @param resourceTitle Title of the borrowed resource.
     * @param borrowerName Name of the person who borrowed it.
     */
    static void loanRow(const std::string& resourceTitle,
                        const std::string& borrowerName);

    /**
     * @brief Prints a "no results" notice when a report or list is empty.
     *
     * @param context Short description of what was empty (e.g. "loans").
     */
    static void empty(const std::string& context);
};

#endif //LIBRARY_SYS_DISPLAY_H