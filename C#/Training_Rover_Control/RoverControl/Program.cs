namespace RoverControl;
using System;
using System.Collections.Generic;

public class Program
{
    public static void Main(string[] args)
    {
        //Tüm rover bilgilerini tutması için liste koleksiyonu oluşturuyoruz
        List<RoverInfos> rovers = new List<RoverInfos>();

        //UserInput sınıfından düzlemin x ve y koordinatlarını alıyoruz
        UserInput.InputXDimension();
        UserInput.InputYDimension();

        while (true)
        {
            Console.WriteLine("Press 1 to View Deployed Rovers\nPress 2 to Deploy a New Rover\nPress 3 to select a rover and then Move it\nPress q to exit the program: ");
            string? select = Console.ReadLine();
            if (select == "1")
            {
                //seçim 1 ise öncelikle listemiz boş mu değil mi ona bakıyoruz
                if (rovers.Count == 0)
                {
                    Console.WriteLine("You haven't deploy any rover yet. Returning to main menu...");
                    continue;
                }
                foreach (RoverInfos rover in rovers)
                {
                    rover.DisplayRoverInfos();
                }
            }
            else if (select == "2")
            {
                UserInput userInput = new UserInput();
                RoverInfos createRover = new RoverInfos(); // yeni bir rover oluşturduk
                createRover.Name = userInput.Name(); //ismi atadık
                int controlName = 0; //isim kullanılıyor mu onu test etmek için
                foreach (RoverInfos rover in rovers)
                {
                    if (createRover.Name == rover.Name && createRover != rover) //birebir aynı rover değilse ama isimleri eşitse
                    {
                        Console.WriteLine("The name is using by another rover, returning to main menu...");
                        controlName = 1;
                        break;
                    }
                }
                if (controlName == 1)
                {
                    continue;
                }
                createRover.X = userInput.InputRoverX(); //roverın x,y,d değerlerini alıyoruz
                createRover.Y = userInput.InputRoverY();
                createRover.Direction = userInput.InputDirection();
                int controlDuplicate = 0; //aynı noktada başka rover var mı kontrol etmek için
                foreach (RoverInfos rover in rovers)
                {
                    if (createRover.X == rover.X && createRover.Y == rover.Y && createRover != rover)
                    {
                        Console.WriteLine("There is another rover at that coordinates, returning to main menu...");
                        controlDuplicate = 1;
                        break;
                    }
                }
                if (controlDuplicate == 0)
                {
                    rovers.Add(createRover);
                }
            }
            else if (select == "3")
            {
                Console.WriteLine("Enter the name of the rover that you want to move (Please pay attention to upper and lower case letters): "); //hangi roverın hareket ettirileceğini seçmek için bir mekanizmaya ihtiyaç vardı, ismini girmenin mantıklı olduğunu düşündüm. Kulanıcı adı mantığında çalışıyor büyük küçük harf duyarlı
                string? selection = Console.ReadLine();
                int testName = 0;
                foreach (RoverInfos rover in rovers)
                {
                    if (selection == rover.Name)
                    {
                        ControlTheRover controlTheRover = new ControlTheRover(); //ismi girilen rover listede bulunuyorsa controlTheRover sınıfından MoveRover metodunu çağırıyoruz
                        controlTheRover.MoveRover(rover,rovers);
                        rover.DisplayRoverInfos();
                        testName = 1;
                        break;
                    }
                }
                if (testName == 0)
                {
                    Console.WriteLine("There already is a rover with that name, returning to main menu...");
                }
            }
            else if (select == "q")
            {
                Console.WriteLine("Exiting the program...");
                break;
            }
            else
            {
                Console.WriteLine("You entered a mistaken value, returning to main menu...");
            }    
        }
    }
}