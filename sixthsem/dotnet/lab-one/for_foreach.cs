using System;
 
class Program
{
    static void Main(string[] args)
    {
        // for loop
        Console.WriteLine("Using for loop:");
        for (int i = 1; i <= 5; i++)
        {
            Console.WriteLine(i);
        }
 
        // foreach loop
        int[] numbers = { 10, 20, 30, 40, 50 };
        Console.WriteLine("\nUsing foreach loop:");
        foreach (int num in numbers)
        {
            Console.WriteLine(num);
        }
    }
}
