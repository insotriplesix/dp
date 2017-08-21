namespace Mazes
{
    public static class PyramidMazeTask
    {
        // Go to the farthest right side
        public static void GoToRightSide(Robot robot, int width, int height)
        {
            for (int i = 0; i < width - 3; ++i)
                robot.MoveTo(Direction.Right);
        }

        // Go to the farthest left side
        public static void GoToLeftSide(Robot robot, int width, int height)
        {
            for (int i = 0; i < width - 3; ++i)
                robot.MoveTo(Direction.Left);
        }

        // Make a "snake curve"
        public static void MakeCurve(Robot robot, int width, int height)
        {
            GoToRightSide(robot, width, height);
            robot.MoveTo(Direction.Up);
            robot.MoveTo(Direction.Up);
            GoToLeftSide(robot, width - 2, height);
        }

        public static void MoveOut(Robot robot, int width, int height)
        {
            var len = height > 5 ? height / 4 : 1;
            var step = 0;
            for (int i = 0; i < len; ++step)
            {
                MakeCurve(robot, width - step * 2, height - step * 2);
                if (++i != len)
                {
                    robot.MoveTo(Direction.Up);
                    robot.MoveTo(Direction.Up);
                    ++step;
                }
            }
        }
    }
}
