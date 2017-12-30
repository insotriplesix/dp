using System;

namespace GeometryTasks
{
    public class Vector
    {
        public double X;
        public double Y;
    }

    public class Segment
    {
        public Vector Begin;
        public Vector End;
    }

    public class Geometry
    {
        public static double GetLength(Vector vec)
        {
            return Math.Sqrt(vec.X * vec.X + vec.Y * vec.Y);
        }

        public static Vector Add(Vector vec1, Vector vec2)
        {
            return new Vector { X = vec1.X + vec2.X, Y = vec1.Y + vec2.Y };
        }

        public static double GetLength(Segment seg)
        {
            double diffX = Math.Abs(seg.End.X - seg.Begin.X);
            double diffY = Math.Abs(seg.End.Y - seg.Begin.Y);

            return Math.Sqrt((diffX * diffX) + (diffY * diffY));
        }

        public static bool IsVectorInSegment(Vector vec, Segment seg)
        {
			return (vec.X >= seg.Begin.X && vec.X <= seg.End.X &&
					vec.Y >= seg.Begin.Y && vec.Y <= seg.End.Y &&
					((vec.X - seg.Begin.X) * (seg.End.Y - seg.Begin.Y) - 
					 (vec.Y - seg.Begin.Y) * (seg.End.X - seg.Begin.X) == 0));
        }
    }
}
