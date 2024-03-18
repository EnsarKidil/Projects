namespace RoverControl;

public class ControlTheRover
{
    private readonly int _intPlateuX = UserInput.IntPlateuX;
    private readonly int _intPlateuY = UserInput.IntPlateuY;
    public void MoveRover(RoverInfos rover,List<RoverInfos> rovers)
    {
        Console.WriteLine("Please enter l to turn the rover to left, r to turn the rover to right and m to move the rover, Input Example = (llmrlmm): ");
        string? moveInfo = Console.ReadLine();
        List<char> directions = new List<char>(){'N', 'E', 'S', 'W'}; //NESW yönlerini saat yönünde olacak bir sıra ile bir listeye tanımladım
        int tempX = rover.X; //temp tanımlama sebebim roverın gidileceği yolda başka bir rover varsa ilk konumuna geri döndürmek
        int tempY = rover.Y; //bunun sebebi bence girilen rotada başka bir rover varsa o rotaya doğru ilerlemeye başlamamalı, dolayısıyla bu gerçekleştiğinde x ve y değeri ilk halne geri döndüğü için oraya yönlenmemiş olacak
        char tempDirection = rover.Direction;
        int controlTestRover = 0; //roverın karşılaştığı herhangi bir rover var ise bu değeri değiştiriyoruz ve ilk haline geri döndürüyoruz
        if (!string.IsNullOrEmpty(moveInfo))
        {
            foreach (char i in moveInfo)
            {
                if (i == 'l')
                {
                    int index = directions.IndexOf(rover.Direction); //NESW listesinde şu anki yönün indexini alıyor, sola dönmesini istediği için bir gerisindeki liste elemanını yeni yön olarak atıyor 
                    if (index == 0)
                    {
                        rover.Direction = directions[3];
                    }
                    else
                    {
                        rover.Direction = directions[index - 1];
                    }
                }

                else if (i == 'r')
                {
                    int index = directions.IndexOf(rover.Direction); //aynı mantık
                    if (index == 3)
                    {
                        rover.Direction = directions[0];
                    }
                    else
                    {
                        rover.Direction = directions[index + 1];
                    }
                }

                else if (i == 'm')
                {
                    if (rover.Direction == 'N')
                    {
                        rover.Y += 1;
                        if (rover.Y > _intPlateuY)
                        {
                            rover.Y = _intPlateuY; //düzlem dışına çıkmaya çalışılırsa rover bulunduğu yerde duruyor
                            Console.WriteLine("The rover cannot go outside of the coordinate system, it has been stopped at the border");
                            break;
                        }

                        foreach (RoverInfos testRover in rovers)
                        {
                            if (testRover.X == rover.X && testRover.Y == rover.Y && testRover != rover)
                            {
                                Console.WriteLine("There is another rover at the road you specified, the process is cancelled...");
                                rover.X = tempX;
                                rover.Y = tempY;
                                rover.Direction = tempDirection;
                                controlTestRover = 1;  //rover ile karşılaştıysak controlTestRover = 1 oluyor
                                break;
                            }
                        }
                    }

                    else if (rover.Direction == 'E')
                    {
                        rover.X += 1;
                        if (rover.X > _intPlateuX)
                        {
                            rover.X = _intPlateuX;
                            Console.WriteLine("The rover cannot go outside of the coordinate system, it has been stopped at the border");
                            break;
                        }

                        foreach (RoverInfos testRover in rovers)
                        {
                            if (testRover.X == rover.X && testRover.Y == rover.Y && testRover != rover)
                            {
                                Console.WriteLine("There is another rover at the road you specified, the process is cancelled...");
                                rover.X = tempX;
                                rover.Y = tempY;
                                rover.Direction = tempDirection;
                                controlTestRover = 1;
                                break;
                            }
                        }
                    }
                    else if (rover.Direction == 'S')
                    {
                        rover.Y -= 1;
                        if (rover.Y < 0)
                        {
                            rover.Y = 0;
                            Console.WriteLine("The rover cannot go outside of the coordinate system, it has been stopped at the border");
                            break;
                        }

                        foreach (RoverInfos testRover in rovers)
                        {
                            if (testRover.X == rover.X && testRover.Y == rover.Y && testRover != rover)
                            {
                                Console.WriteLine("There is another rover at the road you specified, the process is cancelled...");
                                rover.X = tempX;
                                rover.Y = tempY;
                                rover.Direction = tempDirection;
                                controlTestRover = 1;
                                break;
                            }
                        }
                    }
                    else if (rover.Direction == 'W')
                    {
                        rover.X -= 1;
                        if (rover.X < 0)
                        {
                            rover.X = 0;
                            Console.WriteLine("The rover cannot go outside of the coordinate system, it has been stopped at the border");
                            break;
                        }

                        foreach (RoverInfos testRover in rovers)
                        {
                            if (testRover.X == rover.X && testRover.Y == rover.Y && testRover != rover)
                            {
                                Console.WriteLine("There is another rover at the road you specified, the process is cancelled...");
                                rover.X = tempX;
                                rover.Y = tempY;
                                rover.Direction = tempDirection;
                                controlTestRover = 1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        rover.X = tempX;
                        rover.Y = tempY;
                        rover.Direction = tempDirection;
                        Console.WriteLine("A mistaken input has detected, the process is cancelled...");
                        break;
                    }

                    if (controlTestRover == 1)
                    {
                        break; //controlTestRover değişkeninin değeri değiştirildiyse döngü duracak
                    }
                }
                
            }
        }
        else
        {
            Console.WriteLine("The input cannot be blank, returning to main menu...");
        }
    }
}
