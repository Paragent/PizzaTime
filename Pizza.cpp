#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza
{
protected:
    string name;
    string description;
    int size;
    int salt;
    float cost;
    int cheese;

public:
    Pizza(string NAME, string DESCRIPTION, int SIZE, float COST)
    {
        name = NAME;
        description = DESCRIPTION;
        size = SIZE;
        cost = COST;
    }

    virtual float Price()
    {
        float price = cost;

        if (size == 25 or size == 30 or size == 35 or size == 40)
        {
            price *= size / 10;
        }
        else
        {
            cout << "Wrong size." << endl;
            return 1;
        }

        price += salt * 1.3;
        price += cheese * 1.5;

        return price;
    }

    virtual void PrintDescription()
    {
        cout << "- Pizza - " << name << endl;
        cout << "- Description - " << description << endl;
        cout << "- Size - " << size << endl;
        cout << "- Salt - " << salt << endl;
        cout << "- Cheese - " << cheese << endl;
        cout << "- Cost - " << Price() << " rub" << endl;
    }

    void Setsalt(int s) { salt = s; }
    void Setcheese(int c) { cheese = c; }

    virtual ~Pizza() {}
};

class PizzaPepperoni : public Pizza
{
public:
    PizzaPepperoni(int ss) : Pizza("Pizza Pepperoni", "Tomato sauce, pepperoni, cheese", ss, 500) {}
};

class HawaiianPizza : public Pizza
{
public:
    HawaiianPizza(int ss) : Pizza("Hawaiian pizza", "Pineapple, ham, dough, cheese.", ss, 300) {}
};

class PizzaMargarita : public Pizza
{
public:
    PizzaMargarita(int ss) : Pizza("Pizza Margarita", "Simple and classic - tomatoes, mozzarella, basil", ss, 450) {}
};

class Pizza4cheese : public Pizza
{
public:
    Pizza4cheese(int ss) : Pizza("Four-cheese Pizza", "Mozzarella, gorgonzola, parmesan, feta", ss, 600) {}
};

class PizzaVegetarian : public Pizza
{
public:
    PizzaVegetarian(int ss) : Pizza("Vegetarian Pizza", "Tomatoes, peppers, mushrooms, olives, cheese", ss, 350) {}
};

class OrderPizza
{
private:
    vector<Pizza *> pizzas;

public:
    ~OrderPizza()
    {
        for (Pizza *p : pizzas)
        {
            delete p;
        }
    }

    void AddPizza(Pizza *pizza)
    {
        pizzas.push_back(pizza);
    }

    void PrintTotalPrice()
    {
        double totalPrice = 0;
        for (Pizza *pizza : pizzas)
        {
            totalPrice += pizza->Price();
        }

        cout << "Total Price: " << totalPrice << " rub" << endl;
    }
};

int main()
{
    OrderPizza order;

    char answer = 'y';
    int nm, sz, salt, cheese;

    while (answer == 'y')
    {
        cout << "Choose pizza: (1) Pepperoni, (2) Hawaiian, (3) Margarita, (4) Four-cheese, (5) Vegetarian" << endl;
        cin >> nm;
        cout << "Choose size: 25, 30, 35, 40 " << endl;
        cin >> sz;

        Pizza *SelectedPizza = nullptr;

        switch (nm)
        {
        case 1:
            SelectedPizza = new PizzaPepperoni(sz);
            break;
        case 2:
            SelectedPizza = new HawaiianPizza(sz);
            break;
        case 3:
            SelectedPizza = new PizzaMargarita(sz);
            break;
        case 4:
            SelectedPizza = new Pizza4cheese(sz);
            break;
        case 5:
            SelectedPizza = new PizzaVegetarian(sz);
            break;
        default:
            cout << "Wrong choice" << endl;
            continue;
        }

        cout << "Enter salt quantity: ";
        cin >> salt;
        cout << "Enter cheese quantity: ";
        cin >> cheese;

        SelectedPizza->Setsalt(salt);
        SelectedPizza->Setcheese(cheese);

        SelectedPizza->PrintDescription();

        float pr = SelectedPizza->Price();
        order.AddPizza(SelectedPizza);

        cout << "Would you like to add another pizza? (y - yes, n - no)" << endl;
        cin >> answer;
    }

    order.PrintTotalPrice();

    return 0;
}
