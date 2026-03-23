//
// Created by Mykyta Khomiakov on 23/03/2026.
//

#include "Display.h"
#include <iostream>
#include <chrono>
#include <thread>

// ────────────────────────────────────────────────────────────────────────────
// Core effects
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Prints each character individually with a short sleep between them,
 *        replicating the C# DisplayMessage typewriter effect.
 *
 * std::cout.flush() is called after every character so the terminal renders
 * it immediately rather than buffering the whole string first.
 */
void Display::typewrite(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

/**
 * @brief Wraps typewrite() and appends a newline at the end.
 */
void Display::typewriteLine(const std::string& text, int delayMs) {
    typewrite(text, delayMs);
    std::cout << "\n";
}

// ────────────────────────────────────────────────────────────────────────────
// Structural chrome
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Sends the ANSI "erase screen / move cursor home" sequence.
 */
void Display::clearScreen() {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

/**
 * @brief Prints a 56-character horizontal rule in the supplied colour,
 *        then resets formatting.
 */
void Display::rule(const char* colour) {
    std::cout << colour
              << "────────────────────────────────────────────────────────"
              << RESET << "\n";
}

/**
 * @brief Animates the application banner on startup.
 *
 * The title types in at full speed; the subtitle uses a slightly slower
 * delay so the two lines feel distinct.
 */
void Display::banner() {
    clearScreen();
    std::cout << "\n";
    rule(CYAN);
    std::cout << BOLD << CYAN;
    typewriteLine("  UNIVERSITY LIBRARY MANAGEMENT SYSTEM", 22);
    std::cout << RESET << DIM;
    typewriteLine("  Resource & Loan Tracking  //  v1.0", 12);
    std::cout << RESET;
    rule(CYAN);
    std::cout << "\n";
}

// ────────────────────────────────────────────────────────────────────────────
// Menu
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Renders the six-option main menu.
 *
 * Shortcut digits are printed in bold cyan to draw the eye; option labels
 * are plain white so the layout stays readable without being loud.
 */
void Display::menu() {
    std::cout << "\n";
    rule();
    std::cout << BOLD << WHITE << "  MENU\n" << RESET;
    rule();

    // Each option: coloured key  plain label
    std::cout << "  " << BOLD << CYAN  << "1" << RESET << WHITE << "  Borrow a resource\n"   << RESET;
    std::cout << "  " << BOLD << CYAN  << "2" << RESET << WHITE << "  Return a resource\n"   << RESET;
    std::cout << "  " << BOLD << CYAN  << "3" << RESET << WHITE << "  List available\n"       << RESET;
    std::cout << "  " << BOLD << CYAN  << "4" << RESET << WHITE << "  Loan report\n"          << RESET;
    std::cout << "  " << BOLD << CYAN  << "5" << RESET << WHITE << "  User report\n"          << RESET;
    std::cout << "  " << BOLD << RED   << "0" << RESET << WHITE << "  Exit\n"                 << RESET;

    rule();
}

// ────────────────────────────────────────────────────────────────────────────
// Prompts & feedback
// ────────────────────────────────────────────────────────────────────────────

/**
 * @brief Displays a right-pointing arrow prompt in yellow, then reads an int.
 *
 * @param label  The field name shown next to the arrow.
 */
int Display::promptInt(const std::string& label) {
    int value;
    std::cout << YELLOW << "  > " << WHITE << label << " : " << RESET;
    std::cin  >> value;
    return value;
}

/**
 * @brief Displays a right-pointing arrow prompt in yellow, then reads a string.
 *
 * @param label  The field name shown next to the arrow.
 */
std::string Display::promptStr(const std::string& label) {
    std::string value;
    std::cout << YELLOW << "  > " << WHITE << label << " : " << RESET;
    std::cin  >> value;
    return value;
}

/**
 * @brief Prints a green checkmark followed by the message text.
 */
void Display::success(const std::string& text) {
    std::cout << "\n  " << GREEN << "✓  " << RESET << WHITE << text << RESET << "\n";
}

/**
 * @brief Prints a red cross followed by the message text.
 */
void Display::error(const std::string& text) {
    std::cout << "\n  " << RED << "✗  " << RESET << WHITE << text << RESET << "\n";
}

/**
 * @brief Prints the section heading in bold cyan, flanked by rules,
 *        so each report has a clear visual boundary.
 */
void Display::heading(const std::string& heading) {
    std::cout << "\n";
    rule();
    std::cout << "  " << BOLD << CYAN << heading << RESET << "\n";
    rule();
}

/**
 * @brief Prints one data row: the ID is rendered as a small grey badge on
 *        the left and the label follows in plain white.
 */
void Display::row(const std::string& id, const std::string& label) {
    std::cout << "  " << DIM << GREY << "[" << id << "]" << RESET
              << "  " << WHITE << label << RESET << "\n";
}

/**
 * @brief Prints a loan row with the resource title on the left and the
 *        borrower name dimmed on the right, separated by an arrow.
 */
void Display::loanRow(const std::string& resourceTitle,
                      const std::string& borrowerName) {
    std::cout << "  " << WHITE << resourceTitle << RESET
              << GREY << DIM << "  →  " << RESET
              << CYAN << borrowerName << RESET << "\n";
}

/**
 * @brief Shows a dimmed italics-style notice when a list or report has no rows.
 */
void Display::empty(const std::string& context) {
    std::cout << "\n  " << DIM << GREY << "(no " << context << " to display)" << RESET << "\n";
}