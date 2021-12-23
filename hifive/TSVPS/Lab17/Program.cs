using System;
using System.Collections.Generic;
using System.Linq;

namespace ConsoleApp1
{
    public class DataStore
    {
        public List<List<int>> m = new List<List<int>>();
        public List<List<int>> s = new List<List<int>>();
        public List<int> sizes = new List<int>();
        public string order = new string('a', 0);

        public DataStore(List<int> l)
        {
            sizes = l;
        }
    }

    public class Mult
    {
        public DataStore dataStore;

        public Mult(DataStore d)
        {
            dataStore = d;
        }

        public int MatrixChainMultCount()
        {
            int n = dataStore.sizes.Count - 1;
            int[,] f = new int[n, n];

            for (int t = 1; t < n; t++)
            {
                for (int k = 0; k < n - t; k++)
                {
                    int min_ = -1;

                    for (int j = k; j < k + t; j++)
                    {
                        int checkMin = f[k, j] + f[j + 1, k + t] + dataStore.sizes[k] * dataStore.sizes[j + 1] * dataStore.sizes[k + t + 1];
                        if (min_ < 0 || checkMin < min_)
                        {
                            min_ = checkMin;
                        }
                    }

                    f[k, k + t] = min_;
                }
            }
            return f[0, n - 1];
        }

        public void MatrixChainOrder()
        {
            int n = dataStore.sizes.Count - 1;

            dataStore.m = new List<List<int>>();
            dataStore.s = new List<List<int>>();
            for (int i = 0; i < n; i++)
            {
                dataStore.m.Add(new List<int>());
                dataStore.s.Add(new List<int>());
                for (int a = 0; a < n; a++)
                {
                    dataStore.m[i].Add(0);
                    dataStore.s[i].Add(0);
                }
            }

            int j;
            for (int l = 1; l < n; l++)
            {
                for (int i = 0; i < n - l; i++)
                {
                    j = i + l;
                    dataStore.m[i][j] = int.MaxValue;
                    for (int k = i; k < j; k++)
                    {
                        int q = dataStore.m[i][k] + dataStore.m[k + 1][j] +
                                dataStore.sizes[i] * dataStore.sizes[k + 1] * dataStore.sizes[j + 1];
                        if (q < dataStore.m[i][j])
                        {
                            dataStore.m[i][j] = q;
                            dataStore.s[i][j] = k;
                        }
                    }
                }
            }
        }

        public void ConstructOrderString(int i, int j)
        {
            if (i == j)
            {
                dataStore.order += "[" + dataStore.sizes[i] + " * " + dataStore.sizes[i + 1] + "]";
            }
            else
            {
                dataStore.order += "(";
                ConstructOrderString(i, dataStore.s[i][j]);
                dataStore.order += " * ";
                ConstructOrderString(dataStore.s[i][j] + 1, j);
                dataStore.order += ")";
            }
        }
    }

    public class Program
    {
        public static void Main(string[] args)
        {
            //List<int> list = new() { 300, 50, 10, 100, 20, 250 };
            List<int> list = new List<int>() { 5, 5, 5, 5, 5, 5 };

            DataStore d = new DataStore(list);
            Mult c = new Mult(d);

            c.MatrixChainOrder();
            c.ConstructOrderString(0, list.Count - 2);

            Console.WriteLine("Matrices count: {0}", list.Count);

            Console.Write("\nMatrices: ");
            Console.Write("[{0} x {1}]", list[0], list[1]);
            for (int i = 1; i < list.Count; i++)
            {
                Console.Write(" * [{0} x {1}]", list[i - 1], list[i]);
            }

            Console.WriteLine("\n\nMultiplication order: {0}", d.order.Substring(1, d.order.Length - 2));
            Console.WriteLine("\nMultiply count: {0}", c.MatrixChainMultCount());
        }
    }
}