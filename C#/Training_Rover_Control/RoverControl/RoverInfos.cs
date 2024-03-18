namespace RoverControl;

public class RoverInfos
{
    //Rover nesnelerinin bilgilerinin tutulacağı bir sınıf oluşturdum.
    //Name değişkeninin string? olma sebebi userInput alırken null atanabilir
    //X, Y ve Direction'da ise string alıp çevirdiğim için null kontrolünü program.cs içinde yaptım
    //Dolayısıyla X, Y ve Direction'un null olma ihtimali yok ama Name'in var
    //DisplayRoverInfos için ekstra tek satırlık bir sınıf açmak yerine RoverInfos sınıfında kullandım
    public string? Name { get; set; }
    public int X { get; set; }
    public int Y { get; set; }
    public char Direction { get; set; }

    public void DisplayRoverInfos()
    {
        Console.WriteLine($"Rover Name: {Name}, Rover Coordinates and Direction (X,Y,D): ({X},{Y},{Direction})");
    }
}