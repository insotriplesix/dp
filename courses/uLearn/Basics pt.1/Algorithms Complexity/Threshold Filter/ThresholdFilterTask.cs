using System.Collections.Generic;

namespace Recognizer
{
    public static class ThresholdFilterTask
    {
        public static double[,] ThresholdFilter(double[,] original, double threshold)
        {
            var width = original.GetLength(0);
            var height = original.GetLength(1);
            var filteredPixels = new double[width, height];

            var thresholdValue = CalculateThresholdValue(original, threshold);

            for (var x = 0; x < width; x++)
                for (var y = 0; y < height; y++)
                    filteredPixels[x, y] = (original[x, y] >= thresholdValue) ? 1.0 : 0.0;

            return filteredPixels;
        }

        private static double CalculateThresholdValue(double[,] original, double threshold)
        {
            var width = original.GetLength(0);
            var height = original.GetLength(1);
            var numberOfPixels = width * height;
            var pixels = new List<double>(width * height);

            var pixelsToChange = (int)(numberOfPixels * threshold);

            for (var x = 0; x < width; x++)
                for (var y = 0; y < height; y++)
                    pixels.Add(original[x, y]);

            pixels.Sort();

            return GetThresholdValue(pixels, numberOfPixels, pixelsToChange);
        }

        private static double GetThresholdValue(List<double> pixels, int numberOfPixels, int pixelsToChange)
        {
            if (pixelsToChange == numberOfPixels)
                return -1.0;
            else if (pixelsToChange == 0)
                return double.MaxValue;
            else
                return pixels[numberOfPixels - pixelsToChange];
        }
    }
}
