namespace RoverControl;

public class UserInput
{
    //UserInput sınıfından kodun farklı yerlerinde X ve Y koordinatlarına erişim ihtiyacı hissettiğim için bunları field olarak tanımladım
    //X ve Y koordinatları değişmeyeceği için static tanımladım
    public static int IntPlateuX { get; private set; }
    public static int IntPlateuY { get; private set; }
    //X koordinatını kullanıcının girmesi için oluşturduğum metot:
    //kullanıcıdan değerleri console.readline ile aldığım için tryParse ile int ve char türlerine çevirdim
    //bunu yaparken tryParse == false kullandığım için null check etmeme gerek yok, sadece stringi alırken nullable tür olarak almalıyım
    public static int InputXDimension()
    {
        int intPlateuX;
        while (true)
        {
            Console.WriteLine("Enter the Plateu's dimension X:");
            string? plateuX = Console.ReadLine();
            if (string.IsNullOrEmpty(plateuX))
            {
                Console.WriteLine("Input cannot be blank");
            }

            else if (!int.TryParse(plateuX, out intPlateuX))
            {
                Console.WriteLine("Please enter an integer value");
            }
            else if (intPlateuX <= 0)
            {
                Console.WriteLine("The X coordinate should be a bigger value than 0");
            }
            else
            {
                IntPlateuX = intPlateuX;
                return intPlateuX;
            }
        }
    }

    public static int InputYDimension()
    {
        //bir öncekiyle aynı işlemler
        int intPlateuY;
        while (true)
        {
            Console.WriteLine("Enter the Plateu's dimension Y:");
            string? plateuY = Console.ReadLine();
            if (string.IsNullOrEmpty(plateuY))
            {
                Console.WriteLine("Input cannot be blank");
            }

            else if (!int.TryParse(plateuY, out intPlateuY))
            {
                Console.WriteLine("Please enter an integer value");
            }
            else if (intPlateuY <= 0)
            {
                Console.WriteLine("The Y coordinate should be bigger than 0");
            }
            else
            {
                IntPlateuY = intPlateuY;
                return intPlateuY;
            }
        }
    }

    public string Name()
    {
        while (true)
        {
            Console.WriteLine("Enter the rover's name: ");
            string? name = Console.ReadLine();
            if (string.IsNullOrEmpty(name))
            {
                Console.WriteLine("Rover's name cannot be blank!");
            }
            else
            {
                return name;
            }
        }
    }

    public int InputRoverX()
    {
        while (true)
        {
            Console.WriteLine("Enter the Rover's X coordinate: ");
            string? roverX = Console.ReadLine();
            int intRoverX;
            if (!int.TryParse(roverX, out intRoverX))
            {
                Console.WriteLine("Please enter an integer value");
            }
            else if (intRoverX > IntPlateuX || intRoverX < 0)
            {
                Console.WriteLine("The input cannot be outside of the coordinate system!");
            }
            else
            {
                return intRoverX;
            }
        }
    }

    public int InputRoverY()
    {
        while (true)
        {
            Console.WriteLine("Enter the Rover's Y coordinate: ");
            string? roverY = Console.ReadLine();
            int intRoverY;
            if (!int.TryParse(roverY, out intRoverY))
            {
                Console.WriteLine("Please enter an integer value");
            }
            else if (intRoverY > IntPlateuY || intRoverY < 0)
            {
                Console.WriteLine("The input cannot be outside of the coordinate system");
            }
            else
            {
                return intRoverY;
            }
        }
    }

    public char InputDirection()
    {
        while (true)
        {
            Console.WriteLine("Enter the rover's direction (E,W,N,S): ");
            string? directionString = Console.ReadLine();
            
            if (string.IsNullOrEmpty(directionString)) //null ise veya boş ise tekrar girmesini isteyecek
            {
                Console.WriteLine("The direction cannot be blank");
                continue;
            }
            char direction = Char.Parse(directionString);
            if (direction != 'E' && direction != 'W' && direction != 'N' && direction!= 'S')
            {
                Console.WriteLine("You entered a mistaken input. Please enter only one of the E,W,N,S directions "); //girilen değer E,W,N,S değilse tekrar girmesini ister
                continue;
            }
            return direction;
        }
    }
}

