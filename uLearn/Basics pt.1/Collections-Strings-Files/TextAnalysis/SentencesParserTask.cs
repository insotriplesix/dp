using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace TextAnalysis
{
    static class SentencesParserTask
    {
        public static readonly string[] StopWords =
        {
            "the", "and", "to", "a", "of", "in", "on", "at", "that",
            "as", "but", "with", "out", "for", "up", "one", "from", "into"
        };

        public static readonly char[] EndOfSentenceChars =
        {
            '.', '!', '?', ';', ':', '(', ')'
        };

        public static List<List<string>> ParseSentences(string text)
        {
            var resultText = new List<List<string>>();
            var sentence = new List<string>();
            var word = new StringBuilder();

            foreach (var c in text)
            {
                if (CharIsLetterOrApostrophe(c))
                {
                    AddCharToWord(c, word);
                }
                else if (((CharIsWordsSeparator(c) && !CharIsEndOfSentence(c)) ||
                    CharIsEndOfSentence(c)) && WordIsNotEmpty(word))
                {
                    if (WordIsNotStopWord(word))
                        AddWordToSentence(word, sentence);
                    word.Clear();
                }

                if (CharIsEndOfSentence(c) && SentenceIsNotEmpty(sentence))
                {
                    AddSentenceToText(sentence, resultText);
                    sentence.Clear();
                }
            }

            if (WordIsNotEmpty(word))
                if (WordIsNotStopWord(word))
                    AddWordToSentence(word, sentence);

            if (SentenceIsNotEmpty(sentence))
                AddSentenceToText(sentence, resultText);

            return resultText;
        }

        public static bool CharIsLetterOrApostrophe(char c)
        {
            return (char.IsLetter(c) || c == '\'');
        }

        public static void AddCharToWord(char c, StringBuilder word)
        {
            word.Append(char.ToLower(c));
        }

        public static bool CharIsWordsSeparator(char c)
        {
            return (char.IsPunctuation(c) || char.IsWhiteSpace(c) || char.IsControl(c) ||
                char.IsSymbol(c) || char.IsDigit(c));
        }

        public static bool CharIsEndOfSentence(char c)
        {
            return EndOfSentenceChars.Contains(c);
        }

        public static bool WordIsNotEmpty(StringBuilder word)
        {
            return word.Length > 0;
        }

        public static bool WordIsNotStopWord(StringBuilder word)
        {
            return !StopWords.Contains(word.ToString());
        }

        public static void AddWordToSentence(StringBuilder word, List<string> sentence)
        {
            sentence.Add(word.ToString());
        }

        public static bool SentenceIsNotEmpty(List<string> sentence)
        {
            return sentence.Count > 0;
        }

        public static void AddSentenceToText(List<string> sentence, List<List<string>> text)
        {
            text.Add(new List<string>(sentence));
        }
    }
}
