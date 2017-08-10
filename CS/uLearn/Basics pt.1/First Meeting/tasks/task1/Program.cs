using System;

namespace Tasks
{
    class Program
    {
        public static void Main()
        {
            Console.Write("Input a: ");
            var a = int.Parse(Console.ReadLine());
            Console.Write("Input b: ");
            var b = int.Parse(Console.ReadLine());

            // 1st case
            var tmp = b;
            b = a;
            a = tmp;

            Console.WriteLine("a is " + a.ToString() + " now");
            Console.WriteLine("b is " + b.ToString() + " now");
         
            Console.Write("Input a: ");
            a = int.Parse(Console.ReadLine());
            Console.Write("Input b: ");
            b = int.Parse(Console.ReadLine());

            // 2nd case
            a ^= b;
            b ^= a;
            a ^= b;

            Console.WriteLine("a is " + a.ToString() + " now");
            Console.WriteLine("b is " + b.ToString() + " now");
        }
    }
}
