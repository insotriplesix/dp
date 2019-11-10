using System.Collections.Generic;
using System.Drawing;

namespace GeometryPainting
{
    public static class SegmentExtensions
    {
        public static Dictionary<Segment, Color> ColoredSegments =
            new Dictionary<Segment, Color>();

        public static Color GetColor(this Segment seg)
        {
            return ColoredSegments.ContainsKey(seg) ? ColoredSegments[seg] : Color.Black;
        }

        public static void SetColor(this Segment seg, Color col)
        {
            var segmentAlreadyInDictionary = ColoredSegments.ContainsKey(seg);

            if (!segmentAlreadyInDictionary)
            {
                ColoredSegments.Add(seg, col);
            }
            else if (segmentAlreadyInDictionary && !ColoredSegments[seg].Equals(col))
            {
                ColoredSegments[seg] = col;
            }
        }
    }
}
