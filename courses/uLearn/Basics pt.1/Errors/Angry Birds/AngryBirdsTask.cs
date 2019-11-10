using System;

namespace AngryBirds
{
    public static class AngryBirdsTask
    {
        public static double FindSightAngle(double v, double distance)
        {
            double g = 9.8;
            double sinAngle = (distance * g) / (v * v);
            return 0.5 * Math.Asin(sinAngle);
        }
    }
}
