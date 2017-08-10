using System;

namespace Billiards
{
	public static class BilliardsTask
	{
		public static double BounceWall(double directionRadians, double wallInclinationRadians)
		{
		    if (wallInclinationRadians * 180 / Math.PI == 90)
			return Math.PI - directionRadians;
		    else if (wallInclinationRadians == 0)
			return 2 * Math.PI - directionRadians;
		    else
			return 2 * wallInclinationRadians - directionRadians;
		}
	}
}
