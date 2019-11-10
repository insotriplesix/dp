using System;
using System.Diagnostics;

namespace NQueens
{
    class Program
    {
        const int N = 4;
        const bool displayResults = true;

        public static void Main()
        {
            for (var i = 0; i < N; i++)
            {
                Console.WriteLine("Chessboard size: {0}x{0}", i);
                Console.WriteLine("Calculate solutions..\n");

                var timer = new Stopwatch();

                timer.Start();
                var solutions = EightQueensTask.CalculateSolutions(i);
                timer.Stop();

                if (displayResults)
                {
                    foreach (var s in solutions)
                    {
                        PrintSolution(s, N);
                        Console.WriteLine();
                    }
                }

                Console.WriteLine("Solutions found: {0}\nTime elapsed: {1} sec",
                    solutions.Count, timer.Elapsed);
            }
        }

        static void PrintSolution(bool[,] field, int N)
        {
            for (var x = 0; x < N; x++)
            {
                for (var y = 0; y < N; y++)
                {
                    if (field[x, y])
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.Write('Q');
                        Console.ForegroundColor = ConsoleColor.Gray;
                    }
                    else
                        Console.Write('*');
                }

                Console.WriteLine();
            }
        }
    }
}
