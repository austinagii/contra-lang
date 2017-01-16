//
// Created by austindevx on 1/6/17.
//

#ifndef CONTRA_LANG_WORDTOKEN_H
#define CONTRA_LANG_WORDTOKEN_H

#include <ctype.h>
#include <vector>
#include <string>
#include <iostream>
#include "Token.h"

namespace frontend {
  /**
   * A token whose string representation begins with either a letter or an underscore and followed by an unlimited sequence
   * of lowercase & uppercase digits, underscores or digits. By these rules this class should encompass both Keywords and
   * identifiers.
   */
  class WordToken : public Token {
  public:
    /**
     * @Constructor
     *
     * @param source The source from which the token was extracted
     */
    explicit WordToken(frontend::Source* source) : Token { source } {
      extract();
    };

    /**
     * Extract a valid word token from the source
     */
    void extract();

    /**
     * Return whether the character is a valid character for a word token.
     *
     * @param   c       The character to be checked
     * @return  bool    Whether the character is a valid token
     *
     */
    static bool isValidWordCharacter(char c);
  };

  void WordToken::extract() {
    std::string text;
    char current = getCurrentCharacter();

    while(isValidWordCharacter(current)) {
      text.push_back(current);
      current = getNextCharacter();
    }

    this->text = text;

    try {
      type = KEYWORDS.at(text);
    } catch (std::out_of_range) {
      type = IDENTIFIER;
    }
  }

  bool WordToken::isValidWordCharacter(char c) {
    return (isalnum(c) || c == '_');
  }
}


#endif //CONTRA_LANG_WORDTOKEN_H
