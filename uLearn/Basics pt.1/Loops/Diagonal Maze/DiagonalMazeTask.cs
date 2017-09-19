namespace Mazes
{
    public static class DiagonalMazeTask
    {
        // Horizontal shift
        public static void MakeHorizontalMove(Robot robot, int width, Direction dir)
        {
            for (int i = 0; i < width; ++i)
                robot.MoveTo(dir);
        }

        // Vertical shift
        public static void MakeVerticalMove(Robot robot, int height, Direction dir)
        {
            for (int i = 0; i < height; ++i)
                robot.MoveTo(dir);
        }

        public static void GoRightDown(Robot robot, int width, int height)
        {
            for (int i = 0; i < height - 2; ++i)
            {
                MakeVerticalMove(robot, width / (height - 1), Direction.Right);
                if (i != (height - 3))
                    MakeHorizontalMove(robot, 1, Direction.Down);
            }
        }

        public static void GoDownRight(Robot robot, int width, int height)
        {
            for (int i = 0; i < width - 2; ++i)
            {
                MakeVerticalMove(robot, (height - 3) / (width - 2), Direction.Down);
                if (i != (width - 3))
                    MakeHorizontalMove(robot, 1, Direction.Right);
            }
        }

        public static void MoveOut(Robot robot, int width, int height)
        {
            // first > then v
            if (width > height)
                GoRightDown(robot, width, height);
            // first v then >
            else
                GoDownRight(robot, width, height);
        }
    }
}
