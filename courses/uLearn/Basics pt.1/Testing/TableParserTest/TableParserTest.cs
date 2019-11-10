public static void RunTests()
{
	NoFields();
	OneField();
	EmptyField();
	MoreThanOneField();
	
	SeparateFieldsByOneSpace();
	SeparateFieldsByMoreThanOneSpace();
	
	QuotedFieldAfterSimpleField();
	QuotedFieldBeforeSimpleField();
	
	SpaceBetweenQuotes();
	SingleQuotesInDoubleQuotes();
	DoubleQuotesInSingleQuotes();
	
	NoClosingQuotationMark();
	IgnoreBoundarySpaces();
	SeparateWithoutSpaces();
	
	BackSlashMagic();
	SingleQuotesMagic();
	DoubleQuotesMagic();
}

public static void NoFields()
{
	Test(String.Empty, new string[0]);
}

public static void OneField()
{
	Test("0xDEADBEEF", new[] { "0xDEADBEEF" });
}

public static void EmptyField()
{
	Test("''", new[] { "" });
}

public static void MoreThanOneField()
{
	Test("i like writing tests", new[] { "i", "like", "writing", "tests" });
}

public static void SeparateFieldsByOneSpace()
{
	Test("separate us plz", new[] { "separate", "us", "plz" });
}

public static void SeparateFieldsByMoreThanOneSpace()
{
	Test("what  about    this?", new[] { "what", "about", "this?" });
}

public static void QuotedFieldAfterSimpleField()
{
	Test("cut 'it'", new[] { "cut", "it" });
}

public static void QuotedFieldBeforeSimpleField()
{
	Test("\"cut\" it", new[] { "cut", "it" });
}

public static void SpaceBetweenQuotes()
{
	Test("' '", new[] { " " });
}

public static void SingleQuotesInDoubleQuotes()
{
	Test("\"'smile plz :)'\"", new[] { "'smile plz :)'" });	
}

public static void DoubleQuotesInSingleQuotes()
{
	Test("'\"another  one :)\"'", new[] { "\"another  one :)\"" });
}

public static void NoClosingQuotationMark()
{
	Test("\"jeeeeez ", new[] { "jeeeeez " });
}

public static void IgnoreBoundarySpaces()
{
	Test(" <-ignore damn spaces->   ", new[] { "<-ignore", "damn", "spaces->" });
}

public static void SeparateWithoutSpaces()
{
	Test("i'm'too'lazy'to'put'spaces'sorry'",
		 new[] {"i", "m", "too", "lazy", "to", "put", "spaces", "sorry"});
}

public static void BackSlashMagic()
{
	Test("\"\\\\\"", new[] { "\\" }); 
}

public static void SingleQuotesMagic()
{
	Test("\'\\\'MAGIC\\\'\'", new[] {"\'MAGIC\'"});
}

public static void DoubleQuotesMagic()
{
	Test("\"\\\"MAGIC\\\"\"", new[] {"\"MAGIC\""});
}
