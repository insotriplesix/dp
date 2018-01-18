using System;

namespace Recognizer
{
    internal static class SobelFilterTask
    {
        public static double[,] SobelFilter(double[,] original, double[,] sx)
        {
            var width = original.GetLength(0);
            var height = original.GetLength(1);
            var filteredPixels = new double[width, height];

            var offsetX = sx.GetLength(0) / 2;
            var offsetY = sx.GetLength(1) / 2;

            var sy = GetTransposedMatrix(sx);

            for (var x = offsetX; x < width - offsetX; x++)
            {
                for (var y = offsetY; y < height - offsetY; y++)
                {
                    var gx = GetConvolution(original, sx, x, y, offsetX);
                    var gy = GetConvolution(original, sy, x, y, offsetY);

                    filteredPixels[x, y] = Math.Sqrt(gx * gx + gy * gy);
                }
            }

            return filteredPixels;
        }

        private static double[,] GetTransposedMatrix(double[,] matrix)
        {
            var width = matrix.GetLength(0);
            var height = matrix.GetLength(1);
            var transposedMatrix = new double[width, height];

            for (var x = 0; x < width; x++)
                for (var y = 0; y < height; y++)
                    transposedMatrix[x, y] = matrix[y, x];

            return transposedMatrix;
        }

        private static double GetConvolution(double[,] original, double[,] s, int x, int y, int offset)
        {
            var width = s.GetLength(0);
            var height = s.GetLength(1);
            var result = 0.0;

            for (var sx = 0; sx < width; sx++)
                for (var sy = 0; sy < height; sy++)
                    result += s[sx, sy] * original[x + sx - offset, y + sy - offset];

            return result;
        }
    }
}


/* 
       Разберитесь, как работает нижеследующий код (называемый фильтрацией Собеля), 
       и какое отношение к нему имеют эти матрицы:

            | -1 -2 -1 |           | -1  0  1 |
       Sx = |  0  0  0 |      Sy = | -2  0  2 |
            |  1  2  1 |           | -1  0  1 |

       https://ru.wikipedia.org/wiki/%D0%9E%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80_%D0%A1%D0%BE%D0%B1%D0%B5%D0%BB%D1%8F

       Попробуйте заменить фильтр Собеля 3x3 на фильтр Собеля 5x5 и сравните результаты. 
       http://www.cim.mcgill.ca/~image529/TA529/Image529_99/assignments/edge_detection/references/sobel.htm

       Обобщите код применения фильтра так, чтобы можно было передавать ему любые матрицы, любого нечетного размера.
       Фильтры Собеля размеров 3 и 5 должны быть частным случаем. 
       После такого обобщения менять фильтр Собеля одного размера на другой будет легко.
*/
