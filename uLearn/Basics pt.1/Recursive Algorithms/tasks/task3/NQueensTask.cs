using System.Collections.Generic;

namespace NQueens
{
    public static class NQueensTask
    {
        public static List<bool[,]> CalculateSolutions(int N)
        {
            var chessboard = new bool[N, N];
            var result = new List<bool[,]>();
            var startPos = 0;
            var col = 0;
            var row = 0;
            var cnt = 0;
            while (true)
            {
                for (col = startPos; col < N; col++, cnt++)
                {
                    chessboard[row, col] = FindSolution(chessboard, N, row, col, result);
                    if (chessboard[row, col])
                    {
                        row++;
                        startPos = 0;
                        break;
                    }
                }
                cnt += 1;
                System.Console.WriteLine("CNT: " + cnt);
                if (col == N && row != N && row != 0)
                    startPos = DeleteQueen(chessboard, N, ref col, ref row);

                if (row == N)
                {
                    var solution = (bool[,])chessboard.Clone();
                    result.Add(solution);

                    startPos = DeleteQueen(chessboard, N, ref col, ref row);
                }

                if (col == N && row == 0) break;
            }
            //System.Console.WriteLine("CNT: " + cnt);
            return result;
        }

        private static bool FindSolution(bool[,] chessboard, int size, int row, int col, List<bool[,]> result)
        {
            var isSafe = true;

            for (var direction = -1; direction <= 1; direction++)
            {
                for (var offset = 1; ; offset++)
                {
                    var offCol = col + direction * offset;
                    var offRow = row - offset;

                    if (offCol >= 0 && offCol < size && offRow >= 0 && offRow < size)
                    {
                        if (chessboard[offRow, offCol])
                        {
                            isSafe = false;
                            break;
                        }
                    }
                    else break;
                }

                if (!isSafe) break;
            }

            return isSafe;
        }

        private static int DeleteQueen(bool[,] chessboard, int size, ref int col, ref int row)
        {
            row--;

            for (col = 0; col < size; col++)
            {
                if (chessboard[row, col])
                {
                    chessboard[row, col] = false;
                    return col + 1;
                }
            }

            return size;
        }
    }
}
