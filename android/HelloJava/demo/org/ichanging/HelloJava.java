package demo.org.ichanging;

public class HelloJava
{
	static void hello()
	{
		System.out.println("Hello Java");
	}
	
	public static void main(String args[])
	{
		if(args != null)
		{
			for(int i = 0;i < args.length ; i++)
			{
				System.out.println("args[" + i +"] = " + args[i]);
			}
		}
		
		hello();
	}	
}