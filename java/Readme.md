# Java Notes Cheatsheet

## Arrays
- `Animal[] zoo = new Animal[4];`
  - Create an array of `Animal` objects with size 4
- `zoo[0] = new Tiger();`
  - Assign objects to array elements
- `String[] cars = {"Volvo", "BMW", "Ford", "Mazda"};`
  - Create a String array with initial values
- `System.out.println(cars.length); // Outputs 4`
  - Get the length of an array
- `int[][] myNumbers = {{1, 2, 3, 4}, {4, 5, 6}};`
  - Create a 2D array
  - `int x = myNumbers[1][2]; // Outputs 6`
    - Access elements in a 2D array
- `Arrays.sort(cars);`
  - Sort an array
  - `System.out.println(Arrays.toString(cars)); // [BMW, Ford, Mazda, Volvo]`
    - Convert array to string for printing

## Sorting Objects
- **Natural Sorting** (implemented in the class)
  - `public class Person implements Comparable<Person> { ... }`
  - `@Override public int compareTo(Person o) { return Double.compare(this.weight, o2.weight); }`
  - `Arrays.sort(listOfPeople);` or `Collections.sort(listOfPeople);`
- **Alternative Sorting** (custom Comparator)
  - `public class SortOnName implements Comparator<Person> { ... }`
  - `@Override public int compare(Person o1, Person o2) { return o1.getName().compareTo(o2.getName()); }`
  - `Arrays.sort(listOfPeople, new SortOnName());`

## ArrayList
- `ArrayList<String> cars = new ArrayList<String>();`
  - Create an ArrayList
- `cars.add("Volvo"); cars.add("BMW"); ...`
  - Add elements
- `cars.get(0); cars.set(0, "Opel"); cars.remove(0); cars.clear(); cars.size();`
  - Access, modify, remove, clear, and get size
- `Collections.sort(cars);`
  - Sort an ArrayList
- `for (String i : cars) { System.out.println(i); }`
  - Iterate over an ArrayList

## Math
- `Math.random(); // Random number between 0.0 (excl) and 1.0 (excl)`
- `int randomNum = (int)(Math.random() * 101); // 0 to 100`
- `Math.sqrt(64); // Returns square root`
- `a >= b, a != b, a == b // Greater than or equal to, Not equal to, Equal to`
- `nr++; nr += 5; // Increment by 1, Increment by 5`

## Randomize List
- `ArrayList<String> mylist = new ArrayList<String>(); // ....`
- `Collections.shuffle(myList); // [Two, One, Three]`

## Break/Continue
- `for (int i = 0; i < 10; i++) { if (i == 4) { continue; } if (i == 6) { break; } }`
  - `continue` skips the current iteration
  - `break` jumps out of the loop

## If-Else
- `if (time < 10) { ... } else if (time < 20) { ... } else { ... }`
- `variable = (condition) ? expressionTrue : expressionFalse;`

## Switch-Case
- `switch (day) { case 1: ...; case 2: ...; ... }`

## Loops
- `while (i < 5) { System.out.println(i); i++; }`
- `do { i++; System.out.println(i); } while (i < 5);`
- `for (int i = 0; i < 5; i++) { System.out.println(i); }`
- `for (type variableName : arrayName) { // code }`
- `Iterator<String> iter = naamArrayList.iterator(); while (iter.hasNext()) { System.out.println(iter.next().toString()); }`

## String Methods
- `name1.length(); name2.concat(name1); name1.equals("cheatsheet"); name1.equalsIgnoreCase(name2);`
- `name1.indexOf('e'); name1.charAt(0); name1.toCharArray();`
- `name1.replace(int 1, int 2, String);`

## Exceptions
- `try { // Block of code to try } catch (Exception e) { // Block of code to handle errors }`
- `finally { try { // Block of code to try } catch (Ecxeption o) { // Block of code to handle errors }}`
- Custom Exception: `public class MijnException extends Exception{ public MijnException (){ super("DezeTekstAlsErrorBvb"); } }`
- Throwing Exception: `public boolean check (Persoon x) throws MijnException{ if (x.getAchternaam().equals(y.getAchternaam())){ return true; } else { throw new MijnException(); } }`

## Upcasting / Downcasting
- Widening Casting (automatically): `int myInt = 9; double myDouble = myInt;`
- Narrowing Casting (manually): `double myDouble = 9.78; int myInt = (int) myDouble;`
- Upcasting: `ParentClass name1 = new ChildClass(Parameters);`
- Downcasting: `ChildClass name2 = (ChildClass) name1;`

## Access Modifiers
- `public`: Visible for all
- `default`: Visible only in package
- `protected`: Visible in class and subclasses
- `private`: Visible only in class

## Keywords
- `ABSTRACT`: Blocks creating object of `ParentClass`, requires use of `ChildClasses`
- `FINAL`: Can't be changed for attribute/method/class
- `INTERFACE`: No attributes, no constructors, only methods without body, uses `implements` (not `extends`)
- `STATIC`: Fixed value for class and all subclasses
- `SUPER`: Calls default/matching constructor (must be first line)

## Collections
- `Stack`: LIFO (Last-In-First-Out) data structure
- `Queue`: FIFO (First-In-First-Out) data structure
- `List`: `ArrayList`, `LinkedList`
- `Set`: `HashSet`, `TreeSet`
- `Map`: `HashMap`, `TreeMap`