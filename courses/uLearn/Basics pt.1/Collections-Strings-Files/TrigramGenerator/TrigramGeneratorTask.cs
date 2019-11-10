using System.Collections.Generic;
using System.Text;

namespace TextAnalysis
{
	internal static class TrigramGeneratorTask
	{
		/*
		Повторите ту идею с Биграммами, только используя триграммную модель текста.
		Теперь вам преедается словарь, в котором ключем являются два первых слова триграмм текста (разделенные пробелом),
		а значение — третье слово триграммы.
		Продолжите фразу до длины phraseWordsCount слов так, чтобы каждое следующее 
		слово определялось двумя предыдущими по переданному словарю.
		*/
		public static string ContinuePhraseWithTrigramms(Dictionary<string, string> mostFrequentNextWords, string phraseBeginning, int phraseWordsCount)
		{
            var finalPhrase = new StringBuilder(phraseBeginning);
            var nextBigram = phraseBeginning;

            for (var i = 2; i < phraseWordsCount; i++)
            {
                if (!mostFrequentNextWords.ContainsKey(nextBigram))
                    break;

                var word = mostFrequentNextWords[nextBigram];
                finalPhrase.Append(" " + word);
                nextBigram = nextBigram.Split(' ')[1] + " " + word;
            }

            return finalPhrase.ToString();
		}
	}
}
