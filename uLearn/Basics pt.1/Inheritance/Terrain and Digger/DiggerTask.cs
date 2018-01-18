using System.Windows.Forms;

namespace Digger
{
    public class Player : ICreature
    {
        public CreatureCommand Act(int x, int y)
        {
            var player = new CreatureCommand();
            var key = Game.KeyPressed;
            
            if (key == Keys.Up && y - 1 >= 0)
            {
                player.DeltaY = -1;
            }
            else if (key == Keys.Down && y + 1 < Game.MapHeight)
            {
                player.DeltaY = 1;
            }
            else if (key == Keys.Left && x - 1 >= 0)
            {
                player.DeltaX = -1;
            }
            else if (key == Keys.Right && x + 1 < Game.MapWidth)
            {
                player.DeltaX = 1;
            }

            return player;
        }

        public bool DeadInConflict(ICreature conflictedObject)
        {
            return false;
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
}
