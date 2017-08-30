public static bool HorizontalCheck(Mark[,] field, Mark mark)
{
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (field[i, j] != mark) break;	
		}
		if (j == 3) return true;	
	}
	return false;
}

public static bool VerticalCheck(Mark[,] field, Mark mark)
{
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (field[j, i] != mark) break;	
		}
		if (j == 3) return true;	
	}
	return false;
}

public static bool DiagonalCheck(Mark[,] field, Mark mark)
{
	int i;
	for (i = 0; i < 3; ++i) {
		if (field[i,i] != mark) break;
	}
	if (i == 3) return true;
	
	for (i = 2; i >= 0; --i) {
		if (field[2-i,i] != mark) break;
	}	
	return i < 0 ? true : false;
}

public static bool CheckStatus(Mark[,] field, Mark mark)
{
	return (HorizontalCheck(field, mark)) ? true :
		   (VerticalCheck(field, mark) ? true :
		   (DiagonalCheck(field, mark) ? true : false));
}

public static GameResult GetGameResult(Mark[,] field)
{	
	bool isCrossWin = CheckStatus(field, Mark.Cross);
	bool isCircleWin = CheckStatus(field, Mark.Circle);
	bool isDraw = (isCrossWin == isCircleWin);
	
	return isDraw ? GameResult.Draw : (isCrossWin ? GameResult.CrossWin : GameResult.CircleWin);
}
