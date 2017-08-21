namespace Mazes
{
	public static class PyramidMazeTask
	{
        // Horizontal shift
        public static void MakeHorizontalMove(Robot robot, int width, Direction dir)
        {
            for (int i = 0; i < width - 3; ++i)
                robot.MoveTo(dir);
        }

        // Vertical shift
        public static void MakeVerticalMove(Robot robot, int height, Direction dir)
        {
            for (int i = 0; i < height - 3; ++i)
                robot.MoveTo(dir);
        }

        // Make a "snake curve"
        public static void MakeCurve(Robot robot, int width, int height)
        {
            MakeHorizontalMove(robot, width, Direction.Right);
            robot.MoveTo(Direction.Up);
            robot.MoveTo(Direction.Up);
            MakeHorizontalMove(robot, width - 2, Direction.Left);
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
