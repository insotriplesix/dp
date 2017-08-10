using System;

namespace Task1
{
    class Program
    {
        public static void Main()
        {
            Console.Write("Input a: ");
            var a = int.Parse(Console.ReadLine());
            Console.Write("Input b: ");
            var b = int.Parse(Console.ReadLine());

            var counter = 0;
            for (int i = a; i < b; ++i)
            {
                if ((i % 400 == 0) || (i % 100 != 0 && i % 4 == 0))
                {
                    ++counter;
                    Console.WriteLine(i.ToString() + " ");
                }
            }
            Console.WriteLine();
            Console.WriteLine(counter);
        }
    }
}
