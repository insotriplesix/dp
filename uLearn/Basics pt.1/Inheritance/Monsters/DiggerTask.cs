using System.Windows.Forms;

namespace Digger
{
    public class Player : ICreature
    {
        public CreatureCommand Act(int x, int y)
        {
            var player = new CreatureCommand();
            var key = Game.KeyPressed;
            
            if (key == Keys.Up && y - 1 >= 0 &&
                !(Game.Map[x, y - 1] is Sack))
            {
                player.DeltaY = -1;
            }
			
            if (key == Keys.Down && y + 1 < Game.MapHeight &&
				!(Game.Map[x, y + 1] is Sack))
            {
                player.DeltaY = 1;
            }
			
            if (key == Keys.Left && x - 1 >= 0 &&
                !(Game.Map[x - 1, y] is Sack))
            {
                player.DeltaX = -1;
            }
			
            if (key == Keys.Right && x + 1 < Game.MapWidth &&
                !(Game.Map[x + 1, y] is Sack))
            {
                player.DeltaX = 1;
            }

            return player;
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            return (conflictedObject is Sack || conflictedObject is Monster) ?
                true : false;
        }

        public int GetDrawingPriority()
        {
            return 1;
        }

        public string GetImageFileName()
        {
            return "Digger.png";
        }
    }

    public class Terrain : ICreature
    {
        public CreatureCommand Act(int x, int y)
        {
            return new CreatureCommand();
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            return true;
        }

        public int GetDrawingPriority()
        {
            return 0;
        }

        public string GetImageFileName()
        {
            return "Terrain.png";
        }
    }

    public class Sack : ICreature
    {
        private int fellCells = 0;

        public CreatureCommand Act(int x, int y)
        {
            if (HasOpportunityToFall(x, y))
            {
                return Fall();
            }
            else
            {
                return Idle();
            }
        }

        public bool HasOpportunityToFall(int x, int y)
        {
            if (y + 1 < Game.MapHeight)
            {
                var bottomObject = Game.Map[x, y + 1];

                return ((bottomObject is Player || bottomObject is Monster)
                    && fellCells >= 1) || (bottomObject == null);
            }
            else
            {
                return false;
            }
        }

        public CreatureCommand Fall()
        {
            fellCells++;
            return new CreatureCommand() { DeltaY = 1 };
        }

        public CreatureCommand Idle()
        {
            if (fellCells > 1)
            {
                fellCells = 0;
                return new CreatureCommand() { TransformTo = new Gold() };
            }
            else
            {
                fellCells = 0;
                return new CreatureCommand();
            }
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            return false;
        }

        public int GetDrawingPriority()
        {
            return 2;
        }

        public string GetImageFileName()
        {
            return "Sack.png";
        }
    }

    public class Gold : ICreature
    {
        public CreatureCommand Act(int x, int y)
        {
            return new CreatureCommand();
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            if (conflictedObject is Player)
            {
                Game.Scores += 10;
                return true;
            }
            else if (conflictedObject is Monster)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public int GetDrawingPriority()
        {
            return 2;
        }

        public string GetImageFileName()
        {
            return "Gold.png";
        }
    }

    public class Monster : ICreature
    {
        private int offsetX = 0;
        private int offsetY = 0;

        public CreatureCommand Act(int x, int y)
        {
            var playerCoordinates = GetPlayerLocation();

            if (playerCoordinates != null)
            {
                offsetX = playerCoordinates[0] - x;
                offsetY = playerCoordinates[1] - y;
            }

            if (playerCoordinates != null && HasOpportunityToWalk(x, y))
            {
                return Walk();
            }
            else
            {
                return Idle();
            }
        }

        public int[] GetPlayerLocation()
        {
            var width = Game.MapWidth;
            var height = Game.MapHeight;

            for (var x = 0; x < width; x++)
            {
                for (var y = 0; y < height; y++)
                {
                    if (Game.Map[x, y] is Player)
                    {
                        return new int[] { x, y };
                    }
                }
            }

            return null;
        }

        public bool HasOpportunityToWalk(int x, int y)
        {
            if (CheckTop(x, y) || CheckBottom(x, y) ||
                CheckLeft(x, y) || CheckRight(x, y))
            {
                return true;
            }

            return false;
        }

        public bool CheckTop(int x, int y)
        {
            if (y - 1 >= 0 && offsetY != 0)
            {
                if (CheckNextCreature(x, y - 1, 0, -1))
                {
                    return true;
                }
            }

            return false;
        }

        public bool CheckBottom(int x, int y)
        {
            if (y + 1 < Game.MapHeight && offsetY != 0)
            {
                if (CheckNextCreature(x, y + 1, 0, 1))
                {
                    return true;
                }
            }

            return false;
        }

        public bool CheckLeft(int x, int y)
        {
            if (x - 1 >= 0 && offsetX != 0)
            {
                if (CheckNextCreature(x - 1, y, -1, 0))
                {
                    return true;
                }
            }

            return false;
        }

        public bool CheckRight(int x, int y)
        {
            if (x + 1 < Game.MapWidth && offsetX != 0)
            {
                if (CheckNextCreature(x + 1, y, 1, 0))
                {
                    return true;
                }
            }

            return false;
        }

        public bool CheckNextCreature(int x, int y, int dx, int dy)
        {
            var nextObject = Game.Map[x, y];

            if (nextObject == null || nextObject is Gold || nextObject is Player)
            {
                offsetX = dx;
                offsetY = dy;
                return true;
            }

            return false;
        }

        public CreatureCommand Walk()
        {
            if (offsetX != 0)
            {
                return new CreatureCommand() { DeltaX = offsetX };
            }
            else if (offsetY != 0)
            {
                return new CreatureCommand() { DeltaY = offsetY };
            }
            else
            {
                return new CreatureCommand();
            }
        }

        public CreatureCommand Idle()
        {
            return new CreatureCommand();
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            return (conflictedObject is Sack || conflictedObject is Monster) ? true : false;
        }

        public int GetDrawingPriority()
        {
            return 1;
        }

        public string GetImageFileName()
        {
            return "Monster.png";
        }
    }
}
