using System.Collections.Generic;

namespace Recognizer
{
	internal static class MedianFilterTask
	{
		public static double[,] MedianFilter(double[,] original)
		{
            var width = original.GetLength(0);
            var height = original.GetLength(1);
            var filteredPixels = new double[width, height];

            for (var x = 0; x < width; x++)
                for (var y = 0; y < height; y++)
                    filteredPixels[x, y] = GetPixelValue(x, y, original);

            return filteredPixels;
        }

        private static double GetPixelValue(int x, int y, double[,] original)
        {
            var width = original.GetLength(0);
            var height = original.GetLength(1);
            var edgeValues = new List<double>();

            for (var offsetX = -1; offsetX < 2; offsetX++)
            {
                for (var offsetY = -1; offsetY < 2; offsetY++)
                {
                    if (PixelIsInsideBoundaries(x + offsetX, y + offsetY, width, height))
                        edgeValues.Add(original[x + offsetX, y + offsetY]);
                }
            }

            edgeValues.Sort();

            return GetMedianValue(edgeValues);
        }

        private static bool PixelIsInsideBoundaries(int x, int y, int width, int height)
        {
            return (x > -1 && y > -1) && (x < width && y < height);
        }

        private static double GetMedianValue(List<double> edge)
        {
            if (edge.Count % 2 == 0)
                return (edge[edge.Count / 2 - 1] + edge[edge.Count / 2]) / 2;
            else
                return edge[edge.Count / 2];
        }
    }
}
