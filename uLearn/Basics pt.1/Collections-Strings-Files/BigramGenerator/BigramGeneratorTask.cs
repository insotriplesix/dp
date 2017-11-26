using System.Collections.Generic;
using System.Text;

namespace TextAnalysis
{
	static class BigramGeneratorTask
	{
		public static string ContinuePhraseWithBigramms(
			Dictionary<string, string> mostFrequentNextWords, 
			string phraseBeginning, 
			int phraseWordsCount)
		{
            var finalPhrase = new StringBuilder(phraseBeginning);
            var word = phraseBeginning;

            for (var i = 1; i < phraseWordsCount; i++)
            { 
                if (!mostFrequentNextWords.ContainsKey(word))
                    break;

                word = mostFrequentNextWords[word];
                finalPhrase.Append(" " + word);
            }

			return finalPhrase.ToString();
		}
	}
}
