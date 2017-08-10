using System;

namespace Task1
{
    class Program
    {
        public static void Main()
        {
            Console.Write("Input H value: ");
            var h = int.Parse(Console.ReadLine());
            var angle = 30;
            Console.WriteLine(angle * h < 180 ? angle * h : 360 - Math.Abs(12 - h) * angle);          
        }
    }
}
