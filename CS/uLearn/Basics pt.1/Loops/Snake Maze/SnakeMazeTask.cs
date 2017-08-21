namespace Mazes
{
    public static class SnakeMazeTask
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
            robot.MoveTo(Direction.Down);
            robot.MoveTo(Direction.Down);
            MakeHorizontalMove(robot, width, Direction.Left);
        }

        public static void MoveOut(Robot robot, int width, int height)
        {
            var len = height > 5 ? height / 4 : 1;
            for (int i = 0; i < len;)
            {
                MakeCurve(robot, width, height);
                if (++i != len)
                {
                    robot.MoveTo(Direction.Down);
                    robot.MoveTo(Direction.Down);
                }  
            }
        }
    }
}
