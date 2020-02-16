package acronym

import (
	"strings"
	"unicode"
)

// Checks if the input rune is a letter.
func IsLetter(s string, i int) bool {
	cur := rune(s[i])

	if i == 0 { return unicode.IsLetter(cur) }

	prev := rune(s[i - 1])

	return unicode.IsLetter(cur) && !unicode.IsLetter(prev) && prev != '\''
}

// Creates an abbreviation from the input string.
func Abbreviate(s string) string {
	abbr := ""

	for i, r := range s {
		if IsLetter(s, i) {
			abbr += strings.ToUpper(string(r))
		}
	}

	return abbr
}
