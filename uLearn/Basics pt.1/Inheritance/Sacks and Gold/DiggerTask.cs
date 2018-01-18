using System.Windows.Forms;

namespace Digger
{
    public class Player : ICreature
    {
        public CreatureCommand Act(int x, int y)
        {
            var player = new CreatureCommand();

            switch (Game.KeyPressed)
            {
                case Keys.Up:
                    if (y - 1 >= 0 && !(Game.Map[x, y - 1] is Sack))
                    {
                        player.DeltaY = -1;
                    }
                    break;
                case Keys.Down:
                    if (y + 1 < Game.MapHeight && !(Game.Map[x, y + 1] is Sack))
                    {
                        player.DeltaY = 1;
                    }
                    break;
                case Keys.Left:
                    if (x - 1 >= 0 && !(Game.Map[x - 1, y] is Sack))
                    {
                        player.DeltaX = -1;
                    }
                    break;
                case Keys.Right:
                    if (x + 1 < Game.MapWidth && !(Game.Map[x + 1, y] is Sack))
                    {
                        player.DeltaX = 1;
                    }
                    break;
                default:
                    break;
            }

            return player;
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            return (conflictedObject is Sack) ? true : false;
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
            return (conflictedObject is Player) ? true : false;
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
        private int offsetY = 0;

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

                return (bottomObject is Player && offsetY >= 1) ||
                    (bottomObject == null);
            }
            else
            {
                return false;
            }
        }

        public CreatureCommand Fall()
        {
            offsetY++;
            return new CreatureCommand() { DeltaY = 1 };
        }

        public CreatureCommand Idle()
        {
            if (offsetY > 1)
            {
                offsetY = 0;
                return new CreatureCommand() { TransformTo = new Gold() };
            }
            else
            {
                offsetY = 0;
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
}
