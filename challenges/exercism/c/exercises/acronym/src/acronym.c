#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "acronym.h"

#define strlen_s(s) (s == NULL ? 0 : strlen(s))

static int is_first_character_of_word(const char *phrase, int index)
{
	if (
		index != 0
		&& isalpha(phrase[index])
		&& !isalpha(phrase[index - 1])
		&& phrase[index - 1] != '\''
	)
		return 1;
	else if (index == 0)
		return 1;
	else
		return 0;
}

char *abbreviate(const char *phrase)
{
	char *acronym = NULL;

	long phrase_len = strlen_s(phrase);
	long acronym_len = 1;
	long letters_count = 0;

	for (int i = 0; i < phrase_len; i++) {
		if (is_first_character_of_word(phrase, i)) {
			// Check if reallocation is needed
			if (letters_count == acronym_len - 1) {
				acronym = realloc(acronym, acronym_len * 2);
				acronym_len *= 2;
			}

			acronym[letters_count++] = toupper(phrase[i]);
		}
	}

	return acronym;
}
