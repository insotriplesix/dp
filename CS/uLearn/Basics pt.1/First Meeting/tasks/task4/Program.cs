using System;

namespace Task1
{
    class Program
    {
        public static void Main()
        {
            Console.Write("Input n: ");
            var n = int.Parse(Console.ReadLine());
            Console.Write("Input x: ");
            var x = int.Parse(Console.ReadLine());
            Console.Write("Input y: ");
            var y = int.Parse(Console.ReadLine());

            int counter = 0;
            for (int i = 1; i < n; ++i)
            {
                if (i % x == 0 && i % y == 0)
                {
                    ++counter;
                    Console.Write(i.ToString() + " ");
                }
            }
            Console.WriteLine();
            Console.WriteLine(counter);
        }
    }
}
