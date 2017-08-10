using System;

namespace Tasks
{
    class Program
    {
        public static void Main()
        {
            Console.Write("Input value: ");
            var value = int.Parse(Console.ReadLine());
            
            for (int i = 0; i < 3; ++i)
            {
                Console.Write(value % 10);
                value /= 10;
            }

            Console.WriteLine();
        }
    }
}
