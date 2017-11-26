using System.Collections.Generic;

namespace TextAnalysis
{
    static class FrequencyAnalysisTask
    {
        public static Dictionary<string, string> GetMostFrequentNextWords(List<List<string>> text)
        {
            var mostFrequentBigrams = new Dictionary<string, string>();
            var rawBigrams = GetRawBigrams(text);

            foreach (var word in rawBigrams)
            {
                var mostFrequentNextWord = GetMostFrequentNextWord(word.Value);
                mostFrequentBigrams.Add(word.Key, mostFrequentNextWord);
            }

            return mostFrequentBigrams;
        }

        public static Dictionary<string, Dictionary<string, int>> GetRawBigrams(List<List<string>> text)
        {
            var bigrams = new Dictionary<string, Dictionary<string, int>>();

            foreach (var sentence in text)
            {
                for (var i = 0; i < sentence.Count - 1; i++)
                {
                    var word = sentence[i];
                    var nextWord = sentence[i + 1];

                    if (!bigrams.ContainsKey(word))
                        bigrams.Add(word, new Dictionary<string, int>());

                    if (!bigrams[word].ContainsKey(nextWord))
                        bigrams[word].Add(nextWord, 1);
                    else
                        bigrams[word][nextWord] += 1;
                }
            }

            return bigrams;
        }

        public static string GetMostFrequentNextWord(Dictionary<string, int> dictionary)
        {
            var maxNextWordFreq = int.MinValue;
            var mostFrequentNextWord = "";

            foreach (var nextWord in dictionary)
            {
                var nextWordFreq = nextWord.Value;

                if (maxNextWordFreq < nextWordFreq)
                {
                    maxNextWordFreq = nextWordFreq;
                    mostFrequentNextWord = nextWord.Key;
                }
                else if (maxNextWordFreq == nextWordFreq)
                    mostFrequentNextWord = GetLexicographicallyFirstWord(mostFrequentNextWord,
                                                                         nextWord.Key);
            }

            return mostFrequentNextWord;
        }

        public static Dictionary<string, string> GetMostFrequentTrigrams(List<List<string>> text)
        {
            var mostFrequentTrigrams = new Dictionary<string, string>();
            var rawTrigrams = GetRawTrigrams(text);

            foreach (var word in rawTrigrams)
            {
                var mostFrequentNextWord = GetMostFrequentNextWord(word.Value);
                mostFrequentTrigrams.Add(word.Key, mostFrequentNextWord);
            }

            return mostFrequentTrigrams;
        }

        public static Dictionary<string, Dictionary<string, int>> GetRawTrigrams(List<List<string>> text)
        {
            var trigrams = new Dictionary<string, Dictionary<string, int>>();

            foreach (var sentence in text)
            {
                for (var i = 0; i < sentence.Count - 2; i++)
                {
                    var bigram = sentence[i] + " " + sentence[i + 1];
                    var nextWord = sentence[i + 2];

                    if (!trigrams.ContainsKey(bigram))
                        trigrams.Add(bigram, new Dictionary<string, int>());

                    if (!trigrams[bigram].ContainsKey(nextWord))
                        trigrams[bigram].Add(nextWord, 1);
                    else
                        trigrams[bigram][nextWord] += 1;
                }
            }

            return trigrams;
        }

        public static string GetLexicographicallyFirstWord(string word1, string word2)
        {
            return string.CompareOrdinal(word1, word2) < 0 ? word1 : word2;
        }
    }
}
