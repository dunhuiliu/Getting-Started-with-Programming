using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;
using System.Media;

namespace c_sharp��ƻ���ַ���
{
	class Program
	{
		static void Main(string[] args)
		{
			SoundPlayer r = new SoundPlayer(@"C:\Users\liudunhui\Documents\Visual Studio 2015\Projects\c - sharp��ƻ���ַ���\c - sharp��ƻ���ַ���\bin\Debug\Bad Apple!!- Alstroemeria Records.wav");
				r.Play();
			string[] arr = Directory.GetFiles(@"D:\�ַ���\bad Apple\�ַ�");//    C:\Users\liudunhui\Pictures\�ַ���\mafei
				for (int i = 0; i <= arr.Length; i++)
				{
					string str = File.ReadAllText(arr[i]);
					Console.Clear();
					Console.Write(str);
					// Thread.Sleep(73);//1000/֡��
					Thread.Sleep(60);



					// Thread.Sleep(999999);
				}
		}
	}
}