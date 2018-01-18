using System;
using System.Drawing;

namespace RoutePlanning
{
    public static class PathFinderTask
    {
        public static int[] FindBestCheckpointsOrder(Point[] checkpoints)
        {
            var numberOfCheckpoints = checkpoints.Length;
            var shortestPath = new int[numberOfCheckpoints];
            var path = new int[numberOfCheckpoints];
            var shortestDistance = double.PositiveInfinity;

            MakePathPermutations(checkpoints, shortestPath, path, 1, shortestDistance);

            return shortestPath;
        }

        private static double MakePathPermutations(Point[] checkpoints, int[] shortestPath,
            int[] path, int position, double shortestDistance)
        {
            var numberOfCheckpoints = checkpoints.Length;
            var distance = checkpoints.GetPathLength(path);

            if (position == path.Length && distance < shortestDistance)
            {
                shortestDistance = distance;
                Array.Copy(path, shortestPath, numberOfCheckpoints);
                return shortestDistance;
            }

            for (var i = 0; i < numberOfCheckpoints; i++)
            {
                var index = Array.IndexOf(path, i, 0, position);

                if (index == -1)
                {
                    path[position] = i;
                    shortestDistance = MakePathPermutations(checkpoints, shortestPath, path,
                        position + 1, shortestDistance);
                }
            }

            return shortestDistance;
        }
    }
}
