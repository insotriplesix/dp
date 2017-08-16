namespace Mazes
{
    public static class EmptyMazeTask
    {
        // Go to the farthest right side
        public static void GoToRightSide(Robot robot, int width, int height)
        {
            for (int i = 0; i < width - 3; ++i)
                robot.MoveTo(Direction.Right);
        }

        // Go to the farthest bottom side
        public static void GoToDownSide(Robot robot, int width, int height)
        {
            for (int i = 0; i < height - 3; ++i)
                robot.MoveTo(Direction.Down);
        }

        public static void MoveOut(Robot robot, int width, int height)
        {
            GoToRightSide(robot, width, height);
            GoToDownSide(robot, width, height);
        }
    }
}
