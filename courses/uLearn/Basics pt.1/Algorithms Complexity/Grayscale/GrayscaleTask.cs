namespace Recognizer
{
	public static class GrayscaleTask
	{
        const double RedFactor = 0.299;
        const double GreenFactor = 0.587;
        const double BlueFactor = 0.114;

        public static double[,] ToGrayscale(Pixel[,] original)
		{
            var width = original.GetLength(0);
            var height = original.GetLength(1);
            var grayscale = new double[width, height];

            for (var x = 0; x < width; x++)
            {
                for (var y = 0; y < height; y++)
                    grayscale[x, y] =
                        (RedFactor * original[x, y].R +
                        GreenFactor * original[x, y].G +
                        BlueFactor * original[x, y].B) / 255;
            }

			return grayscale;
		}
	}
}
