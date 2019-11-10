public class CaseAlternatorTask
{
	public static List<string> AlternateCharCases(string lowercaseWord)
	{
		var result = new List<string>();
		AlternateCharCases(lowercaseWord.ToCharArray(), 0, result);
		return result;
	}

	static void AlternateCharCases(char[] word, int startIndex, List<string> result)
	{
		if (startIndex < word.Length)
		{
			if (char.IsLetter(word[startIndex]))
			{
				word[startIndex] = char.ToLower(word[startIndex]);
				AlternateCharCases(word, startIndex + 1, result);

				word[startIndex] = char.ToUpper(word[startIndex]);
				AlternateCharCases(word, startIndex + 1, result);
			}
			else
			{
				AlternateCharCases(word, startIndex + 1, result);
			}
		}

		var nextWord = new string(word);

		if (!result.Contains(nextWord))
		{
			result.Add(nextWord);
		}
	}
}	
