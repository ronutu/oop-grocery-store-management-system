# OOP Grocery store management system

This project was created during my Object-Oriented Programming (OOP) course to demonstrate the application of core OOP principles. The purpose of the project is to show how these concepts can be used to model real-world problems. In this case, we are developing a grocery store management system.

### Description
The project models a chain of stores with different types: general stores, vegan stores, and online vegan stores. Users can add stores, display information, calculate profits, and compare stores through a simple command-line interface.

### Concepts Used:

1. **Encapsulation**:
   - Classes like `Store`, `VeganStore`, and `OnlineVeganStore` encapsulate both data (e.g., city, number of clients) and methods that operate on this data (e.g., calculating profit, reading, and writing store details).
   - Access to class members is controlled through public getter/setter methods and constructors, keeping some members (e.g., `id`, `counter`) private or protected to maintain control over how they're used.

2. **Inheritance**:
   - `VeganStore` inherits from `Store`, and `OnlineVeganStore` further inherits from `VeganStore`, illustrating class hierarchies and reusability of code. Each class extends or overrides behavior specific to that type of store.
   - This allows for code reuse while introducing new behaviors, such as the `numberOfVeganProducts` in `VeganStore` and `deliveryRadius` in `OnlineVeganStore`.

3. **Polymorphism**:
   - The project demonstrates polymorphism through virtual methods like `read` and `write`, which are overridden in derived classes to provide specific functionality.
   - The use of templates (e.g., `calculateStoreProfit` and `compareStoreProfit`) further showcases polymorphism by enabling generalized behavior for different store types.

4. **Abstraction**:
   - The `IOinterface` abstract class forces derived classes like `Store` to implement the `read` and `write` methods, ensuring that all types of stores have standardized input/output mechanisms.
   - By hiding implementation details, abstraction allows users to interact with the stores in a simplified way (e.g., through the menu system).

5. **Templates**:
   - The project uses function templates for calculating and comparing store profits, making these functions flexible for different store types. This avoids redundant code while maintaining type safety.

6. **Singleton Pattern**:
   - The `displayMenu` class is implemented as a singleton, ensuring only one instance of the menu system exists at a time, which is a common design pattern for managing global resources like application menus.

7. **Standard Library Usage**:
   - The project effectively uses C++ Standard Library containers like `vector`, `list`, `set`, and `map` to store and manage stores, founder names, and other attributes efficiently. These containers help to simplify data management, especially when dealing with a dynamic number of stores.

In summary, this project provided hands-on experience with fundamental OOP principles and C++ features while modeling a practical, real-world scenario of managing grocery store data.
